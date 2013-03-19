stage1exe: lexerDef.h lexer.h parser.h parserDef.h lexer.c parser.c driver.c
	gcc -o stage1exe lexer.c parser.c driver.c -I.
