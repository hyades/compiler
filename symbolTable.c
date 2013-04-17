
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

void insertft(funTable FT[],char *fname, symbol type, int recindex,char *name,int ion , int *offset)
{
	if(checkMultift(FT,fname,recindex,name))
	{
		printf("Multiple Declaration\n");
		return;
	}
	int hval,hval2,hkey=100;
	struct paralist *curr;

	struct paralist *in = (struct paralist*)malloc(sizeof(struct paralist));
	variable t;
	//printf("adding to function %s:%s\n",fname,name);

	hval = hash(fname,hkey);
	strcpy(FT[hval].fname,fname);

	t.type = type;
	t.recindex = -1;
	strcpy(t.name,name);
	t.ion = ion;
	t.offset = *offset;

	in->item = t;
	in->next = NULL;
	if(ion == 0)
	{
		curr = FT[hval].inputList;
		if(curr == NULL)
				FT[hval].inputList = in;

		else 
		{
			//curr = FT[hval].inputList;
			while(curr->next!=NULL)
				curr = curr->next;
			curr->next = in;
		}
	}

	if(ion == 1)
	{
		if(FT[hval].outputList==NULL)
			FT[hval].outputList = in;
		else 
		{
			curr = FT[hval].outputList;
			while(curr->next!=NULL)
				curr = curr->next;
			curr->next = in;
		}
	}


	hval2 = hash(name,hkey);
	strcpy(FT[hval].table[hval2].name,name);
	
	FT[hval].table[hval2].recindex = recindex;
	FT[hval].table[hval2].type = type;
	FT[hval].table[hval2].ion = ion;
	FT[hval].table[hval2].offset = *offset;
	FT[hval].table[hval2].filled = 1;
	FT[hval].filled = 1;
}

//RT,temp2->next[1]->t->lexeme,temp3->next[1]->t->s,temp3->next[2]->t->lexeme

void insertrt(recTable RT[],char *rname, symbol type, char *name)
{
	if(checkMultirt(RT,rname,name))
	{
		printf("Multiple Declaration\n");
		return;
	}
	int hval,hval2,hkey=100;

	//printf("adding to record %s:%s\n",rname,name);
	hval = hash(rname,hkey);
	strcpy(RT[hval].rname,rname);
	if(type == TK_INT)
	{
		strcat(RT[hval].str,(" int"));
		RT[hval].size+=2;
	}
	if(type == TK_REAL)
	{
		strcat(RT[hval].str,(" real"));
		RT[hval].size+=4;
	}
	hval2 = hash(name,hkey);
	strcpy(RT[hval].table[hval2].name,name);
	RT[hval].table[hval2].type = type;
	RT[hval].table[hval2].filled = 1;
	RT[hval].filled = 1;
}


//insert(GT,temp2->next[1]->t->s,temp2->next[2]->t->lexeme)

void insertgt(variable GT[],symbol type, int recindex, char *name)
{
	if(checkMultigt(GT,recindex.name))
	{
		printf("Multiple Declaration\n");
		return;
	}
	int hval,hkey=100;

	//printf("adding to global %s\n",name);
	hval = hash(name,hkey);
	strcpy(GT[hval].name,name);
	GT[hval].recindex = recindex;
	GT[hval].type = type;
	GT[hval].filled = 1;	
}

void initSymbolTable(variable GT[], funTable FT[], recTable RT[])
{
	int i,j;
	for(i=0;i<100;i++)
	{
		GT[i].filled = 0;
		GT[i].recindex = -1;

		RT[i].filled = 0;
		RT[i].str[0] = '\0';
		RT[i].size = 0;


		FT[i].filled = 0;
		FT[i].inputList = NULL;
		FT[i].outputList = NULL;


		for(j=0;j<100;j++)
		{
			FT[i].table[j].filled = 0;
			RT[i].table[j].filled = 0;
			RT[i].table[j].recindex = -1;
			FT[i].table[j].recindex = -1;
		}
	}
}


void printFT(funTable FT[], recTable RT[])
{
	int i,j;
	//printf("FUNCTION NAMES:\n");
	for(i=0;i<100;i++)
	{
		if(FT[i].filled == 1)
		{
			//printf("function:%s\n",FT[i].fname);
			for(j=0;j<100;j++)
				if(FT[i].table[j].filled == 1)
				{	
					if(FT[i].table[j].type == TK_RECORD)
					{
						//RT[FT[i].table[j].recindex].str
						printf("%-30s%-30s%-30s%-5d\n",FT[i].table[j].name,RT[FT[i].table[j].recindex].str,FT[i].fname,FT[i].table[j].offset);
					}
					else if (FT[i].table[j].type == TK_INT)
					{	
						printf("%-30s%-30s%-30s%-5d\n",FT[i].table[j].name,"int",FT[i].fname,FT[i].table[j].offset);
					}
					else if (FT[i].table[j].type == TK_REAL)
					{	
						printf("%-30s%-30s%-30s%-5d\n",FT[i].table[j].name,"real",FT[i].fname,FT[i].table[j].offset);
					}
					//printf("%-30s %-30s %d %d\n",toStr(FT[i].table[j].type),FT[i].table[j].name,FT[i].table[j].offset,FT[i].table[j].ion);
				}
		}
	}
}


void printGT(variable GT[],recTable RT[])
{
	int i,j;
	//printf("GLOBAL NAMES:\n");
	for(i=0;i<100;i++)
	{
		if(GT[i].filled == 1)
		{
			if(GT[i].type == TK_RECORD)
					{
						//RT[GT[i].table[j].recindex].str
						printf("%-30s%-30s%-30s%-5s\n",GT[i].name,RT[GT[i].recindex].str,"global","-");
					}
					else if (GT[i].type == TK_INT)
					{	
						printf("%-30s%-30s%-30s%-5s\n",GT[i].name,"int","global","-");
					}
					else if (GT[i].type == TK_REAL)
					{	
						printf("%-30s%-30s%-30s%-5s\n",GT[i].name,"real","global","-");
					}
		}
	}
}





void createInputParameterTable(funTable FT[],recTable RT[],parseTree A,char *fname, int *offset)
{

	parseTree temp;
	int i,j;
	//printf("INPUT PARS A = %s\n",toStr(A->t->s));

	if(A->t->s == TK_INT)
	{
		temp = A->parent; //temp = parameter_list
		//void insertft(funTable FT[],char *fname, symbol type, int recindex,char *name,int ion , int *offset)

		insertft(FT,fname,temp->next[0]->t->s,-1,temp->next[1]->t->lexeme,0,offset);
		*offset = *offset + 2;
	}
	else if(A->t->s == TK_REAL)
	{
		temp = A->parent; //temp = parameter_list
		//void insertft(funTable FT[],char *fname, symbol type, int recindex,char *name,int ion , int *offset)

		insertft(FT,fname,temp->next[0]->t->s,-1,temp->next[1]->t->lexeme,0,offset);
		*offset = *offset + 4;
	}	
	else if(A->t->s == TK_RECORD)
	{

		temp = A->parent->parent; //parameter_list>(constructed_datatypes>(record id & tk_record) == tk_id)
		int hkey = 100,recindex;
		recindex = hash(temp->next[0]->next[1]->t->lexeme,hkey); // = tk_recordid
		insertft(FT,fname,temp->next[0]->next[0]->t->s,recindex,temp->next[1]->t->lexeme,0,offset);
		*offset = *offset + RT[recindex].size;
	}
	else 
	{
		for(i=0;A->next[i]!=NULL;i++)
		{
			temp = A->next[i];
			createInputParameterTable(FT,RT,temp,fname,offset);
		}
	}

}

void createOutputParameterTable(funTable FT[],recTable RT[],parseTree A,char *fname, int *offset)
{

	parseTree temp;
	int i,j;
	//printf("OUTPUT PARS A = %s\n",toStr(A->t->s));

	if(A->t->s == TK_INT)
	{
		temp = A->parent; //temp = parameter_list
		//void insertft(funTable FT[],char *fname, symbol type, int recindex,char *name,int ion , int *offset)

		insertft(FT,fname,temp->next[0]->t->s,-1,temp->next[1]->t->lexeme,1,offset);
		*offset = *offset + 2;
	}
	else if(A->t->s == TK_REAL)
	{
		temp = A->parent; //temp = parameter_list
		//void insertft(funTable FT[],char *fname, symbol type, int recindex,char *name,int ion , int *offset)

		insertft(FT,fname,temp->next[0]->t->s,-1,temp->next[1]->t->lexeme,1,offset);
		*offset = *offset + 4;
	}	
	else if(A->t->s == TK_RECORD)
	{

		temp = A->parent->parent; //parameter_list>(constructed_datatypes>(record id & tk_record) == tk_id)
		int hkey = 100,recindex;
		recindex = hash(temp->next[0]->next[1]->t->lexeme,hkey); // = tk_recordid
		insertft(FT,fname,temp->next[0]->next[0]->t->s,recindex,temp->next[1]->t->lexeme,1,offset);
		*offset = *offset + RT[recindex].size;
	}
	else 
	{
		for(i=0;A->next[i]!=NULL;i++)
		{
			temp = A->next[i];
			createOutputParameterTable(FT,RT,temp,fname,offset);
		}
	}

}


createFieldRecordsTable(recTable RT[], parseTree A, char *rname)
{

	int i,j;
	parseTree temp;
	//printf("FILED REC A = %s\n",toStr(A->t->s));

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

void createFunctionDeclareTable(variable GT[],funTable FT[],recTable RT[],parseTree A,char * fname,int *offset)
{

	parseTree temp;
	int i,j;
	//printf("FUNCTION DECLARATIONS A = %s\n",toStr(A->t->s));
	if(A->t->s == TK_INT)
	{
		temp = A->parent; //temp = declaration
		//void insertft(funTable FT[],char *fname, symbol type, int recindex,char *name,int ion , int *offset)

		insertft(FT,fname,temp->next[1]->t->s,-1,temp->next[2]->t->lexeme,2,offset);
		*offset = *offset + 2;
	}
	else if(A->t->s == TK_REAL)
	{
		temp = A->parent; //temp = declaration
		//void insertft(funTable FT[],char *fname, symbol type, int recindex,char *name,int ion , int *offset)

		insertft(FT,fname,temp->next[1]->t->s,-1,temp->next[2]->t->lexeme,2,offset);
		*offset = *offset + 4;
	}	
	else if(A->t->s == TK_RECORD)
	{

		temp = A->parent->parent; //declarartion>tk_type == (constructed_datatypes>(record id & tk_record) == tk_id)
		int hkey = 100,recindex;
		recindex = hash(temp->next[1]->next[1]->t->lexeme,hkey); // = tk_recordid
		insertft(FT,fname,temp->next[1]->next[0]->t->s,recindex,temp->next[2]->t->lexeme,2,offset);
		*offset = *offset + RT[recindex].size;
	}
	else 
	{
		for(j=0;A->next[j]!=NULL;j++)
		{
			temp = A->next[j];
			createFunctionDeclareTable(GT,FT,RT,temp,fname,offset);
		}
	}
}



void createFunctionTable(variable GT[], funTable FT[], recTable RT[],parseTree A, char * fname, int *offset)
{

	parseTree temp;
	int i,j;
	//int offset = 1;
	//printf("FUNCTION TABLE A = %s\n",toStr(A->t->s));
	if(A->t->s == TK_INPUT)
	{
		//printf("INPUT = %s\n",toStr(A->t->s));
		temp = A->parent; //parent of tk_ input = input_par
		createInputParameterTable(FT,RT,temp,fname,offset);
	}
	else if(A->t->s == TK_OUTPUT) ////parent of tk_output = output_par
	{
		temp = A->parent;
		createOutputParameterTable(FT,RT,temp,fname,offset);
	}
	
	else if(A->t->s == declaration)
	{
		temp = A; //parent of tk_type = declaration
		createFunctionDeclareTable(GT,FT,RT,temp,fname,offset);
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
	//printf("MAIN FUNCTION TABLE A = %s\n",toStr(A->t->s));
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
		for(i=0;A->next[i]!=NULL;i++)
		{
			temp = A->next[i];
			createRecordTable(RT,temp);
		}


}


createGlobalTable(variable GT[],parseTree A)
{
	parseTree temp;
	int i,j;


	if(A->t->s == TK_GLOBAL)
	{
		temp = A->parent; //parent = declaration
		if(temp->next[1]->t->s == TK_INT || temp->next[1]->t->s == TK_REAL)
		{
			//void insertgt(variable GT[],symbol type, int recindex, char *name)
			insertgt(GT,temp->next[1]->t->s,-1,temp->next[2]->t->lexeme);
		}
		else
		{	
			//if TK_RECORD
			int recindex,hkey = 100;
			recindex = hash(temp->next[1]->next[1]->t->lexeme,hkey);  //temp->next[1]= constructed_datatype
			insertgt(GT,temp->next[1]->next[0]->t->s,recindex,temp->next[2]->t->lexeme);
		}
	}
	else
		for(i=0;A->next[i]!=NULL;i++)
		{
			temp = A->next[i];
			createGlobalTable(GT,temp);
		}
}