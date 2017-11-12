CC = g++
FLAGS=-Wno-deprecated -w -g -std=c++14
CFLAGS=-lfl `llvm-config --cppflags --cxxflags mcjit native --ldflags --libs core` -ltinfo -lpthread -ldl
bcc: parser.tab.c lex.yy.c AstClasses.cpp AstDefs.h
	$(CC) $(FLAGS) lex.yy.c parser.tab.c AstClasses.cpp $(CFLAGS) -o bcc

lex.yy.c: scanner.l parser.tab.h
	flex scanner.l

parser.tab.c: parser.y
	bison -vd parser.y 

clean:
	rm -f *.c parser.tab.h *.output

veryclean:
	rm -rf *.c parser.tab.h *.output bcc output dump* run.sh
