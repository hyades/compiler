/*
-=-=-=-=-=-=-=-=-=-=-=-=-=
BATCH 26
-=-=-=-=-=-=-=-=-=-=-=-=-=
AAYUSH AHUJA 2010A7PS023P
MAYANK GUPTA 2010A7PS022P
-=-=-=-=-=-=-=-=-=-=-=-=-=
parser.c
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

symbol toSym(char *a, keywordTable nt)//return Symbol for given string
{
    int hval,hashkey=2000;
    hval=hash(a,hashkey);
    symbol s;
    while(1)
    {
        if(nt[hval].present==FALSE)
        {
            s=TK_ERROR;
            return s;
        }
        else if(!strcmp(a,nt[hval].keyword))
        {
            s=nt[hval].s;
            return s;
        }
        hval++;
        hval=hval%hashkey;
    }
}

void addNt(keywordTable nt, char *keyword, symbol s)//recursively called to add keyword to keywordTable
{
    int hval,hashkey=2000;
    hval=hash(keyword,hashkey);
    while(nt[hval].present==TRUE)
        hval=(++hval)%hashkey;
    strcpy(nt[hval].keyword, keyword);
    nt[hval].present=TRUE;
    nt[hval].s=s;
}

void initNt(keywordTable nt)
{
    addNt(nt,"program",program);
    addNt(nt,"mainfunction",mainfunction);
    addNt(nt,"otherfunctions",otherfunctions);
    addNt(nt,"function",function);
    addNt(nt,"input_par",input_par);
    addNt(nt,"output_par",output_par);
    addNt(nt,"constructeddatatype",constructeddatatype);
    addNt(nt,"remaining_list",remaining_list);
    addNt(nt,"parameter_list",parameter_list);
    addNt(nt,"stmts",stmts);
    addNt(nt,"typedefinitions",typedefinitions);
    addNt(nt,"typedefinition",typedefinition);
    addNt(nt,"fielddefinitions",fielddefinitions);
    addNt(nt,"primitivedatatype",primitivedatatype);
    addNt(nt,"fielddefinition",fielddefinition);
    addNt(nt,"morefields",morefields);
    addNt(nt,"declarations",declarations);
    addNt(nt,"declaration",declaration);
    addNt(nt,"datatype",datatype);
    addNt(nt,"global_or_not",global_or_not);
    addNt(nt,"assignmentstmt",assignmentstmt);
    addNt(nt,"funcallstmt",funcallstmt);
    addNt(nt,"outputparameters",outputparameters);
    addNt(nt,"inputparameters",inputparameters);
    addNt(nt,"iterativestmt",iterativestmt);
    addNt(nt,"conditionalstmt",conditionalstmt);
    addNt(nt,"elsepart",elsepart);
    addNt(nt,"stmt",stmt);
    addNt(nt,"otherstmts",otherstmts);
    addNt(nt,"iostmt",iostmt);
    addNt(nt,"singleorrecid",singleorrecid);
    addNt(nt,"allvar",allvar);
    addNt(nt,"expprime",expprime);
    addNt(nt,"term",term);
    addNt(nt,"termprime",termprime);
    addNt(nt,"factor",factor);
    addNt(nt,"arithmeticexpression",arithmeticexpression);
    addNt(nt,"highprecedenceoperators",highprecedenceoperators);
    addNt(nt,"lowprecedenceoperators",lowprecedenceoperators);
    addNt(nt,"all",all);
    addNt(nt,"temp",temp);
    addNt(nt,"booleanexpression",booleanexpression);
    addNt(nt,"var",var);
    addNt(nt,"logicalop",logicalop);
    addNt(nt,"relationalop",relationalop);
    addNt(nt,"returnstmt",returnstmt);
    addNt(nt,"optionalreturn",optionalreturn);
    addNt(nt,"more_ids",more_ids);
    addNt(nt,"idlist",idlist);
    addNt(nt,"TK_MINUS",TK_MINUS );
    addNt(nt,"TK_NE",TK_NE );
    addNt(nt,"TK_RECORDID",TK_RECORDID );
    addNt(nt,"TK_COMMENT",TK_COMMENT );
    addNt(nt,"TK_AND",TK_AND );
    addNt(nt,"TK_OP",TK_OP );
    addNt(nt,"TK_CL",TK_CL );
    addNt(nt,"TK_MUL",TK_MUL );
    addNt(nt,"TK_DOT",TK_DOT );
    addNt(nt,"TK_DIV",TK_DIV );
    addNt(nt,"TK_COLON",TK_COLON );
    addNt(nt,"TK_SEM",TK_SEM );
    addNt(nt,"TK_OR",TK_OR );
    addNt(nt,"TK_SQL",TK_SQL );
    addNt(nt,"TK_NUM",TK_NUM );
    addNt(nt,"TK_RNUM",TK_RNUM );
    addNt(nt,"TK_FIELDID",TK_FIELDID );
    addNt(nt,"TK_ID",TK_ID );
    addNt(nt,"TK_SQR",TK_SQR );
    addNt(nt,"TK_FUNID",TK_FUNID );
    addNt(nt,"TK_MAIN",TK_MAIN );
    addNt(nt,"TK_NOT",TK_NOT );
    addNt(nt,"TK_PLUS",TK_PLUS );
    addNt(nt,"TK_LT",TK_LT );
    addNt(nt,"TK_ASSIGNOP",TK_ASSIGNOP );
    addNt(nt,"TK_LE",TK_LE );
    addNt(nt,"TK_EQ",TK_EQ );
    addNt(nt,"TK_GT",TK_GT );
    addNt(nt,"TK_GE",TK_GE );
    addNt(nt,"TK_CALL",TK_CALL );
    addNt(nt,"TK_ELSE",TK_ELSE );
    addNt(nt,"TK_END",TK_END );
    addNt(nt,"TK_ENDIF",TK_ENDIF );
    addNt(nt,"TK_ENDRECORD",TK_ENDRECORD );
    addNt(nt,"TK_ENDWHILE",TK_ENDWHILE );
    addNt(nt,"TK_GLOBAL",TK_GLOBAL );
    addNt(nt,"TK_IF",TK_IF );
    addNt(nt,"TK_INPUT",TK_INPUT );
    addNt(nt,"TK_INT",TK_INT );
    addNt(nt,"TK_INT",TK_INT );
    addNt(nt,"TK_LIST",TK_LIST );
    addNt(nt,"TK_OUTPUT",TK_OUTPUT );
    addNt(nt,"TK_PARAMETER",TK_PARAMETER );
    addNt(nt,"TK_PARAMETERS",TK_PARAMETERS );
    addNt(nt,"TK_READ",TK_READ );
    addNt(nt,"TK_REAL",TK_REAL );
    addNt(nt,"TK_REAL",TK_REAL );
    addNt(nt,"TK_RECORD",TK_RECORD );
    addNt(nt,"TK_RETURN",TK_RETURN );
    addNt(nt,"TK_THEN",TK_THEN );
    addNt(nt,"TK_TYPE",TK_TYPE );
    addNt(nt,"TK_WHILE",TK_WHILE );
    addNt(nt,"TK_WITH",TK_WITH );
    addNt(nt,"TK_WRITE",TK_WRITE );
    addNt(nt,"TK_COMMA",TK_COMMA );
    addNt(nt,"eps",TK_EPS );
}

int createSets(FILE * fp,sets S[],keywordTable nt)
{
    char a[30];
    int i = 0,k=0,firstcount=0,followcount=0;
    while(1)
    {
        fscanf(fp,"%s",a);
        if(feof(fp))break;
        //printf("%s\n",a);
        if(strcmp(a,",")==0)
        {
            k++;
            //printf("COMMA\n");
        }
        else if(k==0)
        {
            //printf("k=0\n");
            S[i].nt = toSym(a,nt);
            //printf("a = %s value = %s\n",a,toStr(toSym(a,nt)));
            firstcount = 0;
            followcount = 0;

        }
        else if(k==1)
        {
            S[i].first[firstcount]  = toSym(a,nt);
            firstcount++;
        }
        else if(k==2)
        {
            S[i].follow[followcount] = toSym(a,nt);
            followcount++;
            //printf("k=3 folllow=%d\n",follow);

        }
        else if(k==3)
        {
            if(strcmp(a,"yes")==0)
                S[i].eps = 1;
            else
                S[i].eps = 0;
            S[i].firstno = firstcount;
            S[i].followno = followcount;
            i++;
            k=0;

        }



    }
    return i;
}

int createGrammar(FILE * fp,grammar G[], keywordTable nt)//load grammar from text file
{
    char a[30];
    int k = 0;
    int ruleNumber = 0;
    int listno = 0;
    while(1)
    {
        fscanf(fp,"%s",a);
        if(feof(fp))break;
        if(k==0)
        {
            G[ruleNumber].ruleNumber = ruleNumber;
            G[ruleNumber].nt = toSym(a,nt);
            k++;
            listno = 0;
        }
        else if(k==1)
        {
            if(strcmp(a,".")==0)
            {
                k=0;
                G[ruleNumber].listno = listno;
                ruleNumber++;
                continue;
            }
            G[ruleNumber].list[listno++] = toSym(a,nt);
        }
    }
    //printf("\n\n\n\nGno = %d\n\n\n\n", ruleNumber);
    return ruleNumber;
}

void createParseTable(grammar G[], Table T[][60], sets S[], int Gno)
{
    int i,j,k, inter,fir;
    for(i=0; i<Gno; i++)
    {
        for(j=0; j<G[i].listno; j++)
        {

            //printf("NT:%d no.:%d thing:%d ",G[i].nt,G[i].listno,G[i].list[j]);
            if(G[i].list[j]==TK_EPS)
            {
                for(k=0; k<S[G[i].nt - program].followno; k++)
                    //T[(int)(G[i].nt-program)][(int)S[G[i].nt].follow[k]]=i;
                    addtoTable(G[i].nt, S[(int)(G[i].nt - program)].follow[k], i, T);
                break;
            }
            else if(isTerminal(G[i].list[j]))
            {
                //printf("Yes\n");
                //T[(int)(G[i].nt-program)][(int)G[i].list[j]]=i;
                //printf("Symbol= %s Terminal found: %s\n",toStr(G[i].nt),toStr(G[i].list[j]));
                addtoTable(G[i].nt, G[i].list[j], i, T);
                break;
            }
            //printf("\n");

            else
            {
                //printf("%d\n", S[G[i].list[j] - program].firstno);
                inter=G[i].list[j];
                fir=(G[i].list[j]- program);
                //printf("Symbol %s Non terminal found:%s\t",toStr(G[i].nt),toStr(G[i].list[j]));
                for(k=0; k<S[fir].firstno; k++)
                {
                    //T[(int)(G[i].nt-program)][(int)(S[(int)(G[i].list[j]- program)]).first[k]]=i;

                    //printf("%d %d %d    ", inter, fir,k);
                    //printf("intermediate:%s , first=%s\n", toStr(inter), toStr(S[fir].first[k]));
                    //printf("\t Adding to table: %s",toStr(S[fir].first[k]));
                    addtoTable(G[i].nt, S[fir].first[k], i, T);
                }
                if (S[G[i].list[j] - program].eps == 0)
                {
                    //printf("doesnt goes to eps\n");
                    break;
                }
                //else printf("goes to eps\n");
            }

        }
        //printf("j: %d list no :%d\t",j,G[i].listno);
        if(j==G[i].listno)
        {

            for(k=0; k<S[G[i].nt - program].followno; k++)
            {
                //T[(int)(G[i].nt-program)][(int)S[G[i].nt].follow[k]]=i;
                addtoTable(G[i].nt, S[(int)(G[i].nt - program)].follow[k], i, T);
                //printf("Adding follow set :%s\n",toStr(S[(int)(G[i].nt - program)].follow[k]));
            }
        }
    }
    //printf("\n\n\n\ni=%d\n\n\n\n", i);

}

void initTable(Table T[][60])//initialize parser table with no rule
{
    int i,j;
    for(i=0; i<60; i++)
        for(j=0; j<60; j++)
            T[i][j]=-1;
}

void addtoTable(symbol nt, symbol t, int ruleno, Table T[][60])//insert rule in table
{
    //printf("nt= %s t=%s\n",toStr(nt),toStr(t));
    T[(int)(nt-program)][(int)t]=ruleno;
}

void printTable(FILE *fp, Table T[][60])//print parser table
{
    int i,j;
    for(i=-1; i<(int)program; i++)
        fprintf(fp, "%s,", toStr(i));
    fprintf(fp, "\n");
    for(i=0; i<(int)idlist - (int)program + 1 ; i++)
    {
        fprintf(fp, "%s\t", toStr(i+program));
        for(j=0; j<(int)program; j++)
            if(T[i][j]>=0)
                fprintf(fp, "%d,", T[i][j]+1);
            else
                fprintf(fp, " ,");
        fprintf(fp, "\n");
    }
    for(i=0; i<=(int)idlist - (int)program; i++)
    {
        for(j=0; j<(int)program; j++)
            printf("%d ",T[i][j]+1);
        printf("\n");
    }
}

bool isTerminal(symbol s)//returns true if given symbol is terminal
{
    //printf("value:%d\n",s-program);
    if((int)(s-program)<0) return 1;
    return 0;
}

Stack stack_push(Stack S,parseTree t)
{
    if(S.top==NULL)
        S.top=t;
    else
    {
        t->stacknext = S.top;
        S.top=t;
    }
    S.size++;
    
    return S;
}

Stack stack_pop(Stack S)
{
    parseTree p;
    p=S.top;
    S.top=S.top->stacknext;
    free(p);
    S.size--;
    return S;
}

parseTree stack_top(Stack S)
{
    return S.top;
}



parseTree createParseNode(char * lexeme,int lineno,symbol s,parseTree parent)
{
	parseTree temp;
	int i;
    temp = (parseTree)malloc(sizeof(parseTree));
    strcpy(temp->lexeme,lexeme);
    temp->lineno = lineno;
    temp->visited = 0;
    temp->s = s;
    temp->parent = parent;
    temp->stacknext = NULL;
    for(i=0;i<20;i++)temp->child[i] = NULL;
    printf("created new node with %s\n",toStr(temp->s));	
    return temp;
}

parseTree  parseInputSourceCode(int fd, Table T[][60], keywordTable kt, grammar G[])
{
	Stack ST;
	parseTree q;
	ST.top = NULL;
	ST.size = 0;
	parseTree temp,newnode;
	parseTree PT = createParseNode("program",0,program,NULL);
	ST = stack_push(ST,PT);
	tokenInfo t;
	bool error = 0;
	int linenumber=0,rule,i,j;
	printf("stack top : %d size:%d\n",(ST.top->s),ST.size);
	q = ST.top;
	printf("stack q : %d \n",(q->s));
	t = getNextToken(fd,kt,&error,&linenumber);
	ST.top = q;
	printf("stack q : %d t:%d \n",&q,&t);
	printf("stack top : %d size:%d\n",(ST.top->s),ST.size);
	printf("read: %s\n",toStr(t->s));
	//printf("stack top : %s\n",toStr(S.top->s));
	while(!error && ST.size)
	
	{	
		//printf("stack top : %s\n",toStr(S.top->s));
		if(isTerminal(ST.top->s))
		{
			printf("terminal %s\n",toStr(t->s));
			if(stack_top(ST)->s == t->s)
			{
				stack_pop(ST);
				free(t);
				t = getNextToken(fd, kt, &error, &linenumber);
				printf("read: %s\n",toStr(t->s));
				
			}
			else
			{
				error = 1;
				printf("ERROR\n");
			}
		}
		else
		{	
			printf("NON-terminal %s\n",toStr(t->s));
			i = (int)(ST.top->s-program);
			j = (int)(t->s);
			rule = T[i][j];
			if(rule==-1)
			{
				error=1;
				printf("%d: Unexpected %s.",linenumber,t->lexeme);
				break;
			}		
			temp = stack_top(ST);			
			for(i = G[rule].listno-1;i>=0;i--)
			{				
				newnode = createParseNode(t->lexeme,linenumber,t->s,temp);
				temp->child[i] = newnode;
				ST = stack_push(ST,newnode);
			}
			
		}	
	}
	return PT;
}

void printParseTree(parseTree  PT, FILE *outfile)
{	
	int j;
	while(1)
	{
		printf("%s \n",toStr(PT->s));
		PT->visited = 1;
		for(j=0;j<20;j++)
		{
			if(PT->child[j])
				if(PT->child[j]->visited==0)
					{
						PT = PT->child[j];
						break;
					}
			
		}
		if(j==20)
		{
			if(PT->s == program)break;
			else
				PT = PT->parent;
		}
	}	

}


