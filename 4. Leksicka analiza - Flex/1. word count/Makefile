lexer: lex.yy.c
	gcc lex.yy.c -o lexer

lex.yy.c: word_count.l
	flex word_count.l

.PHONY: clean

clean:
	rm lexer lex.yy.c