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




struct tnode{
    tokenInfo t;
    int ruleno;//used by AST to know which grammar rule was applied for the non-terminal,for terminals it is -1
    int lineno;
    struct tnode* parent;
    bool visited;
    struct tnode* next[20];//assuming length of RHS of rules is bounded by 20 
};

typedef struct tnode* ParseTree;

struct snode{
    ParseTree ref;//to Parse Tree 
    struct snode* next;
};

typedef struct{
    struct snode* top;
    int size;
}Stack;




#endif // PARSERDEF_H_INCLUDED
