/*
-=-=-=-=-=-=-=-=-=-=-=-=-=
BATCH 26
-=-=-=-=-=-=-=-=-=-=-=-=-=
AAYUSH AHUJA 2010A7PS023P
MAYANK GUPTA 2010A7PS022P
-=-=-=-=-=-=-=-=-=-=-=-=-=
codegen.h
-=-=-=-=-=-=-=-=-=-=-=-=-=
*/

char longtext[500] = "printf proc\npush bx\npush cx\npush dx\nmov cx,0\nmov bx,10\nloop1:\nmov dx,0\ndiv bx\npush dx\ninc cx\ncmp ax,0\njne loop1\nloop2:\npop dx\nmov ah,02h\nadd dl,'0'\nint 21h\nloop loop2\npop dx\npop cx\npop bx\nret\nprintf endp\nscanf proc\npush bx\npush cx\npush dx\nmov bx,10\nmov ax,0\nloop3:\npush ax\nmov ah,01h\nint 21h\ncmp al,0dh\nje finish\nsub al,'0'\nmov cl,al\npop ax\nmul bx\nadd ax,cx\njmp loop3\nfinish:\npop ax\npop dx\npop cx\npop bx\nret\nscanf endp\n";