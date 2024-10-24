#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  pid_t pid;

  // Create a child process
  pid = fork();

  if (pid < 0) {
    // Error occurred
    printf("Fork failed!\n");
    return 1;

  } else if (pid == 0) {
    // Child process
    printf("Child Process:\n");
    printf("Child PID: %d\n", getpid());
    printf("Parent PID (of child): %d\n", getppid());

  } else {
    // Parent process
    printf("Parent Process:\n");
    printf("Parent PID: %d\n", getpid());
    printf("Child PID: %d\n", pid);
  }

  return 0;
}
