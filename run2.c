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
    FILE *set=fopen("sets.txt", "r");
    FILE *grammar=fopen("rules.txt", "r");
    FILE *fp=fopen("parsetable.txt", "w");
    Table T[60][60];
    grammar G[70];
    sets S[60];
    keyword kn[200];
    for(i=0; i<200; i++)
        kn[i].present=FALSE;
    keywordTable nt = kn;
    initNt(nt);
    createGrammar(grammar, )

    return 0;
}
