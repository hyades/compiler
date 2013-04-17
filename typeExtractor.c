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
	printf("finding type of %s in %s\n",varname,funname );
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

symbol getRecType(recTable RT[],char *recname, char *varname)//return type of variable varname part of record recname
{
	int hashkey=100;
	int rval=hash(recname, hashkey);
	if(RT[rval].filled)
		printf("filled\n");
	if(RT[rval].filled && !strcmp(RT[rval].rname,recname))
	{
		printf("rname found%s\n", RT[rval].rname);
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
		{
			printf("singleorrecid %s %s\n", A->next[0]->next[0]->t->lexeme,A->next[0]->next[1]->t->lexeme);	
			s1=getRecType(RT,A->next[0]->next[0]->t->lexeme,A->next[0]->next[1]->t->lexeme);
		}
		else if(A->next[0]->t->s==TK_ID)
			s1=getVarType(GT,FT,A->next[0]->t->lexeme,funname);
		s2=typeCheck(A->next[2],GT,FT,RT,funname);
		printf("%s %s %s %s\n",toStr(A->next[0]->t->s),toStr(s1),toStr(A->next[2]->t->s),toStr(s2));
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
			s1=getRecType(RT,A->next[0]->next[0]->t->lexeme,A->next[0]->next[1]->t->lexeme);
		else if(A->next[0]->t->s==TK_ID)
			s1=getVarType(GT,FT,A->next[0]->t->lexeme,funname);
		else
			s1=typeCheck(A->next[0],GT,FT,RT,funname);

		if(A->next[2]->t->s==singleorrecid)
			s2=getRecType(RT,A->next[2]->next[0]->t->lexeme,A->next[2]->next[1]->t->lexeme);
		else if(A->next[2]->t->s==TK_ID)
			s2=getVarType(GT,FT,A->next[2]->t->lexeme,funname);
		else
			s2=typeCheck(A->next[1],GT,FT,RT,funname);

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
			s2=typeCheck(A->next[0],GT,FT,RT,funname);

		if(A->next[2]->t->s==singleorrecid)
			s2=getRecType(RT,A->next[2]->next[0]->t->lexeme,A->next[2]->next[1]->t->lexeme);
		else if(A->next[2]->t->s==TK_ID)
			s2=getVarType(GT,FT,A->next[2]->t->lexeme,funname);
		else
			s2=typeCheck(A->next[1],GT,FT,RT,funname);
		
		if(s1==TK_ERROR || s2==TK_ERROR)
			return TK_ERROR;//unknown datatype
		else if(s1!=s2)
			return TK_ERROR2;//mismatched datatype
		else
		{
			return TK_EPS;
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
}

void typeParse(parseTree A,variable GT[], funTable FT[],recTable RT[],char *funname)
{
	int i;
	symbol s1;
	if(A->t->s==assignmentstmt || A->t->s==iostmt || A->t->s==conditionalstmt || A->t->s==booleanexpression || A->t->s==arithmeticexpression || A->t->s==iterativestmt)
	{
		s1=typeCheck(A,GT,FT,RT,funname);
		if(s1==TK_ERROR)
			printf("TK_ERROR\n");
		else if(s1==TK_ERROR2)
			printf("TK_ERROR2\n");
		else
			printf("%s\n", toStr(s1));
	 	return;
	}
	if(A->t->s==function || A->t->s==mainfunction)
		strcpy(funname,A->next[0]->t->lexeme);
	for(i=0;A->next[i]!=NULL && i<20;i++)
		typeParse(A->next[i],GT,FT,RT,funname);
}

	// An identifier cannot be declared multiple times in the same scope.
	// An identifier must be declared before its use.
	// An identifier declared globally cannot be declared anywhere else in function definitions.
	// The types and  the number of parameters returned by a function must be the same as that of the parameters used in invoking the function.
	// The parameters being returned by a function must be assigned a value. If a parameter does not get a value assigned within the function 
	// 	definition, it should be reported as an error.
	// The function that does not return any value, must be invoked appropriately.
	// Function input parameters passed while invoking it should be of the same type as those used in the function definition. 
	// 	Number of input parameters must be same as that of those used in the function definition.
	// An if statement must have the expression of boolean type.
	// Function overloading is not allowed.
	// The function cannot be invoked recursively.
	// An identifier used beyond its scope must be viewed as undefined
	// A record type definition is visible anywhere in the program.
	// The right hand side expression of an assignment statement must be of the same type as that of the left hand side identifier.
	// A function definition for a function being used (say F1) by another (say F2) must precede the definition of the function using it(i.e. F2).
	// A  while statement  must redefine the variable that participates in the iterations. As an instance, consider the following example
	//                 while(c3<=c5)
	//                         write(c3);
	//                        c3<---c3+2.34;
	//                 end