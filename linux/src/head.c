#include <stdio.h>
#include <stdlib.h>

static void exec_head(FILE *fp, long n_lines) {
  int c;

  if (n_lines <= 0) return;
  while ((c = getc(fp)) != EOF) {
    if (putchar(c) < 0) exit(1);
    if (c == '\n') {
      n_lines--;
      if (n_lines == 0) return;
    }
  }
}

int main(int argc, char *argv[]) {
  long n_lines;

  if (argc < 2) {
    fprintf(stderr, "Usage: %s n [file file...]\n", argv[0]);
    exit(1);
  }

  n_lines = atol(argv[1]);
  if (argc == 2) exec_head(stdin, n_lines);
  else {
    for (int i = 2; i < argc; i++) {
      FILE *fp;

      fp = fopen(argv[i], "r");
      if (!fp) {
        perror(argv[1]);
        exit(1);
      }
      exec_head(fp, n_lines);
      fclose(fp);
    }
  }

  exit(0);
}
