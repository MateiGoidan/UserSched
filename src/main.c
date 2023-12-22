#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int fqueue = -1, rqueue = -1;

struct Process {
  unsigned int trun;
  unsigned int tsleep;
  unsigned int state;
  unsigned int user;
} run_queue[100], wait_queue[100];

int genereaza_numar_nou() {
  srand(time(NULL) ^ clock()); // Set the seed for the random number generator
  return rand();
}

int process_time() { return genereaza_numar_nou() % 120 + 1; }

int sleep_time() { return genereaza_numar_nou() % 30 + 1; }

int main() {
  for (int i = 0; i < 10; i++) {
    run_queue[i].trun = process_time();
    printf("run_queue[i].trun = %d\n", run_queue[i].trun);
  }
  return 0;
}
