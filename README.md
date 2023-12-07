# Lexer (Midterm Project)
## Intro

Modern translation systems often use lexical analysis to divide input into meaningful units. Once these meaningful units (or lexemes or tokens) have been derived, other components within the translation system are used to determine the relationships among the lexemes. Lexical analyzers (or lexers) are commonly used in compilers, interpreters, and other translation systems that you have often used. The act of lexical analysis is also known as scanning. 

This repository was a midterm project for my CS210 class. It takes a file and translates it into a lexem file. Here is an example below:

This file, when inputted:
````
module complex_number interface

    type complex_number_type;

    /*
     * accessors
     */
    accessor imaginary(c: complex_number_type) return float;
    accessor real(c: complex_number_type) return float;
    /*
     * operations
     */
    function "-"(c1, c2: complex_number_type) return complex_number_type;
    function "+"(c1, c2: complex_number_type) return complex_number_type;

end complex_number;
````
gets translated into:
````
module (keyword)
complex_number (identifier)
interface (keyword)
type (keyword)
complex_number_type (identifier)
; (operator)
/*
     * accessors
     */ (comment)
accessor (keyword)
imaginary (identifier)
( (operator)
c (identifier)
: (operator)
complex_number_type (identifier)
) (operator)
... and so on ...
````
