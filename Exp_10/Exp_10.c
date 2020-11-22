#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct line{
    int address;
    char label[10];
    char opcode[10];
    char operand[10];
}lineBuffer;

struct outLine{
    int startingAddress;
    int length;
    int opcode[10];
    int operandAdd[10];
}textRecord;

void readFrom(FILE *);
void writeTo(FILE *);
int search(char * key, FILE *);
void initializeTextRecord(int);
int calculateHexValue();

void main(){
    char programName[8];
    char temp[20];
    int outLineCounter=0;
    int found = 0;

    int startingAddress, locCtr, length, pgmLength;
    FILE *output, *intermediate, *symTab, *opTab, *variables;

    symTab = fopen("../bin/symTab.txt", "r");
    opTab = fopen("../bin/src/opTab.txt", "r");
    intermediate = fopen("../bin/intermediate.txt", "r");
    output = fopen("../bin/output.txt", "w");
    variables = fopen("../bin/var.txt", "r");
    if(output == NULL){
        printf("\nERROR OPENING FILE");
        exit(1);
    }

    readFrom(intermediate);
    if(strcmp(lineBuffer.opcode, "START")==0){
        strcpy(programName, lineBuffer.label);    
        startingAddress = (int)strtol(lineBuffer.operand, NULL, 16);
        fscanf(variables, "%s %d", temp, &pgmLength);
        readFrom(intermediate);
    }
    fprintf(output, "H%-6s%006X%6X\n", programName, startingAddress, pgmLength);
    initializeTextRecord(startingAddress);
    while(strcmp(lineBuffer.opcode, "END")!=0){
        textRecord.length = (outLineCounter+1)*24;
        found = search(lineBuffer.opcode, opTab);
        if(found!=-1){
            textRecord.opcode[outLineCounter] = found;
            if(lineBuffer.operand != NULL){
                found = search(lineBuffer.operand, symTab);
                if(textRecord.opcode[outLineCounter]==-1){
                    printf("\nSYMBOL NOT FOUND");
                    exit(1);
                }
                else{
                    textRecord.operandAdd[outLineCounter] = found;
                }
            }
        }else if(lineBuffer.opcode == "BYTE"){
            if(lineBuffer.operand[0]=='C'){
                textRecord.operandAdd[outLineCounter] = calculateHexValue();
            }else if(lineBuffer.operand[0]=='X'){
                int tempStr[3];
                for(int i=2;lineBuffer.operand[i]!='\'';i++){
                    tempStr[i-2] = lineBuffer.operand[i];
                }
                textRecord.operandAdd[outLineCounter] = (int)strtol(tempStr, NULL, 15);
            }
        }else if(lineBuffer.opcode == "WORD"){
            textRecord.operandAdd[outLineCounter] = (int)strtol(lineBuffer.operand, NULL, 15);
        }
        outLineCounter++;
        if(outLineCounter>9){
            writeTo(output);
            outLineCounter = 0;
        }
        readFrom(intermediate);
    }
    if(outLineCounter < 10){
        writeTo(output);
        outLineCounter = 0;
    }

    fclose(variables);
    fclose(output);
    fclose(symTab);
    fclose(opTab);
    fclose(intermediate);
    printf("\nPASS 2 SUCCESSFUL");
    return ;
}

void initializeTextRecord(int address){
    textRecord.startingAddress = address;
    textRecord.length = 0;
    memset(textRecord.opcode, -1, 10*sizeof(int));
}
void readFrom(FILE * fin){
    fscanf(fin, "%X %s %s %s", &lineBuffer.address ,lineBuffer.label, lineBuffer.opcode, lineBuffer.operand);
}

void writeTo(FILE * fout){
    fprintf(fout, "T%6X%2X", textRecord.startingAddress, textRecord.length);
    for(int i=0;textRecord.opcode[i]!=-1 && i<11;i++){
        fprintf(fout, "%2X%4X", textRecord.opcode[i], textRecord.operandAdd[i]);
    }
    fprintf(fout, "\n");
}
int search(char * key, FILE * file){
    char fileKey[10];
    int fileKeyValue;
    rewind(file);
    while(fscanf(file, "%s %X", fileKey, &fileKeyValue)!=-1){
        if(strcmp(fileKey, key)==0){
            return fileKeyValue;
        }
    }
    return -1;
}
int calculateHexValue(){
    FILE * fptr;
    fptr = fopen("text.txt", "w+");
    for(int i=2; lineBuffer.operand[i]!='\'';i++){
        fprintf(fptr,"%2X", lineBuffer.operand[i]);
    }
    fclose(fptr);
    fptr = fopen("text.txt", "r");
    int val ;
    fscanf(fptr, "%X", &val);
    fclose(fptr);
    return val;
}
