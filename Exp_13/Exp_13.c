#include <stdio.h>
#include <stdlib.h>

void readAndPrintFrom(FILE *);
void convertToBit(int, int *);

struct inLine{
    char specifier;
    int bitMask;
    int startingAddress;
    int objectCode[10];
    int length;
}inputLine;

int startingAddress;

void main(){
    char endLine;
    char pgmName[8];
    int firstInstr;
    int pgmLength;
    char specifier;
    FILE *input;

    input = fopen("../bin/src/inputFor13.txt", "r");

    if(input == NULL){
        printf("\nERROR OPENING FILE");
        exit(1);
    }
    printf("\nEnter Starting Address: ");
    scanf("%X", &startingAddress);
    fscanf(input, "%c %6s %6X %6X\n", &specifier, pgmName, &firstInstr, &pgmLength);
    printf("\nProgram Name: %s", pgmName);
    printf("\nAddress\t\tObject Code\n\n");
    while((*(*input)._ptr) != 'E'){
        readAndPrintFrom(input);
    }
    fclose(input);
}

void readAndPrintFrom(FILE * fin){
    fscanf(fin, "%c %6X %2X %3X", &inputLine.specifier, &inputLine.startingAddress, &inputLine.length, &inputLine.bitMask);
    int bits[12];
    convertToBit(inputLine.bitMask, bits);
    int byteCounter = 0;
    int i=0;
    for(int i=0;byteCounter<inputLine.length ;i++){
            fscanf(fin, " %6X", &inputLine.objectCode[i]);
            if(bits[byteCounter%3]==1){
                inputLine.objectCode[i] += startingAddress;    
            }
            printf("%X\t\t%0000006X\n", inputLine.startingAddress + byteCounter + startingAddress, inputLine.objectCode[i]);
            byteCounter += 3;
    }
    fscanf(fin, "\n");
}

void convertToBit(int decimal, int * bits){
    int remainder;
    int i;
    for(i=11; i>=0; i--){
        bits[i] = decimal%2;
        decimal = decimal/2;
    }
}