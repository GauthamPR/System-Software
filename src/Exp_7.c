#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const int maxChopstick = 5;
int chopsticks[5];

void eat();
void wait(int *);
void signal(int *);
void initChopsticks();
int idPrompt();

void main(){
    int option;
    initChopsticks();
    while(1){
        printf("\n\nEnter Choice:     1.Eat     2.Exit :  ");
        scanf("%d", &option);
        switch (option){
            case 1:
                eat(idPrompt());
                break;

            case 2:
                return ;
                break;

            default:
                printf("INVALID OPTION");
                break;
            }
    }
}
int idPrompt(){
    int id;
    printf("\tEnter Philosophser Id: ");
    scanf("%d", &id);
    return id;
}

void eat(int id){
    wait(&chopsticks[id]);
    printf("\n\t\tPicked left Chopstick");
    wait(&chopsticks[(id+1)%maxChopstick]);
    printf("\n\t\tPicked right Chopstick");

    printf("\n\n\t\tEating......");
    printf("\n\n\t\tStopped Eating");
    
    signal(&chopsticks[id]);
    printf("\n\n\t\tPut Down left Chopstick");
    signal(&chopsticks[(id+1)%maxChopstick]);
    printf("\n\t\tPut Down right Chopstick");
}

void wait(int *s){
    while((*s)<=0);
    (*s)--;
}

void signal(int *s){
    (*s)++;
}

void initChopsticks(){
    for(int i=0; i<maxChopstick; i++){
        chopsticks[i] = 1;
    }
}