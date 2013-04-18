/*
-=-=-=-=-=-=-=-=-=-=-=-=-=
BATCH 26
-=-=-=-=-=-=-=-=-=-=-=-=-=
AAYUSH AHUJA 2010A7PS023P
MAYANK GUPTA 2010A7PS022P
-=-=-=-=-=-=-=-=-=-=-=-=-=
lexer.c
-=-=-=-=-=-=-=-=-=-=-=-=-=
*/

#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include"lexerDef.h"
#include"lexer.h"

extern bool any_error;
tokenInfo getNextToken(int fp ,keywordTable kt, bool *error, int *linenumber)//get next token
{

    tokenInfo t;
    static int back = 0;
    int state=1,i=0;
    char c;
    char lexeme[100] = {}; //assuming max lexeme size as 100

    while(1)
    {

        switch(state)
        {
        case 1:
            c = getNextChar(fp,&back);
            //printf(" %c ",c);
            if((int)c==EOF)return NULL;
            else if(c=='-')
            {
                state = 2;
                lexeme[i++] = c;
            }
            else if(c=='!')
            {
                state = 3;
                lexeme[i++] = c;
            }
            else if(c=='#')
            {
                state = 5;
                lexeme[i++] = c;
            }
            else if(c=='%')
            {
                state = 7;
                lexeme[i++] = c;
            }
            else if(c=='&')
            {
                state = 8;
                lexeme[i++] = c;
            }
            else if(c=='(')
            {
                state = 11;
                lexeme[i++] = c;
            }
            else if(c==')')
            {
                state = 12;
                lexeme[i++] = c;
            }
            else if(c=='*')
            {
                state = 13;
                lexeme[i++] = c;
            }
            else if(c=='.')
            {
                state = 14;
                lexeme[i++] = c;
            }
            else if(c=='/')
            {
                state = 15;
                lexeme[i++] = c;
            }
            else if(c==':')
            {
                state = 16;
                lexeme[i++] = c;
            }
            else if(c==';')
            {
                state = 17;
                lexeme[i++] = c;
            }
            else if(c==',')
            {
                state = 47;
                lexeme[i++] = c;
            }
            else if(c=='@')
            {
                state = 18;
                lexeme[i++] = c;
            }
            else if(c=='[')
            {
                state = 21;
                lexeme[i++] = c;
            }
            else if(c==']')
            {
                state = 30;
                lexeme[i++] = c;
            }
            else if(c=='_')
            {
                state = 31;
                lexeme[i++] =c;
            }
            else if(c=='~')
            {
                state = 34;
                lexeme[i++] = c;
            }
            else if(c=='+')
            {
                state = 35;
                lexeme[i++] = c;
            }
            else if(c=='<')
            {
                state = 36;
                lexeme[i++] = c;
            }
            else if(c=='=')
            {
                state = 41;
                lexeme[i++] = c;
            }
            else if(c=='>')
            {
                state = 43;
                lexeme[i++] = c;
            }
            else if(isdigit(c))
            {
                state = 22;
                lexeme[i++] = c;
            }
            else if((c=='a')||(c>='e'&&c<='z'))
            {
                state = 26;
                lexeme[i++] =c;
            }
            else if(c>='b'&&c<='d')
            {
                state = 27;
                lexeme[i++] =c;
            }
            else if(isspace(c))
            {
                state = 45;
               if(c=='\n')
                    (*linenumber)++;
            }

            else
            {
                *error = 1;
                t = (tokenInfo)malloc(sizeof(tokenInfo));
                t->s = TK_ERROR2;
                lexeme[i++] =c;
                lexeme[i] = '\0';
                strcpy(t->lexeme,lexeme);
                return t;

            }
            break;

        case 2:
            t = (tokenInfo)malloc(sizeof(tokenInfo));
            t->s = TK_MINUS;
            lexeme[i] = '\0';
            strcpy(t->lexeme,lexeme);
            return t;
            break;

        case 3:
            c = getNextChar(fp,&back);
            if(c=='=')
            {
                state = 4;
                lexeme[i++]=c;
            }
            else
            {
                *error = TRUE;
                t = (tokenInfo)malloc(sizeof(tokenInfo));
                t->s = TK_ERROR;
                lexeme[i] = '\0';
                strcpy(t->lexeme,lexeme);
                return t;
            }
            break;
        case 4:
            t = (tokenInfo)malloc(sizeof(tokenInfo));
            t->s = TK_NE;
            lexeme[i] = '\0';
            strcpy(t->lexeme,lexeme);
            return t;
            break;
        case 5:
            c = getNextChar(fp,&back);
            if(c>='a'&&c<='z')
            {
                state =6;
                lexeme[i++] =c;
            }
            else
            {
                *error = TRUE;
                t = (tokenInfo)malloc(sizeof(tokenInfo));
                t->s = TK_ERROR;
                lexeme[i] = '\0';
                strcpy(t->lexeme,lexeme);
                return t;
            }
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
                back = 1;
                t = (tokenInfo)malloc(sizeof(tokenInfo));
                t->s = TK_RECORDID;
                lexeme[i]='\0';
                strcpy(t->lexeme,lexeme);
                return t;
            }
            break;

        case 7:
            t = (tokenInfo)malloc(sizeof(tokenInfo));
            t->s = TK_COMMENT;
            state = 46; //FOR COMMENTS
            break;
        case 8:
            c = getNextChar(fp,&back);
            if(c=='&')
            {
                state = 9;
                lexeme[i++] = c;
            }
            else
            {
                *error = TRUE;
                t = (tokenInfo)malloc(sizeof(tokenInfo));
                t->s = TK_ERROR;
                lexeme[i] = '\0';
                strcpy(t->lexeme,lexeme);
                return t;
            }
            break;

        case 9:
            c = getNextChar(fp,&back);
            if(c=='&')
            {
                state = 10;
                lexeme[i++] =c;

            }
            else
            {
                *error = TRUE;
                t = (tokenInfo)malloc(sizeof(tokenInfo));
                t->s = TK_ERROR;
                lexeme[i] = '\0';
                strcpy(t->lexeme,lexeme);
                return t;
            }
            break;
        case 10:
            t = (tokenInfo)malloc(sizeof(tokenInfo));
            lexeme[i] = '\0';
            strcpy(t->lexeme,lexeme);
            t->s = TK_AND;
            return t;
            break;
        case 11:
            t = (tokenInfo)malloc(sizeof(tokenInfo));
            t->s = TK_OP;
            lexeme[i] = '\0';
            strcpy(t->lexeme,lexeme);
            return t;
            break;
        case 12:
            t = (tokenInfo)malloc(sizeof(tokenInfo));
            t->s = TK_CL;
            lexeme[i] = '\0';
            strcpy(t->lexeme,lexeme);
            return t;
            break;
        case 13:
            t = (tokenInfo)malloc(sizeof(tokenInfo));
            t->s = TK_MUL;
            lexeme[i] = '\0';
            strcpy(t->lexeme,lexeme);
            return t;
            break;
        case 14:
            t = (tokenInfo)malloc(sizeof(tokenInfo));
            t->s = TK_DOT;
            lexeme[i] = '\0';
            strcpy(t->lexeme,lexeme);
            return t;
            break;
        case 15:
            t = (tokenInfo)malloc(sizeof(tokenInfo));
            t->s = TK_DIV;
            lexeme[i] = '\0';
            strcpy(t->lexeme,lexeme);
            return t;
            break;
        case 16:
            t = (tokenInfo)malloc(sizeof(tokenInfo));
            t->s = TK_COLON;
            lexeme[i] = '\0';
            strcpy(t->lexeme,lexeme);
            return t;
            break;
        case 17:
            t = (tokenInfo)malloc(sizeof(tokenInfo));
            t->s = TK_SEM;
            lexeme[i] = '\0';
            strcpy(t->lexeme,lexeme);
            return t;
            break;
        case 18:
            c = getNextChar(fp,&back);
            if(c=='@')
            {
                lexeme[i++] = c;
                state = 19;
            }
            else
            {
                *error = TRUE;
                t = (tokenInfo)malloc(sizeof(tokenInfo));
                t->s = TK_ERROR;
                lexeme[i] = '\0';
                strcpy(t->lexeme,lexeme);
                return t;
            }
            break;
        case 19:
            c = getNextChar(fp,&back);
            if(c=='@')
            {
                lexeme[i++] = c;
                state = 20;
            }
            else
            {
                *error = TRUE;
                t = (tokenInfo)malloc(sizeof(tokenInfo));
                t->s = TK_ERROR;
                lexeme[i] = '\0';
                strcpy(t->lexeme,lexeme);
                return t;
            }
            break;
        case 20:
            t = (tokenInfo)malloc(sizeof(tokenInfo));
            t->s = TK_OR;
            lexeme[i] = '\0';
            strcpy(t->lexeme,lexeme);
            return t;
            break;
        case 21:
            t = (tokenInfo)malloc(sizeof(tokenInfo));
            t->s = TK_SQL;
            lexeme[i] = '\0';
            strcpy(t->lexeme,lexeme);
            return t;
            break;
        case 22:
            c = getNextChar(fp,&back);
            if(isdigit(c))
            {
                state = 22;
                lexeme[i++] = c;
            }
            else if(c=='.')
            {
                state = 23;
                lexeme[i++] = c;
            }
            else
            {
                back = 1;
                t = (tokenInfo)malloc(sizeof(tokenInfo));
                t->s = TK_NUM;
                lexeme[i]='\0';
                strcpy(t->lexeme,lexeme);
                return t;
            }
            break;
        case 23:
            c = getNextChar(fp,&back);
            if(isdigit(c))
            {
                state = 24;
                lexeme[i++] = c;
            }
            else
            {
                *error = TRUE;
                t = (tokenInfo)malloc(sizeof(tokenInfo));
                t->s = TK_ERROR;
                lexeme[i] = '\0';
                strcpy(t->lexeme,lexeme);
                return t;
            }
            break;
        case 24:
            c = getNextChar(fp,&back);
            if(isdigit(c))
            {
                lexeme[i++] = c;
                state = 25;
            }
            else
            {
                *error = TRUE;
                t = (tokenInfo)malloc(sizeof(tokenInfo));
                t->s = TK_ERROR;
                lexeme[i] = '\0';
                strcpy(t->lexeme,lexeme);
                return t;
            }
            break;
        case 25:
            t = (tokenInfo)malloc(sizeof(tokenInfo));
            t->s = TK_RNUM;
            lexeme[i]='\0';
            strcpy(t->lexeme,lexeme);
            return t;
            break;
        case 26:
            c = getNextChar(fp,&back);
            if(c>='a'&&c<='z')
            {
                lexeme[i++] = c;
                state = 26;
            }
            else
            {
                back = 1;
                //t= (tokenInfo)malloc(sizeof(tokenInfo));
                lexeme[i]='\0';
                t=keywordId(lexeme, kt);
                return t;
            }
            break;

        case 27:
            c = getNextChar(fp,&back);
            if(c>='a'&&c<='z')
            {
                lexeme[i++] = c;
                state = 26;
            }
            else if(c>='2'&&c<='7')
            {
                lexeme[i++] = c;
                state = 28;
            }
            else
            {
                back = 1;
                t = (tokenInfo)malloc(sizeof(tokenInfo));
                t->s = TK_FIELDID;
                lexeme[i]='\0';
                strcpy(t->lexeme,lexeme);
                return t;
            }
            break;
        case 28:
            c = getNextChar(fp,&back);
            if(c>='b'&&c<='d')
            {
                lexeme[i++] = c;
                state = 28;
            }
            else if (c>='2'&&c<='7')
            {
                lexeme[i++] = c;
                state = 29;
            }
            else
            {
                back = 1;
                t = (tokenInfo)malloc(sizeof(tokenInfo));
                t->s = TK_ID;
                lexeme[i]='\0';
                strcpy(t->lexeme,lexeme);
                return t;
            }
            break;
        case 29:
            c = getNextChar(fp,&back);
            if(c>='2'&&c<='7')
            {
                lexeme[i++] = c;
                state = 29;
            }
            else
            {
                back = 1;
                t = (tokenInfo)malloc(sizeof(tokenInfo));
                t->s = TK_ID;
                lexeme[i]='\0';
                strcpy(t->lexeme,lexeme);
                return t;
            }
            break;


        case 30:
            t = (tokenInfo)malloc(sizeof(tokenInfo));
            t->s = TK_SQR;
            lexeme[i]='\0';
            strcpy(t->lexeme,lexeme);
            return t;
            break;
        case 31:
            c = getNextChar(fp,&back);
            if(isalpha(c))
            {
                lexeme[i++] =c;
                state = 32;
            }
            else
            {
                *error = TRUE;
                t = (tokenInfo)malloc(sizeof(tokenInfo));
                t->s = TK_ERROR;
                lexeme[i] = '\0';
                strcpy(t->lexeme,lexeme);
                return t;
            }
            break;
        case 32:
            c = getNextChar(fp,&back);
            if(isalpha(c))
            {
                lexeme[i++] = c;
                state = 32;
            }
            else if(isdigit(c))
            {
                lexeme[i++] = c;
                state =  33;
            }
            else
            {
                back = 1;
                //t = (tokenInfo)malloc(sizeof(tokenInfo));
                lexeme[i]='\0';
                t=mainFun(lexeme, kt);
                return t;
            }
            break;
        case 33:
            c = getNextChar(fp,&back);
            if(isdigit(c))
            {
                lexeme[i++] = c;
                state = 33;
            }
            else
            {
                back = 1;
                t = (tokenInfo)malloc(sizeof(tokenInfo));
                t->s = TK_FUNID;
                lexeme[i]='\0';
                strcpy(t->lexeme,lexeme);
                return t;
            }
            break;
        case 34:
            t = (tokenInfo)malloc(sizeof(tokenInfo));
            t->s = TK_NOT;
            lexeme[i]='\0';
            strcpy(t->lexeme,lexeme);
            return t;
            break;
        case 35:
            t = (tokenInfo)malloc(sizeof(tokenInfo));
            t->s = TK_PLUS;
            lexeme[i]='\0';
            strcpy(t->lexeme,lexeme);
            return t;
            break;
        case 36:
            c = getNextChar(fp,&back);
            if(c=='-')
            {
                state = 37;
                lexeme[i++]=c;
            }
            else if(c=='=')
            {
                state = 40;
                lexeme[i++]=c;
            }
            else
            {
                t = (tokenInfo)malloc(sizeof(tokenInfo));
                t->s = TK_LT;
                lexeme[i]='\0';
                strcpy(t->lexeme,lexeme);
                return t;
            }
            break;
        case 37:
            c = getNextChar(fp,&back);
            if(c=='-')
            {
                state = 38;
                lexeme[i++] = c;
            }
            else
            {
                *error = TRUE;
                t = (tokenInfo)malloc(sizeof(tokenInfo));
                t->s = TK_ERROR;
                lexeme[i] = '\0';
                strcpy(t->lexeme,lexeme);
                return t;
            }
            break;

        case 38:
            c = getNextChar(fp,&back);
            if(c=='-')
            {
                state = 39;
                lexeme[i++]=c;
            }
            else
            {
                *error = TRUE;
                t = (tokenInfo)malloc(sizeof(tokenInfo));
                t->s = TK_ERROR;
                lexeme[i] = '\0';
                strcpy(t->lexeme,lexeme);
                return t;
            }
            break;
        case 39:
            t = (tokenInfo)malloc(sizeof(tokenInfo));
            t->s = TK_ASSIGNOP;
            lexeme[i]='\0';
            strcpy(t->lexeme,lexeme);
            return t;
            break;
        case 40:
            t = (tokenInfo)malloc(sizeof(tokenInfo));
            t->s = TK_LE;
            lexeme[i]='\0';
            strcpy(t->lexeme,lexeme);
            return t;
            break;

        case 41:
            c = getNextChar(fp,&back);
            if(c=='=')
            {
                state = 42;
                lexeme[i++]=c;
            }
            else
            {
                *error = TRUE;
                t = (tokenInfo)malloc(sizeof(tokenInfo));
                t->s = TK_ERROR;
                lexeme[i] = '\0';
                strcpy(t->lexeme,lexeme);
                return t;
            }
            break;

        case 42:
            t = (tokenInfo)malloc(sizeof(tokenInfo));
            t->s = TK_EQ;
            lexeme[i]='\0';
            strcpy(t->lexeme,lexeme);
            return t;
            break;
        case 43:
            c = getNextChar(fp,&back);
            if(c=='=')
            {
                state = 44;
                lexeme[i++]=c;
            }
            else
            {
                t = (tokenInfo)malloc(sizeof(tokenInfo));
                t->s = TK_GT;
                lexeme[i]='\0';
                strcpy(t->lexeme,lexeme);
                return t;
            }
            break;
        case 44:
            t = (tokenInfo)malloc(sizeof(tokenInfo));
            t->s = TK_GE;
            lexeme[i]='\0';
            strcpy(t->lexeme,lexeme);
            return t;
            break;
        case 45:			//WHITESPACE STATE
            c = getNextChar(fp,&back);
            if(c=='\n')
            {
                //printf("newline\n");
                (*linenumber)++;
                state = 45;
            }
            else if(isspace(c))
            {
                state = 45;
            }
            else
            {
                back = 1;
                state = 1;
            }
            break;
        case 46:			//COMMENT STATE
            c = getNextChar(fp,&back);
            if(c=='\n')
            {
                lexeme[i]='\0';
                strcpy(t->lexeme,lexeme);
                (*linenumber)++;
                return t;
            }
            else state = 46;
            break;
        case 47:
            t = (tokenInfo)malloc(sizeof(tokenInfo));
            t->s = TK_COMMA;
            lexeme[i]='\0';
            strcpy(t->lexeme,lexeme);
            return t;
            break;






        }
        //printf("State = %d   c = %c	line=%d\n", state,c,*linenumber);
    }
}

int getStream(int fp, buffer B, buffersize k)//reads k characters from source file into buffer B
{
    /*
    int ch, i=0;
    for (ch = fgetc(fp); ch != EOF && ch != '\n' && i<k; ch = fgetc(fp))
        B[i++] = (char)ch;
    return fp;
    */
    int amtRead=0;
    amtRead = read(fp,B,k);
    return amtRead;


}


char getNextChar(int fp, int *back)//gets next character from source file at position x
{
    static int x=0,k=1000,y;
    static char cb1[1000];
    static char cb2[1000];
    buffer b1=cb1;
    buffer b2=cb2;
    int flag=0;
    x%=k*2;
    //printf("x = %d\n",x);
    if(*back>=1)
    {
        x-=*back;
        x+=k*2;
        x%=k*2;
        *back=0;
    }
    else
    {
        if(x==0)
        {
            y=getStream(fp, b1, k);
            flag=0;
        }
        else if(x==k)
        {
            y=getStream(fp, b2, k);
            flag=1;
        }
    }
    if(x>=y+flag*k&&y<k)
    {
        x++;
        return (char)EOF;
    }
    if(x<k)
        return b1[x++];
    return b2[x++ - k];
}
void addKeyword(keywordTable kt, char *keyword, symbol s)//recursively called to add keyword to keywordTable
{
    int hval,hashkey=48;//twice the no. of keywords
    hval=hash(keyword,hashkey);
    while(kt[hval].present==TRUE)
        hval=(++hval)%hashkey;
    strcpy(kt[hval].keyword, keyword);
    kt[hval].present=TRUE;
    kt[hval].s=s;
}

int hash(char *keyword, int hashkey)//hash function
{
    int hash=0,mul=3,i=0;
    while(keyword[i]!='\0')
        hash=(hash*mul+keyword[i++])%hashkey;
    return hash;
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

tokenInfo keywordId(char *lexeme, keywordTable kt)//returns token for lexeme if it is a keyword or fieldname
{
    int hval,hashkey=48;//twice the no. of keywords
    tokenInfo t = (tokenInfo)malloc(sizeof(tokenInfo));
    strcpy(t->lexeme,lexeme);
    hval=hash(lexeme,hashkey);
    //printf("%s\n", lexeme);
    while(1)
    {
        if(kt[hval].present==FALSE)
        {
            t->s=TK_FIELDID;
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

tokenInfo mainFun(char *lexeme, keywordTable kt)//returns token for lexeme if it is main or function
{
    tokenInfo t = (tokenInfo)malloc(sizeof(tokenInfo));
    strcpy(t->lexeme,lexeme);
    if(!strcmp(lexeme, "_main"))
    {
        t->s=TK_MAIN;
        return t;
    }
    t->s=TK_FUNID;
    return t;
}

char* toStr ( symbol s )
{
    switch(s)
    {
    case TK_AND  :
        return "TK_AND";
    case TK_ASSIGNOP  :
        return "TK_ASSIGNOP";
    case TK_CALL  :
        return "TK_CALL";
    case TK_CL  :
        return "TK_CL";
    case TK_COLON  :
        return "TK_COLON";
    case TK_COMMENT  :
        return "TK_COMMENT";
    case TK_DIV  :
        return "TK_DIV";
    case TK_DOT  :
        return "TK_DOT";
    case TK_ELSE  :
        return "TK_ELSE";
    case TK_END  :
        return "TK_END";
    case TK_ENDIF  :
        return "TK_ENDIF";
    case TK_ENDRECORD  :
        return "TK_ENDRECORD";
    case TK_ENDWHILE  :
        return "TK_ENDWHILE";
    case TK_EQ  :
        return "TK_EQ";
    case TK_FIELDID  :
        return "TK_FIELDID";
    case TK_FUNID  :
        return "TK_FUNID";
    case TK_GE  :
        return "TK_GE";
    case TK_GLOBAL  :
        return "TK_GLOBAL";
    case TK_GT  :
        return "TK_GT";
    case TK_ID  :
        return "TK_ID";
    case TK_IF  :
        return "TK_IF";
    case TK_INPUT  :
        return "TK_INPUT";
    case TK_INT  :
        return "TK_INT";
    case TK_LE  :
        return "TK_LE";
    case TK_LIST  :
        return "TK_LIST";
    case TK_LT  :
        return "TK_LT";
    case TK_MAIN  :
        return "TK_MAIN";
    case TK_MINUS  :
        return "TK_MINUS";
    case TK_MUL  :
        return "TK_MUL";
    case TK_NE  :
        return "TK_NE";
    case TK_NOT  :
        return "TK_NOT";
    case TK_NUM  :
        return "TK_NUM";
    case TK_OP  :
        return "TK_OP";
    case TK_OR  :
        return "TK_OR";
    case TK_OUTPUT  :
        return "TK_OUTPUT";
    case TK_PARAMETER  :
        return "TK_PARAMETER";
    case TK_PARAMETERS  :
        return "TK_PARAMETERS";
    case TK_PLUS  :
        return "TK_PLUS";
    case TK_READ  :
        return "TK_READ";
    case TK_REAL  :
        return "TK_REAL";
    case TK_RECORD  :
        return "TK_RECORD";
    case TK_RECORDID  :
        return "TK_RECORDID";
    case TK_RETURN  :
        return "TK_RETURN";
    case TK_RNUM  :
        return "TK_RNUM";
    case TK_SEM  :
        return "TK_SEM";
    case TK_SQL  :
        return "TK_SQL";
    case TK_SQR  :
        return "TK_SQR";
    case TK_THEN  :
        return "TK_THEN";
    case TK_TYPE  :
        return "TK_TYPE";
    case TK_WHILE  :
        return "TK_WHILE";
    case TK_WITH  :
        return "TK_WITH";
    case TK_WRITE  :
        return "TK_WRITE";
    case TK_COMMA  :
        return "TK_COMMA";
    case program :
        return "program";
    case mainfunction :
        return "mainfunction";
    case otherfunctions :
        return "otherfunctions";
    case function :
        return "function";
    case input_par :
        return "input_par";
    case output_par :
        return "output_par";
    case constructeddatatype :
        return "constructeddatatype";
    case remaining_list :
        return "remaining_list";
    case parameter_list :
        return "parameter_list";
    case stmts :
        return "stmts";
    case typedefinitions :
        return "typedefinitions";
    case typedefinition :
        return "typedefinition";
    case fielddefinitions :
        return "fielddefinitions";
    case primitivedatatype :
        return "primitivedatatype";
    case fielddefinition :
        return "fielddefinition";
    case morefields :
        return "morefields";
    case declarations :
        return "declarations";
    case declaration :
        return "declaration";
    case datatype :
        return "datatype";
    case global_or_not :
        return "global_or_not";
    case assignmentstmt :
        return "assignmentstmt";
    case funcallstmt :
        return "funcallstmt";
    case outputparameters :
        return "outputparameters";
    case inputparameters :
        return "inputparameters";
    case iterativestmt :
        return "iterativestmt";
    case conditionalstmt :
        return "conditionalstmt";
    case elsepart :
        return "elsepart";
    case stmt :
        return "stmt";
    case otherstmts :
        return "otherstmts";
    case iostmt :
        return "iostmt";
    case singleorrecid :
        return "singleorrecid";
    case allvar :
        return "allvar";
    case expprime :
        return "expprime";
    case term :
        return "term";
    case termprime :
        return "termprime";
    case factor :
        return "factor";
    case arithmeticexpression :
        return "arithmeticexpression";
    case highprecedenceoperators :
        return "highprecedenceoperators";
    case lowprecedenceoperators :
        return "lowprecedenceoperators";
    case all :
        return "all";
    case temp :
        return "temp";
    case booleanexpression :
        return "booleanexpression";
    case var :
        return "var";
    case logicalop :
        return "logicalop";
    case relationalop :
        return "relationalop";
    case returnstmt :
        return "returnstmt";
    case optionalreturn :
        return "optionalreturn";
    case more_ids :
        return "more_ids";
    case newstate :
        return "newstate";
    case idlist :
        return "idlist";
    case TK_EPS :
        return "eps";

    default:
        return "INVALID";
    }
}

tokenList createTokenList(int fp, keywordTable kt)//create Token List
{
    int linenumber = 1,q;
    bool error = 0;
    tokenInfo t;
    tokenList list,curr=NULL;
    while(1)
    {
        t = getNextToken(fp,kt,&error,&linenumber);
        //printf("LEXEME:%s\n",t->lexeme);
        if(t==NULL)
        {
            break;
        }
        
        tokenList temp=(tokenList)malloc(sizeof(tokenList));
        if(curr==NULL)
        {
            curr=temp;
            list=temp;
        }
        else
        {
            curr->next=temp;
            curr=curr->next;
        }
        curr->t=t;
        if(t->s==TK_COMMENT)curr->linenumber=linenumber-1;
        else curr->linenumber=linenumber;
        curr->next=NULL;
        if(error)
            break;
    }
    return list;
}

void printTokenList(keywordTable kt, tokenList list)//print Token List
{
    int q;
    while(list!=NULL)
    {
            //printf("LEXEME:%s\n",list->t->lexeme);
            if(list->t->s==TK_ERROR)
            {
                printf("ERROR_3: Unknown pattern %s\n", list->t->lexeme);
                any_error=1;
                break;
            }
            else if(list->t->s==TK_ERROR2)
            {
                printf("ERROR_2: Unknown Symbol %s at line %d\n", list->t->lexeme, list->linenumber);
                any_error=1;
                break;
            }
            else if((strlen(list->t->lexeme) > 30 && list->t->s==TK_FUNID) || (strlen(list->t->lexeme) > 20 && list->t->s!=TK_FUNID) || list->t->lexeme[strlen(list->t->lexeme)-1] =='!')
            {
                q=20;
                //printf("sdgdg\n");
                if(list->t->s==TK_FUNID)
                    q=30;
                printf("ERROR_1 : Identifier at line %d is longer than the prescribed length of %d characters\n", list->linenumber,q);
                any_error=1;
                break;
            }
            //else
            //    printf("%s\n",list->t->lexeme);

        printf("%-20s%-30s%-10d\n",toStr(list->t->s), list->t->lexeme, list->linenumber);
        list=list->next;
    }
}
