#include<stdio.h>
#include<stdlib.h>

const int lineLength = 57;

void sortQueue(int *, int);
void upSeek(int *, int, int, int *, int *);
void downSeek(int *, int, int, int *, int *);

void fcfs(int *, int, int);
void scan(int *, int, int, int);
void cScan(int *, int, int, int);

void main(){
    int sizeOfQueue, initialHead, maxCylinder;

    printf("\nEnter Size of Queue: ");
    scanf("%d",&sizeOfQueue);

    int queue[sizeOfQueue];

    printf("\nEnter Queue: ");
    for(int i=0; i<sizeOfQueue; i++){
        scanf(" %d", &queue[i]);
    }

    printf("\nEnter Initial head position: ");
    scanf("%d", &initialHead);

    printf("\nEnter Max Cylinder: ");
    scanf("%d", &maxCylinder);

    fcfs(queue, sizeOfQueue, initialHead);

    sortQueue(queue, sizeOfQueue);

    scan(queue, sizeOfQueue, maxCylinder, initialHead);

    cScan(queue, sizeOfQueue, maxCylinder, initialHead);
}

void sortQueue(int * queue, int sizeOfQueue){
    int temp;
    for(int i=0; i<sizeOfQueue; i++){
        for(int k=0; k<(sizeOfQueue-1); k++){
            if(queue[k]>queue[k+1]){
                temp = queue[k];
                queue[k] = queue[k+1];
                queue[k+1] = temp;
            }
        }
    }
    
}

void upSeek(int * queue, int from, int to, int * headerPos, int *totalSeekTime){
    int diff;
    for(int i=from; i<to; i++){
        diff = queue[i] - (*headerPos);
        printf("\n\t%d\t\t\t%d\t\t\t%d", (*headerPos), queue[i], diff);
        (*headerPos) = queue[i];
        (*totalSeekTime) += diff;
    }
}

void downSeek(int * queue, int from, int to, int * headerPos, int *totalSeekTime){
    int diff;
    for(int i=from; i>=to; i--){
        diff = (*headerPos) - queue[i];
        printf("\n\t%d\t\t\t%d\t\t\t%d", (*headerPos), queue[i], diff);
        (*headerPos) = queue[i];
        (*totalSeekTime) += diff;
    }
}

void fcfs(int * queue, int sizeOfQueue, int initialHeadPos){
    int headerPos=initialHeadPos;
    float average;
    int totalSeekTime = 0;
    int diff;
    printf("\n\n\nFCFS");
    printf("\n====");
    printf("\n\n\tInitial Pos\t\tFinal Pos\t\tSeek Time\n\t");
    for(int k=0; k<lineLength; k++){
        printf("-");
    }
    for(int i=0; i<sizeOfQueue; i++){
        diff = abs(queue[i] - headerPos);
        printf("\n\t%d\t\t\t%d\t\t\t%d", headerPos, queue[i], diff);
        headerPos = queue[i];
        totalSeekTime = totalSeekTime + diff;
    }
    average=totalSeekTime/sizeOfQueue;
    printf("\n\nTOTAL TIME: %d", totalSeekTime);
    printf("\nAVERAGE SEEK TIME: %.2f", totalSeekTime/(float)sizeOfQueue);
}

void scan(int * queue, int sizeOfQueue, int maxCylinder, int initialHeadPos){
    int headerPos=initialHeadPos;
    int totalSeekTime = 0;
    int diff, diff1, diff2;
    printf("\n\n\nSCAN");
    printf("\n====");
    printf("\n\n\tInitial Pos\t\tFinal Pos\t\tSeek Time\n\t");
    for(int k=0; k<lineLength; k++){
        printf("-");
    }

    if(headerPos<=queue[0]){
        upSeek(queue, 0, sizeOfQueue, &headerPos, &totalSeekTime);
    }
    else if(headerPos>queue[sizeOfQueue-1]){
        downSeek(queue, sizeOfQueue, 0, &headerPos, &totalSeekTime);
    }
    for(int i=0; i<sizeOfQueue-1; i++){
        if(queue[i]<headerPos && queue[i+1]>headerPos){
            diff1 = abs(queue[i] - headerPos);
            diff2 = abs(queue[i+1] - headerPos);
            if(diff1<diff2){
                downSeek(queue, i, 0, &headerPos, &totalSeekTime);
                
                if(headerPos != 0){
                    diff = headerPos - 0;
                    printf("\n\t%d\t\t\t%d\t\t\t%d", headerPos, 0, diff);
                    headerPos = 0;
                    totalSeekTime = totalSeekTime + diff;
                }

                upSeek(queue, i+1, sizeOfQueue, &headerPos, &totalSeekTime);
            }else{
                upSeek(queue, i+1, sizeOfQueue, &headerPos, &totalSeekTime);
                
                if(headerPos != maxCylinder){
                    diff = maxCylinder - queue[sizeOfQueue-1];
                    printf("\n\t%d\t\t\t%d\t\t\t%d", headerPos, maxCylinder, diff);
                    headerPos = maxCylinder;
                    totalSeekTime = totalSeekTime + diff;
                }

                downSeek(queue, i, 0, &headerPos, &totalSeekTime);
            }
        }
    }
    printf("\n\nTOTAL TIME: %d", totalSeekTime);
    printf("\nAVERAGE SEEK TIME: %.2f", totalSeekTime/(float)sizeOfQueue);
}

void cScan(int * queue, int sizeOfQueue, int maxCylinder, int initialHeadPos){
    int headerPos=initialHeadPos;
    int totalSeekTime = 0;
    int diff, diff1, diff2;
    printf("\n\n\nC-SCAN");
    printf("\n======");
    printf("\n\n\tInitial Pos\t\tFinal Pos\t\tSeek Time\n\t");
    for(int k=0; k<lineLength; k++){
        printf("-");
    }

    if(headerPos<=queue[0]){
        upSeek(queue, 0, sizeOfQueue, &headerPos, &totalSeekTime);
    }
    else if(headerPos>=queue[sizeOfQueue-1]){
        upSeek(queue, 0, sizeOfQueue, &headerPos, &totalSeekTime);
    }
    for(int i=0; i<sizeOfQueue-1; i++){
        if(queue[i]<headerPos && queue[i+1]>headerPos){
            upSeek(queue, i+1, sizeOfQueue, &headerPos, &totalSeekTime);
            
            if(headerPos != maxCylinder){
                diff = maxCylinder - queue[sizeOfQueue-1];
                printf("\n\t%d\t\t\t%d\t\t\t%d", headerPos, maxCylinder, diff);
                headerPos = maxCylinder;
                totalSeekTime = totalSeekTime + diff;
            }

            diff = maxCylinder - 0;
            printf("\n\t%d\t\t\t%d\t\t\t%d", headerPos, 0, diff);
            headerPos = 0;
            totalSeekTime = totalSeekTime + diff;

            upSeek(queue, 0, i+1, &headerPos, &totalSeekTime);
        }
    }
    printf("\n\nTOTAL TIME: %d", totalSeekTime);
    printf("\nAVERAGE SEEK TIME: %.2f", totalSeekTime/(float)sizeOfQueue);
}