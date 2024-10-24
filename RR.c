#include <stdio.h>

struct Process {
  int pid;
  int bursttime;
  int remaining_time;
  int wait_time;
  int turn_around_time;
};

void calculateTimes(struct Process proc[], int n, int quantum) {
  int time = 0;
  int allDone = 0;

  while (!allDone) {
    allDone = 1;

    for (int i = 0; i < n; i++) {
      if (proc[i].remaining_time > 0) {
        allDone = 0;
        if (proc[i].remaining_time > quantum) {
          time += quantum;
          proc[i].remaining_time -= quantum;
        } else {
          time += proc[i].remaining_time;
          proc[i].wait_time = time - proc[i].bursttime;
          proc[i].remaining_time = 0;
        }
      }
    }
  }

  for (int i = 0; i < n; i++) {
    proc[i].turn_around_time = proc[i].bursttime + proc[i].wait_time;
  }
}

void printTimes(struct Process proc[], int n) {
  printf("PID\tBurst Time\tWait Time\tTurnaround Time\n");

  for (int i = 0; i < n; i++) {
    printf("%d\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].bursttime,
           proc[i].wait_time, proc[i].turn_around_time);
  }
}

int main() {
  int n, quantum;

  printf("Enter number of processes: ");
  scanf("%d", &n);

  printf("Enter time quantum: ");
  scanf("%d", &quantum);

  struct Process proc[n];

  for (int i = 0; i < n; i++) {
    printf("Enter burst time for process %d: ", i + 1);
    scanf("%d", &proc[i].bursttime);
    proc[i].pid = i + 1;
    proc[i].remaining_time = proc[i].bursttime;
    proc[i].wait_time = 0;
    proc[i].turn_around_time = 0;
  }

  calculateTimes(proc, n, quantum);

  printTimes(proc, n);

  return 0;
}
