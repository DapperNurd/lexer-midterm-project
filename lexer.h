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