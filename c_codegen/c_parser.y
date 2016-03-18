%code requires{
    #include <stdio.h>
    #include <iostream>
    #include "ast.hpp"
    
    int yylex(void); //recognizes tokens from the input stream and returns them to the parser.
    void yyerror(const char *);
    extern Func_body_list *ast; 
}

%union{
    Value *cvalue;
    Func_body *func_body;
    Func_body_list *func_body_list;
    Expression *cexpr;
    Optr *optr;
    Statement_list *statement_list;
    Var *var;
    Id_list *id_list;
    Argument *argument;
    int number;
    const char* str;
}

%{
    std::vector<std::string> Var::value;
    std::vector<std::string> Var::type;
    std::vector< std::map<std::string, int> > var_stack;
%}

%token COMMA LCURLY RCURLY SEMICN  EQUOP LBKT RBKT
%token <str> DATA_TYPE ID RETURN ADDOP MUNISOP MULTIOP DIVOP FUN_ENTRY
%token <number> NUM
%type <cexpr> EXPR
%type <cvalue> FACTOR
%type <statement> ARITHMETIC
%type <func_body> FUN_BODY
%type <statement_list> STATEMENT_list
%type <func_body_list> FUN_BODY_list
%type <func_body> FUN
%type <var> DATA_VAR
%type <var> DATA_DECLARE
%type <id_list> ID_list
%type <var> ARGUMENT
%left ADDOP MUNISOP
%left MULTIOP DIVOP
%start START


%%
START :
|FUN 
;

FUN : DATA_TYPE FUN_ENTRY LCURLY RCURLY FUN { std::cout << "NOTHING" << std::endl;}
| DATA_TYPE FUN_ENTRY LBKT ARGUMENT COMMA ARGUMENT RBKT LCURLY FUN_BODY_list RCURLY FUN{Var* v = new Var();std::cout<<"_"<<$2<<":\n      subu $sp, $sp, 8\n  sw $fp, 8($sp)\n    sw $ra, 4($sp)\n    addiu $fp, $sp, 8 \n    subu $sp, $sp, 12"<<std::endl; ast = $9;}
| FUN { ast = $1;}
;

ARGUMENT : DATA_TYPE ID {$$ = new Var($2); $$->Add_type($1);}

FUN_BODY_list : FUN_BODY_list FUN_BODY { $1->Add($2); $$ = $1;}
| FUN_BODY {$$ = new Func_body_list(); $$->Add($1); }
;

FUN_BODY : STATEMENT_list{$$ = $1;}
;

STATEMENT_list : STATEMENT_list ARITHMETIC RETURN EXPR SEMICN{$1->Add($2); $$ = $1; }
| ARITHMETIC RETURN EXPR SEMICN{$$ = new Statement_list(); $$->Add($1);}
| RETURN EXPR SEMICN{$$->retrun_to_MIPS();}
;

ARITHMETIC: DATA_VAR EQUOP EXPR SEMICN { $$ = new Statement(); $$->Add($1, $3); }
| DATA_DECLARE {$$ = new Statement(); $$->Add($1);}
;

DATA_DECLARE : DATA_VAR SEMICN {$1->Add_semi(); $$ = $1;}
| DATA_VAR COMMA ID_list SEMICN {$3->Add_type($1->get_type()); $1->Add_id($3); $1->Add_semi(); $$ = $1;}
;

ID_list : ID_list COMMA ID {$1->Add($3); $$ = $1;}
| ID { $$ = new Id_list(); $$->Add($1); }
;

DATA_VAR: DATA_TYPE ID {$$ = new Var($2); $$->Add_type($1);}
| ID {$$ = new Var($1, true); }
;

EXPR: EXPR ADDOP EXPR { $$ = new Expr(); Optr* a = new Optr($2); $$->Add($1, a, $3); $$ -> to_MIPS();}
| EXPR MUNISOP EXPR { $$ = new Expr(); Optr* a = new Optr($2); $$->Add($1, a, $3); $$ -> to_MIPS();}
| EXPR MULTIOP EXPR { $$ = new Expr(); Optr* a = new Optr($2); $$->Add($1, a, $3); $$ -> to_MIPS();}
| EXPR DIVOP EXPR { $$ = new Expr(); Optr* a = new Optr($2); $$->Add($1, a, $3); $$ -> to_MIPS();}
| FACTOR {$$ = new Expr(); $$->Add($1); $$ -> to_MIPS();}
;

FACTOR: LBKT EXPR RBKT {$2->set_bracket(1); $$ = $2; }
| NUM { $$ = new Number($1);}
| ID {$$ = new Var($1, true); }
;

%%

void  yyerror(const char *s) {
    fprintf(stderr, "%s\n", s);
    exit(1);
}
