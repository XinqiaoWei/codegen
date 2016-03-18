%option noyywrap 

%{
    #include <iostream>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string>
    #include "Parser.tab.h"
%}

%%

[0-9]+                  { yylval.number = atoi(yytext);
                          return NUM;
                        }

[0-9]+"."[0.9]+         { yylval.number = atof(yytext);
                          return NUM;
                        }

"int"                   { yylval.str = strdup(yytext);
                          return DATA_TYPE;
                        }

"="                     { return EQUOP; }

","                     { return COMMA; }

"+"                     { yylval.str=strdup(yytext);
                          return ADDOP;
                        }

"-"                     { yylval.str=strdup(yytext);
                          return MUNISOP;
                        }

"*"                     { yylval.str=strdup(yytext);
                          return MULTIOP;
                        }
    
"/"                     { yylval.str=strdup(yytext);
                          return DIVOP;
                        }
    
"("                     { return LBKT; }

")"                     { return RBKT; }

"{"                     { return LCURLY; }

"}"                     { return RCURLY; }

";"                     { return SEMICN; }

\n                      {}

[a-zA-Z][a-zA-Z_0-9]*   { yylval.str=strdup(yytext);
                          return ID;
                        }

"return".*              { yylval.str=strdup(yytext);
                          return RETURN;
                        }


%%
    
    
