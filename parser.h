#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

void createParseTable(grammar G[], Table T[][60], sets S[], int Gno);
//parseTree  parseInputSourceCode(char *testcaseFile, Table T);
//void printParseTree(parseTree  PT, char *outfile);
symbol toSym(char *a, keywordTable nt);//return string as symbol
int createGrammar(FILE * fp,grammar G[], keywordTable nt);
int createSets(FILE * fp,sets S[], keywordTable nt);
void addNt(keywordTable nt, char *keyword, symbol s);//recursively called to add non-terminal to non-terminal Table
void initNt(keywordTable nt);//initialize non-terminals table
void initTable(Table T[][60]);
void addtoTable(symbol nt, symbol t, int ruleno, Table T[][60]);
bool isTerminal(symbol s);
#endif // PARSER_H_INCLUDED
