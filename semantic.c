/*
-=-=-=-=-=-=-=-=-=-=-=-=-=
BATCH 26
-=-=-=-=-=-=-=-=-=-=-=-=-=
AAYUSH AHUJA 2010A7PS023P
MAYANK GUPTA 2010A7PS022P
-=-=-=-=-=-=-=-=-=-=-=-=-=
semantic.c
-=-=-=-=-=-=-=-=-=-=-=-=-=
*/

#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>

#include"lexerDef.h"
#include"lexer.h"
#include"parserDef.h"
#include"parser.h"
#include"symbolTable.h"
#include"semantic.h"


int checkMultift(funTable FT[],char* fname,int recindex,char* name)
{
	int hval,hval2,hkey=100;
	hval = hash(fname,hkey);
	hval2 = hash(name,hkey);
	if(FT[hval].table[hval2].filled)
		printf("ERROR: Variable %s has been declared multiple times in function %s\n",name,fname);
	return FT[hval].table[hval2].filled;
}

int checkMultirt(recTable RT[],char* rname,char* name)
{
	int hval,hval2,hkey=100;
	hval = hash(rname,hkey);
	hval2 = hash(name,hkey);
	if(RT[hval].table[hval2].filled)
		printf("ERROR: Variable %s has been declared multiple times in record %s\n",name,rname);
	return RT[hval].table[hval2].filled;
}

int checkMultigt(variable GT[],int recindex,char* name)
{
	int hval,hkey=100;
	hval = hash(name,hkey);
	if(GT[hval].filled)
		printf("ERROR: Variable %s has been declared multiple times globally\n",name);
	return GT[hval].filled;
}