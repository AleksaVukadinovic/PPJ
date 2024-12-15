%option noyywrap

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int broj_linija = 0;
int broj_karaktera = 0;
%}

%%

\n {broj_linija++;}
. {broj_karaktera++;}

%%

int main() {
    yylex();

    printf("Broj linija: %d, broj karaktera: %d\n", broj_linija, broj_karaktera);
    exit(EXIT_SUCCESS);
}