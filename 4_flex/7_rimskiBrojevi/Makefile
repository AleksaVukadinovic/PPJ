lexer: lex.yy.c
	gcc lex.yy.c -o lexer

lex.yy.c: 7.l
	flex 7.l

.PHONY: clean

clean:
	rm lexer lex.yy.c