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

begin {
    return BEGIN_T;
}
end {
    return END_T;
}
while {
    return WHILE_T;
}
print {
    return PRINT_T;
}
if {
    return IF_T;
}
else  {
    return ELSE_T;
}
then {
    return THEN_T;
}
do {
    return DO_T;
}
[a-zA-Z_][a-zA-Z0-9_]* {
    yylval.s = new std::string(yytext);
    return ID_T;
}
[0-9]+ {
    yylval.i = atoi(yytext);
    return NUM_T;
}
":=" {
    return ASSIGN_T;
}
[+;.()<>-] {
    return *yytext;
}
[ \t\n] {

}
. {
    std::cerr << "Lekscika greska: " << (*yytext) << std::endl;
    exit(EXIT_FAILURE);
}
%%
