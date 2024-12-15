lexer: lex.yy.c
	gcc lex.yy.c -o lexer

lex.yy.c: 5.l
	flex 5.l

.PHONY: clean

clean:
	rm lex.yy.c lexer