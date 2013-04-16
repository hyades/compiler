
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

void insertft(funTable FT[],char *fname, symbol type, char *rec_name,char *name,int ion , int *offset)
{
	int hval,hval2,hkey=100;
	//printf("adding to function %s:%s\n",fname,name);
	hval = hash(fname,hkey);
	strcpy(FT[hval].fname,fname);
	hval2 = hash(name,hkey);
	strcpy(FT[hval].table[hval2].name,name);
	strcpy(FT[hval].table[hval2].rec_name,rec_name);
	FT[hval].table[hval2].type = type;
	FT[hval].table[hval2].ion = ion;
	FT[hval].table[hval2].offset = *offset;
	FT[hval].table[hval2].filled = 1;
	FT[hval].filled = 1;
}

//RT,temp2->next[1]->t->lexeme,temp3->next[1]->t->s,temp3->next[2]->t->lexeme

void insertrt(recTable RT[],char *rname, symbol type, char *name)
{
	int hval,hval2,hkey=100;

	//printf("adding to record %s:%s\n",rname,name);
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

	//printf("adding to global %s\n",name);
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

// void createSymbolTable(variable GT[], funTable FT[], recTable RT[],parseTree A)
// {
// 	int i,j,k,offset=1;
// 	parseTree temp,temp1,temp2,temp3;
// 	for(i=0;A->next[i]!=NULL;i++)
// 	{
// 		if(A->next[i]->t->s==function)
// 		{
// 			temp = A->next[i];	
// 			if(temp->next[1]->t->s==parameter_list)
// 			{
// 				temp1 = temp->next[1];
// 				offset = 0;
// 				for(j=0;temp1->next[j]!=NULL;j+=2)
// 				{
// 					//check
// 					insertft(FT,temp->next[0]->t->lexeme,temp1->next[j]->t->s,temp1->next[j+1]->t->lexeme,0,offset) ;
// 					// ft _functionname int d3b4b5 input==0 offset
// 				}				
// 			}
// 			if(temp->next[2]->t->s==parameter_list)
// 			{
// 				temp1 = temp->next[2];
// 				offset = 0;
// 				for(j=0;temp1->next[j]!=NULL;j+=2)
// 				{
// 					//check
// 					insertft(FT,temp->next[0]->t->lexeme,temp1->next[j]->t->s,temp1->next[j+1]->t->lexeme,1,offset) ;
// 					// ft _functionname int d3b4b5 outputs==1 offset
// 				}				
// 			}
// 			else if(temp->next[2]->t->s==stmts)
// 			{
// 				temp1 = temp->next[2];
// 				offset=1;
// 				for(j=0;temp1->next[j]!=NULL;j++)
// 				{

// 					temp2 = temp1->next[j];
// 					if(temp2->t->s == typedefinition)
// 					{
// 						//rec
// 						//check
// 						//if(!check(RT,temp2->next[1]->t->lexeme))
// 							for(k=2;temp2->next[k]->t->s != TK_ENDRECORD;k++)
// 							{
// 								temp3 = temp2->next[k]; //field-defination
// 								insertrt(RT,temp2->next[1]->t->lexeme,temp3->next[1]->t->s,temp3->next[2]->t->lexeme);
// 							}
// 						/*
// 						else
// 						{
// 							printf("MULTIPLE DECLARATIONS OF RECORD %s\n",temp2->next[1]->t->lexeme);
// 							return;
// 						}
// 						*/

// 					}
// 					else if(temp2->t->s == declaration)
// 					{
// 						//ft
// 						if(temp2->next[3]!=NULL)
// 						{
// 							//global
// 							//check
// 							insertgt(GT,temp2->next[1]->t->s,temp2->next[2]->t->lexeme);
// 						}
// 						else
// 						{
// 							//check
// 							insertft(FT,temp->next[0]->t->lexeme,temp2->next[1]->t->s,temp2->next[2]->t->lexeme,2,offset) ;
// 							offset++;	
// 						}
						
// 						// ft _functionname int d3b4b5 normal == 2 offset
// 					}
// 					else if(temp2->t->s == declarations)
// 					{	
// 						for(k=0;temp2->next[k]!=NULL;k++)
// 						{
							
// 							//ft
// 							if(temp2->next[k]->next[3]!=NULL)
// 							{
// 								//global
// 								//check
// 								insertgt(GT,temp2->next[k]->next[1]->t->s,temp2->next[k]->next[2]->t->lexeme);
// 							}
// 							else
// 							{
// 								//check
// 								insertft(FT,temp->next[0]->t->lexeme,temp2->next[k]->next[1]->t->s,temp2->next[k]->next[2]->t->lexeme,2,offset) ;
// 								offset++;	
// 							}
// 						}
						
// 						// ft _functionname int d3b4b5 normal == 2 offset
// 					}

// 					else
// 						break;
// 				}
								
// 			}
// 			if(temp->next[3]->t->s==stmts)
// 			{
// 				temp1 = temp->next[3];
// 				offset=1;
// 				for(j=0;temp1->next[j]!=NULL;j++)
// 				{

// 					temp2 = temp1->next[j];
// 					if(temp2->t->s == typedefinition)
// 					{
// 						//rec
// 						//check
// 						//if(!check(RT,temp2->next[1]->t->lexeme))
// 							for(k=2;temp2->next[k]->t->s != TK_ENDRECORD;k++)
// 							{
// 								temp3 = temp2->next[k]; //field-defination
// 								insertrt(RT,temp2->next[1]->t->lexeme,temp3->next[1]->t->s,temp3->next[2]->t->lexeme);
// 							}
// 						/*
// 						else
// 						{
// 							printf("MULTIPLE DECLARATIONS OF RECORD %s\n",temp2->next[1]->t->lexeme);
// 							return;
// 						}
// 						*/

// 					}
// 					else if(temp2->t->s == declaration)
// 					{
// 						//ft
// 						if(temp2->next[3]!=NULL)
// 						{
// 							//global
// 							//check
// 							insertgt(GT,temp2->next[1]->t->s,temp2->next[2]->t->lexeme);
// 						}
// 						else
// 						{
// 							//check
// 							insertft(FT,temp->next[0]->t->lexeme,temp2->next[1]->t->s,temp2->next[2]->t->lexeme,2,offset) ;
// 							offset++;	
// 						}
						
// 						// ft _functionname int d3b4b5 normal == 2 offset
// 					}
// 					else if(temp2->t->s == declarations)
// 					{	
// 						for(k=0;temp2->next[k]!=NULL;k++)
// 						{
							
// 							//ft
// 							if(temp2->next[k]->next[3]!=NULL)
// 							{
// 								//global
// 								//check
// 								insertgt(GT,temp2->next[k]->next[1]->t->s,temp2->next[k]->next[2]->t->lexeme);
// 							}
// 							else
// 							{
// 								//check
// 								insertft(FT,temp->next[0]->t->lexeme,temp2->next[k]->next[1]->t->s,temp2->next[k]->next[2]->t->lexeme,2,offset) ;
// 								offset++;	
// 							}
// 						}
						
// 						// ft _functionname int d3b4b5 normal == 2 offset
// 					}
// 					else
// 						break;
// 				}
								
// 			}
// 		}
// 		else
// 		{

// 		}
// 	}
// }




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





void createInputParameterTable(funTable FT[],parseTree A,char *fname, int *offset)
{

	parseTree temp;
	int i,j;
	printf("INPUT PARS A = %s\n",toStr(A->t->s));

	if(A->t->s == TK_INT || A->t->s == TK_REAL)
	{
		temp = A->parent;
		//insertft(funTable FT[],char *fname, symbol type, char *rec_name,char *name,int ion , int offset)
		insertft(FT,fname,temp->next[0]->t->s,"",temp->next[1]->t->lexeme,0,offset);
		*offset = *offset + 1;
	}	
	else if(A->t->s == TK_RECORD)
	{

		temp = A->parent;
		insertft(FT,fname,temp->next[0]->t->s,temp->next[1]->t->lexeme,temp->parent->next[1]->t->lexeme,0,offset);
		*offset = *offset + 1;
	}
	else 
	{
		for(i=0;A->next[i]!=NULL;i++)
		{
			temp = A->next[i];
			createInputParameterTable(FT,temp,fname,offset);
		}
	}

}







void createOutputParameterTable(funTable FT[],parseTree A,char *fname, int *offset)
{

	parseTree temp;
	int i,j;
	printf("OUTPUT PARS A = %s\n",toStr(A->t->s));

	if(A->t->s == TK_INT || A->t->s == TK_REAL)
	{
		temp = A->parent;
		//insertft(funTable FT[],char *fname, symbol type, char *rec_name,char *name,int ion , int offset)
		insertft(FT,fname,temp->next[0]->t->s,"",temp->next[1]->t->lexeme,1,offset);
		*offset = *offset + 1;
	}	
	else if(A->t->s == TK_RECORD)
	{

		temp = A->parent;
		insertft(FT,fname,temp->next[0]->t->s,temp->next[1]->t->lexeme,temp->next[2]->t->lexeme,1,offset);
		*offset = *offset + 1;
	}
	else 
	{
		for(i=0;A->next[i]!=NULL;i++)
		{
			temp = A->next[i];
			createOutputParameterTable(FT,temp,fname,offset);
		}
	}

}


createFieldRecordsTable(recTable RT[], parseTree A, char *rname)
{

	int i,j;
	parseTree temp;
	printf("FILED REC A = %s\n",toStr(A->t->s));

	if(A->t->s ==TK_TYPE)
	{
		temp = A->parent;
		//void insertrt(recTable RT[],char *rname, symbol type, char *name)
		insertrt(RT,rname,temp->next[1]->t->s,temp->next[2]->t->lexeme);
	}
	else
	{
		for(i=0;A->next[i]!=NULL;i++)
		{
			temp = A->next[i];
			createFieldRecordsTable(RT,temp,rname);
		}
	}
}




void createRecordTable(recTable RT[],parseTree A)
{

	parseTree temp;
	int i,j;
	printf("REC TABLE A = %s\n",toStr(A->t->s));

	if(A->t->s ==TK_RECORD)
	{
		temp = A->parent;
		createFieldRecordsTable(RT,temp,temp->next[1]->t->lexeme);
	}
	else
	{
		for(i=0;A->next[i]!=NULL;i++)
		{
			temp = A->next[i];
			createRecordTable(RT,temp);
		}
	}
}


void createFunctionDeclareTable(variable GT[],funTable FT[],recTable RT[],parseTree A,char * fname,int *offset)
{

	parseTree temp;
	int i,j;
	printf("FUNCTION DECLARE A = %s\n",toStr(A->t->s));
	if(A->t->s == TK_TYPE)
	{
		temp = A->parent; //parent = declaration
		if(temp->next[3]==NULL)
		{

			//void insertft(funTable FT[],char *fname, symbol type, char *rec_name,char *name,int ion , int offset)
			insertft(FT,fname,temp->next[1]->t->s,"",temp->next[2]->t->lexeme,2,offset);
			if(temp->next[1]->t->s == TK_INT)
				*offset = *offset + 2;
			if(temp->next[1]->t->s == TK_REAL)
				*offset = *offset + 4;

		}
		


	}
	else 
	{
		for(j=0;A->next[j]!=NULL;j++)
		{
			temp = A->next[j];
			createFunctionDeclareTable(GT,FT,temp,fname,offset);
		}
	}
}



void createFunctionTable(variable GT[], funTable FT[], recTable RT[],parseTree A, char * fname, int *offset)
{

	parseTree temp;
	int i,j;
	//int offset = 1;
	printf("FUNCTION TABLE A = %s\n",toStr(A->t->s));
	if(A->t->s == TK_INPUT)
	{
		//printf("INPUT = %s\n",toStr(A->t->s));
		temp = A->parent; //parent of tk_ input = input_par
		createInputParameterTable(FT,temp,fname,offset);
	}
	else if(A->t->s == TK_OUTPUT) ////parent of tk_output = output_par
	{
		temp = A->parent;
		createOutputParameterTable(FT,temp,fname,offset);
	}
	if(A->t->s == TK_RECORD)
	{

		temp = A->parent; //parent of record = typedefination
		if(temp->next[3]->t->s == TK_ENDRECORD)
			createRecordTable(RT,temp);
		else
			for(i=0;A->next[i]!=NULL;i++)
			{
				temp = A->next[i];
				createFunctionTable(GT,FT,RT,temp,offset);
			}
	}
	if(A->t->s == TK_RECORDID)
	{
		A = A->parent
	}
	else if(A->t->s == TK_TYPE)
	{
		temp = A->parent; //parent of tk_type = declaration
		createFunctionDeclareTable(GT,FT,temp,fname,offset);
	}
	else
	{
		for(i=0;A->next[i]!=NULL;i++)
		{
			temp = A->next[i];
			createFunctionTable(GT,FT,RT,temp,fname,offset);
		}
	}
}


void createMainFunctionTable(variable GT[], funTable FT[], recTable RT[], parseTree A,int *offset)
{
	parseTree temp;
	int i,j;
	printf("MAIN FUNCTION TABLE A = %s\n",toStr(A->t->s));
	char fname[] = "_main";
	//int offset;
	
	if(A->t->s == declaration)
	{
		temp = A; // declaration
		createFunctionDeclareTable(GT,FT,RT,temp,fname,offset);
	}
	else
	{
		for(i=0;A->next[i]!=NULL;i++)
		{
			temp = A->next[i];
			createMainFunctionTable(GT,FT,RT,temp,offset);
		}
	}

}







void createSymbolTable(variable GT[], funTable FT[], recTable RT[],parseTree A)
{

	parseTree temp;
	int i,j,k;
	//printf("SYMBOL TABLE A = %s\n",toStr(A->t->s));

	if(A->t->s == TK_FUNID)
	{

		temp = A->parent; //parent of funid = function
		int offset = 0;
		createFunctionTable(GT,FT,RT,temp,A->t->lexeme,&offset);
	}

	else if(A->t->s == TK_MAIN)
	{
		temp = A->parent;
		int offset = 0;
		createMainFunctionTable(GT,FT,RT,temp,&offset);
	}
	else
	{
		for(i=0;A->next[i]!=NULL;i++)
		{
			temp = A->next[i];
			createSymbolTable(GT,FT,RT,temp);
		}
	}
}





createRecordTable(recTable RT[], parseTree A)
{
	parseTree temp;
	int i,j;
	if(A->t->s == typedefinition)
	{
		temp  = A;
		createFieldRecordsTable(RT,temp,temp->next[1]->t->lexeme);
	}
	else
		for(i=0;A[i]!=NULL;i++)
		{
			temp = A->next[i];
			createRecordTable(GT,temp);
		}


}


createGlobalTable(variable GT[],parseTree A)
{
	parseTree temp;
	int i,j;


	if(A->t->s == TK_GLOBAL)
	{
		temp = A->parent;
		insertgt(GT,temp->next[1]->t->s,temp->next[2]->t->lexeme);
	}
	else
		for(i=0;A[i]!=NULL;i++)
		{
			temp = A->next[i];
			createGlobalTable(GT,temp);
		}
}





