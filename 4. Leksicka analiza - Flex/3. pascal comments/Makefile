lexer: lex.yy.c
	gcc lex.yy.c -o lexer

lex.yy.c: pascal.l
	flex pascal.l

.PHONY: clean

clean:
	rm lexer lex.yy.c