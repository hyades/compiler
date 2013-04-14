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
	int offset;
	int ion;
	bool filled;

} variable;

typedef struct
{

	char fname[35];
	variable table[100]; //assumming function can contain max 100 variables

}funTable;

typedef struct
{
	char rname[35];
	variable table[100];

}recTable;

variable GT[100]; //max 100 globals possible *********ADD TO DRIVER***********
funTable FT[100];
recTable RT[100];



void createSymbolTable(variable GT[], funTable FT[], recTable RT[],parseTree A);
void initSymbolTable(variable GT[], funTable FT[], recTable RT[]);

#endif 
//symbol_H_INCLUDED