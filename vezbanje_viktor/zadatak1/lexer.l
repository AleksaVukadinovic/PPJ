%option noyywrap

%{
    #include <iostream>
    #include <cstdlib>
    #include <vector>

    #include "SyntaxTree.hpp"
    #include "parser.tab.hpp"
%}

%%

"def" {
    return DEF_T;
}
"print" {
    return PRINT_T; 
}
[a-zA-Z_][a-zA-Z0-9_]* { 
    yylval.s = new std::string(yytext);
    return ID_T; 
}
[0-9]+(\.[0-9]+)? {
    yylval.d = atof(yytext);
    return NUM_T;
}
[+*/();=-] {
    return *yytext;
} 
[ \n\t] {

}
. {
    std::cerr << "Leksicka greska" << std::endl;
}

%%