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

extern bool any_error;

int checkMultift(funTable FT[],char* fname,int recindex,char* name)
{
	int hval,hval2,hkey=100;
	hval = hash(fname,hkey);
	hval2 = hash(name,hkey);
	if(FT[hval].table[hval2].filled)
	{
		printf("ERROR: Variable %s has been declared multiple times in function %s\n",name,fname);
		any_error=1;
	}
	return FT[hval].table[hval2].filled;
}

int checkMultiftN(funTable FT[],char* fname,int recindex,char* name)
{
	int hval,hval2,hkey=100;
	hval = hash(fname,hkey);
	hval2 = hash(name,hkey);
	return FT[hval].table[hval2].filled;
}

int checkMultirt(recTable RT[],char* rname,char* name)
{
	int hval,hval2,hkey=100;
	hval = hash(rname,hkey);
	hval2 = hash(name,hkey);
	if(RT[hval].table[hval2].filled)
	{
		printf("ERROR: Variable %s has been declared multiple times in record %s\n",name,rname);
		any_error=1;
	}
	return RT[hval].table[hval2].filled;
}

int checkMultigt(variable GT[],int recindex,char* name)
{
	int hval,hkey=100;
	hval = hash(name,hkey);
	if(GT[hval].filled)
	{
		printf("ERROR: Variable %s has been already globally declared\n",name);
		any_error=1;
	}
	return GT[hval].filled;
}

int checkMultigtN(variable GT[],int recindex,char* name)
{
	int hval,hkey=100;
	hval = hash(name,hkey);
	return GT[hval].filled;
}

int checkMultiFun(funTable FT[], char* fname)
{
	int hval,hkey=100;
	hval=hash(fname,hkey);
	if(FT[hval].filled)
	{
		printf("ERROR: Function overloading is not allowed. Function %s has been overloaded\n", fname);
		any_error=1;
	}
	return FT[hval].filled;
}