#include "lexer.h"
// ^ includes <stdio.h>, <stdlib.h>, <ctype.h>, and <string.h>

const int KEYWORDS_COUNT = 37;
char* keywordsList[] = { "accessor", "and", "array", "begin", "bool", "case", "character", "constant", "else", "elsif", "end", "exit", "function",
    "if", "in", "integer", "interface", "is", "loop", "module", "mutator", "natural", "null", "of", "or", "other", "out",
    "positive", "procedure", "range", "return", "struct", "subtype", "then", "type", "when", "while" };

const int OPERATOR_COUNT = 27; 
char* operatorList[] = { ":=", "..", "<<", ">>", "<>", "<=", ">=", "**", "!=", "=>",
    ".", "<", ">", "(", ")", "+", "-", "*", "/", "|", "&", ";", ",", ":", "[", "]", "=" };


void processString(char* string, enum lexerState* state, FILE *file) {

    int stringLength = strlen(string);

    int start = 0;

    int dotCout;

    char* tokenStr = malloc(sizeof(char) * stringLength);

    for(int i = 0; i < stringLength; i++) {

        if(*state == none) {
            memset(tokenStr, '\0', stringLength); // clears anything in tokenStr
            if(isalpha(string[i])) {
                *state = eToken;
                start = i;
            }
            else if(string[i] == '"') {
                *state = eString;
            }
            else if(string[i] == '\'') {
                *state = eCharacter;
            }
            else if(string[i] == '/' && string[i+1] == '*') {
                *state = eComment;
            }
            else if(ispunct(string[i])) {
                start = i;
                *state = eOperator;
            }
            else if(isdigit(string[i])) {
                dotCout = 0;
                *state = eNumeric;
            }
        }

        if(*state == eToken) {
            tokenStr[i-start] = string[i];
            fprintf(file, "%c", string[i]);
            if(!(isalnum(string[i+1]) || string[i+1] == '_')) { // is letter, digit, or _
                processWord(tokenStr, file);
                *state = none;
            }
        }
        else if(*state == eOperator) {
            tokenStr[i-start] = string[i];
            fprintf(file, "%c", string[i]);
            if(checkForSelectCases(string[i], string[i+1])) {
                tokenStr[i+1-start] = string[i+1];
                fprintf(file, "%c", string[i+1]);
                i++;
            }
            processOperator(tokenStr, file);
            *state = none;
        }
        else if(*state == eNumeric) {
            fprintf(file, "%c", string[i]);
            if(string[i+1] == '.' && isdigit(string[i+2]) && dotCout < 1) {
                fprintf(file, "%c", string[i+1]);
                dotCout++;
                i++;
            }
            else if(!(isdigit(string[i+1]) || string[i+1] == '#')) {
                fprintf(file, "%s", " (numeric literal)\n");
                *state = none;
            }
        }
        else if(*state == eString) {
            fprintf(file, "%c", string[i]);
            if(string[i+1] == '"') { // checking to see if the next char is a string (end of string)
                fprintf(file, "%c", string[i+1]);
                i++; // increments past the closing " so it dosen't start the string again
                fprintf(file, "%s", " (string)\n");
                *state = none;
            }
        }
        else if(*state == eCharacter) {
            fprintf(file, "%c%c%c%s", string[i], string[i+1], string[i+2], " (character literal)\n");
            i += 2;
            *state = none;
        }
        else if(*state == eComment) {
            fprintf(file, "%c", string[i]);
            if(string[i] == '*' && string[i+1] == '/') {   
                fprintf(file, "%c", string[i+1]);
                i++;
                fprintf(file, "%s", " (comment)\n");
                *state = none;
            }
        }
    }
    
    free(tokenStr);
}

void processWord(char* string, FILE *file) {

    for(int i = 0; i < KEYWORDS_COUNT; i++) {
        if(strcmp(string, keywordsList[i]) == 0) { // strcmp returns 0 if they are equal
            fprintf(file, "%s", " (keyword)\n");
            return;
        }
    }
    fprintf(file, "%s", " (identifier)\n");
}

void processOperator(char* string, FILE *file) {

    // Before doing it this way I had a very long switch statemtnt to check for every type of operator
    // I'm not sure that this way is necessarily more practical, or even efficient, but it is WAY
    // easier to read and makes the code much nicer to look at.

    for(int i = 0; i < OPERATOR_COUNT; i++) {
        if(strcmp(string, operatorList[i]) == 0) { // strcmp returns 0 if they are equal
            fprintf(file, "%s", " (operator)\n");
            return;
        }
    }
    fprintf(file, "%s", " (UNK)\n");
}

int checkForSelectCases(char char1, char char2) {

    const int COUNT = 10;
    char* doubleOperators[] = { ":=", "..", "<<", ">>", "<>", "<=", ">=", "**", "!=", "=>" };
    
    char string[2] = { char1, char2 };
    for(int i = 0; i < COUNT; i++) {
        if(strcmp(string, doubleOperators[i]) == 0) {
            return 1; // != 0 is true, == 0 is false
        }
    }

    return 0; // != 0 is true, == 0 is false
}