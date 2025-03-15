## Process Scheduling Simulation

### Overview
This C++ program simulates various process scheduling algorithms. It allows the user to select a scheduling method and runs the simulation to compute waiting times and turnaround times for a set of predefined processes.

### Features
- Simulates multiple scheduling algorithms:
  - **First Come First Served (FCFS)**
  - **Shortest Job First (SJF)**
  - **Shortest Remaining Time First (SRT)**
  - **Round Robin (RR)**
  - **Preemptive Priority Scheduling (with aging)**
  - **Non-Preemptive Priority Scheduling (with aging)**
- Tracks important metrics such as waiting time and turnaround time.
- Implements process queue management.

### Program Structure
#### 1. **Process Structure**
Each process is represented by a `struct` named `process`, which contains attributes such as:
- `arrivalTime`: Time when the process enters the system.
- `burstTime`: Total CPU time required.
- `priority`: Priority level (used in priority-based scheduling).
- `waitingTime`: Time spent waiting in the ready queue.
- `turnAroundTime`: Total time from arrival to completion.
- `tempBurstTime`: Temporary burst time (for preemptive scheduling).
- `tempPriority`: Temporary priority (for aging-based priority adjustments).
- `exitTime`: Time when the process completes execution.

#### 2. **Data Initialization**
The function `createProcesses()` initializes a predefined set of processes with their attributes such as:
- Arrival time
- Burst time
- Priority
- Aging parameters (for priority adjustments over time)

#### 3. **User Input**
The program presents a menu for the user to select one of the scheduling algorithms:  
1- First Come First Served  
2- Shortest Job First  
3- Shortest Remaining Time First  
4- Round Robin (q = 5)  
5- Preemptive Priority Scheduling (with aging)    
6- Non-Preemptive Priority Scheduling (with aging)  
7- Exit
The user selects an option, and the corresponding scheduling algorithm is executed.

#### 4. **Scheduling Algorithms**
Each scheduling method is implemented as a function:

##### **First Come First Served (FCFS)**
- Executes processes in the order they arrive.
- No preemption.

##### **Shortest Job First (SJF)**
- Sorts processes by burst time.
- Non-preemptive: Once a process starts, it runs to completion.

##### **Shortest Remaining Time First (SRT)**
- Preemptive version of SJF.
- A new process with a shorter burst time can interrupt the current one.

##### **Round Robin (RR)**
- Time-sharing scheduling with a fixed quantum (`q = 5`).
- Processes take turns executing for a time slice before moving to the back of the queue.

##### **Preemptive Priority Scheduling**
- Higher priority processes can preempt lower-priority ones.
- Aging: If a process waits too long, its priority decreases to prevent starvation.

##### **Non-Preemptive Priority Scheduling**
- Similar to preemptive priority scheduling but does not allow interruption once a process starts.

#### 5. **Performance Metrics**
At the end of execution, the program calculates and displays:
- Average waiting time
- Average turnaround time

### Program Output Example

#### simulation of First Come First Served (FCFS):
  <img width="1332" alt="image" src="https://github.com/user-attachments/assets/c660a5fd-f8c5-4ab8-be9e-aab043b2c30b" />
  
#### simulation of Shortest Job First (SJF): 
  <img width="1339" alt="image" src="https://github.com/user-attachments/assets/7381dc05-b3fd-4fd9-8a85-f3ebf6231dae" />
  
#### simulation of Shortest Remaining Time First (SRT):
  <img width="1343" alt="image" src="https://github.com/user-attachments/assets/e014de55-da96-4e65-8a2f-bee35c21b0a2" />
  
#### simulation of Round Robin (RR):
  <img width="1337" alt="image" src="https://github.com/user-attachments/assets/9cdd81dd-df64-45d7-b5e6-a7efd2a6d401" />
  
#### simulation of Preemptive Priority Scheduling:  
  <img width="1344" alt="image" src="https://github.com/user-attachments/assets/02f31642-fd69-4012-96cc-0974d773881b" />
  
#### simulation of Non-Preemptive Priority Scheduling:  
  <img width="1341" alt="image" src="https://github.com/user-attachments/assets/24336766-bd45-4b41-9112-15fe3c9ad23b" />










