#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int underlineLength = 46;

struct frames{
    int index;
    struct frames *next;
};

void printFrames(int *, int);
int hitOrMiss(int *, int, int);
int findToReplaceIndex(int *, int, int *, int, int);
struct frames * createQ(int);
void updateAccess(struct frames **, struct frames **, int);
void printSummary(int);

void fcfs(int *, int, int);
void optimal(int *, int, int);
void lru(int*, int, int);
void mru(int*, int, int);

void main(){
    int numberOfFrames, numberOfPages;

    printf("\nEnter number of frames: ");
    scanf("%d", &numberOfFrames);

    underlineLength+=3*numberOfFrames;

    printf("\nEnter number of pages: ");
    scanf("%d", &numberOfPages);

    int referenceString[numberOfPages];

    printf("\nEnter reference String: ");
    for(int i =0; i<numberOfPages; i++){
        scanf("%1d", &referenceString[i]);
    }

    fcfs(referenceString, numberOfPages, numberOfFrames);

    optimal(referenceString, numberOfPages, numberOfFrames);

    lru(referenceString, numberOfPages, numberOfFrames);

    mru(referenceString, numberOfPages, numberOfFrames);
}

void printFrames(int * arr, int length){
    for(int i=0; i<length; i++){
        printf("%d ", arr[i]);
    }
}

int hitOrMiss(int * frames, int numberOfFrames, int key){
    for(int i = 0; i<numberOfFrames; i++){
        if(frames[i] == key){
            return i;
        }
    }
    return -1;
}

int findToReplaceIndex(int* frames, int numberOfFrames, int * referenceString, int numberOfPages, int currentReferenceIndex){
    int framesFound[numberOfFrames];
    memset(framesFound, 100, numberOfFrames*sizeof(int));
    int flag=0;

    for(int i=0; i<numberOfFrames; i++){
        if(frames[i]==-1){
            return i;
        }
        for(int j=currentReferenceIndex; j<numberOfPages; j++){
            if(frames[i]==referenceString[j]){
                framesFound[i]=j;
                break;
            }
        }
    }

    int largest = 0;
    for(int i=0; i<numberOfFrames; i++){
        if(framesFound[i]>framesFound[largest]){
            largest = i;
        }
    }
    return largest;
}

struct frames * createQ(int numberOfFrames){
    struct frames * front, * rear, * temp, *head;
    front=NULL;
    for(int i=0; i<numberOfFrames; i++){
        temp = (struct frames *) malloc(sizeof(struct frames));
        temp->index=i;
        if(front == NULL){
            front = temp;
            rear = temp;
        }else{
            rear->next=temp;
            rear=temp;
        }

    }
    rear->next=front;

    return rear;    
}

void updateAccess(struct frames ** front, struct frames ** rear, int index){
    struct frames * temp, *traverse;
    if(index == (*front)->index){
        (*front) = (*front)->next;
        (*rear) = (*rear)->next;
    }else{
        traverse=(*front);
        do{
            if(index == traverse->next->index){
                temp = traverse->next;
                traverse->next = temp->next;
                (*rear)->next=temp;
                temp->next=(*front);
                (*rear)=temp;
                break;
            }
            traverse=traverse->next;
        }while(traverse!=(*front));
    }
}

void printSummary(int pageFaults){
    printf("\n\n\tTOTAL PAGE FAULTS: %d\t\n", pageFaults);
}

void fcfs(int * referenceString, int numberOfPages, int numberOfFrames){
    int pageFaults = 0;
    
    printf("\n\tFCFS\n\t");
    for(int i = 0; i<underlineLength; i++){
        printf("=");
    }
    printf("\n");
    int frames[numberOfFrames];
    memset(frames, -1, numberOfFrames*sizeof(int));
    int currentFrame=0;
    for(int i=0; i<numberOfPages; i++){
        printf("\n\tReference Key: %d\t", referenceString[i]);
        if(hitOrMiss(frames, numberOfFrames, referenceString[i])==-1){
            printf("Page Fault\tFrames: ");
            pageFaults++;

            frames[currentFrame]=referenceString[i];
            currentFrame=(currentFrame+1)%numberOfFrames;
            
            printFrames(frames, numberOfFrames);
        }
        else{
            printf("Hit");
        }
    }
    printSummary(pageFaults);
    printf("\n");
}

void optimal(int * referenceString, int numberOfPages, int numberOfFrames){
    int pageFaults=0;
    
    printf("\n\tOptimal\n\t");
    for(int i=0; i<underlineLength; i++){
        printf("=");
    }
    printf("\n");

    int frames[numberOfFrames];
    memset(frames, -1, numberOfFrames*sizeof(int));

    for (int i = 0; i < numberOfPages; i++){
        printf("\n\tReference Key: %d\t", referenceString[i]);
        if(hitOrMiss(frames, numberOfFrames, referenceString[i])==-1){
            printf("Page Fault\tFrames: ");
            pageFaults++;

            frames[findToReplaceIndex(frames, numberOfFrames, referenceString, numberOfPages, i+1)]=referenceString[i];
            printFrames(frames, numberOfFrames);
        }else{
            printf("Hit");
        }
    }
    printSummary(pageFaults);
    printf("\n");
}

void lru(int * referenceString, int numberOfPages, int numberOfFrames){
    int pageFaults=0;
    
    printf("\n\tLeast Recently Used\n\t");
    for(int i=0; i<underlineLength; i++){
        printf("=");
    }

    int frames[numberOfFrames];
    memset(frames, -1, numberOfFrames*sizeof(int));

    struct frames * rear, *front, *traverse;
    rear = createQ(numberOfFrames);
    front=rear->next;

    printf("\n");
    
    for (int i = 0; i < numberOfPages; i++){
        printf("\n\tReference Key: %d\t", referenceString[i]);
        int result = hitOrMiss(frames, numberOfFrames, referenceString[i]);
        if(result==-1){
            printf("Page Fault\tFrames: ");
            pageFaults++;

            frames[front->index] = referenceString[i];
            front=front->next;
            rear=rear->next;
            printFrames(frames, numberOfFrames);
        }else{
            updateAccess(&front, &rear, result);
            printf("Hit");
        }
    }
    printSummary(pageFaults);
    printf("\n");
}

void mru(int * referenceString, int numberOfPages, int numberOfFrames){
    int pageFaults=0, mostRecent=0;
    
    printf("\n\tMost Recently Used\n\t");
    for(int i=0; i<underlineLength; i++){
        printf("=");
    }

    int frames[numberOfFrames];
    memset(frames, -1, numberOfFrames*sizeof(int));

    printf("\n");
    
    for (int i = 0; i < numberOfPages; i++){
        printf("\n\tReference Key: %d\t", referenceString[i]);

        int result = hitOrMiss(frames, numberOfFrames, referenceString[i]);
        if(result==-1){
            printf("Page Fault\tFrames: ");
            pageFaults++;

            frames[mostRecent] = referenceString[i];
            if(frames[mostRecent+1]==-1){
                mostRecent++;
            }
            
            printFrames(frames, numberOfFrames);
        }else{
            mostRecent = result;
            printf("Hit");
        }
    }
    printSummary(pageFaults);
    printf("\n");
}