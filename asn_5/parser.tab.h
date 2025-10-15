/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    NEQ = 258,                     /* NEQ  */
    LEQ = 259,                     /* LEQ  */
    GEQ = 260,                     /* GEQ  */
    EQ = 261,                      /* EQ  */
    MAX = 262,                     /* MAX  */
    MIN = 263,                     /* MIN  */
    INC = 264,                     /* INC  */
    DEC = 265,                     /* DEC  */
    AND = 266,                     /* AND  */
    OR = 267,                      /* OR  */
    NOT = 268,                     /* NOT  */
    PRECOMPILER = 269,             /* PRECOMPILER  */
    NUMCONST = 270,                /* NUMCONST  */
    ERROR = 271,                   /* ERROR  */
    COMMENT = 272,                 /* COMMENT  */
    ID = 273,                      /* ID  */
    INT = 274,                     /* INT  */
    CHAR = 275,                    /* CHAR  */
    IF = 276,                      /* IF  */
    THEN = 277,                    /* THEN  */
    ELSE = 278,                    /* ELSE  */
    WHILE = 279,                   /* WHILE  */
    DO = 280,                      /* DO  */
    FOR = 281,                     /* FOR  */
    TO = 282,                      /* TO  */
    BY = 283,                      /* BY  */
    STRINGCONST = 284,             /* STRINGCONST  */
    CHARCONST = 285,               /* CHARCONST  */
    BOOL = 286,                    /* BOOL  */
    BOOLCONST = 287,               /* BOOLCONST  */
    STATIC = 288,                  /* STATIC  */
    RETURN = 289,                  /* RETURN  */
    BREAK = 290,                   /* BREAK  */
    SUBASS = 291,                  /* SUBASS  */
    ADDASS = 292,                  /* ADDASS  */
    MULASS = 293,                  /* MULASS  */
    DIVASS = 294,                  /* DIVASS  */
    FIRSTSTOP = 295,               /* FIRSTSTOP  */
    LASTSTOP = 296,                /* LASTSTOP  */
    LASTTERM = 297                 /* LASTTERM  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 80 "parser.y"

   struct   TokenData *tinfo;
   struct   TreeNode *tree;
   ExpType  type;

#line 112 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
