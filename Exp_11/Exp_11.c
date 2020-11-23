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
    int operand[10];
    int opcode[10];
    int objcode;
    int length;
}outputLine;

void readFrom(FILE *);
void writeTo(FILE *);
void insertIntoSymTab(char *, int);
int searchSymTab(char *);
int search(char * key, FILE *);
void setSymbolValueAndReplaceOperand(char *, int );
void initTables();
int searchOpTab();
void addToList(char *, int);
int calculateHexValue();
int calculateIntValue();

void main(){
    int startingAddress, locCtr, found, recCtr=0, first;
    char pgmName[8];
    FILE *source, *opTab, *output;
    initTables();

    source = fopen("../bin/src/source4.txt", "r");
    opTab = fopen("../bin/src/opTab.txt", "r");
    output = fopen("../bin/output.txt", "w");

    if(source == NULL){
        printf("\nERROR OPENING FILE");
        exit(1);
    }

    readFrom(source);
    if(strcmp(inputLine.opcode, "START")==0){
        startingAddress = (int)strtol(inputLine.operand, NULL, 16);
        strcpy(pgmName, inputLine.label);
        locCtr = startingAddress;
        readFrom(source);
    }else{
        locCtr = 0;
    }
    fprintf(output, "H%-6s%0000006X\n", pgmName, startingAddress);
    while(strcmp(inputLine.opcode, "END")!=0){
        if(strcmp(inputLine.label, "**")!=0){
            if(strcmp(inputLine.label, "FIRST")==0){
                first = locCtr;
            }
            found = searchSymTab(inputLine.label);
            if(found!=-1){
                if(found == -2){
                    setSymbolValueAndReplaceOperand(inputLine.label, locCtr);
                }
            }else{
                insertIntoSymTab(inputLine.label, locCtr);
            }
        }
        found = searchOpTab(inputLine.opcode, opTab);
        if(found!=-1){
            outputLine.opcode[recCtr] = found;
            found = searchSymTab(inputLine.operand);
            if(found!=-1){
                outputLine.operand[recCtr] = found;
                if(found != -2){
                    outputLine.operand[recCtr] = found;
                }
                else{
                    addToList(inputLine.operand, recCtr);
                }
            }else{
                insertIntoSymTab(inputLine.operand, -2);
                addToList(inputLine.operand, recCtr);
            }
            locCtr += 3;
        }else if(strcmp(inputLine.opcode, "WORD")==0){
            locCtr += 3;
            outputLine.opcode[recCtr] = -2;
            outputLine.operand[recCtr] = atoi(inputLine.operand);
        }else if(strcmp(inputLine.opcode, "RESW")==0){
            outputLine.opcode[recCtr] = -4;
            locCtr += 3*(atoi(inputLine.operand));
        }else if(strcmp(inputLine.opcode, "RESB")==0){
            locCtr += atoi(inputLine.operand);
        }else if(strcmp(inputLine.opcode, "BYTE")==0){
             if(inputLine.operand[0]=='C'){
                locCtr += (strlen(inputLine.operand)-3);
                outputLine.operand[recCtr] = calculateHexValue();
            }else if(inputLine.operand[0]=='X'){
                char tempStr[3];
                for(int i=2;inputLine.operand[i]!='\'';i++){
                    tempStr[i-2] = inputLine.operand[i];
                }
                locCtr += (strlen(tempStr)/2);
                outputLine.operand[recCtr] = calculateIntValue();
            }
        }
        recCtr++;
        if(recCtr>9){
            outputLine.length = locCtr-outputLine.startingAddress;
            writeTo(output);
            recCtr = 0;
        }
        readFrom(source);
    }
    outputLine.length = locCtr-outputLine.startingAddress;
    writeTo(output);

    fprintf(output, "E%0000006X", first);
    fclose(opTab);
    fclose(source);

    fseek(output, 13, SEEK_SET);
    fprintf(output, " %000000X\n", locCtr - startingAddress);
    fclose(output);
    printf("\nASSEMBLE SUCCESSFUL");
    return ;
}

void addToList(char * symbol, int addr){
    int i;
    for(i=0; i<maxRows; i++){
        if(strcmp(symTab[i].label, symbol)==0){
            break;
        }
    }
    struct elem * new = (struct elem *) malloc(sizeof(struct elem));
    new->address = addr;
    new->next = NULL;
    symTab[i].next = new;
}
void readFrom(FILE * fin){
    fscanf(fin, "%s %s %s ", inputLine.label, inputLine.opcode, inputLine.operand);
}

void writeTo(FILE * fout){
    fprintf(fout, "T %0000006X %002X", outputLine.startingAddress, outputLine.length);
    int byteCounter = 0;
    for(int i=0;byteCounter<outputLine.length && i<10;i++){
        if(outputLine.opcode[i] == -2){
            byteCounter +=3 ;
            fprintf(fout, " %0000006X", outputLine.operand[i]);
        }else if(outputLine.opcode[i] == -3){
            byteCounter += 1;
            fprintf(fout, " %002X", outputLine.operand[i]);
        }else if(outputLine.opcode[i] == -4){
            byteCounter += 3;
            fprintf(fout, " ______");
        }
        else{
            byteCounter += 3;
            fprintf(fout, " %002X%00004X", outputLine.opcode[i], outputLine.operand[i]);
        }
    }
    fprintf(fout, "\n");
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
            return;
        }
    }       
}
void setSymbolValueAndReplaceOperand(char * label, int value){
    int i=0;
    for(i=0; i<maxRows; i++){
        if(strcmp(symTab[i].label, label)==0){
            symTab[i].address = value;
            break;
        }
    }
    struct elem * traverse = symTab[i].next;
    while(traverse != NULL){
        outputLine.operand[traverse->address] = value;
        traverse = traverse->next;
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
int searchOpTab(char * key, FILE * file){
    int flag = 1;
    for(int i=0; i<strlen(key); i++){
        if(key[i] == ','){
            key[i] = '\0';
            flag = 0;
        }
    }
    char fileKey[10];
    int fileKeyValue;
    rewind(file);
    while(fscanf(file, "%s %X", fileKey, &fileKeyValue)!=-1){
        if(strcmp(fileKey, key)==0){
            if(flag == 0){
                return (fileKeyValue+(8*4096));
            }
            return fileKeyValue;
        }
    }
    return -1;
}
void initTables(){
    for(int i=0; i<maxRows; i++){
        strcpy(symTab[i].label, initialLabelValue);
        symTab[i].next = NULL;
    }
}
int calculateHexValue(){
    FILE * fptr;
    fptr = fopen("text.txt", "w+");
    for(int i=2; inputLine.operand[i]!='\'';i++){
        fprintf(fptr,"%2X", inputLine.operand[i]);
    }
    fclose(fptr);
    fptr = fopen("text.txt", "r");
    int val ;
    fscanf(fptr, "%X", &val);
    fclose(fptr);
    remove("text.txt");
    return val;
}
int calculateIntValue(){
    FILE * fptr;
    fptr = fopen("text.txt", "w+");
    char temp[10];
    for(int i=2; inputLine.operand[i]!='\'';i++){
        temp[i-2]=inputLine.operand[i];
    }
    fprintf(fptr, "%s", temp);
    fclose(fptr);
    fptr = fopen("text.txt", "r");
    int val ;
    fscanf(fptr, "%X", &val);
    fclose(fptr);
    remove("text.txt");
    return val;
}