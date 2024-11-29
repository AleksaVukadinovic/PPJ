%option noyywrap

%{
    #include <stdio.h>
    #include <stdlib.h>

    // 0 je rezervisan broj -- EOF

    #define I_CONST (1)
    #define F_CONST (2)
%}

DIGIT [0-9]

%%

[+-]?{DIGIT}+                                   {return I_CONST; }
[+-]?{DIGIT}+\.{DIGIT}*([Ee][+-]?{DIGIT}+)?     {return F_CONST; }
.                                               { }
\n                                              { }
%%

int main(int argc, char** argv){
    int token = 0;
    while(token = yylex()){
        switch(token) {
            case I_CONST:
                printf("Ceo broj: %s\n", yytext);
                break;
            case F_CONST:
                printf("Realan broj: %s\n", yytext);
                break;
        }
    }
    
    exit(EXIT_SUCCESS);
}