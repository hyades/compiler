/*
-=-=-=-=-=-=-=-=-=-=-=-=-=
BATCH 26
-=-=-=-=-=-=-=-=-=-=-=-=-=
AAYUSH AHUJA 2010A7PS023P
MAYANK GUPTA 2010A7PS022P
-=-=-=-=-=-=-=-=-=-=-=-=-=
typeExtractor.h
-=-=-=-=-=-=-=-=-=-=-=-=-=
*/

#ifndef EXTRACTOR_H_INCLUDED 
#define EXTRACTOR_H_INCLUDED

symbol getVarType(variable GT[], funTable FT[],char *varname,char *funname);//return type of variable varname
symbol getRecType(recTable RT[],variable GT[], funTable FT[],char *recname, char *varname,char *funname);//return type of variable varname part of record recname

symbol typeCheck(parseTree A,variable GT[], funTable FT[],recTable RT[],char *funname);//checks if types are compatible
#endif 
//EXTRACTOR_H_INCLUDED