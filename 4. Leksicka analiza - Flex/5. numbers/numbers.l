%option noyywrap

%{
  #include <stdio.h>
  #include <stdlib.h>

  // 0 je rezervisan broj koji oznacava EOF, njega ne smemo sami da vracamo
  #define I_CONST (1)
  #define F_CONST (2)
%}

SIGN [+-]
DIGIT [0-9]

%%

{SIGN}?{DIGIT}+ {return I_CONST;}
{SIGN}?{DIGIT}+\.{DIGIT}*([Ee]{SIGN}?{DIGIT}+)? {return F_CONST;}
. {}
\n {}

%%

int main() {
  int token = 0;
  while(token = yylex()) {
    switch(token) {
      case I_CONST:
        printf("Ceo broj: %s\n", yytext);
        break;
      case F_CONST:
        printf("Realan broj: %s\n", yytext);
        break;
    }
  }

  exit(EXIT_SUCCESS);
}