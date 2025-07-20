lexer: lex.yy.c
	gcc lex.yy.c -o lexer

lex.yy.c: c_com.l
	flex c_com.l

.PHONY: clean

clean:
	rm lexer lex.yy.c