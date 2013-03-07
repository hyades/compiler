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

tokenInfo getNextToken(FILE *fp)//get next token
{

    tokeninfo t;
    static bool back = 0;
    int state=1,i=0;
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
            break;

        case 3:
            c = getNextChar(fp,&back);
            if(c=='=')state = 4;
            break;
        case 4:
            t = (tokenInfo)malloc(sizeof(tokenInfo));
            t->s = TK_NT;
            return t;
            break;
        case 5:
            c = getNextChar(fp,&back);
            if(c>='a'&&c<='z')state =6;
            break;

        case 6:
            c = getNextChar(fp,&back);
            if(c>='a'&&c<='z')
            {
                state = 6;
                lexeme[i++] = c;
            }

            else
            {
                t = (tokenInfo)malloc(sizeof(tokenInfo));
                t->s = TK_RECORDID;
                strcpy(t->lexeme,lexeme);
                return t;
            }
            break;

        case 7:
            t = (tokenInfo)malloc(sizeof(tokenInfo));
            t->s = TK_COMMENT;
            return t;
            break;
        case 8:
            c = getNextChar(fp,&back);
            if(c=='&')
            {
                state = 9;
                lexeme[i++] = c;
            }
            break;

        case 9:
            c = getNextChar(fp,&back);
            if(c=='&')
            {
                state = 10;
                lexeme[i++] =c;

            }
            break;
        case 10:
            t = (tokenInfo)malloc(sizeof(tokenInfo));
            strcpy(t->lexeme,lexeme);
            t->s = TK_AND;
            return t;
            break;
        case 11:
            t = (tokenInfo)malloc(sizeof(tokenInfo));
            t->s = TK_OP;
            return t;
            break;
        case 12:
            t = (tokenInfo)malloc(sizeof(tokenInfo));
            t->s = TK_CL;
            return t;
            break;
        case 13:
            t = (tokenInfo)malloc(sizeof(tokenInfo));
            t->s = TK_MUL;
            return t;
            break;
        case 14:
            t = (tokenInfo)malloc(sizeof(tokenInfo));
            t->s = TK_DOT;
            return t;
            break;
        case 15:
            t = (tokenInfo)malloc(sizeof(tokenInfo));
            t->s = TK_DIV;
            return t;
            break;
        case 16:
            t = (tokenInfo)malloc(sizeof(tokenInfo));
            t->s = TK_COLON;
            return t;
            break;
        case 17:
            t = (tokenInfo)malloc(sizeof(tokenInfo));
            t->s = TK_SEM;
            return t;
            break;
        case 18:
            c = getNextChar(fp,&back);
            if(c=='@')
            {
                lexeme[i++] = c;
                state = 19;
            }
            break;
        case 19:
            c = getNextChar(fp,&back);
            if(c=='@')
            {
                lexeme[i++] = c;
                state = 20;
            }
            break;
        case 20:
            t = (tokenInfo)malloc(sizeof(tokenInfo));
            t->s = TK_OR;
            strcpy(t->lexeme,lexeme);
            return t;
            break;
        case 21:
            t = (tokenInfo)malloc(sizeof(tokenInfo));
            t->s = TK_SQL;
            return t;
            break;
        case 30:
            t = (tokenInfo)malloc(sizeof(tokenInfo));
            t->s = TK_SQR;
            return t;
            break;
        case 31:
            //take care of _main lexeme use lookup

        case 34:
            t = (tokenInfo)malloc(sizeof(tokenInfo));
            t->s = TK_NOT;
            return t;
            break;
        case 35:
            t = (tokenInfo)malloc(sizeof(tokenInfo));
            t->s = TK_PLUS;
            return t;
            break;
        case 36:
            //todo
        case 41:
            //todo
        case 43:
            //todo








        }
    }
}

FILE *getStream(FILE *fp, buffer B, buffersize k)//reads k characters from source file into buffer B
{
    int ch, i=0;
    for (ch = fgetc(fp); ch != EOF && ch != '\n' && i<k; ch = fgetc(fp))
        B[i++] = (char)ch;
    return fp;
}


char getNextChar(FILE *fp, bool *back)//gets next character from source file at position x
{
    static int x=0,k=100;
    static buffer b1=(buffer)malloc(sizeof(buffer));
    static buffer b2=(buffer)malloc(sizeof(buffer));
    x%=k*2;
    if(*back==TRUE)
    {
        x--;
        x+=k*2;
        x%=k*2;
        *back=FALSE;
    }
    else
    {
        if(x==0)
            fp=getStream(fp, b1, k);
        else if(x==100)
            fp=getStream(fp, b2, k);
    }
    if(fp==EOF)
    {
        x++;
        return (char)EOF;
    }
    if(x<100)
        return *b1[x++];
    return *b2[x++-100];
}

void addKeyword(keywordTable kt, char *keyword, symbol s)//recursively called to add keyword to keywordTable
{
    int hval,hashkey=48;//twice the no. of keywords
    hval=hash(keyword);
    while(kt[h].present==TRUE)
        hval=(++hval)%hashkey;
    strcpy(kt[hval].keyword, keyword);
    KT[hval].present=TRUE;
    KT[hval].s=s;
}

int hash(char *keyword, int hashkey)//hash function
{
    int hval=0,mul=3,i=0;
    while(keyword[i]!='\0')
        hval=(hval*mul+s[i++])%hashkey;
    return hval;
}

void initkt(keywordTable kt)//initialize keywordTable with keywords
{
    addKeyword(kt, "_main", TK_MAIN );
    addKeyword(kt, "call", TK_CALL);
    addKeyword(kt, "else", TK_ELSE);
    addKeyword(kt, "end", TK_END);
    addKeyword(kt, "endif", TK_ENDIF);
    addKeyword(kt, "endrecord", TK_ENDRECORD);
    addKeyword(kt, "endwhile", TK_ENDWHILE);
    addKeyword(kt, "global", TK_GLOBAL);
    addKeyword(kt, "if", TK_IF);
    addKeyword(kt, "input", TK_INPUT);
    addKeyword(kt, "int", TK_INT);
    addKeyword(kt, "list", TK_LIST);
    addKeyword(kt, "output", TK_OUTPUT);
    addKeyword(kt, "parameter", TK_PARAMETER);
    addKeyword(kt, "parameters", TK_PARAMETERS);
    addKeyword(kt, "read", TK_READ);
    addKeyword(kt, "real", TK_REAL);
    addKeyword(kt, "record", TK_RECORD);
    addKeyword(kt, "return", TK_RETURN);
    addKeyword(kt, "then", TK_THEN);
    addKeyword(kt, "type", TK_TYPE);
    addKeyword(kt, "while", TK_WHILE);
    addKeyword(kt, "with", TK_WITH);
    addKeyword(kt, "write", TK_WRITE);
}

ptoken keywordId(char *lexeme, keywordTable kt)//returns token for lexeme if it is a keyword or fieldname
{
    int hval,hashkey=48;//twice the no. of keywords
    ptoken t=(ptoken)malloc(sizeof(ptoken));
    strcpy(t->lexeme,lexeme);
    hval=hash(lexeme,hashkey);
    while(1)
    {
        if(kt[hval].present==FALSE)
        {
            t->s=TK_ID;
            return t;
        }
        else if(!strcmp(lexeme,kt[hval].keyword))
        {
            t->s=kt[hval].s;
            return t;
        }
        hval++;
        hval=hval%hashkey;
    }
}

ptoken mainFun(char *lexeme, keywordTable kt)//returns token for lexeme if it is main or function
{
    strcpy(t->lexeme,lexeme);
    if(!strcmp(lexeme, "_main"))
    {
        t->s=TK_MAIN;
        return t;
    }
    t->=TK_FUNID;
    return t;
}
