#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER_SIZE 2048

static void exec_cat(FILE *fp);
static void kill(const char *s);

int main(int argc, char *argv[]) {
  int i;

  // Output chars read from standard input if no valid filename is given
  if (argc == 1) {
    exec_cat(stdin);
  } else {
    for (i = 1; i < argc; i++) {
      FILE *fp;
      fp = fopen(argv[i], "r");
      if (!fp) kill(argv[i]);
      exec_cat(fp);
      fclose(fp);
    }
    exit(0);
  }
}

static void exec_cat(FILE *fp) {
  int c;

  while ((c = fgetc(fp)) != EOF) {
    if (putchar(c) < 0) exit(1);
  }
}

static void kill(const char *s) {
  perror(s);
  exit(1);
}
