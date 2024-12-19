%option noyywrap

%{
    #include <stdio.h>
    #include <stdlib.h>
    int brojLinija = 0;
%}

%x comment

%%

"/*"    {BEGIN(comment); }
<comment>[^*\n]*    { }
<comment>"*"*       { }
<comment>\n         {brojLinija++; }
<comment>\*+"/"     {BEGIN(INITIAL); }

\n                  {brojLinija++; ECHO;}
.                   {ECHO;}

%%

int main(int argc, char** argv){

    // yyin - ulazni tok
    // yyout - izlazni tok

    if(argc>1){
        yyin = fopen(argv[1], "r");
        if(yyin == NULL)
            exit(EXIT_FAILURE);
    } else {
        yyin = stdin;
    }

    if (argc > 2) {
        yyout = fopen(argv[2], "w");
        if(yyout == NULL)
            exit(EXIT_FAILURE);
    } else {
        yyout = stdout;
    }

    yylex();

    printf("Broj linija: %d\n", brojLinija);

    if(yyin != stdin) {
        fclose(yyin);
    }
    if(yyout != stdout){
        fclose(yyout);
    }

    exit(EXIT_SUCCESS);
}