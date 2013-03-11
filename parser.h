#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

void createParseTable(grammar G, table T);
parseTree  parseInputSourceCode(char *testcaseFile, table T);
void printParseTree(parseTree  PT, char *outfile);
symbol toSym(char *a, keywordTable nt);//return string as symbol
void createGrammar(FILE * fp,grammar G, keywordTable nt);
void addNt(keywordTable nt, char *keyword, symbol s);//recursively called to add non-terminal to non-terminal Table
void initNt(keywordTable nt);//initialize non-terminals table
#endif // PARSER_H_INCLUDED
