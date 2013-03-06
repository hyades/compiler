#ifndef LEXERDEF_H_INCLUDED
#define LEXERDEF_H_INCLUDED
typedef char[] *buffer;
typdef int buffersize;
buffersize k=1024;

typedef enum {/*tokens come here*/} symbol;

typedef enum{FALSE,TRUE} bool;

typedef struct{
	symbol s;
	char lexeme[100];
}token;
typedef token* ptoken;

typedef struct{
	bool present;
	symbol s;
	char keyword[100];
}keyword;

typedef keyword* keywordTable;


#endif // LEXERDEF_H_INCLUDED
