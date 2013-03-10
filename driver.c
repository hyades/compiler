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

int main(int argc, char *argv[])
{
    int opt,fp,i;
    keyword kw[48];
    for(i=0; i<48; i++)
        kw[i].present=FALSE;
    keywordTable kt = kw;
    initkt(kt);
    keyword kn[100];
    for(i=0; i<100; i++)
        kn[i].present=FALSE;
    keywordTable nt = kn;
    initNt(nt);
    fp = open(argv[1],O_RDONLY);
    if(fp==-1)
    {
        printf("input file not found");
        return 0;
    }
    tokenList list=createTokenList(fp, kt);
    do
    {
        printf("\n 1 : Print the token list.\n 2 : Verify the syntactic correctness\n 3 : Print abstract syntax tree\n 4: Exit\n\nSelect option->");
        scanf("%d", &opt);
        switch(opt)
        {
        case 1:
            printTokenList(fp ,kt, list);
            break;
/*      case 2:
            table T;
            grammar G;
            //load grammar here
            createParseTable(G,T);
            parseTree PT = parseInputSourceCode(argv[0],T);
            printParseTree(PT, argv[1]);
            break;
        case 3:
            abstractSyntaxTree A;
            createAbstractSyntaxtree(PT,A);
            int *totalAllocatedMemory;
            printAST(A, argv[2], totalAllocatedMemory);
            break;
*/
        case 4:
            break;
        default:
            printf("\nPlease select a valid option\n");
        }
    }
    while(opt!=4);
    return 0;
}
