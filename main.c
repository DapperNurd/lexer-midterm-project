#include "lexer.h"
// ^ includes <stdio.h>, <stdlib.h>, <ctype.h>, and <string.h>

int main(int argc, char *argv[]) {

    // if(argc <= 1) {
    //     printf("Please include the file name in the command line arguments.\nExmaple: ./lexer example.cci\n");
    //     return 0;
    // }

    FILE *openedFile;
    // FILE *outputFile;

    // Open a file in read mode
    // openedFile = fopen(argv[1], "r");
    // outputFile = fopen(argv[1] + ".lexer", "w");
    openedFile = fopen("files/trie.cci", "r");

    char myString[256];

    enum lexerState currState = none;

    // NOTE FOR LATER
    // MAKE NUMEBR ALSO INCLUDE #

    while(fgets(myString, 256, openedFile)) {
        // printf("%i\n", strlen(myString));
        // currState = processString(myString, currState);

        char* processedStr = malloc(384);
        strcpy(processedStr, processString(myString, &currState));
        printf("%s", processedStr);
        free(processedStr);
        
        // printf("%s", processString(myString, &currState));
        // processString(myString, &currState);
    }

    fclose(openedFile);

    return 0;
}