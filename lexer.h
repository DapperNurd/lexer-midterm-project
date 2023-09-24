#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum lexerState { none, eComment, eString, eCharacter, eOperator, eNumeric, eToken };

/** Notes for myself
 * all operators that have more than one char start with a single char operator (!= starts with !, which is its own operator)
 * should have a system to interpret a word (as it ends with a space or operator or such, non a-z, and figure otu whether its a keyword or identifier)
 * numerics with a decimal should test if the . has another number after it or another .
 * UNK is unknown and SHOULD NOT be found, but include for debugging
*/

void processString(char string[], enum lexerState* state, FILE *file);

void processWord(char* string, FILE *file);

void processOperator(char* string, FILE *file);

int checkForSelectCases(char char1, char char2);

#endif