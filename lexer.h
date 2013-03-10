/*
-=-=-=-=-=-=-=-=-=-=-=-=-=
BATCH 26
-=-=-=-=-=-=-=-=-=-=-=-=-=
AAYUSH AHUJA 2010A7PS023P
MAYANK GUPTA 2010A7PS022P
-=-=-=-=-=-=-=-=-=-=-=-=-=
lexer.h
-=-=-=-=-=-=-=-=-=-=-=-=-=
*/

#ifndef LEXER_H_INCLUDED
#define LEXER_H_INCLUDED
int getStream(int fp, buffer B, buffersize k);//reads k characters from source file into buffer B
tokenInfo getNextToken(int fp, keywordTable kt, bool *error, int *linenumber);//get next token
char getNextChar(int fp, int *back);//gets next character from source file at position x
token keywordId(char *lexeme, keywordTable kt);//returns token for lexeme if it is a keyword or fieldname
token mainFun(char *lexeme, keywordTable kt);//returns token for lexeme if it is main or function
void addKeyword(keywordTable kt, char *keyword, symbol s);//recursively called to add keyword to keywordTable
int hash(char *keyword, int hashkey);//find hash value of string based on hashkey
void initkt(keywordTable kt);//initialize keyword table
char* toStr ( symbol s );//return Symbol as string
tokenList createTokenList(int fp, keywordTable kt);//create Token List
void printTokenList(int fp, keywordTable kt, tokenList list);//print Token List
#endif // LEXER_H_INCLUDED
