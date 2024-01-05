#ifndef PROCESS
#define PROCESS

#include <stdbool.h>

struct Process {
  int pid;
  int burstTime;
  int burstTimeRemaining; // the amount of CPU time remaining after each
                          // execution
  int completionTime;
  int turnaroundTime;
  int waitingTime;
  bool isComplete;
};

#endif // !PROCESS
