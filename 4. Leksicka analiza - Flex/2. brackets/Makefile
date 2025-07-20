lexer: lex.yy.c
	gcc lex.yy.c -o lexer

lex.yy.c: brackets.l
	flex brackets.l

.PHONY: clean

clean:
	rm lexer lex.yy.c