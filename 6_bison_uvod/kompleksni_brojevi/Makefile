parser: parser.o lexer.o kb.o
	g++ parser.o lexer.o kb.o -o parser

kb.o: kompleksni_brojevi.cpp kompleksni_brojevi.hpp
	g++ -c kompleksni_brojevi.cpp -o kb.o

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