%option noyywrap

%{
  #include <iostream>
  #include <cstdlib>
  #include <map>
  #include <vector>

  #include "Function.hpp"
  #include "SymbolTable.hpp"
  #include "SyntaxTree.hpp"
  #include "parser.tab.hpp"
%}

%%
sin {
  return SIN_T;
}
cos {
  return COS_T;
}
tan {
  return TAN_T;
}
cot {
  return COT_T;
}
exp {
  return EXP_T;
}
log {
  return LOG_T;
}
pow {
  return POW_T;
}
sqrt {
  return SQRT_T;
}
x {
  yylval.s = new std::string(yytext);
  return X_T;
}
[a-zA-Z_][a-zA-Z0-9_]* {
  yylval.s = new std::string(yytext);
  return ID_T;
}
[0-9]+(.[0-9]*)? {
  yylval.d = atof(yytext);
  return NUM_T;
}
[+/*()=\n-] {
  return *yytext;
}
"["|"]"|"'" {
  return *yytext;
}
[ \t] {

}
. {
  std::cerr << "Leksicka greska: " << (*yytext) << std::endl;
  exit(EXIT_FAILURE);
}

%%