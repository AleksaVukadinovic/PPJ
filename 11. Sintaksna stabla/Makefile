parser: parser.o lexer.o SymbolTable.o SyntaxTree.o
	g++ parser.o lexer.o SymbolTable.o SyntaxTree.o -o parser

SymbolTable.o: SymbolTable.hpp SymbolTable.cpp
	g++ -c SymbolTable.cpp -o SymbolTable.o

SyntaxTree.o: SyntaxTree.hpp SyntaxTree.cpp
	g++ -c SyntaxTree.cpp -o SyntaxTree.o

lexer.o: lex.yy.c
	g++ -c lex.yy.c -o lexer.o

parser.o: parser.tab.hpp parser.tab.cpp
	g++ -c parser.tab.cpp -o parser.o

lex.yy.c: lexer.l parser.tab.hpp
	flex -l lexer.l

parser.tab.hpp parser.tab.cpp: parser.ypp
	bison -d -v parser.ypp

.PHONY: clean

clean:
	rm -rf *.tab.* *.yy.* *.o *.output parser