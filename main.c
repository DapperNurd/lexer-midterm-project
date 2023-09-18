#include "lexer.h"
// ^ includes <stdio.h>, <stdlib.h>, and <string.h>

int main(int argc, char *argv[]) {

    // if(argc <= 1) {
    //     printf("Please include the file name in the command line arguments.\nExmaple: ./lexer example.cci\n");
    //     return 0;
    // }

    FILE *fptr;

    // Open a file in read mode
    // fptr = fopen(argv[1], "r");
    fptr = fopen("example.cci", "r");

    char myString[256];

    while(fgets(myString, 256, fptr)) {
        printf("%i\n", strlen(myString));
    }

    fclose(fptr);

    return 0;
}