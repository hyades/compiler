/*
-=-=-=-=-=-=-=-=-=-=-=-=-=
BATCH 26
-=-=-=-=-=-=-=-=-=-=-=-=-=
AAYUSH AHUJA 2010A7PS023P
MAYANK GUPTA 2010A7PS022P
-=-=-=-=-=-=-=-=-=-=-=-=-=
symbolTable.h
-=-=-=-=-=-=-=-=-=-=-=-=-=
*/

#ifndef SYMBOL_H_INCLUDED 
#define SYMBOL_H_INCLUDED


typedef struct
{

	symbol type;
	char name[30];
	int recindex;
	int offset;
	int ion;
	bool filled;


} variable;


struct paralist
{
	variable item;
	struct paralist *next;
};


typedef struct
{

	char fname[35];
	variable table[50]; //assumming function can contain max 100 variables
	bool filled;
	struct paralist *inputList;
	struct paralist *outputList;

}funTable;

typedef struct
{
	char rname[35];
	variable table[100];
	bool filled;
	char str[100];
	int size;

}recTable;




void createSymbolTable(variable GT[], funTable FT[], recTable RT[],parseTree A);
void initSymbolTable(variable GT[], funTable FT[], recTable RT[]);

#endif 
//symbol_H_INCLUDED