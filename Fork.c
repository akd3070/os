#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  pid_t child_pid;
  child_pid = fork();

  if (child_pid == 0) {
    printf("Child process\n", getpid());
  }

  else if (child_pid > 0) {
    printf("Parent process\n", getpid(), pid);
  }

  else {
    printf("Fork failed");
  }

  return 0;
}
