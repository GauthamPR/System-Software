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
}textRecord;

void readFrom(FILE *);
void writeTo(FILE *);
int search(char * key, FILE *);
void initializeTextRecord(int);

void main(){
    char programName[8];
    char temp[10];
    int outLineCounter=0;

    int startingAddress, locCtr, length, pgmLength;
    FILE *output, *intermediate, *symTab, *opTab, *variables;

    symTab = fopen("../bin/symTab.txt", "r");
    opTab = fopen("../bin/opTab.txt", "r");
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
    fprintf(output, "H%6s%6X%6X\n", programName, startingAddress, pgmLength);
    initializeTextRecord(startingAddress);
    while(strcmp(lineBuffer.opcode, "END")!=0){
        if(search(lineBuffer.opcode, opTab)!=-1){
            if(lineBuffer.operand != NULL){
                textRecord.opcode[outLineCounter] = search(lineBuffer.operand, symTab);
                if(textRecord.opcode[outLineCounter]==-1){
                    printf("\nSYMBOL NOT FOUND");
                    exit(1);
                }
            }
        }else if(lineBuffer.opcode == "BYTE" || lineBuffer.opcode == "WORD"){
            //CONVERT
        }
        outLineCounter++;
        textRecord.length = outLineCounter*24;
        if(outLineCounter>9){
            writeTo(output);
        }
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
    fscanf(fin, "%X %s %s %s", lineBuffer.address,lineBuffer.label, lineBuffer.opcode, lineBuffer.operand);
}

void writeTo(FILE * fout){
    fprintf(fout, "T%6X %2X", textRecord.startingAddress, textRecord.length);
    for(int i=0;textRecord.opcode[i]!=0 && i<11;i++){
        fprintf(fout, "%6X",  textRecord.opcode[i]);
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
