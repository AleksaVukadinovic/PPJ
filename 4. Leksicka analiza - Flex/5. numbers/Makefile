lexer: lex.yy.c
	gcc lex.yy.c -o lexer

lex.yy.c: numbers.l
	flex numbers.l

.PHONY: clean

clean:
	rm lexer lex.yy.c