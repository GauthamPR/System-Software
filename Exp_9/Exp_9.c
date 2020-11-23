#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct line{
    char label[10];
    char opcode[10];
    char operand[10];
}inputLine;

void readFrom(FILE *);
void writeTo(int, FILE *);
void insertInto(FILE *, char *, int);
int search(char * key, FILE *);

void main(){
    int startingAddress, locCtr, length, pgmLength;
    FILE *source, *intermediate, *symTab, *opTab, *variables;

    variables = fopen("../bin/var.txt", "w");
    source = fopen("../bin/src/source3.txt", "r");
    symTab = fopen("../bin/symTab.txt", "w+");
    opTab = fopen("../bin/src/opTab.txt", "r");
    intermediate = fopen("../bin/intermediate.txt", "w");

    if(source == NULL){
        printf("\nERROR OPENING FILE");
        exit(1);
    }
    readFrom(source);
    if(strcmp(inputLine.opcode, "START")==0){
        startingAddress = (int)strtol(inputLine.operand, NULL, 16);
        locCtr = startingAddress;
        writeTo(locCtr, intermediate);
        readFrom(source);
    }else{
        locCtr = 0;
    }
    while(strcmp(inputLine.opcode, "END")!=0){
        writeTo(locCtr, intermediate);
        if(strcmp(inputLine.label, "**")!=0){
            if(search(inputLine.label, symTab)){
                printf("\nLABEL ALREADY EXISTS: %s", inputLine.label);
            }else{
                insertInto(symTab, inputLine.label, locCtr);
            }
        }
        if(strcmp(inputLine.opcode, "WORD")==0){
            locCtr += 3;
        }else if(strcmp(inputLine.opcode, "RESW")==0){
            locCtr += (3 * atoi(inputLine.operand));
        }else if(strcmp(inputLine.opcode, "RESB")==0){
            locCtr += atoi(inputLine.operand);
        }else if(strcmp(inputLine.opcode, "BYTE")==0){
            if(inputLine.operand[0]=='C'){
                length = strlen(inputLine.operand) - 3;
            }else if(inputLine.operand[0]=='X'){
                length = strlen(inputLine.operand) - 3;
                length = (length/2) + (length%2);
            }
            locCtr += length;
        }else{
            if(search(inputLine.opcode, opTab)==1){
                locCtr += 3;
            }else{
                printf("\nINVALID OPERATION CODE: %s", inputLine.opcode);
            }
        }
        readFrom(source);
    }
    
    writeTo(0, intermediate);
    pgmLength = locCtr-startingAddress;
    fprintf(variables, "ProgramLength %d", pgmLength);

    fclose(variables);
    fclose(source);
    fclose(symTab);
    fclose(opTab);
    fclose(intermediate);
    printf("\nPASS 1 SUCCESSFUL");
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