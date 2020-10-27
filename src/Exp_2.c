#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Process {
    int id;
    int size;
    struct Process * link;
};

struct Process * head;

struct Process * findProcess(int);
int printMenu();
void deleteProcess(struct Process *);

void addHandle(int *, int, int * );
void deleteHandle(int *, int, int *);

void main(){
    int pageSize, memorySize, totalFrames, framesLeft;
    char userChoice='y';
    head = (struct Process *) malloc(sizeof(struct Process));
    head->id = -1;
    head->link = NULL;

    printf("\nEnter total memory size: ");
    scanf("%d", &memorySize);
    printf("Enter page/frame size: ");
    scanf("%d", &pageSize);

    totalFrames = memorySize/pageSize;
    framesLeft = totalFrames;
    int frames[totalFrames];
    memset(frames, -1, totalFrames*sizeof(int));

    printf("\nTOTAL AVAILABLE FRAMES: %d", framesLeft);

    do{
        switch(printMenu()){
            case 1: addHandle(&framesLeft, pageSize, frames);
                    break;
            case 2: deleteHandle(&framesLeft, pageSize, frames);
                    break;
            default: printf("Invalid Choice");
                    break;
        }
        printf("\n\nDo you want to do more?(y/n): ");
        scanf(" %c", &userChoice);
    }while(userChoice=='y');
}

void addHandle(int *framesLeft, int frameSize, int * frames){
    int processId, processSize;
    struct Process * traverse = head;
    while(traverse->link != NULL){
        traverse = traverse->link;
    }
    printf("\n\tEnter process Id: ");
    scanf("%d", &processId);
    
    if(findProcess(processId)!=0){
        printf("\tPROCESS ALREADY EXISTS");
        return ;
    }

    printf("\tEnter process Size: ");
    scanf("%d", &processSize);


    if((processSize/frameSize) > *framesLeft){
        printf("\tMEMORY FULL");
        return ;
    }else{
        *framesLeft -= (processSize%frameSize) == 0 ?(processSize/frameSize): ((processSize/frameSize)+1);
    }

    printf("\nFRAMES LEFT: %d", *framesLeft);

    struct Process * newProcess = (struct Process *) malloc (sizeof(struct Process));
    newProcess->id = processId;
    newProcess->size = processSize;
    traverse->link = newProcess;
    newProcess->link = NULL;
}

void deleteHandle(int *framesLeft, int frameSize, int * frames){
    int processId;
    struct Process * processFound;
    printf("\n\tEnter Process Id: ");
    scanf("%d", &processId);

    processFound = findProcess(processId);

    if(processFound!=0){
        printf("\tDELETED PROCESS:\tprocess Id: %d\tprocess Size: %d", processFound->id, processFound->size);
        (*framesLeft) += (processFound->size%frameSize) == 0 ? (processFound->size/frameSize) : ((processFound->size/frameSize)+1);
        deleteProcess(processFound);
    }else{
        printf("\tPROCESS NOT FOUND");
    }
    printf("\n\nFRAMES LEFT: %d", *framesLeft);
}

void deleteProcess(struct Process * processToDelete){
    struct Process * traverse = head;
    while(traverse->link != processToDelete){
        traverse = traverse->link;
    }
    traverse->link = processToDelete->link;
    realloc(processToDelete, sizeof(struct Process *));
}

int printMenu(){
    int userChoice;
    printf("\n\nDo you want to: 1.Add   2.Delete  : ");
    scanf("%d", &userChoice);
    return userChoice;
}

struct Process * findProcess(int processId){
    struct Process * traverse = head;
    while(traverse->link != NULL){
        traverse = traverse->link;
        if(traverse->id==processId){
            return traverse;
        }
    }
    return 0;
}