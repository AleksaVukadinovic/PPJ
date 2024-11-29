%option noyywrap

%{
    #include <stdio.h>
    #include <stdlib.h>

    int brojOtvorenih = 0;
%}

%%

"("     {brojOtvorenih++; ECHO;}
")"     {
            ECHO;
            if (brojOtvorenih > 0)
                brojOtvorenih--;
            else {
                printf("Zagrade nisu uparene\n");
                return -1;
            }
        }
.       {
            ECHO;
}
\n      {
            ECHO;
}
%%

int main(){
    if(yylex()==-1) {
        printf("Greska\n");
        exit(EXIT_FAILURE);
    }

    if(brojOtvorenih == 0)
        printf("Zagrade su uparene\n");
    else
        printf("Zagrade nisu uparene\n");
    exit(EXIT_SUCCESS);
}