#include "../hfiles/process.h"
#include "../hfiles/user.h"
#include <linux/limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

#define MAX_VALUE 99999

int timeQuantum, numbUsers;

struct Process processesA[101] = {{1, 5, 5, 0, 0, 0, false},
                                  {2, 4, 4, 0, 0, 0, false},
                                  {3, 2, 2, 0, 0, 0, false},
                                  {4, 1, 1, 0, 0, 0, false}};

struct Process processesB[101] = {{1, 6, 6, 0, 0, 0, false},
                                  {2, 5, 5, 0, 0, 0, false},
                                  {3, 1, 3, 0, 0, 0, false},
                                  {4, 2, 2, 0, 0, 0, false}};

struct User users[2] = {{4, processesA, 4, 4}, {2, processesB, 4, 4}};

int NumbGenerator() {
  srand(time(NULL) ^ clock()); // Set the seed for the random number generator
  return rand();
}

int ProcessTime() { return NumbGenerator() % 120 + 1; }

int SleepTime() { return NumbGenerator() % 30 + 1; }

int ProcessCmp(const void *a, const void *b) {
  const struct Process *processA = (struct Process *)a;
  const struct Process *processB = (struct Process *)b;

  if (processA->burstTimeRemaining < processB->burstTimeRemaining) {
    return -1;
  } else if (processA->burstTimeRemaining > processB->burstTimeRemaining) {
    return 1;
  } else {
    return 0;
  }
}

void WRR(struct User *users, struct Process queue[], bool *Ok, int *n) {
  (*Ok) = false;
  for (int i = 0; i < numbUsers; i++) {
    int numb = 0;
    if (users[i].remaining_processes > 0) {
      (*Ok) = true;
      for (int j = (users[i].processes_nr - users[i].remaining_processes);
           j < users[i].processes_nr; j++) {
        if (numb >= users[i].weight)
          break;
        else {
          if (!users[i].processes[j].isComplete) {
            queue[*n] = users[i].processes[j];
            (*n)++;
            numb++;
            users[i].remaining_processes--;
          }
        }
      }
    }
  }
}

void RR(struct Process *queue, const int n) {
  // Declaring the run and wait queue
  int runQueue[n];
  int waithQueue[n];
  int frunQueue = 0, rrunQueue = 0;
  int fwaitQueue = 0, rwaitQueue = 0;
  int currentTime = 0, numbExecuted = 0;

  // Separating the processes into queues
  runQueue[0] = 0;
  rrunQueue++;
  for (int i = 1; i < n; i++) {
    waithQueue[i - 1] = i;
    rwaitQueue++;
  }

  while (frunQueue < rrunQueue || fwaitQueue < rwaitQueue) {
    int x = runQueue[frunQueue];
    if (queue[x].burstTimeRemaining <= timeQuantum) {
      currentTime += queue[x].burstTimeRemaining;
      queue[x].completionTime = currentTime;
      queue[x].isComplete = true;
      queue[x].turnaroundTime = queue[x].waitingTime + queue[x].burstTime;
      queue[x].burstTimeRemaining = 0;
      numbExecuted++;

      if (numbExecuted < n) {
        int oldProcess = runQueue[frunQueue];
        int newProcess = waithQueue[fwaitQueue];
        runQueue[rrunQueue] = newProcess;
        queue[newProcess].waitingTime = queue[oldProcess].completionTime;
        rrunQueue++;
        fwaitQueue++;
      }

      frunQueue++;
    } else {
      queue[x].burstTimeRemaining -= timeQuantum;
      currentTime += timeQuantum;
    }
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

int main(int argc, char *argv[]) {
  timeQuantum = 2;
  numbUsers = 2;

  bool OK_WRR = true;

  while (OK_WRR) {
    // The queue for each cycle
    struct Process cycleQueue[MAX_VALUE];
    int n = 0;

    WRR(users, cycleQueue, &OK_WRR, &n);

    if (OK_WRR) {
      qsort(cycleQueue, n, sizeof(struct Process), ProcessCmp);

      RR(cycleQueue, n);

      Output(cycleQueue, n);
      printf("\n");
    }
  }

  return EXIT_SUCCESS;
}
