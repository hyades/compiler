/*
-=-=-=-=-=-=-=-=-=-=-=-=-=
BATCH 26
-=-=-=-=-=-=-=-=-=-=-=-=-=
AAYUSH AHUJA 2010A7PS023P
MAYANK GUPTA 2010A7PS022P
-=-=-=-=-=-=-=-=-=-=-=-=-=
typeExtractor.c
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
#include"typeExtractor.h"

//arithmetic operator	int/real on both sides
//assignment	int/real/record on both sides

symbol getVarType(variable GT[], funTable FT[],char *varname,char *funname)//return type of variable varname
{
	int hashkey=100;
	int hval=hash(varname, hashkey);
	if(GT[hval].filled && !strcmp(GT[hval].name,varname))
		return GT[hval].type;
	else
	{
		int fval=hash(funname, hashkey);
			if(FT[fval].filled && !strcmp(FT[fval].name,funname))
			{
				if(FT[fval].table[hval].filled && !strcmp(FT[fval].table[hval].name,varname))
					return FT[fval].table[hval].type;
			}
	}
	return TK_ERROR;
}

symbol getRecType(recTable RT[],char *recname, char *varname)//return type of variable varname part of record recname
{
	int hashkey=100;
	int rval=hash(recname, hashkey);
	if(RT[rval].filled && !strcmp(RT[rval],recname))
	{
		int hval=hash(varname, hashkey);
		if(RT[rval].table[hval].filled && !strcmp(RT[rval].table[hval].name,varname))
			return RT[rval].table[hval].type;
	}
}

symbol typeCheck(parseTree A,variable GT[], funTable FT[],recTable RT[],char *funname)//checks if types are compatible
{
	symbol s1,s2,s3,s4,s5;
	if(A->t->s == assignmentstmt)
	{
		if(A->next[0]->t->s==singleorrecid)
			s1=getRecType(RT,A->next[0]->next[0]->t->lexeme,A->next[0]->next[1]->t->lexeme);
		else if(A->next[0]->t->s==TK_ID)
			s1=getVarType(GT,FT,A->next[0]->t->lexeme,funname);
		s2=typeCheck(A->next[2],GT,FT,RT);
		if(s1==TK_ERROR || s2==TK_ERROR)
			return TK_ERROR;//unknown datatype
		else if(s1!=s2)
			return TK_ERROR2;//mismatched datatype
		else
		{
			return s1;
		}
	}
	else if(A->t->s == iterativestmt)
	{
		if(A->next[1]->t->s==booleanexpression)
			return typeCheck(A->next[1],GT,FT,RT,funname);
		else
		{
			printf("iterativestmt error");
			return TK_ERROR;
		}
	}
	else if(A->t->s == conditionalstmt)
	{
		if(A->next[1]->t->s==booleanexpression)
			return typeCheck(A->next[1],GT,FT,RT,funname);
		else
		{
			printf("conditionalstmt error");
			return TK_ERROR;
		}
	}
	else if(A->t->s == iostmt)
	{
		if(A->next[0]->t->s==TK_READ)
		{
			if(A->next[1]->t->s==singleorrecid)
				return getRecType(RT,A->next[1]->next[0]->t->lexeme,A->next[1]->next[1]->t->lexeme);
			else if(A->next[1]->t->s==TK_ID)
				return getVarType(GT,FT,A->next[1]->t->lexeme,funname);
			else
			{
				printf("iostmt read error");
				return TK_ERROR;
			}
		}
		else
		{
			if(A->next[1]->t->s!=allvar)
				return A->next[1]->t->s;
			else
				return A->next[1]->next[1]->t->s;
		}
	}
	else if(A->t->s == funcallstmt)
	{
		for(i=0;A->next[i]!=NULL;i++)
		{
			if(A->next[i]==outputparameters || A->next[i]==inputparameters)
			{
				temp=A->next[i]->next[0];
				offset=0;
				while(temp!=NULL)
				{
					s1=getVarType(GT,FT,temp->next[0]->t->lexeme,funname);
					//check if this type is correct as per function definition
					if(s1==TK_ERROR)
						if(checkRec(RT,temp->next[0]->t->lexeme))//check if record exists
						{
							//if this type is correct as per function definition
						}
					temp=temp->next[1];
					offset++;
				}
			}
		}
	}
	else if(A->t->s == arithmeticexpression)
	{
		if(A->next[0]->t->s==singleorrecid)
			s1=getRecType(RT,A->next[0]->next[0]->t->lexeme,A->next[0]->next[1]->t->lexeme);
		else if(A->next[0]->t->s==TK_ID)
			s1=getVarType(GT,FT,A->next[0]->t->lexeme,funname);
		else
			s2=typeCheck(A->next[0],GT,FT,RT);

		if(A->next[2]->t->s==singleorrecid)
			s2=getRecType(RT,A->next[2]->next[0]->t->lexeme,A->next[2]->next[1]->t->lexeme);
		else if(A->next[2]->t->s==TK_ID)
			s2=getVarType(GT,FT,A->next[2]->t->lexeme,funname);
		else
			s2=typeCheck(A->next[1],GT,FT,RT);

		if(s1==TK_ERROR || s2==TK_ERROR)
			return TK_ERROR;//unknown datatype
		else if(s1!=s2)
			return TK_ERROR2;//mismatched datatype
		else
		{
			return s1;
		}
	}
	else if(A->t->s == booleanexpression)
	{
		if(A->next[0]->t->s==singleorrecid)
			s1=getRecType(RT,A->next[0]->next[0]->t->lexeme,A->next[0]->next[1]->t->lexeme);
		else if(A->next[0]->t->s==TK_ID)
			s1=getVarType(GT,FT,A->next[0]->t->lexeme,funname);
		else
			s2=typeCheck(A->next[0],GT,FT,RT);

		if(A->next[2]->t->s==singleorrecid)
			s2=getRecType(RT,A->next[2]->next[0]->t->lexeme,A->next[2]->next[1]->t->lexeme);
		else if(A->next[2]->t->s==TK_ID)
			s2=getVarType(GT,FT,A->next[2]->t->lexeme,funname);
		else
			s2=typeCheck(A->next[1],GT,FT,RT);
		
		if(s1==TK_ERROR || s2==TK_ERROR)
			return TK_ERROR;//unknown datatype
		else if(s1!=s2)
			return TK_ERROR2;//mismatched datatype
		else
		{
			return s1;
		}
	}
}