%option noyywrap

%{
    #include <iostream>
    #include <cstdlib>
    #include <map>
    #include "KompleksniBroj.hpp"
    #include "parser.tab.hpp"
%}

%%
print   {return PRINT_T;}
arg     {return ARG_T;}
mod     {return MOD_T;}
re      {return RE_T;}
im      {return IM_T;}
def     {return DEF_T;}
[A-Za-z_][A-Za-z0-9_]* {
                            yylval.s = new std::string(yytext);
                            return ID;
                        }
[0-9]+(\.[0-9]*)?       {
                            yylval.v = atof(yytext);
                            return BROJ;
                        }
"=="            {   
                    return EQ;
                }
"!="            {  return NEQ;}
[+*/<>(),;=~-]  {   
                    return *yytext;
                }
[ \t\n]         {}
.               {
                    std::cerr<<"Leksicka greska: "
                        << (*yytext) << std::endl;
                    exit(EXIT_FAILURE);
                }

%%