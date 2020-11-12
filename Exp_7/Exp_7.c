#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int numberOfChopsticks, numberOfPhilosophers;
int chopsticks[10];

int wait(int *);
void signal(int *);
void initChopsticks();
int startEat(int);
void stopEat(int);
void printChops();

void main(){
    int finishedEating[10];
    memset(finishedEating, 0, 10*sizeof(int));
    int count = 0;
    printf("%d", finishedEating[4]);
    printf("\n\nEnter Number Of Philosophers: ");
    scanf("%d", &numberOfPhilosophers);
    numberOfChopsticks = numberOfPhilosophers;
    initChopsticks();
    while(count < numberOfPhilosophers){
        for(int i=0; i<numberOfPhilosophers; i++){
            printChops();
            if(finishedEating[i] < 2){
                if(startEat(i) == 1){
                    printf("\nPhilosopher %d is eating", i+1);
                    finishedEating[i] = 1;
                }else{
                    printf("\nPhilosopher %d is thinking", i+1);
                    if(finishedEating[i]==1){
                        count++;
                        finishedEating[i]=2;
                    }
                }
            }else{
                printf("\nPhilosopher %d is thinking2", i+1);
            }
            printChops();
            printf("\n");
        }
        printf("\n");
    }
}

int startEat(int i){
    int blocked = 0;
    if(wait(&chopsticks[i]) == 0){
        blocked++;
    }
    if(wait(&chopsticks[(i+1)%numberOfChopsticks]) == 0){
        blocked += 2;
    }

    if(blocked == 0){
        return 1;
    }
    if(blocked == 1){
        signal(&chopsticks[(i+1)%numberOfChopsticks]);
    }
    if(blocked == 2){
        signal(&chopsticks[i]);
        return 0;
    }
    if(blocked == 3){
        printf("\t\t\t\t\tHEHE");
        signal(&chopsticks[i]);
        signal(&chopsticks[(i+1)%numberOfChopsticks]);
        return 0;
    }
}
void stopEat(int i){
    printf("\n\tPhilosopher %d has stopped Eating", i+1);
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
    printChops();
}
void printChops(){
    printf("\nChopStick: ");
    for(int i=0; i<numberOfChopsticks; i++){
        printf("%d",chopsticks[i]);
    }
}