parser: parser.o lexer.o polinom.o
	g++ parser.o lexer.o polinom.o -o parser

polinom.o: Polinom.hpp Polinom.cpp
	g++ -c Polinom.cpp -o polinom.o

lexer.o: lex.yy.c
	g++ -c lex.yy.c -o lexer.o

parser.o: parser.tab.cpp parser.tab.hpp
	g++ -c parser.tab.cpp -o parser.o

lex.yy.c: lexer.l parser.tab.hpp
	flex -l lexer.l

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v parser.ypp

.PHONY: clean

clean:
	rm -rf *.tab.* *.yy.* *.o p*.output parser