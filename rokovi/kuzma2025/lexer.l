%option noyywrap

%{
  #include <iostream>
  #include <cstdlib>
  #include <map>
  #include <vector>

  #include "SymbolTable.hpp"
  #include "SyntaxTree.hpp"
  #include "parser.tab.hpp"
%}

%%

def {
  return DEF_T;
}
print {
  return PRINT_T;
}
while {
  return WHILE_T;
}
if {
  return IF_T;
}
else {
  return ELSE_T;
}
[a-zA-Z_][a-zA-Z0-9_]* {
  yylval.s = new std::string(yytext);
  return ID_T;
}
[0-9]+(\.[0-9]+)? {
  yylval.d = atof(yytext);
  return NUM_T;
}
[+=*/;\{\}()<>-] {
  return *yytext;
}
[ \t\n] {

}
. {
  std::cerr << "Lekscika greksa: " << (*yytext) << std::endl;
  exit(EXIT_FAILURE);
}


%%