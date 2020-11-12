#include<stdio.h>
#include<stdlib.h>

struct process{
    int PID;
    int burstTime;
    int priority;
    int remainingBurstTime;
    int waitingTime;
    int turnAroundTime;
    struct process* next;
};

void prepareArrivalQueue(struct process **, struct process **);
void printQueue(char *, struct process **, struct process **);

void findTimesOfFCFS(struct process **, struct process **);
void findTimesOfSJF(struct process **, struct process **);
void findTimesOfRoundRobin(int, struct process **, struct process **);
void findTimesOfPriority(struct process **, struct process **);

void main(){
    struct process* head, * rear, * front;
    char optionAtInput;
    int timeSlice;
    head = (struct process *) malloc(sizeof(struct process));
    rear = head;
    front = head;
    head->PID = 0;
    head->next = NULL;

    do{
        prepareArrivalQueue(&front, &rear);
        printf("\nDo you want to enter more processes?(y/n): ");
        scanf(" %c", &optionAtInput);
    }while(optionAtInput == 'y');

    printf("Enter Time Slice for Round Robin: ");
    scanf("%d", &timeSlice);

    findTimesOfFCFS(&front, &rear);
    printQueue("FCFS", &front, &rear);

    findTimesOfRoundRobin(timeSlice, &front, &rear);
    printQueue("Round Robin", &front, &rear);

    findTimesOfSJF(&front, &rear);
    printQueue("SJF", &front, &rear);

    findTimesOfPriority(&front, &rear);
    printQueue("Priority", &front, &rear);
}


void prepareArrivalQueue(struct process** front, struct process** rear){
    int numberOfProcesses;
    printf("\nEnter number of processes: ");
    scanf("%d", &numberOfProcesses);
    for(int i = 0; i<numberOfProcesses; i++){
        struct process* newProcess = (struct process *) malloc(sizeof(struct process));
        newProcess->PID = (*rear)->PID+1;
        printf("\n\tProcess ID: %d", newProcess->PID);
        printf("\n\tEnter Priority: ");
        scanf("%d", &newProcess->priority);
        printf("\tEnter Burst Time: ");
        scanf("%d", &newProcess->burstTime);
        newProcess->remainingBurstTime = newProcess->burstTime;
        (*rear)->next = newProcess;
        *rear = newProcess;
    }
    if((*front)->next != NULL){
        *front = (*front)->next;
    }
    (*rear)->next = (*front);
}

void printQueue(char * heading, struct process ** front, struct process ** rear){
    
    int numberOfProcesses = 0;
    float averageWaitingTime = 0;
    float averageTurnaroundTime = 0;
    struct process *seeker = *front;
    printf("\n%s", heading);

    do{
        printf("\n\tPID: %d", seeker->PID);
        printf("\tBurst Time: %d", seeker->burstTime);
        printf("\tWaiting Time: %d", seeker->waitingTime);
        printf(" \tTurnaround Time: %d", seeker->turnAroundTime);
        numberOfProcesses++;
        averageWaitingTime += seeker->waitingTime;
        averageTurnaroundTime += seeker->turnAroundTime;
        seeker = seeker->next;
        }while(seeker!=*front);

    printf("\n\n\tAverage Waiting Time: %f\n\tAverage Turnaround Time: %f\n", averageWaitingTime/numberOfProcesses, averageTurnaroundTime/numberOfProcesses);
}

void findTimesOfFCFS(struct process ** front, struct process ** rear){
    int clock = 0;
    struct process *seeker = *front;
    do{
        seeker->waitingTime = clock;
        seeker->turnAroundTime = clock + seeker->burstTime;
        clock += seeker->burstTime;
        seeker = seeker->next;
    }while(seeker!=*front);
}

void findTimesOfSJF(struct process ** front, struct process ** rear){
    struct process *seeker;
    struct process *temp = (struct process *) malloc(sizeof(struct process));
    struct process *random = *front;
    do{
        seeker = *front;
        do{
            if(seeker->burstTime > seeker->next->burstTime){
                temp->PID = seeker->PID;
                temp->burstTime = seeker->burstTime;
                temp->remainingBurstTime = seeker->remainingBurstTime;
                temp->priority = seeker->priority;
                
                seeker->PID = seeker->next->PID;
                seeker->burstTime = seeker->next->burstTime;
                seeker->remainingBurstTime = seeker->next->remainingBurstTime;
                seeker->priority = seeker->next->priority;

                seeker->next->PID = temp->PID;
                seeker->next->burstTime = temp->burstTime;
                seeker->next->remainingBurstTime = temp->remainingBurstTime;
                seeker->next->priority = temp->priority;

            }
            seeker = seeker->next;
        }while(seeker != *rear);
        random = random->next;
    }while(random != *front);
    findTimesOfFCFS(front, rear);
}


void findTimesOfRoundRobin(int timeSlice, struct process ** front, struct process ** rear){
    int clock = 0;
    int flag = 0;
    struct process * seeker = *front;

    do{
        flag = 0;
        do{
            if(seeker->remainingBurstTime != 0){
                flag = 1;
                if(seeker->remainingBurstTime <= timeSlice){
                    clock += seeker->remainingBurstTime;
                    seeker->remainingBurstTime = 0;
                    seeker->turnAroundTime = clock;
                    seeker->waitingTime = seeker->turnAroundTime-seeker->burstTime;
                }else{
                    clock += timeSlice;
                    seeker->remainingBurstTime -= timeSlice;
                }
            }
            seeker = seeker->next;
        }while(seeker != *front);
    }while(flag);
}

void findTimesOfPriority(struct process ** front, struct process ** rear){
    struct process *seeker = *front;
    struct process *temp = (struct process *) malloc(sizeof(struct process));
    struct process *random = *front;
    do{
        seeker = *front;
        do{
            if(seeker->priority > seeker->next->priority){
                temp->PID = seeker->PID;
                temp->burstTime = seeker->burstTime;
                temp->remainingBurstTime = seeker->remainingBurstTime;
                temp->priority = seeker->priority;
                
                seeker->PID = seeker->next->PID;
                seeker->burstTime = seeker->next->burstTime;
                seeker->remainingBurstTime = seeker->next->remainingBurstTime;
                seeker->priority = seeker->next->priority;

                seeker->next->PID = temp->PID;
                seeker->next->burstTime = temp->burstTime;
                seeker->next->remainingBurstTime = temp->remainingBurstTime;
                seeker->next->priority = temp->priority;

            }
            seeker = seeker->next;
        }while(seeker != *rear);
        random = random->next;
    }while(random != *front);
    findTimesOfFCFS(front, rear);
}