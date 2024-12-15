%option noyywrap

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int brojOtvorenih = 0;
    int brojZatvorenih = 0;
%}

%%

"(" {brojOtvorenih++;
    ECHO;}
")" {brojZatvorenih++;
    ECHO;
    if(brojZatvorenih > brojOtvorenih){
        fprintf(stderr, "Nisu uparene");
        return -1;
    }}
. {ECHO;}
%%

int main() {
    if(yylex()==-1)
        exit(EXIT_FAILURE);
    if(brojOtvorenih != brojZatvorenih){
        fprintf(stderr, "Nisu uparene");
        exit(EXIT_FAILURE);
    }
    printf("Uparene su!\n");
    exit(EXIT_SUCCESS);
}