parser: parser.o lexer.o
	g++ lexer.o parser.o -o parser

Type.o: Type.hpp Type.cpp
	g++ -c Type.cpp -o Type.o

SymbolTable.o: SymbolTable.hpp SymbolTable.cpp
	g++ -c SymbolTable.cpp -o SymbolTable.o

lexer.o: lex.yy.c
	g++ -c lex.yy.c -o lexer.o

lex.yy.c: lexer.l
	flex -l lexer.l

parser.o: parser.tab.hpp parser.tab.cpp
	g++ -c parser.tab.cpp -o parser.o

parser.tab.hpp parser.tab.cpp: parser.ypp
	bison -d -v parser.ypp

.PHONY: clean

clean:
	rm -rf *.yy.* *.yab.* *.o *.output parser