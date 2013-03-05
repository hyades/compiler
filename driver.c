#include<stdio.h>
int main(int argc, char *argv[])
{
    int opt;
    do
    {
        printf("\n 1 : Print the token list.\n 2 : Verify the syntactic correctness\n 3 : Print abstract syntax tree\n 4: Exit\n\nSelect option->");
        scanf("%d", &opt);
        FILE *fp=fopen(argv[0], "r");
        switch(opt)
        {
            case 1: tokenInfo  tokens=getNextToken(fp);
                    //print tokens here
                    break;
            case 2: table T;
                    grammar G;
                    //load grammar here
                    createParseTable(G,T);
                    parseTree PT = parseInputSourceCode(argv[0],T);
                    printParseTree(PT, argv[1]);
                    break;
            case 3: abstractSyntaxTree A;
                    createAbstractSyntaxtree(PT,A);
                    int *totalAllocatedMemory;
                    printAST(A, argv[2], totalAllocatedMemory);
                    break;
            case 4: break;
            default:printf("\nPlease select a valid option\n");
        }
    }while(opt!=4);
    return 0;
}
