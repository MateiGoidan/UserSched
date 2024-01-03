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
    struct Process* procese;
    int nr_procese;
};

void wrr(struct User* users, struct Process Coada[])
{
    int l_coada = -1;
    for(int i = 0; i <= sizeof(users) / sizeof(users[0]); i++)
    {
        int nr = 0;
        for(int j = 0; j < sizeof(users[i].procese[j]) / sizeof(users[i].procese[0]); j++)
        {
            if(nr >= users[i].weight)
                break;
            else
            {
                if(!users[i].procese[j].isComplete)
                {
                    l_coada ++;
                    Coada[l_coada] = users[i].procese[j];
                    nr ++;
                    users[i].nr_procese --;
                }
            }
        }
    }
    
}



#endif