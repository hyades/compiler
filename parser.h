#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

void createParseTable(grammar G[], Table T[][60], sets S[], int Gno);
ParseTree  parseInputSourceCode(int file, Table T[][60], keywordTable kt, grammar G[], bool*error);
void printParseTree(ParseTree  PT);
symbol toSym(char *a, keywordTable nt);//return Symbol for given string
int createGrammar(FILE * fp,grammar G[], keywordTable nt);//load grammar from text file
int createSets(FILE * fp,sets S[], keywordTable nt);
void addNt(keywordTable nt, char *keyword, symbol s);//recursively called to add non-terminal to non-terminal Table
void initNt(keywordTable nt);//initialize non-terminals table
void initTable(Table T[][60]);//initialize parser table with no rule
void addtoTable(symbol nt, symbol t, int ruleno, Table T[][60]);//insert rule in table
bool isTerminal(symbol s);//returns true if given symbol is terminal
void printTable(FILE *fp, Table T[][60]);//print parser table


Stack push(Stack S,ParseTree ref);
Stack pop(Stack S);


#endif // PARSER_H_INCLUDED
