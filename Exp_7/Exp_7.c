#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int numberOfChopsticks, numberOfPhilosophers;
int chopsticks[10];

int wait(int *);
void signal(int *);
void initChopsticks();
int tryEat(int);
void stopEat(int);
void printChops();

void main(){
    int philosopherStatus[10];  //0-hungry  1-eating    2-finished
    memset(philosopherStatus, 0, 10*sizeof(int));

    int finishedEating = 0;

    printf("\n\nEnter Number Of Philosophers: ");   //less than 10
    scanf("%d", &numberOfPhilosophers);
    numberOfChopsticks = numberOfPhilosophers;
    initChopsticks();
    printChops();
    while(finishedEating < numberOfPhilosophers){
        for(int i=0; i<numberOfPhilosophers; i++){
            if(philosopherStatus[i] == 0){
                if(tryEat(i) == 1){
                    printf("\n\tPhilosopher %d is Eating", i+1);
                    philosopherStatus[i] = 1;
                }else{
                    printf("\n\tPhilosopher %d is Hungry", i+1);
                }
            }else if(philosopherStatus[i]==1){
                printf("\n\tPhilosopher %d has finished Eating", i+1);
                finishedEating++;
                stopEat(i);
                philosopherStatus[i]=2;
            }else if(philosopherStatus[i]==2){
                printf("\n\tPhilosopher %d has finished Eating", i+1);
            }
            printChops();
            printf("\n");
        }
        printf("\n");
    }
}

int tryEat(int i){
    int blocked = 0;
    if(wait(&chopsticks[i]) == 0){
        blocked++;
    }
    if(wait(&chopsticks[(i+1)%numberOfChopsticks]) == 0){
        blocked += 2;
    }

    if(blocked == 1){
        signal(&chopsticks[(i+1)%numberOfChopsticks]);
        return 0;
    }
    if(blocked == 2){
        signal(&chopsticks[i]);
        return 0;
    }
    if(blocked == 3){
        return 0;
    }
    return 1;
}
void stopEat(int i){
    signal(&chopsticks[i]);
    signal(&chopsticks[(i+1)%numberOfChopsticks]);
}
int wait(int *s){
    if((*s)<=0){
        printf("BLOCKED");
        return 0;
    }
    (*s)--;
    return 1;
}

void signal(int *s){
    (*s)++;
}

void initChopsticks(){
    for(int i=0; i<numberOfChopsticks; i++){
        chopsticks[i] = 1;
    }
}

void printChops(){
    printf("\nChopStick: ");
    for(int i=0; i<numberOfChopsticks; i++){
        printf("%d",chopsticks[i]);
    }
}