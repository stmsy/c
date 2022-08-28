#include <stdio.h>
#include <stdlib.h>

static void exec_wc_l(FILE *fp);
static void kill(const char *s);

int main(int argc, char *argv[]) {
  int i;
  FILE *fp;

  // Output chars read from standard input if no valid filename is given
  if (argc == 1) {
    exec_wc_l(stdin);
  } else {
    for (i = 1; i < argc; i++) {
      fp = fopen(argv[i], "r");
      if (!fp) kill(argv[i]);
      exec_wc_l(fp);
      fclose(fp);
    }
  }
  exit(0);
}

static void exec_wc_l(FILE *fp) {
  unsigned long count;
  int c;
  int prev = '\n';

  count = 0;
  while ((c = getc(fp)) != EOF) {
    if (c == '\n') count++;
    prev = c;
  }
  // Check '\n' at end-of-file
  if (prev != '\n') count++;

  printf("%lu\n", count);
}

static void kill(const char *s) {
  perror(s);
  exit(1);
}
