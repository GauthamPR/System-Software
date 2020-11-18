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
void insertInto(FILE *, char *, int);
int search(char * key, FILE *);

void main(){
    int startingAddress, locCtr, length, pgmLength;
    FILE *source, *intermediate, *symTab, *opTab;

    source = fopen("source.txt", "r");
    symTab = fopen("symTab.txt", "w+");
    opTab = fopen("opTab.txt", "r");
    intermediate = fopen("intermediate.txt", "w");

    if(source == NULL){
        printf("\nERROR OPENING FILE");
        exit(1);
    }
    readFrom(source);
    if(strcmp(lineBuffer.opcode, "START")==0){
        startingAddress = atoi(lineBuffer.operand);
        locCtr = startingAddress;
        writeTo(locCtr, intermediate);
        readFrom(source);
    }else{
        locCtr = 0;
    }
    while(strcmp(lineBuffer.opcode, "END")!=0){
        if(strcmp(lineBuffer.label, "**")!=0){
            if(search(lineBuffer.label, symTab)){
                printf("\nLABEL ALREADY EXISTS: %s", lineBuffer.label);
            }else{
                insertInto(symTab, lineBuffer.label, locCtr);
            }
        }
        if(strcmp(lineBuffer.opcode, "WORD")==0){
            locCtr += 3;
        }else if(strcmp(lineBuffer.operand, "RESW")==0){
            locCtr += (3 * lineBuffer.operand[0]);
        }else if(strcmp(lineBuffer.operand, "RESB")==0){
            locCtr += lineBuffer.operand[0];
        }else if(strcmp(lineBuffer.operand, "BYTE")==0){
            length = strlen(lineBuffer.operand) - 3;
            locCtr += length;
        }else{
            if(search(lineBuffer.opcode, opTab)==1){
                locCtr += 3;
            }else{
                printf("\nINVALID OPERATION CODE: %s", lineBuffer.opcode);
            }
        }
        writeTo(locCtr, intermediate);
        readFrom(source);
    }
    
    writeTo(0, intermediate);
    pgmLength = locCtr-startingAddress;

    fclose(source);
    fclose(symTab);
    fclose(opTab);
    fclose(intermediate);
    return ;
}

void readFrom(FILE * fin){
    fscanf(fin, "%s %s %s", lineBuffer.label, lineBuffer.opcode, lineBuffer.operand);
}

void writeTo(int locCtr, FILE * fout){
    fprintf(fout, "%d %s %s %s\n", locCtr, lineBuffer.label, lineBuffer.opcode, lineBuffer.operand);
}
void insertInto(FILE * file, char * label, int locCtr){
    fprintf(file, "%s %d\n", label, locCtr);
}
int search(char * key, FILE * file){
    char fileKey[10];
    int fileAddress, ableToRead = 1;
    rewind(file);
    while(ableToRead==1){
        ableToRead = fscanf(file, "%s %d", fileKey, &fileAddress);
        if(strcmp(fileKey, key)==0){
            return 1;
        }
    }
    return 0;
}