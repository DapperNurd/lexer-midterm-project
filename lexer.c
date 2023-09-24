/**
 * Ben Bonus
 * PA1
 * lexer.c
*/
#include "lexer.h"
// ^ includes <stdio.h>, <stdlib.h>, <ctype.h>, and <string.h>

// Array (and int size) of keywords to process
const int KEYWORDS_COUNT = 37;
char* keywordsList[] = { "accessor", "and", "array", "begin", "bool", "case", "character", "constant", "else", "elsif", "end", "exit", "function",
    "if", "in", "integer", "interface", "is", "loop", "module", "mutator", "natural", "null", "of", "or", "other", "out",
    "positive", "procedure", "range", "return", "struct", "subtype", "then", "type", "when", "while" };

// Array (and int size) of single operators to process
const int SINGLE_OP_COUNT = 17; 
char* singleOperators[] = { ".", "<", ">", "(", ")", "+", "-", "*", "/", "|", "&", ";", ",", ":", "[", "]", "=" };

// Array (and int size) of double operators to process
const int DOUBLE_OP_COUNT = 10;
char* doubleOperators[] = { ":=", "..", "<<", ">>", "<>", "<=", ">=", "**", "!=", "=>" };

void processString(char* string, enum lexerState* state, FILE *file) {

    int stringLength = strlen(string); // String length... self-explanatory

    int start = 0; // Variable for handling string copying

    int dotCout; // Variable for handling '.' count in numerics (cannot be > 1)

    char* tokenStr = malloc(sizeof(char) * stringLength); // variable used for copying string and various testing of tokens

    for(int i = 0; i < stringLength; i++) { // Loops through each char

        // Main state-handling test
        if(*state == none) {
            memset(tokenStr, '\0', stringLength); // Clears anything in tokenStr (sets it all to '\0')
            // TOKEN STATE SET (keywords and identifiers)
            if(isalpha(string[i])) { // If the current char is a letter (isalpha() provided by <ctype.h>)
                *state = eToken;
                start = i;
            }
            // STRING STATE SET
            else if(string[i] == '"') { // If the current char is a double-quote
                *state = eString;
            }
            // CHARACTER LITERAL STATE SET
            else if(string[i] == '\'') { // If the current char is a single-quote
                *state = eCharacter;
            }
            // COMMENT STATE SET
            else if(string[i] == '/' && string[i+1] == '*') { // If the current char is a backslash and the next char is an asterisk
                *state = eComment;
            }
            // OPERATOR STATE SET
            else if(ispunct(string[i])) { // If the current char is a symbol (ispunct() provided by <ctype.h>)
                start = i;
                *state = eOperator;
            }
            // NUMERIC LITERAL STATE SET
            else if(isdigit(string[i])) { // If the current char is a number (isdigit() provided by <ctype.h>)
                dotCout = 0;
                *state = eNumeric;
            }
        }

        // TOKEN STATE HANDLER
        if(*state == eToken) {
            tokenStr[i-start] = string[i]; // Copies each char, while in token state, to the variable
            fprintf(file, "%c", string[i]); // Prints each char, while in state, to the file
            // STATE END CHECK
            if(!(isalnum(string[i+1]) || string[i+1] == '_')) { // is letter, digit, or _   (isalnum() provided by <ctype.h>)
                processWord(tokenStr, file); // Function for determining keyword vs. identifier
                *state = none; // Set state to none
            }
        }
        // OPERATOR STATE HANDLER
        else if(*state == eOperator) {
            tokenStr[i-start] = string[i]; // Copies each char, while in token state, to the variable
            fprintf(file, "%c", string[i]); // Prints each char, while in state, to the file
            if(checkForSelectCases(string[i], string[i+1])) { // Function which checks if the current char and the next char combine to form one of the specific double operators... If this is true then it is guarenteed one of the operators
                fprintf(file, "%c", string[i+1]); // Similarly prints the next char to the file
                fprintf(file, "%s", " (operator)\n"); // Prints the type and a new line
                i++; // Increments i past the next char
            }
            else {
                processOperator(tokenStr, file); // Function for checking if symbol is an operator or an UNK
            }
            *state = none; // Set state to none
            // *No state end check as operators are a fixed length (1 or 2 chars)
        }
        // NUMERIC LITERAL STATE HANDLER
        else if(*state == eNumeric) {
            fprintf(file, "%c", string[i]); // Prints each char, while in state, to the file
            // Decimal checking
            if(string[i+1] == '.' && isdigit(string[i+2]) && dotCout < 1) { // If the next char is a '.' and the following char is a digit AND the dotCount is less than 1
                fprintf(file, "%c", string[i+1]); // Prints the next char
                dotCout++; // Increases dotCount
                i++; // Increases i
            }
            // STATE END CHECK
            else if(!(isdigit(string[i+1]) || (isdigit(string[i]) && string[i+1] == '#'))) { // If the next char is not a digit or a '#'
                fprintf(file, "%s", " (numeric literal)\n"); // Prints the type and a new line
                *state = none; // Set state to none
            }
        }
        // STRING STATE HANDLER
        else if(*state == eString) {
            fprintf(file, "%c", string[i]); // Prints each char, while in state, to the file
            // STATE END CHECK
            if(string[i+1] == '"') { // checking to see if the next char is a string (end of string)
                fprintf(file, "%c", string[i+1]); // Prints the ending double-quote
                i++; // increments past the closing " so it dosen't start the string again
                fprintf(file, "%s", " (string)\n"); // Prints the type and a new line
                *state = none; // Set state to none
            }
        }
        // CHARACTER STATE HANDLER
        else if(*state == eCharacter) {
            fprintf(file, "%c%c%c%s", string[i], string[i+1], string[i+2], " (character literal)\n"); // Prints the next 3 chars to the file as well as the type and a new line
            i += 2; // Increments i by two
            *state = none; // Sets state to none
            // *No state end check because characters are a fixed length (3 chars)
        }
        // COMMENT STATE HANDLER
        else if(*state == eComment) {
            fprintf(file, "%c", string[i]); // Prints each char, while in state, to the file
            // STATE END CHECK
            if(string[i] == '*' && string[i+1] == '/') { // If the next char is an asterisk and the following is a backslash (end of comment)
                fprintf(file, "%c", string[i+1]); // Prints the next char ('\') to the file
                i++; // increments i
                fprintf(file, "%s", " (comment)\n"); // Prints the type and a new line
                *state = none; // Sets state to none
            }
        }
    }
    
    free(tokenStr); // Frees copied-string variable for token handling
}

void processWord(char* string, FILE *file) {

    for(int i = 0; i < KEYWORDS_COUNT; i++) { // Loops through array of keywords
        if(strcmp(string, keywordsList[i]) == 0) { // Checks if the tested string is the same as one in the array (strcmp returns 0 if they are equal)
            fprintf(file, "%s", " (keyword)\n"); // Prints the type and a new line (keyword)
            return;
        }
    }

    fprintf(file, "%s", " (identifier)\n"); // Prints the type and a new line (identifier, because it was not in the array of keywords)
}

void processOperator(char* string, FILE *file) {

    // Before doing it this way I had a very long switch statemtnt to check for every type of operator
    // I'm not sure that this way is necessarily more practical, or even efficient, but it is WAY
    // easier to read and makes the code much nicer to look at.

    for(int i = 0; i < SINGLE_OP_COUNT; i++) { // Loops through the array of operators
        if(strcmp(string, singleOperators[i]) == 0) { // Checks if the tested string is the same as one in the array (strcmp returns 0 if they are equal)
            fprintf(file, "%s", " (operator)\n"); // Prints the type and a new line (operator)
            return;
        }
    }
    fprintf(file, "%s", " (UNK)\n"); // Prints the type and a new line (UNK, because it was not in the list of operators and is some other symbol)
}

int checkForSelectCases(char char1, char char2) {
    
    char string[2] = { char1, char2 }; // Combines the two passed chars into a string
    for(int i = 0; i < DOUBLE_OP_COUNT; i++) { // Loops through the list of double operators
        if(strcmp(string, doubleOperators[i]) == 0) { // Tests if the combined chars is one of the operators
            return 1; // (true) Using 1 and 0 as psuedo-bools
        }
    }

    return 0; // (false) Using 1 and 0 as psuedo-bools
}