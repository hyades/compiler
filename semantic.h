/*
-=-=-=-=-=-=-=-=-=-=-=-=-=
BATCH 26
-=-=-=-=-=-=-=-=-=-=-=-=-=
AAYUSH AHUJA 2010A7PS023P
MAYANK GUPTA 2010A7PS022P
-=-=-=-=-=-=-=-=-=-=-=-=-=
semantic.h
-=-=-=-=-=-=-=-=-=-=-=-=-=
*/

#ifndef SEMANTIC_H_INCLUDED 
#define SEMANTIC_H_INCLUDED


int checkMultift(funTable FT[],char* fname,int recindex,char* name);
int checkMultiftN(funTable FT[],char* fname,int recindex,char* name);
int checkMultirt(recTable RT[],char* rname,char* name);
int checkMultigt(variable GT[],int recindex,char* name);
int checkMultigtN(variable GT[],int recindex,char* name);
int checkMultiFun(funTable FT[], char* fname);
#endif 
//SEMANTIC_H_INCLUDED