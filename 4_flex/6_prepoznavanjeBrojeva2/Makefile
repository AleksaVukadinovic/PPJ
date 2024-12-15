lexer: lex.yy.c
	gcc lex.yy.c -o lexer

lex.yy.c: 6.l
	flex 6.l

.PHONY: clean

clean:
	rm lex.yy.c lexer