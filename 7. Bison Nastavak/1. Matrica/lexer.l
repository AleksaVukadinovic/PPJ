%{
  #include <iostream>
  #include <cstdlib>
  #include <map>
  #include <vector>
  #include "Matrica.hpp"
  #include "parser.tab.hpp"
%}

%%

size {
  return SIZE_T;
}
rows {
  return ROWS_T;
}
cols {
  return COLS_T;
}
[a-zA-Z_][a-zA-Z0-9_]* {
  yylval.s = new std::string(yytext);
  return ID;
}
[0-9]+(\.[0-9]*)? {
  yylval.d = atof(yytext);
  return BROJ;
}
"./" {
  return PODELI_T;
}
".*" {
  return POMNOZI_T;
}
"==" {
  return EQ_T;
}
"!=" {
  return NEQ_T;
}
"["|"]"|"'" { 
  return *yytext;
}
[+*(),;:=\n-] {
  return *yytext;
}
%.* { }
[ \t] { }
. {
  std::cerr << "Leksicka greska: " << (*yytext) << std::endl;
  exit(EXIT_FAILURE);
}
%%