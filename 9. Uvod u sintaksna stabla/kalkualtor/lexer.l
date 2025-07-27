%option noyywrap

%{
  #include <iostream>
  #include <cstdlib>
  #include <string>

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
%[hdb] {
  yylval.c = yytext[1];
  return FORMAT_T;
} 
[a-zA-Z_][a-zA-Z0-9_]* {
  yylval.s = new std::string(yytext);
  return ID_T;
}
[0-9]+ {
  yylval.i = atoi(yytext);
  return INT_T;
}
"==" {
  return EQ_T;
}
"!=" {
  return NEQ_T;
}
"<<" {
  return SHIFTL_T;
}
">>" {
  return SHIFTR_T;
}
[="%,;+*/~|&^-] {
  return *yytext;
}
. {
  std::cerr << "Leksicka greska: " << *yytext << std::endl; 
}

%%

