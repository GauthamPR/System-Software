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

    source = fopen("./src/source2.txt", "r");
    symTab = fopen("symTab.txt", "w+");
    opTab = fopen("./bin/opTab.txt", "r");
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
        writeTo(locCtr, intermediate);
        if(strcmp(lineBuffer.label, "**")!=0){
            if(search(lineBuffer.label, symTab)){
                printf("\nLABEL ALREADY EXISTS: %s", lineBuffer.label);
            }else{
                insertInto(symTab, lineBuffer.label, locCtr);
            }
        }
        if(strcmp(lineBuffer.opcode, "WORD")==0){
            locCtr += 3;
        }else if(strcmp(lineBuffer.opcode, "RESW")==0){
            locCtr += (3 * atoi(lineBuffer.operand));
        }else if(strcmp(lineBuffer.opcode, "RESB")==0){
            locCtr += atoi(lineBuffer.operand);
        }else if(strcmp(lineBuffer.opcode, "BYTE")==0){
            length = strlen(lineBuffer.operand) - 3;
            locCtr += length;
        }else{
            if(search(lineBuffer.opcode, opTab)==1){
                locCtr += 3;
            }else{
                printf("\nINVALID OPERATION CODE: %s", lineBuffer.opcode);
            }
        }
        readFrom(source);
    }
    
    writeTo(0, intermediate);
    pgmLength = locCtr-startingAddress;

    fclose(source);
    fclose(symTab);
    fclose(opTab);
    fclose(intermediate);
    printf("\nPASS 1 SUCCESSFUL");
    return ;
}

void readFrom(FILE * fin){
    fscanf(fin, "%s %s %s", lineBuffer.label, lineBuffer.opcode, lineBuffer.operand);
}

void writeTo(int locCtr, FILE * fout){
    fprintf(fout, "%d %s %s %s\n", locCtr, lineBuffer.label, lineBuffer.opcode, lineBuffer.operand);
}
void insertInto(FILE * file, char * label, int locCtr){
    fseek(file, 0, SEEK_END);
    fprintf(file, "%s %d\n", label, locCtr);
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