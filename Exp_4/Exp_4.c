#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define maxProcess 10

struct Process {
    int pid;
    int seq;
    int allocated[maxProcess];
    int maximum[maxProcess];
    int need[maxProcess];
    struct Process * next;
};

struct Process * runningHead;
struct Process * sequenceHead;

int available[maxProcess];

void createProcesses(int, int);
void calculateNeed(int, int);
int calculateSafeSequence(int, int);
void showAll(int, int);

void main(){
    int numberOfProcesses, numberOfResources;
    runningHead = (struct Process *) malloc(sizeof(struct Process));
    sequenceHead = (struct Process *) malloc(sizeof(struct Process));
    sequenceHead->next = NULL;
    runningHead->next = NULL;
    
    //system("cls");

    printf("\nEnter number of Processes: ");
    scanf("%d", &numberOfProcesses);
    printf("\nEnter number of Resources: ");
    scanf("%d", &numberOfResources);

    createProcesses(numberOfProcesses, numberOfResources);

    printf("\nEnter Available Resources: ");
    for(int i=0; i<numberOfResources; i++){
        scanf("%1d", &available[i]);
    }

    calculateNeed(numberOfProcesses, numberOfResources);
    showAll(numberOfProcesses, numberOfResources);
    if(calculateSafeSequence(numberOfProcesses, numberOfResources) == 0){
        printf("\n\nUNSAFE STATE");
    }else{
        struct Process * traverse = sequenceHead->next;
        printf("\n\nSAFE SEQUENCE: ");
        for(int i=0; i<numberOfProcesses; i++){
            printf("P%d ", traverse->pid);
            traverse = traverse->next;
        }
    }
    printf("\n\n");
}

void createProcesses(int numberOfProcesses, int numberOfResources){
    struct Process * front = runningHead;
    

    for(int i=0; i<numberOfProcesses; i++){
        struct Process * new = (struct Process *) malloc(sizeof(struct Process));
        front->next=new;

        new->pid=i+1;
        printf("\n\tProcess %d", i+1);
        printf("\n\tEnter Allocated: ");
        for(int j=0; j<numberOfResources; j++){
            scanf(" %d", &new->allocated[j]);
        }
        printf("\tEnter Maximum: ");
        for(int j=0; j<numberOfResources; j++){
            scanf(" %d", &new->maximum[j]);
        }
        front=front->next;
        front->next=NULL;
    }
}

void calculateNeed(int numberOfProcesses, int numberOfResources){
    struct Process * traverse = runningHead->next;
    for(int i=0; i<numberOfProcesses; i++){
        for(int j=0; j<numberOfResources; j++){
            traverse->need[j] = traverse->maximum[j]-traverse->allocated[j];
        }
        traverse = traverse->next;
    }
}

void showAll(int numberOfProcesses, int numberOfResources){
    struct Process * traverse = runningHead->next;

    printf("\n\n");
    printf("Processes\t\tAllocated\tMaximum\t\tNeed");
    printf("\n");
    for(int k=0; k<64; k++){
        printf("=");
    }
    for(int i=0; i<numberOfProcesses; i++){
        printf("\nProcess %d\t\t", traverse->pid);
        for(int j=0; j<numberOfResources; j++){
            printf("%d ", traverse->allocated[j]);
        }
        printf("\t\t");
        for(int j=0; j<numberOfResources; j++){
            printf("%d ", traverse->maximum[j]);
        }
        printf("\t\t");
        for(int j=0; j<numberOfResources; j++){
            printf("%d ", traverse->need[j]);
        }
        traverse=traverse->next;
    }
}

int calculateSafeSequence(int numberOfProcesses, int numberOfResources){

    int numberOfSafe = 0, foundSafe = 0, allLess = 1;
    struct Process * traverse = runningHead->next;
    struct Process * tempTraverse1, * tempTraverse2;

    while(numberOfSafe < numberOfProcesses){
        foundSafe = 0;
        for(int i=0; i<numberOfProcesses-numberOfSafe; i++){
            allLess = 1;
            for(int j=0; j<numberOfResources; j++){
                if(traverse->need[j]>available[j]){
                    allLess = 0;
                }
            }
            if(allLess == 1){
                foundSafe = 1;
                numberOfSafe++;
                break;
            }
            traverse = traverse->next;
        }
        if(foundSafe == 1){
            //printf("process%d", traverse->pid); debug
            for(int j=0; j<numberOfResources; j++){
                available[j] = available[j] + traverse->allocated[j];
            }
            tempTraverse1 = runningHead;
            while(tempTraverse1->next != traverse){
                tempTraverse1 = tempTraverse1->next;
            }
            
            tempTraverse2 = sequenceHead;
            while(tempTraverse2->next != NULL){
                tempTraverse2 = tempTraverse2->next;
            }

            /*for(int j=0; j<numberOfResources; j++){
                printf("%d", available[j]);
            }
            debug*/
            tempTraverse2->next = traverse;
            tempTraverse1->next = traverse->next;
            traverse->next = NULL;
            if(tempTraverse1->next == NULL){
                traverse = runningHead->next;
            }else{
                traverse = tempTraverse1->next;
            }
            
            //printf("Completed");  debug
        }else{
            return 0;
        }
    }
    return 1;
}