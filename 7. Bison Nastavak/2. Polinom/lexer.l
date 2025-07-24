%{
  #include <iostream>
  #include <cstdlib>
  #include <map>
  #include <cmath>
  #include <vector>
  #include "Polinom.hpp"
  #include "parser.tab.hpp"
%}

%%
print {
  return PRINT_T;
}
deg {
  return DEG_T;
}
poly {
  return POLY_T;
}
int {
  return INT_T;
}
[a-zA-Z_][a-zA-Z0-9_]* {
  yylval.s = new std::string(yytext);
  return ID;
}
[0-9]+(\.[0-9]*)? {
  yylval.d = atof(yytext);
  return BROJ;
}
"==" {
  return EQ_T;
}
"!=" {
  return NEQ_T;
}
"[" {
  return *yytext;
}
"]" {
  return *yytext;
}
"'" {
  return *yytext;
}
[+*/()=<>;,-] {
  return *yytext;
}
[ \t\n] {

}
. {
  std::cerr << "Leksicka greska: " << (*yytext) << std::endl;
  exit(EXIT_FAILURE);
}
%%