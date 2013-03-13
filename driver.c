/*
-=-=-=-=-=-=-=-=-=-=-=-=-=
BATCH 26
-=-=-=-=-=-=-=-=-=-=-=-=-=
AAYUSH AHUJA 2010A7PS023P
MAYANK GUPTA 2010A7PS022P
-=-=-=-=-=-=-=-=-=-=-=-=-=
driver.c
-=-=-=-=-=-=-=-=-=-=-=-=-=
*/
#include<ctype.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<malloc.h>
#include "lexerDef.h"
#include "lexer.h"
#include "parserDef.h"
#include "parser.h"


int main(int argc, char *argv[])
{
    FILE *s=fopen("set.txt", "r");
    FILE *g=fopen("grammar.txt", "r");
    FILE *p=fopen("parsetable.csv", "w");
    FILE *tree=fopen("tree.txt", "w");
    if(s==NULL)
    {
        printf("Sets file not found\n");
        return 0;
    }    
    if(g==NULL)
    {
        printf("Grammar file not found\n");
        return 0;
    }    
    if(p==NULL)
    {
        printf("parsetable file can not be opened\n");
        return 0;
    }    
    if(tree==NULL)
    {
        printf("tree file can not be opened\n");
        return 0;
    }
    int opt,i,fp,Gno;
    fp = open(argv[1],O_RDONLY);
    if(fp==-1)
    {
        printf("input file not found\n");
        return 0;
    }
    bool error = 0;
    Table T[60][60];
    grammar G[100];
    sets S[60];
    keyword kw[48];
    keyword kn[200];
    parseTree P;
    for(i=0; i<48; i++)
        kw[i].present=FALSE;
    keywordTable kt = kw;
    initkt(kt);
    for(i=0; i<200; i++)
        kn[i].present=FALSE;
    keywordTable nt = kn;
    initNt(nt);
    Gno=createGrammar(g,G,nt);
    createSets(s,S,nt);
    initTable(T);
    createParseTable(G,T,S,Gno);
    printTable(p, T);
    tokenList list;
    do
    {
        printf("\n 1 : Print the token list.\n 2 : Verify the syntactic correctness\n 3 : Print abstract syntax tree\n 4: Exit\n\nSelect option->");
        scanf("%d", &opt);
        switch(opt)
        {
        case 1:
            list=createTokenList(fp, kt);
            printTokenList(kt, list);
            break;
        case 2:
            P = parseInputSourceCode(fp, T, kt, G, &error);
            if(error)
                printf("error\n");
            printParseTree(P, tree);
            break;
            /*        case 3:
                        abstractSyntaxTree A;
                        createAbstractSyntaxtree(PT,A);
                        int *totalAllocatedMemory;
                        printAST(A, argv[2], totalAllocatedMemory);
                        break;
            */
        default:
            printf("\nPlease select a valid option\n");
        }
    }while(opt!=1 && opt!=2);
    fclose(s);
    fclose(g);
    fclose(p);
    fclose(tree);
    return 0;
}
