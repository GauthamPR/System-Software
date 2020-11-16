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
void writeToFile();
void readFromFile();

void main(){
    int option;
    initTables();
    readFromFile();
    while(1){
        printf("\nEnter Option:\t1.Enter Values\t2.Write to file\t3.Search Values\t4.Exit:\t");
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
            searchValues();
            break;
        case 4:
            exit(1);
        default:
            break;
        }
    }
}

void enterValues(){
    char label[labelSize];
    int address, key;
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
    return key;
}

void searchValues(){
    return;
}
void insertIntoTable(int key, char * label, int address){
    struct elem* traverse = table->next;
    if(strcmp(table[key].label, initialTableValue) == 0){
        strcpy(table[key].label, label);
        table[key].address = address;
        table[key].next = NULL;
        printf("\nValues inserted directly");
    }else{
        if(strcmp(label, table[key].label)==0){
            printf("\nLABEL ALREADY EXISTS");
            return;
        }
        while(traverse!=NULL){
            if(strcmp(label, table[key].label)==0){
                printf("\nLABEL ALREADY EXISTS");
                return;
            }
            traverse = traverse->next;
        }
        struct elem * newElem = (struct elem *)malloc(sizeof(struct elem));
        strcpy(newElem->label, label);
        newElem->address = address;
        newElem->next = NULL;
        traverse = newElem;
        printf("\nValues entered as linked list");
    }
}
void initTables(){
    for(int i=0; i<maxRows; i++){
        strcpy(table[i].label, initialTableValue);
        table[i].next = NULL;
    }
}

void readFromFile(){
    FILE *fptr;
    fptr = fopen("sym.txt", "r");
    if(fptr == NULL){
        printf("\nERROR OPENING FILE ForREAD");
        return ;
    }
    for(int i=0; i<maxRows; i++){
        fread(&table[i], sizeof(struct elem), 1, fptr);
        struct elem * traverse = table[i].next;
        struct elem * prev = &table[i];
        while(traverse != NULL){
            traverse = (struct traverse *) malloc(sizeof(struct elem));
            fread(traverse, sizeof(struct elem), 1, fptr);
            prev->next = traverse;
            prev = prev->next;
        }
    }
    if(fread != 0){
        printf("\nFiles read Successfully");
    }else{
        printf("\nERROR reading Files");
    }
    fclose(fptr);
}

void writeToFile(){
    FILE *fptr;
    fptr = fopen("sym.txt", "w");
    if(fptr == NULL){
        printf("\nERROR OPENING FILE for Write");
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
        printf("\nFiles wrote Successfully");
    }else{
        printf("\nERROR reading Files");
    }
    fclose(fptr);
}