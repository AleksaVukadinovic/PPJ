lexer: lex.yy.c
	gcc lex.yy.c -o lexer

lex.yy.c: zagrade.l
	flex zagrade.l

.PHONY: clean

clean:
	rm lexer lex.yy.c