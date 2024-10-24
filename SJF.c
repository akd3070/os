#include <stdio.h>

struct Process {
  int pid;
  int burstTime;
  int waitTime;
  int turnAroundTime;
};

//@sort_processes_burst  : Function to sort the processes by burst time (SJF
//scheduling)
//@calculateTimes : Function to calculate waiting and turnaround times
//@cal_avg : Function to calculate average waiting and turnaround times

void sort_processes_burst(struct Process proc[], int n) {
  struct Process temp;
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      if (proc[i].burstTime > proc[j].burstTime) {
        // Swap processes
        temp = proc[i];
        proc[i] = proc[j];
        proc[j] = temp;
      }
    }
  }
}

void cal_times(struct Process proc[], int n) {
  proc[0].waitTime = 0;

  for (int i = 1; i < n; i++) {
    proc[i].waitTime = proc[i - 1].waitTime + proc[i - 1].burstTime;
  }

  for (int i = 0; i < n; i++) {
    proc[i].turnAroundTime = proc[i].burstTime + proc[i].waitTime;
  }
}

void cal_avg(struct Process proc[], int n) {
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

  sort_processes_burst(proc, n);

  cal_times(proc, n);

  print_process(proc, n);

  cal_avg(proc, n);

  return 0;
}
