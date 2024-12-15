lexer: lex.yy.c
	gcc lex.yy.c -o lexer

lex.yy.c: 2.l
	flex 2.l

.PHONY: clean

clean:
	rm lex.yy.c lexer 