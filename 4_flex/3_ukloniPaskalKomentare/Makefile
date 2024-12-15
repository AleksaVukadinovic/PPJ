lexer: lex.yy.c
	gcc lex.yy.c -o lexer

lex.yy.c: 3.l
	flex 3.l

.PHONY: clean

clean:
	rm lex.yy.c lexer