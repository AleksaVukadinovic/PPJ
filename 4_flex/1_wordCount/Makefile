lexer: lex.yy.c
	gcc lex.yy.c -o lexer

lex.yy.c: 1.l
	flex 1.l

.PHONY: clean

clean:
	rm lexer lex.yy.c