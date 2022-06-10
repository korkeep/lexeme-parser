/*
    front.c: a lexical analyzer system for simple arithmetic expressions
    author: korkeep
    date: 2022-06-10
*/
#include<stdio.h>
#include<ctype.h>

/* global declarartions */
int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE *in_fp, *fopen();

/* function declarations */
void addChar();
void getChar();
void getNonBlank();
int lex();

/* character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26

/* main driver */
void main(){
    /* open the input data file and process its contents */
    if((in_fp = fopen("front.in", "r")) == NULL)
        printf("ERROR - cannot open the front.in \n");
    else{
        getChar();
        do{
            lex();
        }while(nextToken != EOF);
    }
}

/* lookup: lookup operators and parentheses and return the token */
int lookup(char ch){
    switch(ch){
        case '(': addChar(); nextToken = LEFT_PAREN; break;
        case ')': addChar(); nextToken = RIGHT_PAREN; break;
        case '+': addChar(); nextToken = ADD_OP; break;
        case '-': addChar(); nextToken = SUB_OP; break;
        case '*': addChar(); nextToken = MULT_OP; break;
        case '/': addChar(); nextToken = DIV_OP; break;
        default: addChar(); nextToken = EOF; break;
    }
    return nextToken;
}

/* addChar: add nextChar to lexeme */
void addChar(){
    if(lexLen <= 98){
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    }
    else
        printf("Error - lexeme is too long \n");
}

/* getChar: get the next char of input and determine its class */
void getChar(){
    if((nextChar = getc(in_fp)) != EOF){
        if(isalpha(nextChar)) charClass = LETTER;
        else if(isdigit(nextChar)) charClass = DIGIT;
        else charClass = UNKNOWN;
    }
    else
        charClass = EOF;
}

/* getNonBlank: call getChar until it returns a non-whitespace char */
void getNonBlank(){
    while(isspace(nextChar))
        getChar();
}

/* lex: lexical analyzer for arithmetic expressions */
int lex(){
    lexLen = 0;
    getNonBlank();
    switch(charClass){
        /* parse identifiers */
        case LETTER:
            addChar(); getChar();
            while(charClass == LETTER || charClass == DIGIT){
                addChar(); getChar();
            }
            nextToken = IDENT;
            break;
        /* parse integer literals */
        case DIGIT:
            addChar(); getChar();
            while(charClass == DIGIT){
                addChar(); getChar();
            }
            nextToken = INT_LIT;
            break;
        /* parentheses and operators */
        case UNKNOWN:
            lookup(nextChar);
            getChar();
            break;
        /* EOF */
        case EOF:
            nextToken = EOF;
            lexeme[0] = 'E'; lexeme[1] = 'O'; lexeme[2] = 'F'; lexeme[3] = 0;
            break;
    }
    printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);
    return nextToken;
}