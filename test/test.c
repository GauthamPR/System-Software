#include<stdio.h>
#include<conio.h>
#include<string.h>

#define maxRows 10

int hash(char * label){
    char traverse = label[0];
    int sumOfChars = 0;
    int i = 0;
    while(traverse!='\0'){
        sumOfChars += traverse;
        traverse = label[++i];
    }
    int key = (sumOfChars*i) % maxRows;
    return key;
}

void main(){
    char label[10];
    while(1){        
        printf("Enter Label: ");
        scanf("%s", label);
        printf("\n hash Value: %d", hash(label));
    }
}