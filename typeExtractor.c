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
#include"semantic.h"
#include"typeExtractor.h"

extern bool any_error;

symbol getVarType(variable GT[], funTable FT[],char *varname,char *funname)//return type of variable varname
{
	// printf("finding type of %s in %s\n",varname,funname );
	int hashkey=100;
	int hval=hash(varname, hashkey);
	if(GT[hval].filled && !strcmp(GT[hval].name,varname))
		return GT[hval].type;
	else
	{
		int fval=hash(funname, hashkey);
			if(FT[fval].filled && !strcmp(FT[fval].fname,funname))
			{
				if(FT[fval].table[hval].filled && !strcmp(FT[fval].table[hval].name,varname))
					return FT[fval].table[hval].type;
			}
	}
	return TK_ERROR;
}

symbol getRecType(recTable RT[],variable GT[], funTable FT[],char *recname, char *varname,char *funname)//return type of variable varname part of record recname
{
	int hashkey=100;
	int hval=hash(funname, hashkey);
	int rval=hash(recname, hashkey);
	int rindex=FT[hval].table[rval].recindex;
	int vval=hash(varname, hashkey);
	if(RT[rindex].table[vval].filled && !strcmp(RT[rindex].table[vval].name,varname))
		return RT[rindex].table[vval].type;
	return TK_ERROR;
}

symbol typeCheck(parseTree A,variable GT[], funTable FT[],recTable RT[],char *funname)//checks if types are compatible
{
	symbol s1,s2,s3,s4,s5;
	int i;
	if(A->t->s == assignmentstmt)
	{
		if(A->next[0]->t->s==singleorrecid)
		{
			//printf("singleorrecid %s %s\n", A->next[0]->next[0]->t->lexeme,A->next[0]->next[1]->t->lexeme);	
			s1=getRecType(RT,GT,FT,A->next[0]->next[0]->t->lexeme,A->next[0]->next[1]->t->lexeme,funname);
		}
		else if(A->next[0]->t->s==TK_ID)
			s1=getVarType(GT,FT,A->next[0]->t->lexeme,funname);
		s2=typeCheck(A->next[2],GT,FT,RT,funname);
		//printf("%s %s %s %s\n",toStr(A->next[0]->t->s),toStr(s1),toStr(A->next[2]->t->s),toStr(s2));
		if(s1==TK_ERROR || s2==TK_ERROR)
		{
			if(s1==TK_ERROR || s2==TK_ERROR)
			{
				if(A->next[0]->t->s==singleorrecid && s1==TK_ERROR)
				{
					printf("ERROR: Variable %s of Record %s is not declared in this scope\n",A->next[0]->next[1]->t->lexeme,A->next[0]->next[0]->t->lexeme);
					any_error=1;
				}
				else if(A->next[0]->t->s==TK_ID && s1==TK_ERROR)
				{
					printf("ERROR: Variable %s is not declared in this scope\n",A->next[0]->t->lexeme);
					any_error=1;
				}
				return TK_ERROR;
			}
		}
		else if(s1!=s2)
		{
			printf("ERROR: Mismatched Datatype. Datatype %s does not match %s\n",toStr(s1),toStr(s2));
			any_error=1;
			return TK_ERROR2;//mismatched datatype
		}
		else
		{
			return s1;
		}
	}
	else if(A->t->s == iterativestmt)
	{
		return typeCheck(A->next[1],GT,FT,RT,funname);
	}
	else if(A->t->s == conditionalstmt)
	{
		return typeCheck(A->next[1],GT,FT,RT,funname);
	}
	else if(A->t->s == iostmt)
	{
		if(A->next[1]->t->s==singleorrecid)
			return getRecType(RT,GT,FT,A->next[1]->next[0]->t->lexeme,A->next[1]->next[1]->t->lexeme,funname);
		else if(A->next[1]->t->s==TK_ID)
			return getVarType(GT,FT,A->next[1]->t->lexeme,funname);
		else
		{
			return typeCheck(A->next[1],GT,FT,RT,funname);
		}
	}
	// else if(A->t->s == funcallstmt)
	// {
	// 	for(i=0;A->next[i]!=NULL;i++)
	// 	{
	// 		if(A->next[i]==outputparameters || A->next[i]==inputparameters)
	// 		{
	// 			temp=A->next[i]->next[0];
	// 			offset=0;
	// 			while(temp!=NULL)
	// 			{
	// 				s1=getVarType(GT,FT,temp->next[0]->t->lexeme,funname);
	// 				//check if this type is correct as per function definition
	// 				if(s1==TK_ERROR)
	// 					if(checkRec(RT,temp->next[0]->t->lexeme))//check if record exists
	// 					{
	// 						//if this type is correct as per function definition
	// 					}
	// 				temp=temp->next[1];
	// 				offset++;
	// 			}
	// 		}
	// 	}
	// }
	else if(A->t->s == arithmeticexpression)
	{
		if(A->next[0]->t->s==singleorrecid)
			s1=getRecType(RT,GT,FT,A->next[0]->next[0]->t->lexeme,A->next[0]->next[1]->t->lexeme,funname);
		else if(A->next[0]->t->s==TK_ID)
			s1=getVarType(GT,FT,A->next[0]->t->lexeme,funname);
		else
			s1=typeCheck(A->next[0],GT,FT,RT,funname);

		if(A->next[1]->t->s==singleorrecid)
			s2=getRecType(RT,GT,FT,A->next[1]->next[0]->t->lexeme,A->next[1]->next[1]->t->lexeme,funname);
		else if(A->next[1]->t->s==TK_ID)
			s2=getVarType(GT,FT,A->next[1]->t->lexeme,funname);
		else
			s2=typeCheck(A->next[1],GT,FT,RT,funname);
		//printf("ae %s %s %s %s\n",toStr(A->next[0]->t->s),toStr(s1),toStr(A->next[1]->t->s),toStr(s2));
		if(s1==TK_ERROR || s2==TK_ERROR)
		{
			if(s1==TK_ERROR || s2==TK_ERROR)
			{
				if(A->next[0]->t->s==singleorrecid && s1==TK_ERROR)
				{
					printf("ERROR: Variable %s of Record %s is not declared in this scope\n",A->next[0]->next[1]->t->lexeme,A->next[0]->next[0]->t->lexeme);
					any_error=1;
				}
				else if(A->next[0]->t->s==TK_ID && s1==TK_ERROR)
				s1=getVarType(GT,FT,A->next[0]->t->lexeme,funname);
					printf("ERROR: Variable %s is not declared in this scope\n",A->next[0]->t->lexeme);
					any_error=1;
				return TK_ERROR;
			}
		}
		else if(s1!=s2)
		{
			printf("ERROR: Mismatched Datatype. Datatype %s does not match %s\n",toStr(s1),toStr(s2));
			any_error=1;
			return TK_ERROR2;//mismatched datatype
		}
		else
		{
			return s1;
		}
	}
	else if(A->t->s == booleanexpression || A->t->s == TK_EQ || A->t->s == TK_LE || A->t->s == TK_LT || A->t->s == TK_GE || A->t->s == TK_GT || A->t->s == TK_AND || A->t->s == TK_OR)
	{
		if(A->next[0]->t->s==singleorrecid)
			s1=getRecType(RT,GT,FT,A->next[0]->next[0]->t->lexeme,A->next[0]->next[1]->t->lexeme,funname);
		else if(A->next[0]->t->s==TK_ID)
			s1=getVarType(GT,FT,A->next[0]->t->lexeme,funname);
		else
			s1=typeCheck(A->next[0],GT,FT,RT,funname);

		if(A->next[1]->t->s==singleorrecid)
			s2=getRecType(RT,GT,FT,A->next[1]->next[0]->t->lexeme,A->next[1]->next[1]->t->lexeme,funname);
		else if(A->next[1]->t->s==TK_ID)
			s2=getVarType(GT,FT,A->next[1]->t->lexeme,funname);
		else
			s2=typeCheck(A->next[1],GT,FT,RT,funname);
		//printf("be %s %s %s %s\n",toStr(A->next[0]->t->s),toStr(s1),toStr(A->next[1]->t->s),toStr(s2));
		if(s1==TK_ERROR || s2==TK_ERROR)
		{
			if(A->next[0]->t->s==singleorrecid && s1==TK_ERROR)
			{
				printf("ERROR: Variable %s of Record %s is not declared in this scope\n",A->next[0]->next[1]->t->lexeme,A->next[0]->next[0]->t->lexeme);
				any_error=1;
			}
			else if(A->next[0]->t->s==TK_ID && s1==TK_ERROR)
			{
				printf("ERROR: Variable %s is not declared in this scope\n",A->next[0]->t->lexeme);
				any_error=1;
			}
			return TK_ERROR;
		}
		else if(s1!=s2)
		{
			printf("ERROR: Mismatched Datatype. Datatype %s does not match %s\n",toStr(s1),toStr(s2));
			any_error=1;
			return TK_ERROR2;//mismatched datatype
		}
		else
		{
			return TK_INT;
		}
	}
	else if(A->t->s==TK_NUM)
	{
		return TK_INT;
	}
	else if(A->t->s==TK_RNUM)
	{
		return TK_REAL;
	}
	else if(A->t->s==TK_NOT)
	{
		return TK_INT;
	}
	else if(A->t->s==TK_FUNID && A->t->lexeme==funname)
	{
		printf("ERROR: Function %s can't be called recursively\n", funname);
		any_error=1;
		return TK_ERROR;
	}
	else
	{
		s1=TK_ERROR;
		if(A->next[0]!=NULL)
		s1=typeCheck(A->next[0],GT,FT,RT,funname);
		for(i=1;A->next[i]!=NULL && i<20;i++)
		{
			if(s1!=typeCheck(A->next[i],GT,FT,RT,funname))
			{
				return TK_ERROR;
			}
		}
		return s1;
	}
}

void typeParse(parseTree A,variable GT[], funTable FT[],recTable RT[],char *funname)
{
	int i;
	symbol s1;
	if(A->t->s==assignmentstmt || A->t->s==iostmt || A->t->s==conditionalstmt || A->t->s==booleanexpression || A->t->s==arithmeticexpression || A->t->s==iterativestmt)
	{
		s1=typeCheck(A,GT,FT,RT,funname);
		if(s1==TK_ERROR)
			any_error=1;
	 	return;
	}
	if(A->t->s==function || A->t->s==mainfunction)
		strcpy(funname,A->next[0]->t->lexeme);
	for(i=0;A->next[i]!=NULL && i<20;i++)
		typeParse(A->next[i],GT,FT,RT,funname);
}