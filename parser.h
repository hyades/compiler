/*
-=-=-=-=-=-=-=-=-=-=-=-=-=
BATCH 26
-=-=-=-=-=-=-=-=-=-=-=-=-=
AAYUSH AHUJA 2010A7PS023P
MAYANK GUPTA 2010A7PS022P
-=-=-=-=-=-=-=-=-=-=-=-=-=
parser.h
-=-=-=-=-=-=-=-=-=-=-=-=-=
*/

#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

void createParseTable(grammar G[], Table T[][60], sets S[], int Gno);
parseTree  parseInputSourceCode(int file, Table T[][60], keywordTable kt, grammar G[], bool*error);
void printParseTree(parseTree  PT, FILE *outfile);
symbol toSym(char *a, keywordTable nt);//return Symbol for given string
int createGrammar(FILE * fp,grammar G[], keywordTable nt);//load grammar from text file
void createSets(FILE * fp,sets S[], keywordTable nt);
void addNt(keywordTable nt, char *keyword, symbol s);//recursively called to add non-terminal to non-terminal Table
void initNt(keywordTable nt);//initialize non-terminals table
void initTable(Table T[][60]);//initialize parser table with no rule
void addtoTable(symbol nt, symbol t, int ruleno, Table T[][60]);//insert rule in table
bool isTerminal(symbol s);//returns true if given symbol is terminal
void printTable(FILE *fp, Table T[][60]);//print parser table
parseTree createParseNode(symbol s);
struct stackNode* createStackNode(parseTree tree);
Stack push(Stack S,parseTree tree);
Stack pop(Stack S);


#endif // PARSER_H_INCLUDED
