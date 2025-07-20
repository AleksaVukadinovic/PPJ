%option noyywrap

%{
  #include <stdio.h>
  #include <stdlib.h>


%}

%%

"{"[^}]*"}" { 

}

"(*".*?"*)" {

}

%%

int main(){
  yylex();

  exit(EXIT_SUCCESS);
}