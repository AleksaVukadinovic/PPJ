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

int main(){
    int celi = 0, realni = 0;
    int token;
    while(token = yylex()){
        switch(token){
            case I_CONST:
                celi++;
                printf("Nadjena celobrojna konstanta: %s\n", yytext);
                break;
            case F_CONST:
                realni++;
                printf("Nadjena realna konstanta: %s\n", yytext);
                break;
        }
    }
    printf("Celih brojeva: %d\n", celi);
    printf("Realnih brojeva: %d\n", realni);
    exit(EXIT_SUCCESS);
}