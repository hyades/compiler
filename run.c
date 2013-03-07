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

int main()
{
    int fp,i;
    tokenInfo t;
    keyword kt[48];
    for(i=0; i<48; i++)
        kt[i].present=FALSE;
    fp = open("input.txt",O_RDONLY);
    if(fp==-1)
    {
        printf("not found");
        return 0;
    }
    int linenumber = 1;
    bool error = 0;
    initkt(kt);
        FILE *f = fopen("tokens.txt","w");
        while(1)
        {
            t = getNextToken(fp,kt,&error,&linenumber);
            if(t==NULL)break;
            if(t->lexeme)
                fprintf(f,"[ %s %s %d ]\n",toStr(t->s),t->lexeme,linenumber);
            else
                fprintf(f,"[ %s %d ]\n",toStr(t->s),linenumber);
        }
    close(fp);
        return 0;

}
