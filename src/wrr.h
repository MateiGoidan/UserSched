#ifndef WRR_H
#define WRR_H

#include <stdio.h>

struct Process {
  int pid;
  int arrivalTime;
  int burstTime;
  int burstTimeRemaining; // the amount of CPU time remaining after each
                          // execution
  int completionTime;
  int turnaroundTime;
  int waitingTime;
  bool isComplete;
  bool inQueue;
};

struct User
{
    int weight;
    struct Process* processes;
    int processes_nr;
    int remaining_processes;
};

void wrr(struct User* users, struct Process Coada[], bool *Ok, int *n)
{
    
    int l_coada = -1;
    (*Ok) = false;
    for(int i = 0; i <= (sizeof(users) / sizeof(users[0]) + 1); i++)
    {
        int nr = 0;
        if(users[i].remaining_processes > 0)
        {
            (*Ok) = true;
            for(int j = (users[i].processes_nr - users[i].remaining_processes); j < users[i].processes_nr; j++)
            {

                if(nr >= users[i].weight)
                    break;
                else
                {
                    if(!users[i].processes[j].isComplete)
                    {
                        l_coada ++;
                        Coada[l_coada] = users[i].processes[j];
                        nr ++;
                        (*n) ++;
                        users[i].remaining_processes --;
                    }
                }
            }
        }
    }
    
}



#endif