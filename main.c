/**
 * Ben Bonus
 * PA1
 * main.c
*/
#include "lexer.h"
// ^ includes <stdio.h>, <stdlib.h>, <ctype.h>, and <string.h>

int main(int argc, char *argv[]) {

    // Error msg if no file is added to the executable line in terminal
    if(argc <= 1) { 
        printf("Please include the file name in the command line arguments.\nExmaple: ./lexer example.cci\n");
        return 0;
    }

    // File opening
    FILE *openedFile;
    FILE *outputFile;

    openedFile = fopen(argv[1], "r"); // "r" read mode
    if(openedFile == NULL) { // Checks to make sure the openedFile exists, otherwise returns.
        printf("ERROR: File not found.\n");
        return 0;
    }

    strcat(argv[1], ".lexer"); // Adds ".lexer" onto the end of the argv[1] string for saving the new file
    outputFile = fopen(argv[1], "w"); // "w" write mode

    // File processing and outputting
    char myString[256]; // used for file reading
    enum lexerState currState = none; // used for state handling... gets passed into function

    while(fgets(myString, 256, openedFile)) { // Reads to the end of file
        processString(myString, &currState, outputFile); // Processes file line-by-line (outputs from within the function)
    }

    // Closing file
    fclose(openedFile);
    fclose(outputFile);

    return 0;
}