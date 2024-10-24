#include <stdbool.h>
#include <stdio.h>

#define MAX_PROCESSES 100

struct Process {
  int pid;
  int burst_time;
  int arrival_time;
  int wait_time;
  int turn_around_time;
  bool is_system;  // is it a system process (gets higher priority)
};

void fcfs(struct Process queue[], int n) {
  int total_wait_time = 0, total_turn_around_time = 0;

  queue[0].wait_time = 0;

  for (int i = 1; i < n; i++) {
    queue[i].wait_time = queue[i - 1].wait_time + queue[i - 1].burst_time;
    total_wait_time += queue[i].wait_time;
  }

  for (int i = 0; i < n; i++) {
    queue[i].turn_around_time = queue[i].wait_time + queue[i].burst_time;
    total_turn_around_time += queue[i].turn_around_time;
  }

  printf("\nPID\tBurst Time\tArrival Time\tWait Time\tTurnaround Time\n");
  for (int i = 0; i < n; i++) {
    printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", queue[i].pid, queue[i].burst_time,
           queue[i].arrival_time, queue[i].wait_time,
           queue[i].turn_around_time);
  }

  printf("\nAverage waiting time: %.2f", (float)total_wait_time / n);
  printf("\nAverage turnaround time: %.2f\n",
         (float)total_turn_around_time / n);
}

int main() {
  int n;
  struct Process system_queue[MAX_PROCESSES], user_queue[MAX_PROCESSES];
  int sys_count = 0, usr_count = 0;

  printf("Enter number of processes: ");
  scanf("%d", &n);

  for (int i = 0; i < n; i++) {
    struct Process p;
    p.pid = i + 1;
    printf("\nProcess %d:\n", p.pid);
    printf("Enter burst time: ");
    scanf("%d", &p.burst_time);
    printf("Enter arrival time: ");
    scanf("%d", &p.arrival_time);
    printf("Is this a system process? (1 for yes, 0 for no): ");
    scanf("%d", (int *)&p.is_system);

    // Add to the respective queue
    if (p.is_system) {
      system_queue[sys_count++] = p;
    } else {
      user_queue[usr_count++] = p;
    }
  }

  printf("\nSystem Processes (High Priority) Scheduling:\n");
  if (sys_count > 0) {
    fcfs(system_queue, sys_count);
  } else {
    printf("No system processes.\n");
  }

  printf("\nUser Processes (Low Priority) Scheduling:\n");
  if (usr_count > 0) {
    fcfs(user_queue, usr_count);
  } else {
    printf("No user processes.\n");
  }

  return 0;
}
