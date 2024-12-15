lexer: lex.yy.c
	gcc lex.yy.c -o lexer

lex.yy.c: wc.l
	flex wc.l

.PHONY: clean

clean:
	rm lexer lex.yy.c