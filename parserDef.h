/*
-=-=-=-=-=-=-=-=-=-=-=-=-=
BATCH 26
-=-=-=-=-=-=-=-=-=-=-=-=-=
AAYUSH AHUJA 2010A7PS023P
MAYANK GUPTA 2010A7PS022P
-=-=-=-=-=-=-=-=-=-=-=-=-=
parserDef.h
-=-=-=-=-=-=-=-=-=-=-=-=-=
*/

#ifndef PARSERDEF_H_INCLUDED
#define PARSERDEF_H_INCLUDED

typedef struct
{
    symbol nt;
    symbol first[60];
    int firstno;
    int followno;
    symbol follow[60];
    bool eps;

} sets;

typedef struct
{
    symbol nt;
    int ruleNumber;
    symbol list[20];
    int listno;

} grammar;

typedef int Table;

struct parsetree
{
    tokenInfo t;
    int ruleno;//used by AST to know which grammar rule was applied for the non-terminal,for terminals it is -1
    int lineno;
    struct parsetree* parent;
    bool visited;
    struct parsetree* next[20];//assuming length of RHS of rules is bounded by 20 
};

typedef struct parsetree* parseTree;

struct stackNode
{
    parseTree tree;//to Parse Tree 
    struct stackNode* next;
};

typedef struct
{
    struct stackNode* top;
    int size;
}Stack;




#endif // PARSERDEF_H_INCLUDED
