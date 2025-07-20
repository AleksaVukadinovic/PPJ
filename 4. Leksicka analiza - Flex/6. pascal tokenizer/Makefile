lexer: lex.yy.c
	gcc lex.yy.c -o lexer

lex.yy.c: tokenizer.l
	flex tokenizer.l

.PHONY: clean

clean:
	rm lexer lex.yy.c