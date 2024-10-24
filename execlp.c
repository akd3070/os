#include <stdio.h>
#include <unistd.h>

int main() {
  printf("Executing ls command using execlp:\n");

  // Using execlp() to execute the 'ls' command
  execlp("ls", "ls", "-l", NULL);

  perror("execlp failed");

  return 1;
}
