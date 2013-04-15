
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

void insertft(funTable FT[],char *fname, symbol type, char *name,int ion , int offset)
{
	int hval,hval2,hkey=100;

	hval = hash(fname,hkey);
	strcpy(FT[hval].fname,fname);
	hval2 = hash(name,hkey);
	strcpy(FT[hval].table[hval2].name,name);
	FT[hval].table[hval2].type = type;
	FT[hval].table[hval2].ion = ion;
	FT[hval].table[hval2].offset = offset;
	FT[hval].table[hval2].filled = 1;
	FT[hval].filled = 1;
}

//RT,temp2->next[1]->t->lexeme,temp3->next[1]->t->s,temp3->next[2]->t->lexeme

void insertrt(recTable RT[],char *rname, symbol type, char *name)
{
	int hval,hval2,hkey=100;

	hval = hash(rname,hkey);
	strcpy(RT[hval].rname,rname);
	hval2 = hash(name,hkey);
	strcpy(RT[hval].table[hval2].name,name);
	RT[hval].table[hval2].type = type;
	RT[hval].table[hval2].filled = 1;
	RT[hval].filled = 1;
}


//insert(GT,temp2->next[1]->t->s,temp2->next[2]->t->lexeme)

void insertgt(variable GT[],symbol type, char *name)
{
	int hval,hkey=100;

	hval = hash(name,hkey);
	strcpy(GT[hval].name,name);
	GT[hval].type = type;
	GT[hval].filled = 1;	
}

void initSymbolTable(variable GT[], funTable FT[], recTable RT[])
{
	int i,j;
	for(i=0;i<100;i++)
	{
		GT[i].filled = 0;
		RT[i].filled = 0;
		FT[i].filled = 0;
		for(j=0;j<100;j++)
		{
			FT[i].table[j].filled = 0;
			RT[i].table[j].filled = 0;
		}
	}
}

void createSymbolTable(variable GT[], funTable FT[], recTable RT[],parseTree A)
{
	int i,j,k,offset=1;
	parseTree temp,temp1,temp2,temp3;
	for(i=0;A->next[i]!=NULL;i++)
	{
		if(A->next[i]->t->s==function)
		{
			temp = A->next[i];	
			if(temp->next[1]->t->s==parameter_list)
			{
				temp1 = temp->next[1];
				offset = 0;
				for(j=0;temp1->next[j]!=NULL;j+=2)
				{
					//check
					insertft(FT,temp->next[0]->t->lexeme,temp1->next[j]->t->s,temp1->next[j+1]->t->lexeme,0,offset) ;
					// ft _functionname int d3b4b5 input==0 offset
				}				
			}
			if(temp->next[2]->t->s==parameter_list)
			{
				temp1 = temp->next[2];
				offset = 0;
				for(j=0;temp1->next[j]!=NULL;j+=2)
				{
					//check
					insertft(FT,temp->next[0]->t->lexeme,temp1->next[j]->t->s,temp1->next[j+1]->t->lexeme,1,offset) ;
					// ft _functionname int d3b4b5 outputs==1 offset
				}				
			}
			else if(temp->next[2]->t->s==stmts)
			{
				temp1 = temp->next[2];
				offset=1;
				for(j=0;temp1->next[j]!=NULL;j++)
				{

					temp2 = temp1->next[j];
					if(temp2->t->s == typedefinition)
					{
						//rec
						//check
						//if(!check(RT,temp2->next[1]->t->lexeme))
							for(k=2;temp2->next[k]->t->s != TK_ENDRECORD;k++)
							{
								temp3 = temp2->next[k]; //field-defination
								insertrt(RT,temp2->next[1]->t->lexeme,temp3->next[1]->t->s,temp3->next[2]->t->lexeme);
							}
						/*
						else
						{
							printf("MULTIPLE DECLARATIONS OF RECORD %s\n",temp2->next[1]->t->lexeme);
							return;
						}
						*/

					}
					else if(temp2->t->s == declaration)
					{
						//ft
						if(temp2->next[3]!=NULL)
						{
							//global
							//check
							insertgt(GT,temp2->next[1]->t->s,temp2->next[2]->t->lexeme);
						}
						else
						{
							//check
							insertft(FT,temp->next[0]->t->lexeme,temp2->next[1]->t->s,temp2->next[2]->t->lexeme,2,offset) ;
							offset++;	
						}
						
						// ft _functionname int d3b4b5 normal == 2 offset
					}
					else if(temp2->t->s == declarations)
					{	
						for(k=0;temp2->next[k]!=NULL;k++)
						{
							
							//ft
							if(temp2->next[k]->next[3]!=NULL)
							{
								//global
								//check
								insertgt(GT,temp2->next[k]->next[1]->t->s,temp2->next[k]->next[2]->t->lexeme);
							}
							else
							{
								//check
								insertft(FT,temp->next[0]->t->lexeme,temp2->next[k]->next[1]->t->s,temp2->next[k]->next[2]->t->lexeme,2,offset) ;
								offset++;	
							}
						}
						
						// ft _functionname int d3b4b5 normal == 2 offset
					}

					else
						break;
				}
								
			}
			if(temp->next[3]->t->s==stmts)
			{
				temp1 = temp->next[3];
				offset=1;
				for(j=0;temp1->next[j]!=NULL;j++)
				{

					temp2 = temp1->next[j];
					if(temp2->t->s == typedefinition)
					{
						//rec
						//check
						//if(!check(RT,temp2->next[1]->t->lexeme))
							for(k=2;temp2->next[k]->t->s != TK_ENDRECORD;k++)
							{
								temp3 = temp2->next[k]; //field-defination
								insertrt(RT,temp2->next[1]->t->lexeme,temp3->next[1]->t->s,temp3->next[2]->t->lexeme);
							}
						/*
						else
						{
							printf("MULTIPLE DECLARATIONS OF RECORD %s\n",temp2->next[1]->t->lexeme);
							return;
						}
						*/

					}
					else if(temp2->t->s == declaration)
					{
						//ft
						if(temp2->next[3]!=NULL)
						{
							//global
							//check
							insertgt(GT,temp2->next[1]->t->s,temp2->next[2]->t->lexeme);
						}
						else
						{
							//check
							insertft(FT,temp->next[0]->t->lexeme,temp2->next[1]->t->s,temp2->next[2]->t->lexeme,2,offset) ;
							offset++;	
						}
						
						// ft _functionname int d3b4b5 normal == 2 offset
					}
					else if(temp2->t->s == declarations)
					{	
						for(k=0;temp2->next[k]!=NULL;k++)
						{
							
							//ft
							if(temp2->next[k]->next[3]!=NULL)
							{
								//global
								//check
								insertgt(GT,temp2->next[k]->next[1]->t->s,temp2->next[k]->next[2]->t->lexeme);
							}
							else
							{
								//check
								insertft(FT,temp->next[0]->t->lexeme,temp2->next[k]->next[1]->t->s,temp2->next[k]->next[2]->t->lexeme,2,offset) ;
								offset++;	
							}
						}
						
						// ft _functionname int d3b4b5 normal == 2 offset
					}
					else
						break;
				}
								
			}
		}
		else
		{

		}
	}
}




void printFT(funTable FT[])
{
	int i,j;
	printf("FUNCTION NAMES:\n");
	for(i=0;i<100;i++)
	{
		if(FT[i].filled == 1)
		{
			printf("function:%s\n",FT[i].fname);
			for(j=0;j<100;j++)
				if(FT[i].table[j].filled == 1)
					printf("%s %s %d %d\n",toStr(FT[i].table[j].type),FT[i].table[j].name,FT[i].table[j].offset,FT[i].table[j].ion);
		}
	}
}



void printRT(recTable RT[])
{
	int i,j;
	printf("RECORD NAMES:\n");
	for(i=0;i<100;i++)
	{
		if(RT[i].filled == 1)
		{
			printf("record:%s\n",RT[i].rname);
			for(j=0;j<100;j++)
				if(RT[i].table[j].filled == 1)
					printf("%s %s\n",toStr(RT[i].table[j].type),RT[i].table[j].name);
		}
	}
}


void printGT(variable GT[])
{
	int i,j;
	printf("GLOBAL NAMES:\n");
	for(i=0;i<100;i++)
	{
		if(GT[i].filled == 1)
		{
			
			printf("%s %s\n",toStr(GT[i].type),GT[i].name);
		}
	}
}
