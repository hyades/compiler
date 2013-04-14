stage1exe: lexerDef.h lexer.h parser.h parserDef.h lexer.c parser.c driver.c
	gcc -o stage1exe -g lexer.c parser.c driver.c symbolTable.c -I.
