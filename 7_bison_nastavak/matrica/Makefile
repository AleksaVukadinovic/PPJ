parser: parser.o lexer.o matrix.o
	g++ parser.o lexer.o matrix.o -o parser

matrix.o: Matrix.cpp Matrix.hpp
	g++ -c Matrix.cpp -o matrix.o

lexer.o: lex.yy.c
	g++ -c lex.yy.c -o lexer.o

parser.o: parser.tab.cpp parser.tab.hpp
	g++ -c parser.tab.cpp -o parser.o

lex.yy.c: lexer.l parser.tab.hpp
	flex -l lexer.l

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v -Wcounterexamples parser.ypp

.PHONY: clean

clean:
	rm -rf *.tab.* *.yy.* *.o p*.output parser