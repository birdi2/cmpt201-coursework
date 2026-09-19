#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

  char *line = NULL;
  char *token;
  char *saveptr;
  size_t size = 0;

  while (1) {
    printf("Please enter some text: ");

    if (getline(&line, &size, stdin) == -1) {

      break;
    }

    printf("Here are the tokens:\n");

    token = strtok_r(line, " ", &saveptr);

    while (token != NULL) {

      printf("%s\n", token);
      token = strtok_r(NULL, " ", &saveptr);
    }
  }

  free(line);
  return 0;
}
