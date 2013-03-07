/*
-=-=-=-=-=-=-=-=-=-=-=-=-=
BATCH 26
-=-=-=-=-=-=-=-=-=-=-=-=-=
AAYUSH AHUJA 2010A7PS023P
MAYANK GUPTA 2010A7PS022P
-=-=-=-=-=-=-=-=-=-=-=-=-=
run.c
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


char* toStr ( symbol s )
{
    switch(s)
    {
        case TK_MAIN:return "TK_MAIN";

    }

}
int main()
{
    int fp;
    tokenInfo t;
    keywordTable kt;
    fp = open("input.txt",O_RDONLY);
    int linenumber = 1;
    bool error = 0;
    initkt(kt);
    FILE *f = fopen("tokens.txt","w");
    while(1)
    {
        t = getNextToken(fp,kt,&error,&linenumber);
        if(!t)break;
        if(t->lexeme)
            fprintf(f,"[ %s %s %d ]\n",toStr(t->s),t->lexeme,linenumber);
        else
            fprintf(f,"[ %s %d ]\n",toStr(t->s),linenumber);
    }

    return 0;
}
