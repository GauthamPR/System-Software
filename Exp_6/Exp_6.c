#include<stdio.h>
#include<stdlib.h>

const int bufferSize = 4;
int buffer[4];
int empty = 4;
int full = 0;
int mutex = 1;

void produce();
void consume();
void wait(int *);
void signal(int *);
void printBuffer();

void main(){
    int option;
    while(1){
        printf("\nEnter Choice:     1.Produce     2.Consume      3.Print Buffer       4.Exit :  ");
        scanf("%d", &option);
        switch (option){
            case 1:
                produce();
                break;
            
            case 2:
                consume();
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

void produce(){
    int produced_item = rand();

    printf("\tPRODUCED %d\n", produced_item);
    wait(&empty);
    wait(&mutex);
    buffer[full] = produced_item;

    signal(&mutex);
    signal(&full);
}

void consume(){
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
            consume();
        }else{
            printf("\n\tBUFFER EMPTY, PRODUCING....");
            produce();
        }
        
    }
    (*s)--;
}

void signal(int *s){
    (*s)++;
}

void printBuffer(){
    printf("Buffer:");
    for(int i=0; i<bufferSize; i++){
        printf(" %d", buffer[i]);
    }
    printf("\n");
}