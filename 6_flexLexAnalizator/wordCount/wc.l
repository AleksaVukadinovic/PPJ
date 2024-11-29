%option noyywrap

%{
    // obicni C/C++ kod
    // kopira se direktno u C fajl
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int brojLinija = 0;
    int brojKaraktera = 0;
    int brojReci = 0;
%}

%%
[a-zA-Z]+   {
                brojReci++;
                brojKaraktera+=strlen(yytext);
            }
.   {brojKaraktera++; }
\n  {
        brojKaraktera++;
        brojLinija++;
    }
%%

int main(){
    yylex();
    printf("Broj karaktera: %d\n", brojKaraktera);
    printf("Broj linija: %d\n", brojLinija);
    printf("Broj reci: %d\n", brojReci);
    exit(EXIT_SUCCESS);
}