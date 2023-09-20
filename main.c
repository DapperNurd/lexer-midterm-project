#include "lexer.h"
// ^ includes <stdio.h>, <stdlib.h>, <ctype.h>, and <string.h>

int main(int argc, char *argv[]) {

    if(argc <= 1) {
        printf("Please include the file name in the command line arguments.\nExmaple: ./lexer example.cci\n");
        return 0;
    }

    FILE *openedFile;
    FILE *outputFile;

    // Open a file in read mode
    // openedFile = fopen(argv[1], "r");
    // outputFile = fopen(argv[1] + ".lexer", "w");
    // fptr = fopen("files/trie.cci", "r");

    char myString[256];

    enum lexerState currState = none;

    while(fgets(myString, 256, openedFile)) {
        // printf("%i\n", strlen(myString));
        // currState = processString(myString, currState);
        fprintf("%s", processString(myString, &currState));
        // processString(myString, &currState);
    }

    fclose(openedFile);

    return 0;
}