lexer: lex.yy.c
	gcc lex.yy.c -o lexer

lex.yy.c: 8.l
	flex 8.l

.PHONY: clean

clean:
	rm lexer lex.yy.c