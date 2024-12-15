%option noyywrap

%{
    #include <stdio.h>
    #include <stdlib.h>

    int vrednost = 0;
%}

hiljade M+
stotine C+|CD|DC*|CM
desetice X+|XL|LX*|XC
jedinice I+|IV|VI*|IX

%%

{hiljade}   {
                // yyleng <=> strlen(yytext)
                vrednost += 1000*yyleng;
            }
{stotine}   {
                if(strcmp(yytext, "CM") == 0)
                    vrednost+=900;
                else if(strcmp(yytext, "CD") == 0)
                    vrednost+=400;
                else {
                    if(yytext[0]=='D'){
                        vrednost+=500;
                        if(yyleng <= 4)
                            vrednost+=100*(yyleng-1);
                        else {
                            printf("Neispravan broj\n");
                            exit(EXIT_FAILURE);
                        }
                    } else {
                        if (yyleng <= 3)
                            vrednost+=100*(yyleng);
                        else {
                            printf("Neispravan broj\n");
                            exit(EXIT_FAILURE);
                        }
                    }
                }
            }
{desetice}  {
                if(strcmp(yytext, "XC") == 0)
                    vrednost+=90;
                else if(strcmp(yytext, "XL") == 0)
                    vrednost+=40;
                else {
                    if(yytext[0]=='L'){
                        vrednost+=50;
                        if(yyleng <= 4)
                            vrednost+=10*(yyleng-1);
                        else {
                            printf("Neispravan broj\n");
                            exit(EXIT_FAILURE);
                        }
                    } else {
                        if (yyleng <= 3)
                            vrednost+=10*(yyleng);
                        else {
                            printf("Neispravan broj\n");
                            exit(EXIT_FAILURE);
                        }
                    }
                }
            }
{jedinice}  {
                if(strcmp(yytext, "IX") == 0)
                    vrednost+=9;
                else if(strcmp(yytext, "IV") == 0)
                    vrednost+=4;
                else {
                    if(yytext[0]=='V'){
                        vrednost+=5;
                        if(yyleng <= 4)
                            vrednost+=1*(yyleng-1);
                        else {
                            printf("Neispravan broj\n");
                            exit(EXIT_FAILURE);
                        }
                    } else {
                        if (yyleng <= 3)
                            vrednost+=1*(yyleng);
                        else {
                            printf("Neispravan broj\n");
                            exit(EXIT_FAILURE);
                        }
                    }
                }
            }
.|\n        {
                if(vrednost > 0) {
                    printf("%d\n", vrednost);
                    vrednost = 0;
                }
                ECHO;
            }

%%

int main(){
    yylex();
    exit(EXIT_SUCCESS);
}