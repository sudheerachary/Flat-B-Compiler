CC = g++

bcc: parser.tab.c lex.yy.c AstClasses.cpp AstDefs.h
	$(CC) lex.yy.c parser.tab.c AstClasses.cpp -lfl -o bcc

lex.yy.c: scanner.l parser.tab.h
	flex scanner.l

parser.tab.c: parser.y 
	bison -vd parser.y 

clean:
	rm -f *.c parser.tab.h *.output

veryclean:
	rm -rf *.c parser.tab.h *.output bcc output
