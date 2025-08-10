%option noyywrap

%{
  #include <iostream>
  #include <cstdlib>
  #include <map>
  #include <vector>
  #include <exception>
  #include "Type.hpp"
  #include "SymbolTable.hpp"
  #include "SyntaxTree.hpp"

  #include "parser.tab.hpp"
%}

%%
int {
  return INT_T;
}
double {
  return DOUBLE_T;
}
string {
  return STRING_T;
}
print {
  return PRINT_T;
}
if {
  return IF_T;
}
else {
  return ELSE_T;
}
while {
  return WHILE_T;
}
[a-zA-Z_][a-zA-Z0-9_]* {
  yylval.str = new std::string(*yytext);
  return ID_T;
}
[0-9]+[.][0-9]* {
  yylval.dval = atof(yytext);
  return RBROJ_T;
}
[0-9]+ {
  yylval.ival = atoi(yytext);
  return IBROJ_T;
}
"\""[^"]*"\"" {
  yylval.str = new std::string(yytext);
  return STRING_VAL_T;
}
"==" {
  return EQ_T;
}
"!=" {
  return EQ_T;
}
"<=" {
  return EQ_T;
}
">=" {
  return EQ_T;
}
[+*/%()={}<>;-] {
  return *yytext;
}
[ \t\n] {

}
. {
  std::cerr << "Leksicka greska: " << (*yytext) << std::endl;
  exit(EXIT_FAILURE);
}
%%