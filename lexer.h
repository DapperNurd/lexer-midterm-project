/**
 * Ben Bonus
 * PA1
 * lexer.h
*/
#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Used for isalpha(), isdigit(), isalnum(), and ispunct()

enum lexerState { none, eComment, eString, eCharacter, eOperator, eNumeric, eToken }; // enum Definition of lexerState

/** Notes for myself
 * all operators that have more than one char start with a single char operator (!= starts with !, which is its own operator)
 * should have a system to interpret a word (as it ends with a space or operator or such, non a-z, and figure otu whether its a keyword or identifier)
 * numerics with a decimal should test if the . has another number after it or another .
 * UNK is unknown and SHOULD NOT be found, but include for debugging
*/

/**
 * [param] char* string          -> string to test
 * [param] enum lexerState state -> enum for state handling
 * [param] File* file            -> File to output to
 * 
 * Formats a string into a list of types with a lexer style
*/
void processString(char string[], enum lexerState* state, FILE *file);

/**
 * [param] char* string -> string to test
 * [param] File* file   -> file to output to
 * 
 * Differs a token (string) as either a keyword or identifer using a pre-determined list of keywords
*/
void processWord(char* string, FILE *file);

/**
 * [param] char* string -> tring to test
 * [param] File* file   -> file to output to
 * 
 * Differs whether a given string is a type operator or UNK
*/
void processOperator(char* string, FILE *file);

/**
 * [param] char char1 -> first char to test
 * [param] char char2 -> char following char1
 * 
 * Formats a string into a list of types with a lexer style
*/
int checkForSelectCases(char char1, char char2);

#endif