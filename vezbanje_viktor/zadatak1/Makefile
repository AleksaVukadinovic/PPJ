parser: parser.o lexer.o tree.o
	g++ parser.o lexer.o tree.o -o parser

parser.o: parser.tab.cpp parser.tab.hpp
	g++ -c parser.tab.cpp -o parser.o

lexer.o: lex.yy.c
	g++ -c lex.yy.c -o lexer.o

tree.o: SyntaxTree.cpp SyntaxTree.hpp
	g++ -c SyntaxTree.cpp -o tree.o

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v parser.ypp

lex.yy.c: lexer.l
	flex -l lexer.l

.PHONY: clean

clean:
	rm -rd *.yy.* *.tab.* *.o *.output parser