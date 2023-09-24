#include "lexer.h"
// ^ includes <stdio.h>, <stdlib.h>, <ctype.h>, and <string.h>

int main(int argc, char *argv[]) {

    // if(argc <= 1) {
    //     printf("Please include the file name in the command line arguments.\nExmaple: ./lexer example.cci\n");
    //     return 0;
    // }

    FILE *openedFile;
    FILE *outputFile;

    // Open a file in read mode
    openedFile = fopen(argv[1], "r");
    strcat(argv[1], ".lexer");
    outputFile = fopen(argv[1], "w");

    char myString[256];

    enum lexerState currState = none;

    // NOTE FOR LATER
    // MAKE NUMEBR ALSO INCLUDE #

    while(fgets(myString, 256, openedFile)) {
        processString(myString, &currState, outputFile);
    }

    fclose(openedFile);
    fclose(outputFile);

    return 0;
}