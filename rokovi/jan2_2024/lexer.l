%option noyywrap

%{
  #include <iostream>
  #include <cstdlib>
  #include <vector>

  #include "SymbolTable.hpp"
  #include "SyntaxTree.hpp"
  #include "parser.tab.hpp"
%}

%%

start {
  return START_T;
}
end {
  return END_T;
}
std_output {
  return STDOUTPUT_T;
}
std_input {
  return STDINPUT_T;
}
std_error {
  return STDERR_T;
}
if {
  return IF_T;
}
else {
  return ELSE_T;
}
print_ALL {
  return PRINTALL_T;
}
string {
  return DEF_T;
}
[a-zA-Z_][a-zA-Z0-9_]* {
  yylval.s = new std::string(yytext);
  return ID_T;
}
\"[^\"]*\" {
  std::string tmp(yytext);
  yylval.s = new std::string(tmp.substr(1, tmp.size() - 2));
  return VAL_T;
}
"<<" {
  return LSHIFT;
}
">>" {
  return RSHIFT;
}
"==" {
  return EQ_T;
}
"!=" {
  return NEQ_T;
}
[;\"=*+~{}()] {
  return *yytext;
} 
[ \t\n] {
  
}
. {
  std::cerr << "Leksicka greska: " << (*yytext) << std::endl;
  exit(EXIT_FAILURE);
}

%%