#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

void createParseTable(grammar G, table T);
parseTree  parseInputSourceCode(char *testcaseFile, table T);
void printParseTree(parseTree  PT, char *outfile);
symbol toSym(char *a);
void createGrammar(int fp,grammar G);

#endif // PARSER_H_INCLUDED
