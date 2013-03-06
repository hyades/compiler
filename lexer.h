#ifndef LEXER_H_INCLUDED
#define LEXER_H_INCLUDED
FILE *getStream(FILE *fp, buffer B, buffersize k);
tokenInfo getNextToken(FILE *fp);
char getNextChar(FILE *fp, bool *back);
token keywordId(char *lexeme, keywordTable kt);//returns token for lexeme if it is a keyword or fieldname
token mainFun(char *lexeme, keywordTable kt);//returns token for lexeme if it is main or function
void addKeyword(keywordTable kt, char *keyword, symbol s);
int hash(char *keyword);//find hash value of string based on key K
void initkt(keywordTable kt);
#endif // LEXER_H_INCLUDED
