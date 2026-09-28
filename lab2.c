#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char *line = NULL;
  size_t size = 0;
  int length;
  int pid;

  while (1) {
    printf("Enter programs to run.\n");
    printf("> ");

    length = getline(&line, &size, stdin);

    if (line[length - 1] == '\n') {
      line[length - 1] == '\0';
    }

    pid = fork();

    // check if pid is child
    if (pid == 0) {
      execlp(line, line, NULL);
      printf("Exec failure\n");
      exit(1);
    } else {
      // parent
      waitpid(pid, NULL, 0);
    }
  }

  free(line);
  return 0;
}
