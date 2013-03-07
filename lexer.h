#ifndef LEXER_H_INCLUDED
#define LEXER_H_INCLUDED
int getStream(int fp, buffer B, buffersize k);//reads k characters from source file into buffer B
tokenInfo getNextToken(int fp, keywordTable kt, bool *error, int *linenumber);//get next token
char getNextChar(int fp, bool *back);//gets next character from source file at position x
token keywordId(char *lexeme, keywordTable kt);//returns token for lexeme if it is a keyword or fieldname
token mainFun(char *lexeme, keywordTable kt);//returns token for lexeme if it is main or function
void addKeyword(keywordTable kt, char *keyword, symbol s);//recursively called to add keyword to keywordTable
int hash(char *keyword, int hashkey);//find hash value of string based on hashkey
void initkt(keywordTable kt);
#endif // LEXER_H_INCLUDED
