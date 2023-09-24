#include "lexer.h"
// ^ includes <stdio.h>, <stdlib.h>, <ctype.h>, and <string.h>

const int KEYWORDS_COUNT = 37;
char* keywordsList[] = { "accessor", "and", "array", "begin", "bool", "case", "character", "constant", "else", "elsif", "end", "exit", "function",
    "if", "in", "integer", "interface", "is", "loop", "module", "mutator", "natural", "null", "of", "or", "other", "out",
    "positive", "procedure", "range", "return", "struct", "subtype", "then", "type", "when", "while" };

const int OPERATOR_COUNT = 27; 
char* operatorList[] = { ":=", "..", "<<", ">>", "<>", "<=", ">=", "**", "!=", "=>",
    ".", "<", ">", "(", ")", "+", "-", "*", "/", "|", "&", ";", ",", ":", "[", "]", "=" };


char* processString(char* string, enum lexerState* state) {

    int stringLength = strlen(string);

    int start = 0;

    int dotCout;

    char* tempStr = malloc(sizeof(char) * stringLength);

    char* returnStr = malloc(384);

    for(int i = 0; i < stringLength; i++) {

        if(*state == none) {
            memset(tempStr, '\0', stringLength); // clears anything in tempStr
            if(isalpha(string[i])) {
                *state = eToken;
                start = i;
            }
            else if(string[i] == '"') {
                *state = eString;
                start = i;
            }
            else if(string[i] == '/' && string[i+1] == '*') {
                start = i;
                *state = eComment;
            }
            else if(ispunct(string[i])) {
                start = i;
                *state = eOperator;
            }
            else if(isdigit(string[i])) {
                start = i;
                dotCout = 0;
                *state = eNumeric;
            }
        }

        if(*state == eToken) {
            tempStr[i-start] = string[i];
            if(!(isalnum(string[i+1]) || string[i+1] == '_')) { // is letter, digit, or _
                processWord(tempStr);
                strcat(returnStr, tempStr);
                *state = none;
            }
        }
        else if(*state == eOperator) {
            tempStr[i-start] = string[i];
            if(checkForSelectCases(string[i], string[i+1])) {
                tempStr[i+1-start] = string[i+1];
                i++;
            }
            processOperator(tempStr);
            strcat(returnStr, tempStr);
            *state = none;
        }
        else if(*state == eNumeric) {
            tempStr[i-start] = string[i];
            if(string[i+1] == '.' && isdigit(string[i+2]) && dotCout < 1) {
                tempStr[i+1-start] = string[i+1];
                tempStr[i+2-start] = string[i+2];
                dotCout++;
                i += 2;
            }
            else if(!isdigit(string[i+1])) {
                strcat(tempStr, " (numeric)\n");
                strcat(returnStr, tempStr);
                *state = none;
            }
        }
        else if(*state == eString) {
            tempStr[i-start] = string[i];
            if(string[i+1] == '"') { // checking to see if the next char is a string (end of string)
                tempStr[i+1-start] = string[i+1];
                i++; // increments past the closing " so it dosen't start the string again
                strcat(tempStr, " (string)\n");
                strcat(returnStr, tempStr);
                *state = none;
            }
        }
        else if(*state == eComment) {
            tempStr[i-start] = string[i];
            if(string[i] == '*' && string[i+1] == '/') {    
                tempStr[i+1-start] = string[i+1];
                i++;
                strcat(tempStr, " (comment)\n");
                strcat(returnStr, tempStr);
                *state = none;
            }
            if(i == stringLength - 1) { // Runs at the end of the line, so comments still get printed even if they aren't closed
                strcat(returnStr, tempStr);
            }
        }
    }
    
    free(tempStr);
    return returnStr;
}

void processWord(char* string) {

    for(int i = 0; i < KEYWORDS_COUNT; i++) {
        if(strcmp(string, keywordsList[i]) == 0) { // strcmp returns 0 if they are equal
            // printf("found string: %s\n", string);
            strcat(string, " (keyword)\n");
            return;
        }
    }
    // printf("did not find string: %s\n", string);
    strcat(string, " (identifier)\n");
}

void processOperator(char* string) {

    // Before doing it this way I had a very long switch statemtnt to check for every type of operator
    // I'm not sure that this way is necessarily more practical, or even efficient, but it is WAY
    // easier to read and makes the code much nicer to look at.

    for(int i = 0; i < OPERATOR_COUNT; i++) {
        if(strcmp(string, operatorList[i]) == 0) { // strcmp returns 0 if they are equal
            // printf("found string: %s\n", string);
            strcat(string, " (operator)\n");
            return;
        }
    }
    // printf("did not find string: %s\n", string);
    strcat(string, " (UNK)\n");
}

int checkForSelectCases(char char1, char char2) {

    const int COUNT = 10;
    char* doubleOperators[] = { ":=", "..", "<<", ">>", "<>", "<=", ">=", "**", "!=", "=>" };
    
    char string[2] = { char1, char2 };
    for(int i = 0; i < COUNT; i++) {
        if(strcmp(string, doubleOperators[i]) == 0) {
            return 1;
        }
    }

    return 0;
}