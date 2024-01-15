/*
 * This code, unlike the code from maine does not include the sorting algorithm
 * SJF after the WW algorithm
 */

#include "..//hfiles/process.h"
#include "../hfiles/user.h"
#include <linux/limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

#define MAX_VALUE 99999

int timeQuantum, numbUsers, numbTests, avgWT, avgTT;
int avgTestWT, avgTestTT;

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
  int runQueue[n];
  int waithQueue[n];
  int frunQueue = 0, rrunQueue = 0;
  int fwaitQueue = 0, rwaitQueue = 0;
  int currentTime = 0, numbExecuted = 0;

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
    avgWaitingTime += processes[i].waitingTime;
    avgTurntaroundTime += processes[i].turnaroundTime;
  }
  avgTestWT = avgTestWT + avgWaitingTime / n;
  avgTestTT = avgTestTT + avgTurntaroundTime / n;
}

void ProcessConstructor(int numbProcess, struct Process *processes) {
  for (int i = 0; i < numbProcess; i++) {
    processes[i].pid = i + 1;
    processes[i].burstTime = rand() % ((numbProcess - 1) * timeQuantum - 1) + 1;
    processes[i].burstTimeRemaining = processes[i].burstTime;
  }
}

struct User UserConstructor() {
  struct User user;
  int numbProcess = rand() % (int)1e2 + 1;
  struct Process *Test =
      (struct Process *)(malloc(numbProcess * sizeof(struct Process)));

  ProcessConstructor(numbProcess, Test);

  user.weight = rand() % numbProcess + 1;
  user.processes = Test;
  user.processes_nr = numbProcess;
  user.remaining_processes = numbProcess;

  return user;
}

int main(int argc, char *argv[]) {
  srand(time(NULL));
  avgWT = 0;
  avgTT = 0;
  timeQuantum = rand() % (int)1e2 + 1;
  numbTests = rand() % (int)1e3 + 1;

  printf("+------+--------------+-------------+--------------+---------------"
         "---+\n");
  printf("| Test | Numb. Users | Numb. Cycles | Waiting Time | Turn Around "
         "Time |\n");
  printf("+------+--------------+-------------+--------------+---------------"
         "---+\n");

  for (int currentTest = 0; currentTest < numbTests; currentTest++) {
    avgTestWT = 1;
    avgTestTT = 1;
    numbUsers = rand() % (int)1e3 + 1;
    struct User users[MAX_VALUE];

    for (int i = 0; i < numbUsers; i++) {
      users[i] = UserConstructor();
    }

    bool OK_WRR = true;

    int numbCycles = 1;
    while (OK_WRR) {
      int n = 0;
      struct Process cycleQueue[MAX_VALUE];

      WRR(users, cycleQueue, &OK_WRR, &n);

      if (OK_WRR) {
        RR(cycleQueue, n);

        Output(cycleQueue, n);
        numbCycles++;
      }
    }
    printf("%d           %d           %d           %d          %d \n",
           currentTest, numbUsers, numbCycles, avgTestWT, avgTestTT);

    avgWT += avgTestWT / numbCycles;
    avgTT += avgTestTT / numbCycles;
  }

  printf("+------+--------------+-------------+--------------+---------------"
         "---+\n");
  printf("Average Waiting Time: %d \nAverage Tuurn Around Time: %d\n",
         avgWT / numbTests, avgTT / numbTests);

  return EXIT_SUCCESS;
}
