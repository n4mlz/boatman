#include "container.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argv[1] == NULL) {
    fprintf(stderr, "Usage: %s run <image> <command>\n", argv[0]);
    return 1;
  }

  if (strcmp(argv[1], "run") == 0) {
    run_container(argv[2], argc - 3, argv + 3);
  } else {
    fprintf(stderr, "Usage: %s run <image> <command>\n", argv[0]);
    return 1;
  }

  return 0;
}
