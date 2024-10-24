#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t child_pid;
    child_pid = fork();  // Creating a child process

    if (child_pid == 0) {
        // This is the child process
        printf("Child process (PID: %d)\n", getpid());
    } 
    else if (child_pid > 0) {
        // This is the parent process
        printf("Parent process (PID: %d), Child PID: %d\n", getpid(), child_pid);
    } 
    else {
        // Fork failed
        printf("Fork failed\n");
    }

    return 0;
}
