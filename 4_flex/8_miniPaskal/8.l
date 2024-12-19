%option noyywrap

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    // 0 je rezervisana kad nista nije pronadjeno, zato brojanje krecemo od 1 
    // token u main-u ce dobiti neku od ovih vrednosti
    #define KLJUCNA_REC 1
    #define ID 2
    #define I_CONST 3
    #define F_CONST 4
    #define AOP 5
    #define ROP 6
    #define INTERPUNKCIJA 7
    #define DODELA 8
    #define Z 9
    #define NN 10
%}

DIGIT [0-9]
CHAR [a-zA-Z]

%%
if|then|begin|end|var|function|integer {return KLJUCNA_REC; }
{CHAR}({CHAR}|{DIGIT})* {return ID;}
[1-9]{DIGIT}* {return I_CONST;}
{DIGIT}+\.{DIGIT}* {return F_CONST;}
[+-/*] {return AOP;}
[<>=]|"<="|">=" {return ROP;}
[,:;.!] {return INTERPUNKCIJA;}
:= {return DODELA;}
"("|")" { return Z; }
"{"[^}\n]*"}" {}
[ \t\n] {}
. {return NN;}
%%

int main(int argc, char* argv[]) {
    int token;

    if ( argc > 1){
        if (( yyin = fopen(argv[1],"r"))==NULL )
            yyin = stdin;
    }
    else
        yyin = stdin;

    while ((token = yylex())!=0) {
        switch(token) {
            case I_CONST:
                printf("Ceo broj: %d\n",atoi(yytext));
                break;
            case F_CONST:
                printf("Realan broj: %f\n",atof(yytext));
                break;
            case ID:
                printf("Identifikator: %s\n",yytext);
                break;
            case KLJUCNA_REC:
                printf("Kljucna rec: %s\n",yytext);
                break;
            case AOP:
                printf("Operator: %s\n",yytext);
                break;
            case ROP:
                printf("Relacioni operator: %s\n",yytext);
                break;
            case DODELA:
                printf("Operator dodele: %s\n",yytext);
                break;
            case INTERPUNKCIJA:
                printf("Ingerpunkcija: %s\n",yytext);
                break;
            case Z:
                printf("Zagrada: %s\n",yytext);
                break;
            case NN:
                fprintf(stderr , "Neprepoznata leksema: %s\n",yytext);
                exit(EXIT_FAILURE);
                break;
        }
    }
    exit(EXIT_SUCCESS);
}