lexer: lex.yy.c
	gcc lex.yy.c -o lexer

lex.yy.c: paskal.l
	flex paskal.l

.PHONY: clean

clean:
	rm lexer lex.yy.c