#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include "wrr.h"

int timeQuantum;

struct Process processes[101] = {{1, 0, 5, 5, 0, 0, 0, false, false},
                                 {2, 1, 4, 4, 0, 0, 0, false, false},
                                 {3, 2, 2, 2, 0, 0, 0, false, false},
                                 {4, 3, 1, 1, 0, 0, 0, false, false}};
                                
struct Process procese[101] = {{1, 0, 6, 6, 0, 0, 0, false, false},
                               {2, 1, 5, 5, 0, 0, 0, false, false},
                               {3, 2, 3, 3, 0, 0, 0, false, false},
                               {4, 3, 2, 2, 0, 0, 0, false, false}};

struct User utilizator[2] = {{4, processes, 4},
                             {2, procese, 4}};

struct Process Coada[101];


int genereaza_numar_nou() {
  srand(time(NULL) ^ clock()); // Set the seed for the random number generator
  return rand();
}

int ProcessCmp(const void *a, const void *b) {
  const struct Process *processA = (struct Process *)a;
  const struct Process *processB = (struct Process *)b;

  if (processA->arrivalTime < processB->arrivalTime) {
    return -1;
  } else if (processA->arrivalTime > processB->arrivalTime) {
    return 1;
  } else {
    return 0;
  }
}

void CheckForNewArrivals(struct Process processes[], const int n,
                         const int timeQuantum, int queue[],
                         const int *currentTime, int *rqueue) {
  for (int i = 0; i < n; i++) {
    struct Process process = processes[i];
    if (process.arrivalTime <= *currentTime && !process.inQueue &&
        !process.isComplete) {
      processes[i].inQueue = true;
      (*rqueue)++;
      queue[*rqueue] = i;
    }
  }
}

void UpdateQueue(struct Process processes[], const int n, const int timeQuantum,
                 int queue[], int *fqueue, int *rqueue, int *currentTime,
                 int *numbExecuted) {
  int index = queue[*fqueue];
  (*fqueue)++;

  if (processes[index].burstTimeRemaining <= timeQuantum) {
    processes[index].isComplete = true;
    (*currentTime) += processes[index].burstTimeRemaining;
    processes[index].completionTime = *currentTime;
    processes[index].waitingTime = processes[index].completionTime -
                                   processes[index].arrivalTime -
                                   processes[index].burstTime;
    processes[index].turnaroundTime =
        processes[index].waitingTime + processes[index].burstTime;
    processes[index].burstTimeRemaining = 0;

    if (processes[index].waitingTime < 0)
      processes[index].waitingTime = 0;

    (*numbExecuted)++;

    if (*numbExecuted < n) {
      CheckForNewArrivals(processes, n, timeQuantum, queue, currentTime,
                          rqueue);
    }
  } else {
    processes[index].burstTimeRemaining -= timeQuantum;
    (*currentTime) += timeQuantum;

    if (*numbExecuted != n) {
      CheckForNewArrivals(processes, n, timeQuantum, queue, currentTime,
                          rqueue);
    }

    (*rqueue)++;
    queue[*rqueue] = index;
  }
}

void RoundRobin(struct Process processes[], const int n,
                const int timeQuantum) {
  if (n <= 0) {
    printf("No processes!");
    return;
  }

  int queue[100001];
  int fqueue = 0, rqueue = -1;
  int currentTime = 0, numbExecuted = 0;

  for (int i = 0; i < n; i++) {
    struct Process process = processes[i];
    if (process.arrivalTime == 0 && !process.inQueue && !process.isComplete) {
      processes[i].inQueue = true;
      rqueue++;
      queue[rqueue] = i;
    }
  }

  while (fqueue <= rqueue) {
    UpdateQueue(processes, n, timeQuantum, queue, &fqueue, &rqueue,
                &currentTime, &numbExecuted);
  }
}

void Output(struct Process processes[], const int n) {
  double avgWaitingTime = 0;
  double avgTurntaroundTime = 0;
  for (int i = 0; i < n; i++) {
    printf("Process %d: Waiting Time: %d Turnaround Time: %d\n",
           processes[i].pid, processes[i].waitingTime,
           processes[i].turnaroundTime);
    avgWaitingTime += processes[i].waitingTime;
    avgTurntaroundTime += processes[i].turnaroundTime;
  }
  printf("Average Waiting Time: %f\n", avgWaitingTime / n);
  printf("Average Turnaround Time: %f\n", avgTurntaroundTime / n);
}

int process_time() { return genereaza_numar_nou() % 120 + 1; }

int sleep_time() { return genereaza_numar_nou() % 30 + 1; }

int main() {
  // Predefined time quantum
  timeQuantum = 2;
  int n = 4;

  /*
  // We must include a process that starts from the start
  processes[0].pid = 1;
  processes[0].arrivalTime = 0;
  processes[0].burstTime = process_time();
  processes[0].burstTimeRemaining = processes[0].burstTime;

  for (int i = 1; i < n; i++) {
    processes[i].pid = i + 1;
    processes[i].arrivalTime = sleep_time();
    processes[i].burstTime = process_time();
    processes[i].burstTimeRemaining = processes[i].burstTime;
  }
  */

  wrr(utilizator, Coada);

  for(int i = 0; i < sizeof(Coada) / sizeof(Coada[0]); i++)
    printf("%d ", Coada[i].pid);

  qsort(processes, n, sizeof(struct Process), ProcessCmp);

  RoundRobin(processes, n, timeQuantum);

  Output(processes, n);

  return 0;
}