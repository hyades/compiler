/*
-=-=-=-=-=-=-=-=-=-=-=-=-=
BATCH 26
-=-=-=-=-=-=-=-=-=-=-=-=-=
AAYUSH AHUJA 2010A7PS023P
MAYANK GUPTA 2010A7PS022P
-=-=-=-=-=-=-=-=-=-=-=-=-=

*/

#include<stdio.h>
#include<ctype.h>
#include<string.h>

#include"lexer.h"

tokenInfo getNextToken(FILE *fp)
{

    tokeninfo t;
    static bool back = 0;
    int state = 1,i=0
    char c;
    char lexeme[100];

    while(1)
    {

        switch(state)
        {
            case 1:
                    c = getNextChar(fp,&back);
                    if(int(c)==EOF)return NULL;
                    else if(c=='-')state = 2;
                    else if(c=='!')state = 3;
                    else if(c=='#')state = 5;
                    else if(c=='%')state = 7;
                    else if(c=='&')state = 8;
                    else if(c=='(')state = 11;
                    else if(c==')')state = 12;
                    else if(c=='*')state = 13;
                    else if(c=='.')state = 14;
                    else if(c=='/')state = 15;
                    else if(c==':')state = 16;
                    else if(c==';')state = 17;
                    else if(c=='@')state = 18;
                    else if(c=='[')state = 21;
                    else if(c==']')state = 30;
                    else if(c=='_')state = 31;
                    else if(c=='~')state = 34;
                    else if(c=='+')state = 35;
                    else if(c=='<')state = 36;
                    else if(c=='=')state = 41;
                    else if(c=='>')state = 43;
                    else if(isdigit(c))state = 22;
                    else if((c=='a')||(c>='e'&&c<='z'))state = 26;
                    else if(c>='b'&&c<='d')state = 27;
                    else if(c==' '||c=='\t'||c=='\n')state = 45;
                    else
                    {
                        *error = TRUE;
                        return NULL;
                    }
                    break;

            case 2:
                    t = (tokenInfo)malloc(sizeof(tokenInfo));
                    t->s = TK_MINUS;
                    return t;

            case 3:
                    c = getNextChar(fp,&back);
                    if(c=='=')state = 4;
                    break;
            case 4:
                    t = (tokenInfo)malloc(sizeof(tokenInfo));
                    t->s = TK_NT;
                    return t;
            case 5:
                    c = getNextChar(fp,&back);
                    if(c>='a'&&c<='z')state =6;
                    break;

            case 6:
                    c = getNextChar(fp,&back);
                    if(c>='a'&&c<='z')state =6;
                    else
                    {
                        t = (tokenInfo)malloc(sizeof(tokenInfo));
                        t->s = TK_RECORDID;
                    }
                    break;







        }
    }
}



