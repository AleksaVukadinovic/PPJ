%option noyywrap

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #define KLJUCNA_REC (1)
    #define ID          (2)
    #define I_CONST     (3)
    #define F_CONST     (4)
    #define AOP         (5)
    #define ROP         (6)
    #define INTERP      (7)
    #define DODELA      (8)
    #define OZ          (9)
    #define ZZ          (10)
    #define NN          (11)
%}

%%

if|then|else|begin|end|var|integer      {return KLJUCNA_REC; }
[a-zA-Z][a-zA-Z0-9]*                    {return ID; }
[+-]?[0-9]+                             {return I_CONST; }
[+-]?[0-9]+\.[0-9]*                     {return F_CONST; }
[+/*-]                                  {return AOP; }
[<>=] | ">=" | "<="                      {return ROP; }
[,.;:]                                  {return INTERP; }
":="                                    {return DODELA; }
"("                                     {return OZ; }
")"                                     {return ZZ; }
[ \t\n]                                 {}
.                                       {return NN; }

%%

int main(int argc, char** argv) {
    int token = 0;
    if(argc>1) {
        yyin = fopen(argv[1], "r");
        if(yyin == NULL)
            exit(EXIT_FAILURE);
    } else {
        yyin=stdin;
    }

    while (token = yylex()) {
        switch(token) {
            case KLJUCNA_REC: printf("Kljucna rec: %s\n", yytext); break;
            case ID: printf("Identifikator: %s\n", yytext); break;
            case I_CONST: printf("Celobrojna konstanta: %s\n", yytext); break;
            case F_CONST: printf("Realna konstanta: %s\n", yytext); break;
            case AOP: printf("Aritmeticki operator: %s\n", yytext); break;
            case ROP: printf("Relacijski operator: %s\n", yytext); break;
            case DODELA: printf("Operator dodele: %s\n", yytext); break;
            case INTERP: printf("Znak interpunkcije: %s\n", yytext); break;
            case OZ: printf("Otvorena zagrada: %s\n", yytext); break;
            case ZZ: printf("Zatvorena zagrada: %s\n", yytext); break;
            case NN: printf("Leksicka greska: %s\n", yytext); break; exit(EXIT_FAILURE);
        }
    }

    if (yyin != stdin) {
        fclose(yyin);
    }

    exit(EXIT_SUCCESS);
}