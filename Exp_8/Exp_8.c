#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define maxRows 10
#define labelSize 10
#define initialTableValue "$EMPTY"

struct elem{
    char label[labelSize];
    int address;
    struct elem* next;
}table[maxRows];

void initTables();
void enterValues();
void searchValues();
void insertIntoTable(int, char *, int);
int hash(char *);

void main(){
    int option;
    printf("\nEnter Option:\t1.Enter Values\t2.Search Values\t3.Exit:\t");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        enterValues();
        break;
    case 2:
        searchValues();
        break;
    case 3:
        exit(1);
        break;
    default:
        break;
    }
}

void enterValues(){
    char label[labelSize];
    int address, key;
    initTables();
    while(1){
    printf("\n\tEnter Label Name:\t");
    scanf("%s", label);
    printf("\tEnter Address:\t");
    scanf("%d", &address);
    printf("Label Value: %s     Address Value: %d\n", label, address);
    key = hash(label);
    insertIntoTable(key, label, address);
    return ;
}

int hash(char * label){
    char traverse = label[0];
    int sumOfChars = 0;
    int i = 0;
    while(traverse!='\0'){
        sumOfChars += traverse;
        traverse = label[++i];
    }
    int key = (sumOfChars*i) % maxRows;
    return key;printf("%c", traverse);
}

void searchValues(){
    return;
}
void insertIntoTable(int key, char * label, int address){
    if(table[key].label == initialTableValue){
        strcpy(table[key].label, label);
        table[key].address = address;
        printf("\nValues inserted directly");
    }else{
        struct elem* traverse = table->next;
        while(traverse!=NULL){
            if(strcmp(label, table[key].label)==0){
                printf("\nLABEL ALREADY EXISTS");
                break;
            }else{
                struct elem * newElem = (struct elem *)malloc(sizeof(struct elem));
                strcpy(newElem->label, label);
                newElem->address = address;
                newElem->next = NULL;
                table[key].next = newElem;
            }
            traverse = traverse->next;
        }
    }
}
void initTables(){
    for(int i=0; i<maxRows; i++){
        strcpy(table[i].label, initialTableValue);
    }
}