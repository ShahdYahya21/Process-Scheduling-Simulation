#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
// process attribute
struct process{
    string s;
    int newArrivalTime;
    int arrivalTime;
    int burstTime;
    int comesBackAfter;
    int priority;
    int waitingTime = 0;
    int turnAroundTime = 0;
    int addedToReadyQueue = 0;
    int tempBurstTime = 0;
    int tempPriority = 0;
    int exitTime = 0;
    int lastTimeEnteredTheReadyQueue;
    int fiveUnitTimer = 5;
    int addedToTheCpu = 0;

};

void createProcesses();

bool compareByBurstTime(process* a,process* b);
void insertProcessToReadyQueue(int process);
bool compareByTempBurstTime(process* a, process* b);
bool compareByTempPriority(process* a, process* b);
void printProcesses();
void schedulerForFCFS();
void schedulerForSJF();
void schedulerForSRT();
void schedulerForRR();
void schedulerForPreemptivePriority();
void schedulerForNonPreemptivePriority();

vector<process> processes(8);
vector<process*> readyQueue;

process* processIntheCpu = new process();
bool start;

int timeCounter;
int allAdded;
int timeQuantum;

int main() {
    createProcesses();
    cout << "Consider the following set of processes:" << endl;
    printProcesses();
    cout << endl << "choose one of the following scheduling algorithms : " << endl;
    cout << "1- First Come First Served\n"
            "2- Shortest Job First\n"
            "3- Shortest Remaining Time First\n"
            "4- Round Robin, with q = 5\n"
            "5- Preemptive Priority Scheduling, with aging; where priority is decremented by 1 if the process remains in the ready queue for 5 time units\n"
            "6- Non-preemptive Priority Scheduling, with aging; where priority is decremented by 1 if the process remains in the ready queue for 5 time units\n"
            "7- Exit\n"
         << endl;
    int choice = 0;
    cout << "Enter your choice (1-7)  ";
    cin >> choice;

    while (choice != 7) {
        switch (choice) {
            case 1:
                schedulerForFCFS();
                break;
            case 2:
                schedulerForSJF();
                break;
            case 3:
                schedulerForSRT();
                break;
            case 4:
                schedulerForRR();
                break;
            case 5:
                schedulerForPreemptivePriority();
                break;
            case 6:
                schedulerForNonPreemptivePriority();
                break;
            default:
                cout << "Invalid choice. Please enter a valid option." << std::endl;
                break;
        }

        // Code outside the switch block
        if (choice == 7) break;
        createProcesses();
        processIntheCpu = new process();
        readyQueue.clear();
        cout << "Enter your choice (1-7)  ";

        cin >> choice;


    }
}





void insertProcessToReadyQueue(int process) {
    readyQueue.push_back(&processes[process]);
}



bool compareByBurstTime(process* a,process* b){
    return a->burstTime < b->burstTime;

}
bool compareByTempBurstTime(process* a, process* b) {
    // Compare by burstTime
    if (a->tempBurstTime < b->tempBurstTime) {
        return true;
    } else if (a->tempBurstTime > b->tempBurstTime) {
        return false;
    } else {
        return a->newArrivalTime < b->newArrivalTime;
    }
}
bool compareByTempPriority(process* a, process* b){
    if (a->tempPriority < b->tempPriority) {
        return true;
    } else if (a->tempPriority > b->tempPriority) {
        return false;
    } else {
        return a->lastTimeEnteredTheReadyQueue < b->lastTimeEnteredTheReadyQueue;
    }
}



void createProcesses(){
    processes[1].arrivalTime = 0;
    processes[2].arrivalTime = 1;
    processes[3].arrivalTime = 3;
    processes[4].arrivalTime = 4;
    processes[5].arrivalTime = 6;
    processes[6].arrivalTime = 7;
    processes[7].arrivalTime = 8;

    processes[1].burstTime = 10;
    processes[2].burstTime = 8;
    processes[3].burstTime = 14;
    processes[4].burstTime = 7;
    processes[5].burstTime = 5;
    processes[6].burstTime = 4;
    processes[7].burstTime = 6;

    processes[1].comesBackAfter = 2;
    processes[2].comesBackAfter = 4;
    processes[3].comesBackAfter = 6;
    processes[4].comesBackAfter = 8;
    processes[5].comesBackAfter = 3;
    processes[6].comesBackAfter = 6;
    processes[7].comesBackAfter = 9;

    processes[1].priority = 3;
    processes[2].priority = 2;
    processes[3].priority = 3;
    processes[4].priority = 1;
    processes[5].priority = 0;
    processes[6].priority = 1;
    processes[7].priority = 2;

    processes[1].tempBurstTime = processes[1].burstTime;
    processes[2].tempBurstTime = processes[2].burstTime;
    processes[3].tempBurstTime = processes[3].burstTime;
    processes[4].tempBurstTime = processes[4].burstTime;
    processes[5].tempBurstTime = processes[5].burstTime;
    processes[6].tempBurstTime = processes[6].burstTime;
    processes[7].tempBurstTime = processes[7].burstTime;

    processes[1].tempPriority = processes[1].priority;
    processes[2].tempPriority = processes[2].priority;
    processes[3].tempPriority = processes[3].priority;
    processes[4].tempPriority = processes[4].priority;
    processes[5].tempPriority = processes[5].priority;
    processes[6].tempPriority = processes[6].priority;
    processes[7].tempPriority = processes[7].priority;

    processes[1].newArrivalTime = processes[1].arrivalTime;
    processes[2].newArrivalTime = processes[2].arrivalTime;
    processes[3].newArrivalTime = processes[3].arrivalTime;
    processes[4].newArrivalTime = processes[4].arrivalTime;
    processes[5].newArrivalTime = processes[5].arrivalTime;
    processes[6].newArrivalTime = processes[6].arrivalTime;
    processes[7].newArrivalTime = processes[7].arrivalTime;

    processes[1].waitingTime = 0;
    processes[2].waitingTime = 0;
    processes[3].waitingTime = 0;
    processes[4].waitingTime = 0;
    processes[5].waitingTime = 0;
    processes[6].waitingTime = 0;
    processes[7].waitingTime = 0;

    processes[1].turnAroundTime = 0;
    processes[2].turnAroundTime = 0;
    processes[3].turnAroundTime = 0;
    processes[4].turnAroundTime = 0;
    processes[5].turnAroundTime = 0;
    processes[6].turnAroundTime = 0;
    processes[7].turnAroundTime = 0;

    processes[1].addedToReadyQueue = 0;
    processes[2].addedToReadyQueue = 0;
    processes[3].addedToReadyQueue = 0;
    processes[4].addedToReadyQueue = 0;
    processes[5].addedToReadyQueue = 0;
    processes[6].addedToReadyQueue = 0;
    processes[7].addedToReadyQueue = 0;

    processes[1].addedToTheCpu = 0;
    processes[2].addedToTheCpu = 0;
    processes[3].addedToTheCpu = 0;
    processes[4].addedToTheCpu = 0;
    processes[5].addedToTheCpu = 0;
    processes[6].addedToTheCpu = 0;
    processes[7].addedToTheCpu = 0;

    processes[1].exitTime = 0;
    processes[2].exitTime = 0;
    processes[3].exitTime = 0;
    processes[4].exitTime = 0;
    processes[5].exitTime = 0;
    processes[6].exitTime = 0;
    processes[7].exitTime = 0;

    processes[1].lastTimeEnteredTheReadyQueue = 0;
    processes[2].lastTimeEnteredTheReadyQueue = 0;
    processes[3].lastTimeEnteredTheReadyQueue = 0;
    processes[4].lastTimeEnteredTheReadyQueue = 0;
    processes[5].lastTimeEnteredTheReadyQueue = 0;
    processes[6].lastTimeEnteredTheReadyQueue = 0;
    processes[7].lastTimeEnteredTheReadyQueue = 0;

    processes[1].s = "process 1";
    processes[2].s = "process 2";
    processes[3].s = "process 3";
    processes[4].s = "process 4";
    processes[5].s = "process 5";
    processes[6].s = "process 6";
    processes[7].s = "process 7";

    processes[1].fiveUnitTimer = 5;
    processes[2].fiveUnitTimer = 5;
    processes[3].fiveUnitTimer = 5;
    processes[4].fiveUnitTimer = 5;
    processes[5].fiveUnitTimer = 5;
    processes[6].fiveUnitTimer = 5;
    processes[7].fiveUnitTimer = 5;

}

void printProcesses(){
    cout<<"           Arrival Time   Burst Time   Comes Back After   Priority"<<endl;
    for(int i = 1; i < processes.size(); i++){
        if(processes[i].burstTime < 10) cout << processes[i].s << "       " << processes[i].newArrivalTime << "            " << processes[i].burstTime << "                 " << processes[i].comesBackAfter << "              " << processes[i].priority << endl;
        else cout << processes[i].s << "       " << processes[i].newArrivalTime << "            " << processes[i].burstTime << "                " << processes[i].comesBackAfter << "              " << processes[i].priority << endl;
    }
}

void schedulerForFCFS(){
    start = true; // flag of not having any process in the cpu
    timeCounter = 0;
    allAdded = 0; // flag indicates that not all processes are added to the ready queue
    while (timeCounter <= 200) {
        // if there is processes need to enter the ready queue
        if (!allAdded) {
            for (int i = 1; i < 8; i++) {
                if (timeCounter == processes[i].newArrivalTime) {
                    insertProcessToReadyQueue(i);
                    processes[i].addedToReadyQueue = 1; // indicates that processes[i] in the ready queue
                }
            }
            // if allAdded flag remains true it means all processes are added and do not need to enter the previous loop
            allAdded = true;
            for (int i = 1; i < 8; i++) {
                if (processes[i].addedToReadyQueue == 0) {
                    allAdded = false;
                    break;
                }
            }
        }
        // Check if ready queue is not empty
        if (!readyQueue.empty()) {
            // if the start is false it means there is process in the cpu
            if (!start) {
                // when the process is finished we replace it with another process
                if (processIntheCpu->tempBurstTime == 0) {
                    //before we replace it we need to calculate the turnaround of the finished process
                    if(processIntheCpu->newArrivalTime != processIntheCpu ->arrivalTime)
                        processIntheCpu->turnAroundTime += timeCounter - (processIntheCpu->newArrivalTime - processIntheCpu->comesBackAfter);
                    else
                        processIntheCpu->turnAroundTime += timeCounter - processIntheCpu->newArrivalTime;
                    // find the new arrival time of the finished process
                    processIntheCpu->newArrivalTime = timeCounter + processIntheCpu->comesBackAfter;
                    processIntheCpu->tempBurstTime = processIntheCpu->burstTime;
                    if (timeCounter != 200) {
                        // replace the process
                        processIntheCpu = readyQueue[0];
                        processIntheCpu->addedToReadyQueue = 0;
                        processIntheCpu->addedToTheCpu = 1;
                        readyQueue.erase(readyQueue.begin());
                        allAdded = 0;
                        // calculate the waiting time of the entered process
                        processIntheCpu->waitingTime += timeCounter - processIntheCpu->newArrivalTime;
                        cout <<timeCounter<<")"<<" | " << processIntheCpu->s<<" ("<<timeCounter<<" - ";



                    }
                }
                    // when the time is 200 the cpu stop working and we calculate the turnaround time of the process in the cpu
                else if(timeCounter == 200){
                    if(processIntheCpu->newArrivalTime != processIntheCpu ->arrivalTime)
                        processIntheCpu->turnAroundTime += timeCounter - (processIntheCpu->newArrivalTime - processIntheCpu->comesBackAfter);
                    else
                        processIntheCpu->turnAroundTime += timeCounter - processIntheCpu->newArrivalTime;
                    cout <<timeCounter<<")"<<endl;

                }
            }
            // when the cpu is empty we add the first process of the ready queue to the cpu
            if (start) {
                processIntheCpu = readyQueue[0];
                processIntheCpu->addedToReadyQueue = 0;
                processIntheCpu->addedToTheCpu = 1;
                readyQueue.erase(readyQueue.begin());
                processIntheCpu->tempBurstTime = processIntheCpu->burstTime;
                start = false;
                allAdded = 0;
                cout<<processIntheCpu->s<<" ("<<timeCounter<<" - ";


            }



        }
        // increment a time counter
        timeCounter++;
        // decrement the burst time of the process in the cpu
        if (processIntheCpu->tempBurstTime) processIntheCpu->tempBurstTime--;

    }
    cout<<endl;
    double avgWaitingTime = 0;
    double avgTurnaroundTime = 0;
    int count1 = 0;
    int count2 = 0;
    for(int i = 1; i < 8 ; i++) {
        if (processes[i].addedToTheCpu)
            cout << processes[i].s << "   waiting time = " << processes[i].waitingTime<<"      ";
        else
            cout << processes[i].s << "   waiting time = infinity";

        if (processes[i].addedToTheCpu)
            cout << "        turnaround time = "<< processes[i].turnAroundTime << endl;
        else
            cout <<"        turnaround time = infinity"<< endl;

        if (processes[i].addedToTheCpu) {
            avgWaitingTime += processes[i].waitingTime;
            count1++;
        }

        if (processes[i].addedToTheCpu) {
            avgTurnaroundTime += processes[i].turnAroundTime;
            count2++;
        }


    }

    cout<<endl;
    cout<<"avg waiting time = "<<avgWaitingTime / count1<<endl;
    cout<<"avg turnaround time = "<<avgTurnaroundTime / count2<<endl;



}

void schedulerForSJF(){
    start = true;// flag of not having any process in the cpu
    allAdded = false;// flag indicates that not all processes are added to the ready queue
    timeCounter = 0;
    while (timeCounter <= 200) {
        // if there is processes need to enter the ready queue
        if (!allAdded) {
            for (int i = 1; i < 8; i++) {
                if (timeCounter == processes[i].newArrivalTime) {
                    insertProcessToReadyQueue(i);
                    processes[i].addedToReadyQueue = 1;// indicates that processes[i] in the ready queue
                }
            }
            // if allAdded flag remains true it means all processes are added and do not need to enter the previous loop
            allAdded = true;
            for (int i = 1; i < 8; i++) {
                if (processes[i].addedToReadyQueue == 0) {
                    allAdded = false;
                    break;
                }
            }
        }
        //sort the ready queue based on burst time
        sort(readyQueue.begin(), readyQueue.end(), compareByBurstTime);
        // Check if ready queue is not empty
        if (!readyQueue.empty()) {
            // if the start is false it means there is process in the cpu
            if (!start) {
                // when the process is finished we replace it with another process
                if (processIntheCpu->tempBurstTime == 0) {
                    //before we replace it we need to calculate the turnaround of the finished process
                    if(processIntheCpu->newArrivalTime != processIntheCpu ->arrivalTime)
                        processIntheCpu->turnAroundTime += timeCounter - (processIntheCpu->newArrivalTime - processIntheCpu->comesBackAfter);
                    else
                        processIntheCpu->turnAroundTime += timeCounter - processIntheCpu->newArrivalTime;

                    // find the new arrival time of the finished process
                    processIntheCpu->newArrivalTime = timeCounter + processIntheCpu->comesBackAfter;
                    processIntheCpu->tempBurstTime = processIntheCpu->burstTime;
                    if (timeCounter != 200) {
                        // replace the process
                        processIntheCpu = readyQueue[0];
                        processIntheCpu->addedToReadyQueue = 0;
                        processIntheCpu->addedToTheCpu = 1;
                        readyQueue.erase(readyQueue.begin());
                        allAdded = 0;
                        // calculate the waiting time of the entered process
                        processIntheCpu->waitingTime += timeCounter - processIntheCpu->newArrivalTime;
                        cout <<timeCounter<<")"<<" | " << processIntheCpu->s<<" ("<<timeCounter<<" - ";


                    }
                }
                    // when the time is 200 the cpu stop working and we calculate the turnaround time of the process in the cpu
                else if(timeCounter == 200){
                    if(processIntheCpu->newArrivalTime != processIntheCpu ->arrivalTime)
                        processIntheCpu->turnAroundTime += timeCounter - (processIntheCpu->newArrivalTime - processIntheCpu->comesBackAfter);
                    else
                        processIntheCpu->turnAroundTime += timeCounter - processIntheCpu->newArrivalTime;
                    cout <<timeCounter<<")"<<endl;

                }
            }
            // when the cpu is empty we add the first process of the ready queue to the cpu
            if (start) {
                processIntheCpu = readyQueue[0];
                processIntheCpu->addedToReadyQueue = 0;
                processIntheCpu->addedToTheCpu = 1;
                readyQueue.erase(readyQueue.begin());
                processIntheCpu->tempBurstTime = processIntheCpu->burstTime;
                start = false;
                allAdded = 0;
                cout<<processIntheCpu->s<<" ("<<timeCounter<<" - ";


            }



        }
        // increment a time counter
        timeCounter++;
        // decrement the burst time of the process in the cpu
        if (processIntheCpu->tempBurstTime) processIntheCpu->tempBurstTime--;

    }
    cout<<endl;
    double avgWaitingTime = 0;
    double avgTurnaroundTime = 0;
    int count1 = 0;
    int count2 = 0;
    for(int i = 1; i < 8 ; i++) {
        if (processes[i].addedToTheCpu)
            cout << processes[i].s << "   waiting time = " << processes[i].waitingTime<<"      ";
        else
            cout << processes[i].s << "   waiting time = infinity";

        if (processes[i].addedToTheCpu)
            cout << "        turnaround time = "<< processes[i].turnAroundTime << endl;
        else
            cout <<"        turnaround time = infinity"<< endl;

        if (processes[i].addedToTheCpu) {
            avgWaitingTime += processes[i].waitingTime;
            count1++;
        }

        if (processes[i].addedToTheCpu) {
            avgTurnaroundTime += processes[i].turnAroundTime;
            count2++;
        }


    }

    cout<<endl;
    cout<<"avg waiting time = "<<avgWaitingTime / count1<<endl;
    cout<<"avg turnaround time = "<<avgTurnaroundTime / count2<<endl;



}


void schedulerForSRT() {
    timeCounter = 0;
    start = true;// flag of not having any process in the cpu
    allAdded = 0;// flag indicates that not all processes are added to the ready queue
    while (timeCounter <= 200) {
        // if there is processes need to enter the ready queue
        if (!allAdded) {
            for (int i = 1; i < 8; i++) {
                if (timeCounter == processes[i].newArrivalTime) {
                    processes[i].addedToReadyQueue = 1;// indicates that processes[i] in the ready queue
                    insertProcessToReadyQueue(i);
                }
            }
            // if allAdded flag remains true it means all processes are added and do not need to enter the previous loop
            allAdded = true;
            for (int i = 1; i < 8; i++) {
                if (processes[i].addedToReadyQueue == 0) {
                    allAdded = false;
                    break;
                }
            }
        }
        //sort the ready queue based on burst time
        sort(readyQueue.begin(), readyQueue.end(), compareByTempBurstTime);
        // Check if ready queue is not empty
        if (!readyQueue.empty()) {
            // when the process is finished or there is a process in the ready queue have less time than the current process in the cpu we replace the current process
            if (!start &&
                (readyQueue[0]->tempBurstTime < processIntheCpu->tempBurstTime ||
                 processIntheCpu->tempBurstTime == 0)) {
                // calculate the waiting time of the new process
                if (readyQueue[0]->exitTime) {
                    if (timeCounter != 200) readyQueue[0]->waitingTime += timeCounter - readyQueue[0]->exitTime;

                } else {
                    if (timeCounter != 200) readyQueue[0]->waitingTime += timeCounter - readyQueue[0]->newArrivalTime;
                }

                if (processIntheCpu->tempBurstTime == 0) {
                    processIntheCpu->tempBurstTime = processIntheCpu->burstTime;
                    processIntheCpu->exitTime = 0;
                    //before we replace it we need to calculate the turnaround of the finished process
                    if (processIntheCpu->newArrivalTime != processIntheCpu->arrivalTime)
                        processIntheCpu->turnAroundTime +=
                                timeCounter - (processIntheCpu->newArrivalTime - processIntheCpu->comesBackAfter);
                    else
                        processIntheCpu->turnAroundTime += timeCounter - processIntheCpu->newArrivalTime;

                    // find the new arrival time of the finished process
                    processIntheCpu->newArrivalTime = timeCounter + processIntheCpu->comesBackAfter;

                }
                else {
                    // when the process to be replaced is not finished we readd it to the ready queue
                    readyQueue.push_back(processIntheCpu);
                    processIntheCpu->addedToReadyQueue = 1;
                    processIntheCpu->exitTime = timeCounter;
                }
                if (timeCounter != 200) {
                    // replace the process
                    processIntheCpu = readyQueue[0];
                    readyQueue.erase(readyQueue.begin());
                    readyQueue[0]->addedToReadyQueue = 0;
                    processIntheCpu->addedToTheCpu = 1;
                    allAdded = 0;
                    cout << timeCounter << ")" << " | " << processIntheCpu->s << " (" << timeCounter << " - ";

                }
            }
                // when the time is 200 the cpu stop working
            else if (timeCounter == 200) {
                processIntheCpu->exitTime = timeCounter;
                cout << timeCounter << ")" << endl;


            }
            // when the cpu is empty we add the first process of the ready queue to the cpu
            if (start) {
                processIntheCpu = readyQueue[0];
                processIntheCpu->addedToReadyQueue = 0;
                processIntheCpu->addedToTheCpu = 1;
                readyQueue.erase(readyQueue.begin());
                start = false;
                allAdded = 0;
                cout << processIntheCpu->s << " (" << timeCounter << " - ";

            }
        }

        // increment a time counter
        timeCounter++;

        // decrement the burst time of the process in the cpu
        if (processIntheCpu->tempBurstTime) {
            processIntheCpu->tempBurstTime--;

        }
    }
    // calculate the turnaround of the preempted processes
    for(int i = 1; i < processes.size(); i++) {
        if (processes[i].tempBurstTime != processes[i].burstTime) {
            if (processes[i].newArrivalTime != processes[i].arrivalTime)
                processes[i].turnAroundTime +=
                        processes[i].exitTime - (processes[i].newArrivalTime - processes[i].comesBackAfter);


            else
                processes[i].turnAroundTime += processes[i].exitTime - processes[i].newArrivalTime;

        }
    }

    cout<<endl;
    double avgWaitingTime = 0;
    double avgTurnaroundTime = 0;
    int count1 = 0;
    int count2 = 0;
    for(int i = 1; i < 8 ; i++) {
        if (processes[i].addedToTheCpu)
            cout << processes[i].s << "   waiting time = " << processes[i].waitingTime<<"      ";
        else
            cout << processes[i].s << "   waiting time = infinity";

        if (processes[i].addedToTheCpu)
            cout << "        turnaround time = "<< processes[i].turnAroundTime << endl;
        else
            cout <<"        turnaround time = infinity"<< endl;

        if (processes[i].addedToTheCpu) {
            avgWaitingTime += processes[i].waitingTime;
            count1++;
        }

        if (processes[i].addedToTheCpu) {
            avgTurnaroundTime += processes[i].turnAroundTime;
            count2++;
        }


    }

    cout<<endl;
    cout<<"avg waiting time = "<<avgWaitingTime / count1<<endl;
    cout<<"avg turnaround time = "<<avgTurnaroundTime / count2<<endl;



}

void schedulerForRR(){
    start = true;// flag of not having any process in the cpu
    allAdded = 0;// flag indicates that not all processes are added to the ready queue
    timeCounter = 0;
    while (timeCounter <= 200) {
        // if there is processes need to enter the ready queue
        if (!allAdded) {
            for (int i = 1; i < 8; i++) {
                if (timeCounter == processes[i].newArrivalTime) {
                    processes[i].addedToReadyQueue = 1;// indicates that processes[i] in the ready queue
                    insertProcessToReadyQueue(i);
                }
            }
            // if allAdded flag remains true it means all processes are added and do not need to enter the previous loop
            allAdded = true;
            for (int i = 1; i < 8; i++) {
                if (processes[i].addedToReadyQueue == 0) {
                    allAdded = false;
                    break;
                }
            }
        }
        // Check if ready queue is not empty
        if (!readyQueue.empty()) {
            // when the time quantum is zero we replace the process in the cpu with a new process
            if (!start && !timeQuantum) {
                if (processIntheCpu->tempBurstTime == 0) {
                    processIntheCpu->tempBurstTime = processIntheCpu->burstTime;
                    //before we replace it we need to calculate the turnaround of the finished process
                    if (processIntheCpu->newArrivalTime != processIntheCpu->arrivalTime)
                        processIntheCpu->turnAroundTime +=
                                timeCounter - (processIntheCpu->newArrivalTime - processIntheCpu->comesBackAfter);
                    else
                        processIntheCpu->turnAroundTime += timeCounter - processIntheCpu->newArrivalTime;
                    // find the new arrival time of the finished process
                    processIntheCpu->newArrivalTime = timeCounter + processIntheCpu->comesBackAfter;
                } else {
                    // when the process to be replaced is not finished we readd it to the ready queue
                    processIntheCpu->exitTime = timeCounter;
                    readyQueue.push_back(processIntheCpu);
                    processIntheCpu->addedToReadyQueue = 1;
                }
                if (timeCounter != 200) {
                    // replace the process
                    processIntheCpu = readyQueue[0];
                    readyQueue.erase(readyQueue.begin());
                    processIntheCpu->addedToReadyQueue = 0;
                    processIntheCpu->addedToTheCpu = 1;
                    cout << timeCounter << ")" << " | " << processIntheCpu->s << " (" << timeCounter << " - ";
                    allAdded = 0;
                    // calculate the waiting time of the new process
                    if (processIntheCpu->tempBurstTime == processIntheCpu->burstTime) {
                        processIntheCpu->waitingTime += timeCounter - processIntheCpu->newArrivalTime;


                    } else {
                        processIntheCpu->waitingTime += timeCounter - processIntheCpu->exitTime;

                    }
//                    define the time quantum of the current process
                    if (processIntheCpu->tempBurstTime >= 5) timeQuantum = 5;
                    else timeQuantum = processIntheCpu->tempBurstTime;
                }
            }
            // when the time is 200 the cpu stop working
            if (timeCounter == 200) {
                processIntheCpu->exitTime = timeCounter;
                cout << timeCounter << ")" << endl;

            }

            // when the cpu is empty we add the first process of the ready queue to the cpu
            if (start) {
                processIntheCpu = readyQueue[0];
                processIntheCpu->addedToReadyQueue = 0;
                processIntheCpu->addedToTheCpu = 1;
                readyQueue.erase(readyQueue.begin());
                start = false;
                allAdded = 0;
                if (processIntheCpu->tempBurstTime >= 5) timeQuantum = 5;
                else timeQuantum = processIntheCpu->tempBurstTime;
                cout<<processIntheCpu->s<<" ("<<timeCounter<<" - ";
            }

        }
        timeCounter++;
        // each time count we decrement the time quantum and burst time
        if (processIntheCpu -> tempBurstTime){
            processIntheCpu -> tempBurstTime--;
            timeQuantum--;

        }
    }
    // calculate the turnaround of the preempted processes
    for(int i = 1; i < processes.size(); i++) {
        if (processes[i].tempBurstTime != processes[i].burstTime) {
            if (processes[i].arrivalTime != processes[i].newArrivalTime)
                processes[i].turnAroundTime +=
                        processes[i].exitTime - ( processes[i].newArrivalTime -  processes[i].comesBackAfter);
            else
                processes[i].turnAroundTime += processes[i].exitTime - processes[i].newArrivalTime;
        }
    }

    cout<<endl;
    double avgWaitingTime = 0;
    double avgTurnaroundTime = 0;
    int count1 = 0;
    int count2 = 0;
    for(int i = 1; i < 8 ; i++) {
        if (processes[i].addedToTheCpu)
            cout << processes[i].s << "   waiting time = " << processes[i].waitingTime<<"      ";
        else
            cout << processes[i].s << "   waiting time = infinity";

        if (processes[i].addedToTheCpu)
            cout << "        turnaround time = "<< processes[i].turnAroundTime << endl;
        else
            cout <<"        turnaround time = infinity"<< endl;

        if (processes[i].addedToTheCpu) {
            avgWaitingTime += processes[i].waitingTime;
            count1++;
        }

        if (processes[i].addedToTheCpu) {
            avgTurnaroundTime += processes[i].turnAroundTime;
            count2++;
        }


    }

    cout<<endl;
    cout<<"avg waiting time = "<<avgWaitingTime / count1<<endl;
    cout<<"avg turnaround time = "<<avgTurnaroundTime / count2<<endl;



}

void schedulerForPreemptivePriority(){
    allAdded = 0;// flag indicates that not all processes are added to the ready queue
    start = true;// flag of not having any process in the cpu
    timeCounter = 0;
    while (timeCounter <= 200) {
        // if there is processes need to enter the ready queue
        if (!allAdded) {
            for (int i = 1; i < 8; i++) {
                if (timeCounter == processes[i].newArrivalTime) {
                    processes[i].lastTimeEnteredTheReadyQueue = processes[i].newArrivalTime;
                    processes[i].addedToReadyQueue = 1;// indicates that processes[i] in the ready queue
                    insertProcessToReadyQueue(i);
                }
            }
            // if allAdded flag remains true it means all processes are added and do not need to enter the previous loop
            allAdded = true;
            for (int i = 1; i < 8; i++) {
                if (processes[i].addedToReadyQueue == 0) {
                    allAdded = false;
                    break;
                }
            }
        }
        //sort the ready queue queue based on the proirity
        sort(readyQueue.begin(),readyQueue.end(),compareByTempPriority);
        // Check if ready queue is not empty
        if (!readyQueue.empty()) {
            // when the process is finished or there is a process in the ready queue have less priority than the current process in the cpu we replace the current process
            if (!start &&
                (readyQueue[0]->tempPriority < processIntheCpu->tempPriority || processIntheCpu->tempBurstTime == 0)) {
                // calculate the waiting time of the new process
                if(timeCounter != 200) {
                    if (readyQueue[0]->exitTime) {
                        readyQueue[0]->waitingTime += timeCounter - readyQueue[0]->exitTime;

                    } else {
                        readyQueue[0]->waitingTime += timeCounter - readyQueue[0]->newArrivalTime;

                    }
                }


                if (processIntheCpu->tempBurstTime == 0) {
                    processIntheCpu->tempBurstTime = processIntheCpu->burstTime;
                    processIntheCpu->tempPriority = processIntheCpu->priority;

                    processIntheCpu->exitTime = 0;
                    //before we replace it we need to calculate the turnaround of the finished process
                    if (processIntheCpu->newArrivalTime != processIntheCpu->arrivalTime)
                        processIntheCpu->turnAroundTime +=
                                timeCounter - (processIntheCpu->newArrivalTime - processIntheCpu->comesBackAfter);
                    else
                        processIntheCpu->turnAroundTime += timeCounter - processIntheCpu->newArrivalTime;
                    // find the new arrival time of the finished process
                    processIntheCpu->newArrivalTime = timeCounter + processIntheCpu->comesBackAfter;

                } else {
                    // when the process to be replaced is not finished we readd it to the ready queue
                    readyQueue.push_back(processIntheCpu);
                    processIntheCpu->addedToReadyQueue = 1;
                    processIntheCpu->exitTime = timeCounter;
                    processIntheCpu -> lastTimeEnteredTheReadyQueue = timeCounter;
                }
                if(timeCounter != 200) {
                    // replace the process
                    processIntheCpu = readyQueue[0];
                    readyQueue.erase(readyQueue.begin());
                    readyQueue[0]->addedToReadyQueue = 0;
                    processIntheCpu->addedToTheCpu = 1;
                    allAdded = 0;
                    cout <<timeCounter<<")"<<" | " << processIntheCpu->s<<" ("<<timeCounter<<" - ";
                }

            }
                // when the time is 200 the cpu stop working
            else if(timeCounter == 200){
                processIntheCpu -> exitTime = timeCounter;
                cout <<timeCounter<<")"<<endl;
            }
            // when the cpu is empty we add the first process of the ready queue to the cpu
            if (start) {
                processIntheCpu = readyQueue[0];
                processIntheCpu->addedToReadyQueue = 0;
                processIntheCpu->addedToTheCpu = 1;
                readyQueue.erase(readyQueue.begin());
                start = false;
                allAdded = 0;
                cout<<processIntheCpu->s<<" ("<<timeCounter<<" - ";
            }

        }
        timeCounter++;
        // each time count we decrement the burst time
        if (processIntheCpu -> tempBurstTime){
            processIntheCpu -> tempBurstTime--;


        }
        // each 5 time counts we decrement the priority of all the processes in the ready queue
        for(int i = 0; i < readyQueue.size(); i++){
            readyQueue[i]->fiveUnitTimer--;
            if(!readyQueue[i]->fiveUnitTimer){
                if(readyQueue[i]->tempPriority) readyQueue[i]->tempPriority--;
                readyQueue[i]->fiveUnitTimer = 5;
            }
        }
    }
    cout<<endl;
    // calculate the turnaround of the preempted processes
    for(int i = 1; i < processes.size(); i++) {
        if (processes[i].tempBurstTime != processes[i].burstTime) {
            if (processes[i].arrivalTime != processes[i].newArrivalTime)
                processes[i].turnAroundTime +=
                        processes[i].exitTime - ( processes[i].newArrivalTime -  processes[i].comesBackAfter);
            else
                processes[i].turnAroundTime += processes[i].exitTime - processes[i].newArrivalTime;
        }
    }

    cout<<endl;
    double avgWaitingTime = 0;
    double avgTurnaroundTime = 0;
    int count1 = 0;
    int count2 = 0;
    for(int i = 1; i < 8 ; i++) {
        if (processes[i].addedToTheCpu)
            cout << processes[i].s << "   waiting time = " << processes[i].waitingTime<<"      ";
        else
            cout << processes[i].s << "   waiting time = infinity";

        if (processes[i].addedToTheCpu)
            cout << "        turnaround time = "<< processes[i].turnAroundTime << endl;
        else
            cout <<"        turnaround time = infinity"<< endl;

        if (processes[i].addedToTheCpu) {
            avgWaitingTime += processes[i].waitingTime;
            count1++;
        }

        if (processes[i].addedToTheCpu) {
            avgTurnaroundTime += processes[i].turnAroundTime;
            count2++;
        }


    }

    cout<<endl;
    cout<<"avg waiting time = "<<avgWaitingTime / count1<<endl;
    cout<<"avg turnaround time = "<<avgTurnaroundTime / count2<<endl;



}

void schedulerForNonPreemptivePriority(){
    allAdded = 0;// flag indicates that not all processes are added to the ready queue
    start = true;// flag of not having any process in the cpu
    timeCounter = 0;
    while (timeCounter <= 200) {
        // if there is processes need to enter the ready queue
        if (!allAdded) {
            for (int i = 1; i < 8; i++) {
                if (timeCounter == processes[i].newArrivalTime) {
                    processes[i].lastTimeEnteredTheReadyQueue = processes[i].newArrivalTime;
                    processes[i].addedToReadyQueue = 1;// indicates that processes[i] in the ready queue
                    insertProcessToReadyQueue(i);
                }
            }
            // if allAdded flag remains true it means all processes are added and do not need to enter the previous loop
            allAdded = true;
            for (int i = 1; i < 8; i++) {
                if (processes[i].addedToReadyQueue == 0) {
                    allAdded = false;
                    break;
                }
            }
        }
        //sort the ready queue queue based on the proirity
        sort(readyQueue.begin(),readyQueue.end(),compareByTempPriority);
        // Check if ready queue is not empty
        if(!readyQueue.empty()){
            // when the process is finished is zero we replace the process in the cpu with a new process
            if (!start && processIntheCpu ->tempBurstTime == 0) {
                processIntheCpu -> tempBurstTime = processIntheCpu -> burstTime;
                processIntheCpu -> tempPriority = processIntheCpu -> priority;

                //before we replace it we need to calculate the turnaround of the finished process
                if (processIntheCpu->newArrivalTime != processIntheCpu->arrivalTime)
                    processIntheCpu->turnAroundTime +=
                            timeCounter - (processIntheCpu->newArrivalTime - processIntheCpu->comesBackAfter);
                else
                    processIntheCpu->turnAroundTime += timeCounter - processIntheCpu->newArrivalTime;

                // find the new arrival time of the finished process
                processIntheCpu->newArrivalTime = timeCounter + processIntheCpu->comesBackAfter;
                if(timeCounter != 200) {
                    // replace the process
                    processIntheCpu = readyQueue[0];
                    processIntheCpu->addedToReadyQueue = 0;
                    processIntheCpu->addedToTheCpu = 1;
                    readyQueue.erase(readyQueue.begin());
                    allAdded = 0;
                    processIntheCpu->waitingTime += timeCounter - processIntheCpu->newArrivalTime;
                    cout <<timeCounter<<")"<<" | " << processIntheCpu->s<<" ("<<timeCounter<<" - ";
                }


            }
                // when the time is 200 the cpu stop working
            else if(timeCounter == 200){
                if (processIntheCpu->newArrivalTime != processIntheCpu->arrivalTime)
                    processIntheCpu->turnAroundTime +=
                            timeCounter - (processIntheCpu->newArrivalTime - processIntheCpu->comesBackAfter);
                else
                    processIntheCpu->turnAroundTime += timeCounter - processIntheCpu->newArrivalTime;
                cout <<timeCounter<<")"<<endl;

            }

            // when the cpu is empty we add the first process of the ready queue to the cpu
            if (start) {
                processIntheCpu = readyQueue[0];
                processIntheCpu->addedToReadyQueue = 0;
                processIntheCpu->addedToTheCpu = 1;
                readyQueue.erase(readyQueue.begin());
                processIntheCpu -> tempBurstTime = processIntheCpu -> burstTime;
                start = false;
                allAdded = 0;
                cout<<processIntheCpu->s<<" ("<<timeCounter<<" - ";

            }
        }
        timeCounter++;
        // each time count we decrement the burst time
        if (processIntheCpu -> tempBurstTime){
            processIntheCpu -> tempBurstTime--;


        }
        // each 5 time counts we decrement the priority of all the processes in the ready queue
        for(int i = 0; i < readyQueue.size(); i++){
            readyQueue[i]->fiveUnitTimer--;
            if(!readyQueue[i]->fiveUnitTimer){
                if(readyQueue[i]->tempPriority) readyQueue[i]->tempPriority--;
                readyQueue[i]->fiveUnitTimer = 5;
            }
        }
    }
    cout<<endl;
    double avgWaitingTime = 0;
    double avgTurnaroundTime = 0;
    int count1 = 0;
    int count2 = 0;
    for(int i = 1; i < 8 ; i++) {
        if (processes[i].addedToTheCpu)
            cout << processes[i].s << "   waiting time = " << processes[i].waitingTime<<"      ";
        else
            cout << processes[i].s << "   waiting time = infinity";

        if (processes[i].addedToTheCpu)
            cout << "        turnaround time = "<< processes[i].turnAroundTime << endl;
        else
            cout <<"        turnaround time = infinity"<< endl;

        if (processes[i].addedToTheCpu) {
            avgWaitingTime += processes[i].waitingTime;
            count1++;
        }

        if (processes[i].addedToTheCpu) {
            avgTurnaroundTime += processes[i].turnAroundTime;
            count2++;
        }


    }

    cout<<endl;
    cout<<"avg waiting time = "<<avgWaitingTime / count1<<endl;
    cout<<"avg turnaround time = "<<avgTurnaroundTime / count2<<endl;



}



