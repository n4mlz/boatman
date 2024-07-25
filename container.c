#define _GNU_SOURCE
#include <sched.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

#define NEW_ROOT "./container_root_fs"

void write_to_file(const char *which, const char *format, ...) {
  FILE *fu = fopen(which, "w");
  va_list args;
  va_start(args, format);
  if (vfprintf(fu, format, args) < 0) {
    perror("cannot write");
    exit(1);
  }
  fclose(fu);
}

int main() {
  mkdir(NEW_ROOT, 0755);

  system("cp -r ./image/alpine/* " NEW_ROOT "/");

  uid_t uid = getuid();
  gid_t gid = getgid();

  if (0 != unshare(CLONE_NEWUSER)) {
    fprintf(stderr, "%s\n", "USER unshare has failed");
    exit(1);
  }

  write_to_file("/proc/self/uid_map", "0 %d 1", uid);
  write_to_file("/proc/self/setgroups", "deny");
  write_to_file("/proc/self/gid_map", "0 %d 1", gid);

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
