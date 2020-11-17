#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct line{
    char label[10];
    char opcode[10];
    char operand[10];
}lineBuffer;

void readFrom(FILE *);
void writeTo(int, FILE *);

void main(){
    int startingAddress, locCtr;
    FILE *source, *intermediate;

    source = fopen("source.txt", "r");
    intermediate = fopen("intermediate.txt", "w");

    if(source == NULL){
        printf("\nERROR OPENING FILE");
        exit(1);
    }
    readFrom(source);
    if(strcmp(lineBuffer.opcode, "START")==0){
        startingAddress = lineBuffer.operand;
        locCtr = startingAddress;
        writeTo(locCtr, intermediate);
        readFrom(source);
    }else{
        locCtr = 0;
    }
    while(strcmp(lineBuffer.opcode, "END")!=0){
        if(strcmp(lineBuffer.label, "**")!=0){
            //search symtab
        }
        if(strcmp(lineBuffer.opcode, "WORD")==0){
            locCtr += 3;
        }else if(strcmp(lineBuffer.operand, "RESW")==0){
            locCtr += (3 * lineBuffer.operand[0]);
        }else if(strcmp(lineBuffer.operand, "RESB")==0){
            locCtr += lineBuffer.operand[0];
        }else if(strcmp(lineBuffer.operand, "BYTE")==0){
            //length calculation
        }else{
            //search for opcode in optable 
            //if found 
            //if not found print Error
        }
        writeTo(locCtr, intermediate);
        readFrom(source);
    }
    
    writeTo(NULL, intermediate);

    fclose(source);
    fclose(intermediate);
    return ;
}

void readFrom(FILE * fin){
    fscanf(fin, "%s %s %s", lineBuffer.label, lineBuffer.opcode, lineBuffer.operand);
}

void writeTo(int locCtr, FILE * fout){
    fprintf(fout, "%s %s %s %s", locCtr, lineBuffer.label, lineBuffer.opcode, lineBuffer.operand);
}