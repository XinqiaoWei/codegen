/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_C_PARSER_TAB_H_INCLUDED
# define YY_YY_C_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "c_parser.y" /* yacc.c:1909  */

    #include <stdio.h>
    #include <iostream>
    #include "ast.hpp"
    
    int yylex(void); //recognizes tokens from the input stream and returns them to the parser.
    void yyerror(const char *);
    extern Func_body_list *ast; 

#line 54 "c_parser.tab.h" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    COMMA = 258,
    LCURLY = 259,
    RCURLY = 260,
    SEMICN = 261,
    EQUOP = 262,
    LBKT = 263,
    RBKT = 264,
    DATA_TYPE = 265,
    ID = 266,
    RETURN = 267,
    ADDOP = 268,
    MUNISOP = 269,
    MULTIOP = 270,
    DIVOP = 271,
    FUN_ENTRY = 272,
    NUM = 273
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 11 "c_parser.y" /* yacc.c:1909  */

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

#line 99 "c_parser.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_C_PARSER_TAB_H_INCLUDED  */
