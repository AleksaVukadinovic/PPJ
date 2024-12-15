lexer: lex.yy.c
	gcc lex.yy.c -o lexer

lex.yy.c: 4.l
	flex 4.l

.PHONY: clean

clean:
	rm lex.yy.c lexer