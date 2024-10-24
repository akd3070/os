#include <stdio.h>

struct Process {
  int pid;
  int burstTime;
  int waitTime;
  int turnAroundTime;
};

//@cal_times : Calculate all the time (waiting time, turnaround time)
//@cal_avg_times : Calculate all the average time (waiting time, turnaround
//time)

void cal_times(struct Process proc[], int n) {
  proc[0].waitTime = 0;

  // Calculating waiting time for all processes
  for (int i = 1; i < n; i++) {
    proc[i].waitTime = proc[i - 1].waitTime + proc[i - 1].burstTime;
  }

  // Calculating turnaround time for all processes
  for (int i = 0; i < n; i++) {
    proc[i].turnAroundTime = proc[i].burstTime + proc[i].waitTime;
  }
}

void cal_avg_times(struct Process proc[], int n) {
  int totalWaitTime = 0, totalTurnAroundTime = 0;

  for (int i = 0; i < n; i++) {
    totalWaitTime += proc[i].waitTime;
    totalTurnAroundTime += proc[i].turnAroundTime;
  }

  printf("Average waiting time: %.2f\n", (float)totalWaitTime / n);
  printf("Average turnaround time: %.2f\n", (float)totalTurnAroundTime / n);
}

void print_process(struct Process proc[], int n) {
  printf("PID\tBurst Time\tWait Time\tTurnaround Time\n");

  for (int i = 0; i < n; i++) {
    printf("%d\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].burstTime,
           proc[i].waitTime, proc[i].turnAroundTime);
  }
}

int main() {
  int n;

  printf("Enter number of processes: ");
  scanf("%d", &n);

  struct Process proc[n];

  for (int i = 0; i < n; i++) {
    proc[i].pid = i + 1;
    printf("Enter burst time for process %d: ", proc[i].pid);
    scanf("%d", &proc[i].burstTime);
  }

  cal_times(proc, n);

  print_process(proc, n);

  cal_avg_times(proc, n);

  return 0;
}
