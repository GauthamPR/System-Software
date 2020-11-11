#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const int maxChopstick = 5;
int chopsticks[5];

int idPrompt();
void startEat(int);
void stopEat(int);
void wait(int *);
void signal(int *);
void printChopsticks();
void first();

void main(){
    int option;
    first();
    printf(" %d", chopsticks[0]);
    while(1){
        printf("\nEnter Choice:     1.Start Eating     2.Stop Eating      3.Print Chopsticks       4.Exit :  ");
        scanf("%d", &option);
        switch (option){
            case 1:
                startEat(idPrompt());
                break;
            
            case 2:
                stopEat(idPrompt());
                break;

            case 3:
                printChopsticks();
                break;
            
            case 4:
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
    printf("Enter philosophser Id: ");
    scanf("%d", &id);
    return id;
}

void startEat(int id){
    printf("Started Eating");
    wait(&chopsticks[id]);
    wait(&chopsticks[(id+1)%maxChopstick]);
}

void stopEat(int id){
    signal(&chopsticks[id]);
    signal(&chopsticks[(id+1)%maxChopstick]); 
}

void wait(int *s){
    if((*s)<=0){
        printf("\nChopstick Not free");
        return ;
    }
    (*s)--;
}

void signal(int *s){
    (*s)++;
}

void printChopsticks(){
    printf("Buffer:");
    for(int i=0; i<maxChopstick; i++){
        printf(" %d", chopsticks[i]);
    }
    printf("\n");
}
void first(){
    for(int i=0; i<maxChopstick; i++){
        chopsticks[i] = 1;
    }
}