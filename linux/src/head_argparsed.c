#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#define _GNU_SOURCE
#define DEFAULT_N_LINES 10

static struct option longopts[] = {
  {"lines", required_argument, NULL, 'n'},
  {"help", no_argument, NULL, 'h'},
  {0, 0, 0, 0}
};

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
  int opt;
  long n_lines;

  if (argc < 2) {
    fprintf(stderr, "Usage: %s [-n N_LINES] [FILE FILE...]\n", argv[0]);
    exit(1);
  }

  while((opt = getopt_long(argc, argv, "n:", longopts, NULL)) != -1) {
    switch (opt) {
    case 'n':
      n_lines = atol(optarg);
      break;
    case 'h':
      fprintf(stderr, "Usage: %s [-n N_LINES] [FILE FILE...]\n", argv[0]);
      exit(0);
    case '?':
      fprintf(stderr, "Usage: %s [-n N_LINES] [FILE FILE...]\n", argv[0]);
      exit(1);
    }
  }

  if (optind == argc) exec_head(stdin, n_lines);
  else {
    for (int i = optind; i < argc; i++) {
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
