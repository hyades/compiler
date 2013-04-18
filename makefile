stage2exe: lexerDef.h lexer.h parser.h parserDef.h lexer.c parser.c driver.c
	gcc -o stage2exe -g lexer.c parser.c driver.c symbolTable.c typeExtractor.c semantic.c codegen.c -I.
