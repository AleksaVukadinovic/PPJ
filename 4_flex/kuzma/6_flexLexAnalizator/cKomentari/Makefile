lexer: lex.yy.c
	gcc lex.yy.c -o lexer

lex.yy.c: ckom.l
	flex ckom.l

.PHONY: clean

clean:
	rm lexer lex.yy.c