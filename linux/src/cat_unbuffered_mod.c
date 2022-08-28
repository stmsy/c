#include <stdio.h>
#include <stdlib.h>

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
  unsigned char buf[BUFFER_SIZE];

  FILE *fp = fopen(filepath, "r");
  // Terminate if failed to open file properly
  if (!fp) kill(filepath);
  for (;;) {
    size_t n_read = fread(buf, 1, sizeof buf, fp);
    // Terminate if failed to read from file properly
    if (ferror(fp)) kill(filepath);

    size_t n_written = fwrite(buf, 1, n_read, stdout);
    // Terminate if failed to write to stdout properly
    if (n_written < n_read) kill(filepath);

    if (n_read < sizeof buf) break;
  }
  if (fclose(fp) != 0) kill(filepath);
}

static void kill(const char *s) {
  perror(s);
  exit(1);
}
