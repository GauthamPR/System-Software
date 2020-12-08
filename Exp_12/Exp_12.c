#include <stdio.h>
#include <stdlib.h>

void readAndPrintFrom(FILE *);
struct inLine{
    char specifier;
    int startingAddress;
    int objectCode[10];
    int length;
}inputLine;

void main(){
    char endLine;
    char pgmName[8];
    int firstInstr;
    int pgmLength;
    char specifier;
    FILE *input;

    input = fopen("../bin/output.txt", "r");

    if(input == NULL){
        printf("\nERROR OPENING FILE");
        exit(1);
    }

    fscanf(input, "%c %6s %6X %6X\n", &specifier, pgmName, &firstInstr, &pgmLength);
    while((*(*input)._ptr) != 'E'){
        readAndPrintFrom(input);
    }
    fclose(input);
}

void readAndPrintFrom(FILE * fin){
    fscanf(fin, "%c %6X %2X", &inputLine.specifier, &inputLine.startingAddress, &inputLine.length);
    int byteCounter = 0;
    for(int i=0;byteCounter<inputLine.length ;i++){
            fscanf(fin, " %6X", &inputLine.objectCode[i]);
            printf("%X\t\t%X\n", inputLine.startingAddress + byteCounter, inputLine.objectCode[i]);
            byteCounter += 3;
    }
    fscanf(fin, "\n");
}
