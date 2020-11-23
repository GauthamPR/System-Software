#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define maxRows 20
#define labelSize 10
#define initialLabelValue "$EMPTY"

struct line{
    char label[10];
    char opcode[10];
    char operand[10];
}inputLine;

struct elem{
    char label[labelSize];
    int address;
    struct elem* next;
}symTab[maxRows];

struct outLine{
    int startingAddress;
    int operand;
    int opcode;
    int objcode;
}outputLine;

void readFrom(FILE *);
void writeTo(int, FILE *);
void insertIntoSymTab(char *, int);
int search(char * key, FILE *);
void setSymbolValue(char *, int );

void main(){
    int startingAddress, locCtr, found;
    FILE *source, *opTab;

    source = fopen("../bin/src/source4.txt", "r");
    opTab = fopen("../bin/src/opTab.txt", "r");

    if(source == NULL){
        printf("\nERROR OPENING FILE");
        exit(1);
    }

    readFrom(source);
    if(strcmp(inputLine.opcode, "START")==0){
        startingAddress = (int)strtol(inputLine.operand, NULL, 16);
        locCtr = startingAddress;
        readFrom(source);
    }else{
        locCtr = 0;
    }
    while(strcmp(inputLine.opcode, "END")!=0){
        if(strcmp(inputLine.label, "**")!=0){
            found = searchSymTab(inputLine.label);
            if(found!=-1){
                if(found == -2){
                    setSymbolValue(inputLine.label, locCtr);
                    //set and delete
                }
            }else{
                insertIntoSymTab(inputLine.label, locCtr);
            }
        }
        found = searchOpTab();
        if(found!=-1){
            found = searchSymTab(inputLine.operand);
            if(found!=-1){
                if(found != NULL){
                    outputLine.operand = found;
                }
                else{
                    addToList(locCtr);
                }
            }else{
                insertIntoSymTab(inputLine.operand, -2);
            }
            locCtr += 3;
        }else if(strcmp(inputLine.opcode, "WORD")==0){
            locCtr += 3;
            outputLine.operand = atoi(inputLine.operand);
        }else if(strcmp(inputLine.opcode, "RESW")==0){
            locCtr += 3*(atoi(inputLine.operand));
        }else if(strcmp(inputLine.opcode, "RESB")==0){
            locCtr += atoi(inputLine.operand);
        }else if(strcmp(inputLine.opcode, "BYTE")==0){
             if(inputLine.operand[0]=='C'){
                locCtr += (strlen(inputLine.operand)-3);
                outputLine.operand = calculateHexValue();
            }else if(inputLine.operand[0]=='X'){
                char tempStr[3];
                for(int i=2;inputLine.operand[i]!='\'';i++){
                    tempStr[i-2] = inputLine.operand[i];
                }
                locCtr += (strlen(tempStr)/2);
                outputLine.operand = calculateIntValue();
            }
        }
    }
    
    fclose(opTab);
    fclose(source);
    printf("\nASSEMBLE SUCCESSFUL");
    return ;
}

void readFrom(FILE * fin){
    fscanf(fin, "%s %s %s ", inputLine.label, inputLine.opcode, inputLine.operand);
}

void writeTo(int locCtr, FILE * fout){
    fprintf(fout, "%4X %s %s %s\n", locCtr, inputLine.label, inputLine.opcode, inputLine.operand);
}
void insertInto(FILE * file, char * label, int locCtr){
    fseek(file, 0, SEEK_END);
    fprintf(file, "%s %4X\n", label, locCtr);
}
void insertIntoSymTab(char * label, int value){
    for(int i=0; i<maxRows; i++){
        if(strcmp(symTab[i].label, initialLabelValue) == 0){
            strcpy(symTab[i].label, label);
            symTab[i].address = value;
            symTab[i].next = NULL;
            printf("\tVALUES INSERTED\n");
        }
    }       
}
void setSymbolValue(char * label, int value){
    for(int i=0; i<maxRows; i++){
        if(strcmp(symTab[i].label, label)==0){
            symTab[i].address = value;
        }
    }
}
int searchSymTab(char * label){
    for(int i=0; i<maxRows; i++){
        if(strcmp(symTab[i].label, label)==0){
            return symTab[i].address;
        }
    }
    return -1;
}
int search(char * key, FILE * file){
    char fileKey[10];
    int fileKeyValue;
    rewind(file);
    while(fscanf(file, "%s %d", fileKey, &fileKeyValue)!=-1){
        if(strcmp(fileKey, key)==0){
            return 1;
        }
    }
    return 0;
}