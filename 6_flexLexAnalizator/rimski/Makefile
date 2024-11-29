lexer: lex.yy.c
	gcc lex.yy.c -o lexer

lex.yy.c: rimski.l
	flex rimski.l

.PHONY: clean

clean:
	rm lexer lex.yy.c