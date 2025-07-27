parser: parser.o lexer.o syntax_tree.o tabela.o
	g++ parser.o lexer.o syntax_tree.o tabela.o -o parser

parser.o: parser.tab.hpp parser.tab.cpp
	g++ -c parser.tab.cpp -o parser.o

lexer.o: lex.yy.c
	g++ -c lex.yy.c -o lexer.o

syntax_tree.o: SyntaxTree.hpp SyntaxTree.cpp
	g++ -c SyntaxTree.cpp -o syntax_tree.o

tabela.o: SymbolTable.hpp SymbolTable.cpp
	g++ -c SymbolTable.cpp -o tabela.o

parser.tab.hpp parser.tab.cpp: parser.ypp
	bison -d -v parser.ypp

lex.yy.c: lexer.l
	flex -l lexer.l

.PHONY: clean

clean:
	rm -rf *.yy.* *.o parser *.output *.tab.*