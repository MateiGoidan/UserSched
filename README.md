# UserSched
The scheduling algorithm initiates by scanning through the list of users with pending processes, following a round-robin approach to ensure equitable processing. Upon selecting a user, the algorithm identifies a process associated with that user and allocates a predetermined time quantum for its execution. Each user is assigned a weight, representing their priority in the scheduling queue, which influences the frequency of their process execution.

In this project, a dynamic number of users with varying weights and processes are considered. Initially, the Weighted Round Robin method is employed to organize the processes into a queue structure, with each user's processes stacked according to their weight. This step ensures that users with higher weights receive proportionally more execution opportunities.

Subsequently, the project integrates the Shortest-Job-First (SJF) Scheduling algorithm to optimize the order of execution within each user's process queue. By prioritizing shorter processes, SJF scheduling minimizes overall turnaround time and enhances system efficiency.

Following the sorting phase, the Round Robin Scheduling algorithm, configured with an arrival time of zero, orchestrates the execution of processes within the sorted queues. Round Robin scheduling guarantees fairness by providing each process with a fixed time slice for execution before moving to the next process in the queue. This mechanism enables efficient resource utilization and prevents any single process from monopolizing system resources.

By combining Weighted Round Robin, SJF, and Round Robin scheduling techniques, this project aims to deliver a robust process scheduling framework that optimizes resource allocation, minimizes latency, and ensures equitable processing for diverse user workloads.
