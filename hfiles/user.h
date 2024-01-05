#ifndef USER
#define USER

struct User {
  int weight;
  struct Process *processes;
  int processes_nr;
  int remaining_processes;
};

#endif // !USER
