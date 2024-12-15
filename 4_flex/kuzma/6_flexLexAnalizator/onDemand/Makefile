lexer: lex.yy.c
	gcc lex.yy.c -o lexer

lex.yy.c: onDemand.l
	flex onDemand.l

.PHONY: clean

clean:
	rm lexer lex.yy.c