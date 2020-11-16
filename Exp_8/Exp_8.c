#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define maxRows 10
#define labelSize 10
#define initialLabelValue "$EMPTY"

struct elem{
    char label[labelSize];
    int address;
    struct elem* next;
}table[maxRows];

void enterValues();
void insertIntoTable(int, char *, int);
int hash(char *);
void searchValue();
void display();

void initTables();
void writeToFile();
void readFromFile();

void main(){
    int option;
    initTables();
    readFromFile();
    while(1){
        printf("\nEnter Option:\t1.Enter Values\t\t2.Write to file\t\t3.Search\t4.Display:\t5.Exit:\t");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            enterValues();
            break;
        case 2:
            writeToFile();
            break;
        case 3:
            searchValue();
            break;
        case 4:
            display();
            break;
        case 5:
            exit(1);
            break;
        default:
            break;
        }
    }
}
void enterValues(){
    char label[labelSize];
    int address, key;

    printf("\n\tEnter Label Name: ");
    scanf("%s", label); 
    printf("\tEnter Address: ");
    scanf("%d", &address);

    key = hash(label);
    insertIntoTable(key, label, address);
    return ;
}
void insertIntoTable(int key, char * label, int address){
    if(strcmp(table[key].label, initialLabelValue) == 0){
        strcpy(table[key].label, label);
        table[key].address = address;
        table[key].next = NULL;
        printf("\tVALUES INSERTED\n");
    }else{
        struct elem* traverse = table;
        if(strcmp(label, table[key].label)==0){
            printf("\tLABEL ALREADY EXISTS\n");
            return;
        }
        while(traverse->next!=NULL){
            if(strcmp(label, table[key].label)==0){
                printf("\tLABEL ALREADY EXISTS\n");
                return;
            }
            traverse = traverse->next;
        }
        struct elem * newElem = (struct elem *)malloc(sizeof(struct elem));
        strcpy(newElem->label, label);
        newElem->address = address;
        newElem->next = NULL;
        traverse->next = newElem;
        printf("\tVALUES INSERTED\n");
    }
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
    return key;
}
void display(){
    printf("\n\tLabel\t\t\tAddress");
    printf("\n\t======\t\t\t========\n")    ;
    for(int i=0; i<maxRows; i++){
        if(strcmp(table[i].label, initialLabelValue)==0){
            continue;
        }
        struct elem *traverse = &table[i];
        while(traverse != NULL){
            printf("\t%s\t\t\t%d\n", traverse->label, traverse->address);
            traverse = traverse->next;
        }
    }
}
void searchValue(){
    char searchKey[labelSize];
    printf("\n\tEnter Label to Search for: ");
    scanf("%s", searchKey);
    for(int i=0; i<maxRows; i++){
        if(strcmp(table[i].label, initialLabelValue)==0){
            continue;
        }
        struct elem *traverse = &table[i];
        while(traverse != NULL){
            if(strcmp(traverse->label, searchKey)==0){
                printf("\tAddress: %d\n", traverse->address);
                return;
            }
            traverse = traverse->next;
        }
    }
    printf("\n\tLABEL NOT FOUND\n");
    return;
}

void initTables(){
    for(int i=0; i<maxRows; i++){
        strcpy(table[i].label, initialLabelValue);
        table[i].next = NULL;
    }
}

void readFromFile(){
    FILE *fptr;
    fptr = fopen("sym.txt", "r");
    if(fptr == NULL){
        printf("\nERROR OPENING FILE FOR READ");
        return ;
    }
    for(int i=0; i<maxRows; i++){
        fread(&table[i], sizeof(struct elem), 1, fptr);
        struct elem * traverse = &table[i];
        struct elem * prev = &table[i];
        while(traverse->next != NULL){
            traverse = (struct traverse *) malloc(sizeof(struct elem));
            fread(traverse, sizeof(struct elem), 1, fptr);
            prev->next = traverse;
            prev = prev->next;
        }
    }
    if(fread != 0){
        printf("\nFILE READ SUCCESSFULLY");
    }else{
        printf("\nERROR READING FILE");
    }
    fclose(fptr);
}

void writeToFile(){
    FILE *fptr;
    fptr = fopen("sym.txt", "w");
    if(fptr == NULL){
        printf("\nERROR OPENING FILE FOR WRITE\n");
        return ;
    }
    for(int i=0; i<maxRows; i++){
        fwrite(&table[i], sizeof(struct elem), 1, fptr);
        struct elem * traverse = table[i].next;
        while(traverse != NULL){
            fwrite(traverse, sizeof(struct elem), 1, fptr);
            traverse = traverse->next;
        }
    }
    if(fwrite != 0){
        printf("\n\tWROTE TO FILE SUCCESSFULLY\n");
    }else{
        printf("\nERROR WRITIING FILE\n");
    }
    fclose(fptr);
}