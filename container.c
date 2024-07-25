#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

#define NEW_ROOT "./container_root_fs"

int main() {
  mkdir(NEW_ROOT, 0755);

  system("cp -r ./image/alpine/* " NEW_ROOT "/");

  if (unshare(CLONE_NEWNS) == -1) {
    perror("unshare");
    return 1;
  }

  mount("none", "/", NULL, MS_REC | MS_PRIVATE, NULL);

  mount(NEW_ROOT, NEW_ROOT, NULL, MS_BIND, NULL);
  mount("proc", NEW_ROOT "/proc", "proc", 0, NULL);

  mkdir(NEW_ROOT "/old_root_fs", 0755);

  if (syscall(SYS_pivot_root, NEW_ROOT, NEW_ROOT "/old_root_fs") == -1) {
    perror("pivot_root");
    return 1;
  }

  if (chdir("/") == -1) {
    perror("chdir");
    return 1;
  }

  if (umount2("/old_root_fs", MNT_DETACH) == -1) {
    perror("umount");
    return 1;
  }

  rmdir("/old_root_fs");

  execlp("/bin/sh", "sh", NULL);

  return 0;
}
