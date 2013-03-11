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

symbol toSym(char *a, keywordTable nt)
{
    int hval,hashkey=200;
    hval=hash(a,hashkey);
    symbol s;
    while(1)
    {
        if(kt[hval].present==FALSE)
        {
            s=TK_ERROR;
            return s;
        }
        else if(!strcmp(a,nt[hval].keyword))
        {
            s=kt[hval].s;
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
    addNt(nt,"TK_MINUS ",TK_MINUS );
    addNt(nt,"TK_NE ",TK_NE );
    addNt(nt,"TK_RECORDID ",TK_RECORDID );
    addNt(nt,"TK_COMMENT ",TK_COMMENT );
    addNt(nt,"TK_AND ",TK_AND );
    addNt(nt,"TK_OP ",TK_OP );
    addNt(nt,"TK_CL ",TK_CL );
    addNt(nt,"TK_MUL ",TK_MUL );
    addNt(nt,"TK_DOT ",TK_DOT );
    addNt(nt,"TK_DIV ",TK_DIV );
    addNt(nt,"TK_COLON ",TK_COLON );
    addNt(nt,"TK_SEM ",TK_SEM );
    addNt(nt,"TK_OR ",TK_OR );
    addNt(nt,"TK_SQL ",TK_SQL );
    addNt(nt,"TK_NUM ",TK_NUM );
    addNt(nt,"TK_RNUM ",TK_RNUM );
    addNt(nt,"TK_FIELDID ",TK_FIELDID );
    addNt(nt,"TK_ID ",TK_ID );
    addNt(nt,"TK_SQR ",TK_SQR );
    addNt(nt,"TK_FUNID ",TK_FUNID );
    addNt(nt,"TK_MAIN ",TK_MAIN );
    addNt(nt,"TK_NOT ",TK_NOT );
    addNt(nt,"TK_PLUS ",TK_PLUS );
    addNt(nt,"TK_LT ",TK_LT );
    addNt(nt,"TK_ASSIGNOP ",TK_ASSIGNOP );
    addNt(nt,"TK_LE ",TK_LE );
    addNt(nt,"TK_EQ ",TK_EQ );
    addNt(nt,"TK_GT ",TK_GT );
    addNt(nt,"TK_LE ",TK_LE );
    addNt(nt,"TK_CALL ",TK_CALL );
    addNt(nt,"TK_ELSE ",TK_ELSE );
    addNt(nt,"TK_END ",TK_END );
    addNt(nt,"TK_ENDIF ",TK_ENDIF );
    addNt(nt,"TK_ENDRECORD ",TK_ENDRECORD );
    addNt(nt,"TK_ENDWHILE ",TK_ENDWHILE );
    addNt(nt,"TK_GLOBAL ",TK_GLOBAL );
    addNt(nt,"TK_IF ",TK_IF );
    addNt(nt,"TK_INPUT ",TK_INPUT );
    addNt(nt,"TK_INT ",TK_INT );
    addNt(nt,"TK_INT ",TK_INT );
    addNt(nt,"TK_LIST ",TK_LIST );
    addNt(nt,"TK_OUTPUT ",TK_OUTPUT );
    addNt(nt,"TK_PARAMETER ",TK_PARAMETER );
    addNt(nt,"TK_PARAMETERS ",TK_PARAMETERS );
    addNt(nt,"TK_READ ",TK_READ );
    addNt(nt,"TK_REAL ",TK_REAL );
    addNt(nt,"TK_REAL ",TK_REAL );
    addNt(nt,"TK_RECORD ",TK_RECORD );
    addNt(nt,"TK_RETURN ",TK_RETURN );
    addNt(nt,"TK_THEN ",TK_THEN );
    addNt(nt,"TK_TYPE ",TK_TYPE );
    addNt(nt,"TK_WHILE ",TK_WHILE );
    addNt(nt,"TK_WITH ",TK_WITH );
    addNt(nt,"TK_WRITE ",TK_WRITE );
}

void createGrammar(FILE * fp,grammar G[])
{
    char a[200];
    int i = 0,k=0,first=0,follow=0;
    while(fp.eof())
    {
        fscanf(fp,"%s",a);
        if(a==NULL)break;
        if(strcmp(a,",")==0)
        {
            k++;
            continue;
        }
        if(k==0)
        {
            G[i].nt = toSym(a,nt);
            first = 0;
            follow = 0;

        }
        else if(k==1)
        {
            G[i].first[first++]  = toSym(a,nt);
        }
        else if(k==2)
        {
            G[i].follow[follow++] = toSym(a,nt);

        }
        else
        {
            if(strcmp(a,"yes")==0)
                G[i].eps = 1;
            else
                G[i].eps = 0;
            i++;
            k=0;
        }


    }
}
