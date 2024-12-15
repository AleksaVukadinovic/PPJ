%option noyywrap

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>


%}

%%
"{"[^}]*"}" {}
"(*"([^*]|"*"[^)])*?\*+")"  { }
. {ECHO;}
%%

int main(){
    yylex();

    exit(EXIT_SUCCESS);
}