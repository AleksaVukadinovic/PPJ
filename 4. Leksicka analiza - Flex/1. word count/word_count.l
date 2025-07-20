%option noyywrap

%{
  #include <stdio.h>
  #include <stdlib.h>

  int line_count = 0;
  int char_count = 0;
  int word_count = 0;
%}

%%

. {
  char_count++;
}

\n {
  line_count++;
  char_count++;
}

[a-zA-Z]+ {
  word_count++;
  // char_count += strlen(yytext)
  // yyleng -> duzina teksta koju je lexer prepoznao
}

%%

int main() {
  yylex();

  printf("Broj karaktera: %d\n", char_count);
  printf("Broj linija: %d\n", line_count);
  printf("Broj reci: %d\n", word_count);

  exit(EXIT_SUCCESS);
}