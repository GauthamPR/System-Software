#include<stdio.h>
#include<stdlib.h>

const int maxBuffer = 4;
int buffer[4];
int empty = 4;
int full = 0;
int mutex = 1;

void producer();
void consumer();
void wait(int *);
void signal(int *);
void printBuffer();

void main(){
    int option;
    while(1){
        printf("\nEnter Choice:     1.Producer     2.Consumer      3.Print Buffer       4.Exit :  ");
        scanf("%d", &option);
        switch (option){
            case 1:
                producer();
                break;
            
            case 2:
                consumer();
                break;

            case 3:
                printBuffer();
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

void producer(){
    int produced_item = rand();

    printf("\tPRODUCED %d\n", produced_item);
    wait(&empty);
    wait(&mutex);
    buffer[full] = produced_item;

    signal(&mutex);
    signal(&full);
}

void consumer(){
    wait(&full);
    wait(&mutex);

    buffer[full] = 0;
    printf("\tCONSUMED\n");

    signal(&mutex);
    signal(&empty); 
}

void wait(int *s){
    if((*s)<=0){

        if(empty == 0){
            printf("\n\tBUFFER FULL, CONSUMING....");
            consumer();
        }else{
            printf("\n\tBUFFER EMPTY, PRODUCING....");
            producer();
        }
        
    }
    (*s)--;
}

void signal(int *s){
    (*s)++;
}

void printBuffer(){
    printf("Buffer:");
    for(int i=0; i<maxBuffer; i++){
        printf(" %d", buffer[i]);
    }
    printf("\n");
}