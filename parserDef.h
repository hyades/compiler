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
	char lexeme[100];
    int lineno;
    symbol s;
	bool visited;
	struct parsetree * parent; //parent node
    struct parsetree * child[20]; //Assuming a node cannot have more than 20 children
};
typedef struct parsetree * parseTree;

struct stacknode
{
    parseTree tree;
    struct stacknode * next;
    
};
typedef struct stacknode *stackNode;


struct stack
{
    stackNode top;
    int size;
};

typedef struct stack * Stack;

#endif // PARSERDEF_H_INCLUDED
