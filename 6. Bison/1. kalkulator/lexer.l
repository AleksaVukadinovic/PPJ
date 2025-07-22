%option noyywrap

%{
  #include <iostream>
  #include <cstdlib>
  #include "parser.tab.hpp"  
%}


%%
print {return PRINT_T;}
[A-Za-z_]+[A-Za-z0-9_]* {
  yylval.s = new std::string(yytext);
  return ID;
}
[0-9]+(\.[0-9]*)? {
  yylval.v = atof(yytext);
  return BROJ;
}
"==" {
  return EQ;
}
"!=" {
  return NEQ;
}
">=" {
  return GEQ;
}
"<=" {
  return LEQ;
}
[+*/<>;()=-] {
  return *yytext;
}
[ \t\n] {}
. {
  std::cerr << "Leksicka greska: " << (*yytext) << std::endl;
  exit(EXIT_FAILURE);
}
%%