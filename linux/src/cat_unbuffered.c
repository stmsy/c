#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER_SIZE 2048

static void exec_cat(const char *filepath);
static void kill(const char *s);

int main(int argc, char *argv[]) {
  int i;

  // Terminate with error code 1 if failed to get one or more
  // filenames
  if (argc < 2) {
    fprintf(stderr, "%s: filename not given\n", argv[0]);
    exit(1);
  }

  for (i = 1; i < argc; i++) exec_cat(argv[i]);
  exit(0);
}

static void exec_cat(const char *filepath) {
  int fd, m, n;
  unsigned char buf[BUFFER_SIZE];

  fd = open(filepath, O_RDONLY);
  // Terminate if failed to open file properly
  if (fd < 0) kill(filepath);
  for (;;) {
    m = read(fd, buf, sizeof buf);
    // Terminate if failed to read from file properly
    if (m < 0) kill(filepath);
    // Terminate if reached end-of-file
    if (m == 0) break;
    n = write(STDOUT_FILENO, buf, m);
    // Terminate if failed to write to stdout properly
    if (n < 0) kill(filepath);
  }
  if (close(fd) < 0) kill(filepath);
}

static void kill(const char *s) {
  perror(s);
  exit(1);
}
