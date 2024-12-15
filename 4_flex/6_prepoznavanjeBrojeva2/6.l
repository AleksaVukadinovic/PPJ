%option noyywrap

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #define I_CONST 1
    #define F_CONST 2

    int brojTokena = 0;
%}

DIGIT [0-9]

%%
([+-]?[1-9][0-9]*e?[1-9][0-9]*)|0 {return I_CONST;}
[+-]?((0\.[0-9]*)|([1-9][0-9]*\.[0-9]*))([eE][+-]?[1-9][0-9]*) {return F_CONST;}
. {}
\n {}
%%

int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "Los broj argumenata\n");
        exit(EXIT_FAILURE);
    }

    yyin = fopen(argv[1], "r");
    if (yyin == NULL) {
        fprintf(stderr, "Failed to open input file: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    yyout = fopen(argv[2], "w");
    if (yyout == NULL) {
        fprintf(stderr, "Failed to open output file: %s\n", argv[2]);
        fclose(yyin); // Close input file before exiting
        exit(EXIT_FAILURE);
    }

    int celi = 0, realni = 0;
    int token;
    while ((token = yylex())) {
        switch (token) {
            case I_CONST:
                celi++;
                fprintf(yyout, "Nadjena celobrojna konstanta: %s\n", yytext);
                break;
            case F_CONST:
                realni++;
                fprintf(yyout, "Nadjena realna konstanta: %s\n", yytext);
                break;
        }
    }

    fprintf(yyout, "Celih brojeva: %d\n", celi);
    fprintf(yyout, "Realnih brojeva: %d\n", realni);

    fclose(yyin);
    fclose(yyout);

    exit(EXIT_SUCCESS);
}
