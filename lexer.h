#ifndef LEXER_H_INCLUDED
#define LEXER_H_INCLUDED
FILE *getStream(FILE *fp, buffer B, buffersize k);//reads k characters from source file into buffer B
tokenInfo getNextToken(FILE *fp, keywordTable kt, bool *error);//get next token
char getNextChar(FILE *fp, bool *back);//gets next character from source file at position x
ptoken keywordId(char *lexeme, keywordTable kt);//returns token for lexeme if it is a keyword or fieldname
ptoken mainFun(char *lexeme, keywordTable kt);//returns token for lexeme if it is main or function
void addKeyword(keywordTable kt, char *keyword, symbol s);//recursively called to add keyword to keywordTable
int hash(char *keyword, int hashkey);//find hash value of string based on hashkey
void initkt(keywordTable kt);
#endif // LEXER_H_INCLUDED
