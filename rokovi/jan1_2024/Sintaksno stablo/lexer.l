%option noyywrap

%{
    #include <iostream>
    #include <map>
    #include <vector>
    #include <cstdlib>
    #include <bitset>

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
[a-zA-Z_][a-zA-Z0-9_]* {
    yylval.s = new std::string(yytext);
    return ID_T;
}
[0-9]+(.[0-9]+)? {
    yylval.i = atoi(yytext);
    return NUM_T;
}
\"%[dbh]\" {
    std::string format(yytext);
    yylval.c = format[2];
    return FORMAT_T;
}
"<<" {
    return LSHIFT_T;
}
">>" {
    return RSHIFT_T;
}
"==" {
    return EQ_T;
}
"!=" {
    return NEQ_T;
}
[+*/%;,()=~|&^-] {
    return *yytext;
}
[ \t\n] {

}
. {
    std::cerr << "Leksicka greska: " << (*yytext)<< std::endl;
    exit(EXIT_FAILURE);
}


%%
