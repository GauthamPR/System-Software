#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int numberOfChopsticks, numberOfPhilosophers;
int chopsticks[5];

struct Process{
    int id;
    struct Process * next;
}ready;

void wait(int *);
void signal(int *);
void initChopsticks();
void tryEat(int);

void main(){
    printf("\n\nEnter Number Of Philosophers: ");
    scanf("%d", &numberOfPhilosophers);
    initChopsticks();
    while(traverse != NULL){
        
    }
}

void tryEat(int i){
    printf("\n\tPhilosopher %d has stopped Thinking", i+1);
    
    wait(&chopsticks[i]);
    wait(&chopsticks[(i+1)%numberOfChopsticks]);
    
    printf("\n\tPhilosopher %d has started Eating", i+1);
    printf("\n\tPhilosopher %d has stopped Eating", i+1);
    signal(&chopsticks[i]);
    signal(&chopsticks[(i+1)%numberOfChopsticks]);
}

void wait(int *s){
    if((*s)<=0){
        struct Process * new = (struct Process *) malloc(sizeof(struct Process));

    }
    (*s)--;
}

void signal(int *s){
    (*s)++;
}

void initChopsticks(){

    for(int i=0; i<numberOfChopsticks; i++){
        chopsticks[i] = 1;
    }
}