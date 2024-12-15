%option noyywrap

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int brojLinija = 0;

%}

%%
"//".* {brojLinija++;}
"/*"("*")*[^/]*"*/" {for(int i=0; i<yyleng; i++)
                        if(yytext[i]=='\n')
                            brojLinija++;}
"\n" {brojLinija++; ECHO;}
. {ECHO;}
%%

int main(){
    yylex();
    printf("Broj linija: %d\n", brojLinija+1);
    exit(EXIT_SUCCESS);
}