#include <limits.h>
#include <stdio.h>

struct Process {
  int pid;
  int burst_time;
  int remaining_time;
  int arrival_time;
  int completion_time;
  int wait_time;
  int turn_around_time;
};

//@cal_times : function to calculate waiting time and turnaround time
//@cal_avg_times: function to calculate average waiting and turnaround times
//@print_process: to print the details table of the processes

void cal_times(struct Process proc[], int n) {
  int completed = 0, time = 0, minRemaining = INT_MAX;
  int shortest = 0, finishTime;
  int is_process = 0;

  while (completed != n) {
    // Finding process with the shortest remaining time at current time
    for (int i = 0; i < n; i++) {
      if (proc[i].arrival_time <= time &&
          proc[i].remaining_time < minRemaining && proc[i].remaining_time > 0) {
        minRemaining = proc[i].remaining_time;
        shortest = i;
        is_process = 1;
      }
    }
    // if no process is available at the current time increment time
    if (is_process == 0) {
      time++;
      continue;
    }

    // decrease remaining time for the process with the shortest remaining time
    proc[shortest].remaining_time--;

    // update minimum remaining time for the next iteration
    minRemaining = proc[shortest].remaining_time;
    if (minRemaining == 0) {
      minRemaining = INT_MAX;
    }

    // if a process is completely executed
    if (proc[shortest].remaining_time == 0) {
      completed++;
      is_process = 0;

      // calculate finish time and turnaround time for the completed process
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

    // increment time
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
      "\nPID\tArrival Time\tBurst Time\tCompletion Time\tWaiting "
      "Time\tTurnaround Time\n");

  for (int i = 0; i < n; i++) {
    printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid,
           proc[i].arrival_time, proc[i].burst_time, proc[i].completion_time,
           proc[i].wait_time, proc[i].turn_around_time);
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
    proc[i].remaining_time = proc[i].burst_time;
  }

  cal_times(proc, n);
  print_process(proc, n);
  cal_avg_times(proc, n);
  return 0;
}
