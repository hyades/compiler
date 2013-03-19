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
    int hval,hashkey=200;
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
    int hval,hashkey=200;
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


void initSets(sets S[],grammar G[], int Gno)
{
    //printf("initSets");
    int i,j,x;
    for(i=0;i<60;i++)
    {
        S[i].nt = i+program;
        //S[i].first[60];
        S[i].firstno=0;
        S[i].followno=0;
        //S[i].follow[60];
        for(j=0;j<60;j++)S[i].ft[j]=0;
        for(j=0;j<60;j++)S[i].fw[j]=0;
        S[i].eps=0;
    }
    //printf("initSets");
    for(i=0;i<(int)(idlist-program)+1;i++)
    {    firstSets(S, G,(symbol)i+program,Gno);
      //   printf("initSets");
    }
    for(i=2;i<(int)(idlist-program)+1;i++)
    {    followSets(S, G,(symbol)i+program,Gno);
         printf("-------------initSets %s", toStr(i+program));
         //scanf("%d", &x);
    }
    // followSets(S, G,program,Gno);
}
void firstSets(sets S[], grammar G[],symbol s, int Gno)
{

    int i,j,k;
    bool flag = 0;
    //printf("HELLO");
    if(S[s - program].firstno>0)return;
    printf("%s\n", toStr(s));
    for(i=0;i<Gno;i++)
    {

        if(s==G[i].nt)
        {
            flag = 0;
            if(G[i].list[0]==TK_EPS)
            {    
                S[s-program].eps=1;
                continue;
            }
            for(j=0;!isTerminal(G[i].list[j])&&j<G[i].listno;j++)
            {
                firstSets(S,G,G[i].list[j],Gno);
                for(k=0;k<60;k++)
                    if(S[G[i].list[j]-program].ft[k]==1 && S[s-program].ft[k]==0)
                    {    
                        S[s-program].ft[k] = 1;
                        S[s-program].first[S[s-program].firstno++] = k;
                        printf("");
                    }
                if(S[G[i].list[j]-program].eps==0)
                    {
                        flag =1;
                        break;
                    }

            }
            if(flag==0&&j<G[i].listno)
            {
                S[s-program].ft[G[i].list[j]] = 1;
                S[s-program].first[S[s-program].firstno++] = G[i].list[j]; 
            }
        }   
    }
}


void printFirst(sets S[])
{
    FILE *fp = fopen("firsts","w");
    int i,j;
    for(i=0;i<idlist-program+1;i++)
    {
        fprintf(fp,"%s ",toStr(S[i].nt));
        for(j=0;j<S[i].firstno;j++)
            fprintf(fp, "%s ", toStr(S[i].first[j]));
        fprintf(fp, " , ");
        for(j=0;j<S[i].followno;j++)
            fprintf(fp, "%s ", toStr(S[i].follow[j]));
        //fprintf(fp, " , ");
        fprintf(fp,"\n");
    }
}


void followSets(sets S[], grammar G[],symbol s, int Gno)
{
    int i,j,k,l;
    bool flag = 0;
    //printf("HELLO");
    printf("%s\n", toStr(s));
    for(i=0;i<Gno;i++)
    {
        for(j=0;j<G[i].listno;j++)
            if(s==G[i].list[j])
            {
                
                flag=0;
                for(k=j+1;k<G[i].listno && !isTerminal(G[i].list[k]);k++)
                {
                    //add first of k here

                    for(l=0;l<60;l++)
                        if(S[G[i].list[k] - program].ft[l]==1 && S[s-program].fw[l]==0)
                        {
                            S[s-program].fw[l]=1;
                            S[s-program].follow[S[s-program].followno++]=l;
                        }
                    if(S[G[i].list[k] - program].eps==0)
                    {
                        flag=1;
                        break;
                    }
                }
                if(flag==0 && k==G[i].listno)
                {
                    if(G[i].nt > s)
                        followSets(S,G,G[i].nt,Gno);
                    for(l=0;l<60;l++)
                        if(S[G[i].nt - program].fw[l]==1 && S[s-program].fw[l]==0)
                        {
                            S[s-program].fw[l]=1;
                            S[s-program].follow[S[s-program].followno++]=l;
                        }
                }
                else if(flag==0 && k<G[i].listno && S[s-program].fw[G[i].list[k]]==0)
                {
                        S[s-program].fw[G[i].list[k]]=1;
                        S[s-program].follow[S[s-program].followno++]=G[i].list[k];
                }
            }   
    }
}






void createSets(FILE * fp,sets S[],keywordTable nt)
{
    char a[30];
    int i = 0,k=0,firstcount=0,followcount=0;
    while(1)
    {
        fscanf(fp,"%s",a);
        if(feof(fp))break;
        if(strcmp(a,",")==0)
        {
            k++;
        }
        else if(k==0)
        {
            S[i].nt = toSym(a,nt);
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
    return ruleNumber;
}

void createParseTable(grammar G[], Table T[][60], sets S[], int Gno)
{
    int i,j,k, inter,fir;
    for(i=0; i<Gno; i++)
    {
        for(j=0; j<G[i].listno; j++)
        {
            if(G[i].list[j]==TK_EPS)
            {
                for(k=0; k<S[G[i].nt - program].followno; k++)
                    addtoTable(G[i].nt, S[(int)(G[i].nt - program)].follow[k], i, T);
                break;
            }
            else if(isTerminal(G[i].list[j]))
            {
                addtoTable(G[i].nt, G[i].list[j], i, T);
                break;
            }

            else
            {
                inter=G[i].list[j];
                fir=(G[i].list[j]- program);
                for(k=0; k<S[fir].firstno; k++)
                {
                    addtoTable(G[i].nt, S[fir].first[k], i, T);
                }
                if (S[G[i].list[j] - program].eps == 0)
                {
                    break;
                }
            }

        }
        if(j==G[i].listno)
        {

            for(k=0; k<S[G[i].nt - program].followno; k++)
            {
                addtoTable(G[i].nt, S[(int)(G[i].nt - program)].follow[k], i, T);
            }
        }
    }

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
        fprintf(fp, "%s,", toStr(i+program));
        for(j=0; j<(int)program; j++)
            if(T[i][j]>=0)
                fprintf(fp, "%d,", T[i][j]+1);
            else
                fprintf(fp, " ,");
            fprintf(fp, "\n");
        }
        
}


bool isTerminal(symbol s)//returns true if given symbol is terminal
{
    if((int)(s-program)<0) return 1;
    return 0;
}

Stack push(Stack S,parseTree tree)
{
    if(S.top==NULL)
        S.top=createStackNode(tree);
    else{
        struct stackNode* newnode=createStackNode(tree);
        newnode->next=S.top;
        S.top=newnode;
    }
    S.size++;
    return S;
}

Stack pop(Stack S)
{
    struct stackNode* p;
    p=S.top;
    S.top=S.top->next;
    free(p);
    S.size--;
    return S;
}

struct stackNode* createStackNode(parseTree tree)
{
    struct stackNode* newnode;
    newnode=(struct stackNode*)malloc(sizeof(struct stackNode));
    newnode->tree=tree;
    newnode->next=NULL;
    return newnode;
}


parseTree createParseNode(symbol s,int lineno)
{
    int i;
    tokenInfo t;
    t=(tokenInfo)malloc(sizeof(tokenInfo));
    t->s=s;
    parseTree newnode;
    newnode=(parseTree)malloc(sizeof(struct parsetree));
    newnode->t=t;
    newnode->lineno=lineno;
    newnode->parent=NULL;
    newnode->pull=0;
    for(i=0;i<20;i++)
        newnode->next[i]=NULL;
    return newnode;
}


parseTree parseInputSourceCode(int fp,Table M[][60], keywordTable kt, grammar g[], bool*error, sets Set[])
{
    tokenInfo t;
    parseTree P;
    parseTree parent,child;
    int lineno=1 , i , k,q;
    Stack S;
    S.size=0;
    S.top=NULL;

    P=createParseNode(program,lineno);
    S=push(S,P);
    while(1)
    {
        t = getNextToken(fp, kt, error, &lineno);
        if(t==NULL || *error || t->s != TK_COMMENT)
        {
            if(*error)
            {
                printf("ERROR_5: The token %s for lexeme %s does not match at line %d. The expected token here is ",toStr(t->s), t->lexeme, lineno);
                for(k=0;k<Set[t->s].firstno-1;k++)
                    printf("%s or ", toStr(Set[t->s].first[k]));
                printf("%s\n", toStr(Set[t->s].first[k]));
            }
            break;
        }
    }

    while(!(*error) && S.size && t )
    {
        if(isTerminal(S.top->tree->t->s))
        {
            if(t->s==S.top->tree->t->s)
            {
                S.top->tree->ruleno=-1;
                strcpy(S.top->tree->t->lexeme,t->lexeme);
                free(t);
                S.top->tree->lineno=lineno;
                S=pop(S);
                while(1)
                {
                    t = getNextToken(fp, kt, error, &lineno);
                    if(t==NULL || *error==1 || t->s != TK_COMMENT)
                    {
                        if(*error)
                        {
                            if(t->s==TK_ERROR)
                                printf("ERROR_3: Unknown pattern %s\n", t->lexeme);
                            else if(t->s==TK_ERROR2)
                                printf("ERROR_2: Unknown Symbol %s at line %d\n", t->lexeme, lineno);
                            else if(strlen(t->lexeme) > 30 && t->s==TK_FUNID || strlen(t->lexeme) > 20 && t->s!=TK_FUNID)
                            {
                                q=20;
                                if(t->s==TK_FUNID)
                                    q=30;
                                printf("ERROR_1 : Identifier at line %d is longer than the prescribed length of %d characters\n", lineno,q);
                                break;
                            }
                            return NULL;
                        }
                        break;
                    }
                }
            }
            else if(S.top->tree->t->s==TK_EPS)
            {
                S.top->tree->ruleno=-1;
                S=pop(S);
            }
            else
            {
                *error=1;
                if(*error)
                {
                    printf("ERROR_5: The token %s for lexeme %s does not match at line %d. The expected token here is ",toStr(t->s), t->lexeme, lineno);
                    for(k=0;k<Set[t->s].firstno-1;k++)
                        printf("%s or ", toStr(Set[t->s].first[k]));
                    printf("%s\n", toStr(Set[t->s].first[k]));
                }
                free(t);
                break;
            }
        }
        else
        {
            i=M[S.top->tree->t->s-program][t->s];
            if(i==-1)
            {
                *error=1;
                if(*error)
                {
                    printf("ERROR_5: The token %s for lexeme %s does not match at line %d. The expected token here is ",toStr(t->s), t->lexeme, lineno);
                    for(k=0;k<Set[t->s].firstno-1;k++)
                        printf("%s or ", toStr(Set[t->s].first[k]));
                    printf("%s\n", toStr(Set[t->s].first[k]));
                }
                break;
            }
            parent=S.top->tree;
            parent->ruleno=i;
            S=pop(S);
            for(k=g[i].listno -1 ;k>=0;k--)
            {
                child=createParseNode(g[i].list[k],lineno);
                child->parent = parent;
                S=push(S,child);
                parent->next[k]=child;
            }
        }
    }

    if(!t && *error)
    {
        if(t->s==TK_ERROR)
            printf("ERROR_3: Unknown pattern %s\n", t->lexeme);
        else if(t->s==TK_ERROR2)
            printf("ERROR_2: Unknown Symbol %s at line %d\n", t->lexeme, lineno);
        return NULL;
    }
    else if(t && !S.size)
        printf("ERROR_6: %d: Program did not end prperly. It expected to end near %s\n",lineno,toStr(t->s));
    return P;
}


void printParseTree(parseTree  PT, FILE *outfile)
{
    int i;
    char empty[10], yes[20], no[20];
    strcpy(empty,"----");
    strcpy(yes, "yes");
    strcpy(no, "no");
    if(PT->next[0]==NULL)
        fprintf(outfile, "%-31s", PT->t->lexeme);
    else
        fprintf(outfile, "%-31s", empty);
    fprintf(outfile, "%-5d%-20s", PT->lineno, toStr(PT->t->s));
    if(PT->t->s==TK_NUM || PT->t->s==TK_RNUM)
        fprintf(outfile, "%-21s", PT->t->lexeme);
    else
        fprintf(outfile, "%-21s", empty);
    if(PT->parent!=NULL)
        fprintf(outfile, "%-21s", toStr(PT->parent->t->s));
    else
        fprintf(outfile, "%-21s", empty);
    if(PT->next[0]==NULL)
        fprintf(outfile, "%-5s", yes);
    else
        fprintf(outfile, "%-5s", no);
    if(!isTerminal(PT->t->s))
        fprintf(outfile, "%-21s\n", toStr(PT->t->s));
    else
        fprintf(outfile, "%-21s\n", empty);
    for(i=0;i<20 && PT->next[i]!=NULL;i++)   printParseTree(PT->next[i],outfile);
}

void copyTree(parseTree A , parseTree B)
{
    int i=0;
    A->t->s = B->t->s;
    A->lineno = B->lineno;
    if(isTerminal(B->t->s))
    {
        strcpy(A->t->lexeme,B->t->lexeme);
    }
    while(B->next[i]!=NULL)
    {
        A->next[i] = B->next[i];
        i++;
    }
    A->next[i] = NULL;
}
parseTree createAbstractSyntaxTree(parseTree T)
{
    int n = 0;
    parseTree A = NULL;
    while(T->next[n] != NULL)
        n++;
    if(n==1)
    {
        return createAbstractSyntaxTree(T->next[0]);
    }
    else if(n==0)
    {
        if(T->t->s == TK_EPS || T->t->s == TK_OP || T->t->s == TK_CL || T->t->s == TK_COLON || 
            T->t->s == TK_SEM || T->t->s == TK_SQR || T->t->s == TK_SQL || T->t->s == TK_COMMA || 
            T->t->s==TK_DOT || T->t->s==TK_CALL || T->t->s==TK_WITH || T->t->s==TK_PARAMETERS ||  
            T->t->s==TK_PARAMETER || T->t->s==TK_INPUT || T->t->s==TK_OUTPUT || T->t->s==TK_LIST)
            return NULL;
        if(isTerminal(T->t->s))
        {
            A = createParseNode(T->t->s,T->lineno);
            A->parent=T->parent;
            copyTree(A,T);
        }
        return A;
    }
    else
    {
        int j=0,k=0;
        A = createParseNode(T->t->s,T->lineno);
        A->parent=T->parent;
        parseTree temp;
        while(T->next[j]!=NULL)
        {
            if(T->next[j]->t->s == TK_OP || T->next[j]->t->s==TK_CL || T->next[j]->t->s==TK_COLON || T->next[j]->t->s==TK_SEM || 
                T->next[j]->t->s==TK_SQR || T->next[j]->t->s==TK_SQL || T->next[j]->t->s==TK_COMMA || T->next[j]->t->s==TK_DOT || 
                T->next[j]->t->s==TK_CALL || T->next[j]->t->s==TK_WITH || T->next[j]->t->s==TK_PARAMETERS || T->next[j]->t->s==TK_PARAMETER || 
                T->next[j]->t->s==TK_INPUT || T->next[j]->t->s==TK_OUTPUT || T->next[j]->t->s==TK_LIST)
            {
                j++;
                continue;
            }
            temp = createAbstractSyntaxTree(T->next[j]);
            if(temp != NULL)
            {
                A->next[k] = temp;
                temp->parent = A;
                k++;
            }
            j++;
        }
        j = 0;
        int m = 0, f=0;
        while(A->next[j] != NULL)
        {
            if((A->next[j]->t->s == TK_PLUS || A->next[j]->t->s==TK_MINUS || A->next[j]->t->s == TK_MUL || A->next[j]->t->s==TK_DIV || 
                A->next[j]->t->s==TK_LE || A->next[j]->t->s==TK_LT || A->next[j]->t->s==TK_GT || A->next[j]->t->s==TK_GE || 
                A->next[j]->t->s==TK_NE || A->next[j]->t->s==TK_IF) && (!A->next[j]->pull))
            {
                f = 1;
                m = j;
            }
            j++;
        }
        if(j==1)
        {
            if(!isTerminal(A->t->s))
            {
                copyTree(A,A->next[0]); 
            }
        }
        else if(j==0)
        {
            free(A);
            return NULL;
            
        }
        else if(f)
        {
            A->t->s = A->next[m]->t->s;
            A->lineno = A->next[m]->lineno;
            if(isTerminal(A->next[m]->t->s))
            {
                strcpy(A->t->lexeme,A->next[m]->t->lexeme);
            }
            A->pull = 1;
            m++;
            while(A->next[m] != NULL)
            {
                A->next[m-1] = A->next[m];
                m++;
            }
            A->next[m-1] = NULL;
        }
        return A;
    }
}


void printAST(parseTree PT, FILE *outfile, int *totalAllocatedMemory)
{
    int i;
    char empty[10], yes[20], no[20];
    strcpy(empty,"----");
    strcpy(yes, "yes");
    strcpy(no, "no");
    *totalAllocatedMemory+=sizeof(PT);
    if(PT->next[0]==NULL)
        fprintf(outfile, "%-31s", PT->t->lexeme);
    else
        fprintf(outfile, "%-31s", empty);
    fprintf(outfile, "%-5d%-20s", PT->lineno, toStr(PT->t->s));
    if(PT->t->s==TK_NUM || PT->t->s==TK_RNUM)
        fprintf(outfile, "%-21s", PT->t->lexeme);
    else
        fprintf(outfile, "%-21s", empty);
    if(PT->parent!=NULL)
        fprintf(outfile, "%-21s", toStr(PT->parent->t->s));
    else
        fprintf(outfile, "%-21s", empty);
    if(PT->next[0]==NULL)
        fprintf(outfile, "%-5s", yes);
    else
        fprintf(outfile, "%-5s", no);
    if(!isTerminal(PT->t->s))
        fprintf(outfile, "%-21s\n", toStr(PT->t->s));
    else
        fprintf(outfile, "%-21s\n", empty);
    for(i=0;i<20 && PT->next[i]!=NULL;i++)   printParseTree(PT->next[i],outfile);
}