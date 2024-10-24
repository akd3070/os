#include <limits.h>
#include <stdio.h>

#define MAX_PROCESSES 100

struct Process {
  int pid;
  int burst_time;
  int remaining_time;
  int arrival_time;
  int priority;  // (lower number = higher priority)
  int completion_time;
  int wait_time;
  int turn_around_time;
};

void cal_times(struct Process proc[], int n) {
  int completed = 0, time = 0;
  int minPriority = INT_MAX;
  int shortest = 0, finishTime;
  int isProcess = 0;

  while (completed != n) {
    for (int i = 0; i < n; i++) {
      if (proc[i].arrival_time <= time && proc[i].priority < minPriority &&
          proc[i].remaining_time > 0) {
        minPriority = proc[i].priority;
        shortest = i;
        isProcess = 1;
      }
    }

    if (isProcess == 0) {
      time++;
      continue;
    }

    proc[shortest].remaining_time--;

    minPriority =
        proc[shortest].remaining_time > 0 ? proc[shortest].priority : INT_MAX;

    if (proc[shortest].remaining_time == 0) {
      completed++;
      isProcess = 0;

      finishTime = time + 1;
      proc[shortest].completion_time = finishTime;
      proc[shortest].turn_around_time =
          finishTime - proc[shortest].arrival_time;
      proc[shortest].wait_time =
          proc[shortest].turn_around_time - proc[shortest].burst_time;

      if (proc[shortest].wait_time < 0) {
        proc[shortest].wait_time = 0;  // In case wait time becomes negative
      }
    }

    time++;
  }
}

void cal_avg_times(struct Process proc[], int n) {
  int totalwait_time = 0, totalturn_around_time = 0;

  for (int i = 0; i < n; i++) {
    totalwait_time += proc[i].wait_time;
    totalturn_around_time += proc[i].turn_around_time;
  }

  printf("\nAverage waiting time: %.2f", (float)totalwait_time / n);
  printf("\nAverage turnaround time: %.2f", (float)totalturn_around_time / n);
}

void print_process(struct Process proc[], int n) {
  printf(
      "\nPID\tArrival Time\tBurst Time\tPriority\tCompletion Time\tWaiting "
      "Time\tTurnaround Time\n");

  for (int i = 0; i < n; i++) {
    printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid,
           proc[i].arrival_time, proc[i].burst_time, proc[i].priority,
           proc[i].completion_time, proc[i].wait_time,
           proc[i].turn_around_time);
  }
}

int main() {
  int n;
  printf("Enter number of processes: ");
  scanf("%d", &n);

  struct Process proc[n];

  for (int i = 0; i < n; i++) {
    proc[i].pid = i + 1;
    printf("Enter arrival time for process %d: ", proc[i].pid);
    scanf("%d", &proc[i].arrival_time);
    printf("Enter burst time for process %d: ", proc[i].pid);
    scanf("%d", &proc[i].burst_time);
    printf("Enter priority for process %d: ", proc[i].pid);
    scanf("%d", &proc[i].priority);
    proc[i].remaining_time = proc[i].burst_time;
  }

  cal_times(proc, n);

  print_process(proc, n);

  cal_avg_times(proc, n);

  return 0;
}
