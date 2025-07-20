%option noyywrap

%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>

  #define KLJUCNA_REC (1)
  #define IDENTIFIKATOR (2)
  #define I_CONST (3)
  #define F_CONST (4)
  #define AOP (5)
  #define ROP (6)
  #define INTERPUNKCIJA (7)
  #define DODELA (8)
  #define OZ (9)
  #define ZZ (10)
  #define NN (11)

%}

CHAR [a-zA-Z]
CHAR_OR_NUM [a-zA-Z0-9]
SIGN [+-]
DIGIT [0-9]

%%

if|then|else|begin|end|var|integer {
  return KLJUCNA_REC;
}
{CHAR}{CHAR_OR_NUM}* {
  return IDENTIFIKATOR;
}
{SIGN}?{DIGIT}+ {return I_CONST;}
{SIGN}?{DIGIT}+\.{DIGIT}* {return F_CONST;}
[+/*-] {return AOP;}
[<>=]|"<="|">="|"==" {return ROP;}
[,.;:] {return INTERPUNKCIJA;}
":=" {return DODELA;}
"(" {return OZ;}
")" {return ZZ;}
[ \t\n] {}
. {return NN;}

%%

int main(int argc, char** argv) {
  int token =0;

  if (argc > 1) {
    yyin = fopen(argv[1], "r");
    if(yyin == NULL) {
      exit(EXIT_FAILURE);
    }
  } else {
    yyin = stdin;
  }

  if (argc > 2) {
    yyout = fopen(argv[2], "w");
  if(yyout == NULL) {
      exit(EXIT_FAILURE);
    }
  } else {
    yyout = stdout;
  }

  while ((token = yylex())!=0) {
    switch(token) {
      case I_CONST:
        printf("Ceo broj: %d\n",atoi(yytext));
      break;
        case F_CONST:
      printf("Realan broj: %f\n",atof(yytext));
        break;
      case IDENTIFIKATOR:
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
      case OZ:
        printf("Otvorena zagrada: %s\n",yytext);
        break;
      case ZZ:
        printf("Zatvorena zagrada: %s\n",yytext);
        break;
      case NN:
        fprintf(stderr , "Neprepoznata leksema: %s\n",yytext);
        exit(EXIT_FAILURE);
        break;
    }
 }

  exit(EXIT_SUCCESS);
}