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

}sets;

sets S[60];

typedef struct
{
    symbol nt;
    int ruleNumber;
    symbol list[20];
    int listno;

}grammar;

grammar G[70];

typedef int Table;

Table T[60][60];

struct parsetree
{
    char lexeme[100];
    int lineno;
    symbol s;
    int valueIfNumber;
    symbol parentNodeSymbol;
    bool isLeafNode;
    symbol NodeSymbol;
    struct parsetree * next[20]; //Assuming a node cannot have more than 20 children
};

typedef struct parsetree * ParseTree;



#endif // PARSERDEF_H_INCLUDED
