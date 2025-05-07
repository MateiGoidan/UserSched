# UserSched

### **Table of Content**
- [Description](#description)
- [How It Works](#how-it-works)
- [Objectives](#objectives)
- [Contributors](#contributors)

## Description

This project implements a comprehensive process scheduling framework that combines multiple scheduling algorithms to optimize resource allocation, minimize latency, and ensure fairness among users. It integrates Weighted Round Robin, Shortest-Job-First (SJF), and Round Robin scheduling strategies to deliver efficient and equitable process management.

## How It Works

1. **User and Process Management**
    - The algorithm starts by scanning a dynamic list of users, each with pending processes.
    - A round-robin approach is used to ensure each user is treated fairly when selecting processes.
    - Each user has an assigned weight representing their priority, affecting how often their processes are selected.

2. **Weighted Round Robin Scheduling**
    - Processes are initially organized using the Weighted Round Robin method.
    - Users with higher weights are allocated proportionally more execution opportunities.
    - This results in a stacked queue structure where process frequency aligns with user priority.

3. **Shortest-Job-First (SJF) Scheduling**
    - Within each user's process queue, the SJF algorithm is applied.
    - Processes are sorted based on their execution time, with shorter jobs prioritized.
    - This step aims to reduce overall turnaround time and improve system efficiency.

4. **Round Robin Scheduling**
    - After sorting, the Round Robin algorithm governs execution.
    - An arrival time of zero is assumed for all processes.
    - Each process is given a fixed time quantum for execution before the scheduler moves to the next process.
    - This guarantees fairness and prevents resource monopolization.

## Objectives

- **Fairness**: Every user and process gets equitable access to execution time.
- **Efficiency**: Shorter processes are prioritized to reduce average turnaround time.
- **Scalability**: Supports a dynamic number of users and processes with varying weights.
- **Robustness**: Combines multiple scheduling techniques to handle diverse workloads effectively.

## Contributors
- [Capitanu Andreea](https://github.com/CapitanuAndreea)
- [Goidan Matei](https://github.com/MateiGoidan)
- [Roseti Bogdan](https://github.com/RBogdanDev)
