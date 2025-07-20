%option noyywrap

%{
  #include <stdio.h>
  #include <stdlib.h>

  int bracket_counter = 0;
%}

%%

"(" {
  bracket_counter++;
  ECHO;
}

")" {
  if(bracket_counter > 0)
    bracket_counter--;
  else {
    return -1;
  }
  ECHO;
}

. {
  ECHO;
  // isto sto i printf("%s", yytext)
}

%%

int main() {
  if(yylex()==-1) {
    printf("Zagrade nisu uparene\n");
    exit(EXIT_FAILURE);
  }

  if(!bracket_counter)
    printf("Zagrade su uparene\n");
  else
    printf("Zagrade nisu uparene\n");

  exit(EXIT_SUCCESS);
}