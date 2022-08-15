#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Types of tokens to be defined
typedef enum {
  TK_SYMBOL,  // token for symbols
  TK_NUMBER,     // token for integers
  TK_EOF      // token for end-of-file
} TokenType;

// Struct for input tokens
typedef struct Token Token;
struct Token {
  TokenType type;  // type of token
  Token *next;     // pointer to next input token
  int val;       // value if token type is TK_NUM
  char *str;       // token
};

// Pointer to token currently processed
Token *token;

// Report errors
void error(char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  fprintf(stderr, "\n");
  exit(1);
}

// Check whether or not token is an operator
bool consume_symbol(char op) {
  if (token->type != TK_SYMBOL || token->str[0] != op)
    return false;
  token = token->next;
  return true;
}

// Get an integer from token or raise an error
int expect_number() {
  if (token->type != TK_NUMBER)
    error("Not a number");
  int val = token->val;
  token = token->next;
  return val;
}

// Check whether or not reached at the end of file
bool at_eof() {
  return token->type == TK_EOF;
}

// Create next token and link to cursor
Token *new_token(TokenType type, Token *cur, char *str) {
  Token *another_token = calloc(1, sizeof(Token));
  another_token->type = type;
  another_token->str = str;
  cur->next = another_token;
  return another_token;
}

// Toekenize string into linked list and return head
Token *tokenize(char *p) {
  // Initialize head and point to cursor
  Token head;
  head.next = NULL;
  Token *cur = &head;

  while (*p) {
    // Skip to next token when space character encountered
    if (isspace(*p)) {
      p++;
      continue;
    }

    // Skip to next token when symbols encountered
    if (*p == '+' || *p == '-') {
      cur = new_token(TK_SYMBOL, cur, p++);
      continue;
    }

    // Get maximal length of digits and move to next pointer
    if (isdigit(*p)) {
      cur = new_token(TK_NUMBER, cur, p);
      cur->val = strtol(p, &p, 10);
      continue;
    }

    error("Failed to tokenize");
  }

  new_token(TK_EOF, cur, p);
  return head.next;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Wrong number of arguments input\n");
    return 1;
  }

  // Tokenize the input string
  token = tokenize(argv[1]);

  // Output the first half of assembly
  printf(".intel_syntax noprefix\n");
  printf(".globl main\n");
  printf("main:\n");

  // Expect the first character to be number
  printf("    mov rax, %d\n", expect_number());

  // Read numbers until at the end of file
  while (!at_eof()) {
    if (consume_symbol('+')) {
      printf("    add rax, %d\n", expect_number());
      continue;
    }

    if (consume_symbol('-')) {
      printf("    sub rax, %d\n", expect_number());
      continue;
    }
  }

  printf("    ret\n");
  return 0;
}
