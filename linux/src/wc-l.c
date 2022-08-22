#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER_SIZE 2048

static void exec_wc_l(const char *filepath);
static void kill(const char *s);

int main(int argc, char *argv[]) {
  int i;

  // Terminate with error code 1 if failed to get one or more
  // filenames
  if (argc < 2) {
    fprintf(stderr, "%s: filename not given\n", argv[0]);
    exit(1);
  }

  for (i = 1; i < argc; i++) exec_wc_l(argv[i]);
  exit(0);
}

static void exec_wc_l(const char *filepath) {
  int fd, n;
  unsigned char buf[BUFFER_SIZE];
  unsigned long count = 0;

  fd = open(filepath, O_RDONLY);
  // Terminate if failed to open file properly
  if (fd < 0) kill(filepath);
  for (;;) {
    n = read(fd, buf, sizeof buf);
    // Terminate if failed to read from file properly
    if (n < 0) kill(filepath);
    // Terminate if reached end-of-file
    if (n == 0) break;
    unsigned long i;
    for (i = 0; i < BUFFER_SIZE; i++) {
      if (buf[i] == '\n') count++;
    }
  }
  printf("%lu\n", count);
}

static void kill(const char *s) {
  perror(s);
  exit(1);
}
