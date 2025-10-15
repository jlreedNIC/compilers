/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include "treeUtils.h"
#include "treeNodes.h"
#include "scanType.h"
#include "dot.h"
#include "semantics.h"
#include "symbolTable.h"
#include "codegen.h"
#include "yyerror.h"
using namespace std;

int numErrors;
int numWarnings;
extern int line;
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
// extern yyerror();

// void yyerror(const char *msg);

bool debug = false;
void printDebug(string msg)
{
   if(debug == true)
   {
      cout << msg << "- ";
   }
}

TreeNode *addSibling(TreeNode *t, TreeNode *s)
{
   // printDebug("in addSibling func\n");
   if(s == nullptr)
   {
      printDebug("Sibling is null!\n");
      exit(1);
   }

   if(t == nullptr)
   {
      // printDebug("main is null\n");
      return s;
   }

   TreeNode *ptr = t;
   // ptr = t;
   while(ptr->sibling != nullptr)
   {
      ptr = ptr->sibling;
   }
   ptr->sibling = s;

   // printDebug("leaving sibling\n");
   return t;
}

// pass the static and type attribute down the sibling list
void setType(TreeNode *t, ExpType type, bool isStatic)
{
   // printDebug("in settype func.\n");
   while (t != nullptr)
   {
      t->type = type;
      t->isStatic = isStatic;
      t = t->sibling;
   }
}

// the syntax tree goes here
TreeNode *syntaxTree;


#line 149 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_3_ = 3,                         /* '='  */
  YYSYMBOL_4_ = 4,                         /* '*'  */
  YYSYMBOL_5_ = 5,                         /* '+'  */
  YYSYMBOL_6_ = 6,                         /* '/'  */
  YYSYMBOL_7_ = 7,                         /* '%'  */
  YYSYMBOL_8_ = 8,                         /* '-'  */
  YYSYMBOL_9_ = 9,                         /* '<'  */
  YYSYMBOL_10_ = 10,                       /* '>'  */
  YYSYMBOL_11_ = 11,                       /* '?'  */
  YYSYMBOL_12_ = 12,                       /* '('  */
  YYSYMBOL_13_ = 13,                       /* ')'  */
  YYSYMBOL_14_ = 14,                       /* ','  */
  YYSYMBOL_15_ = 15,                       /* ';'  */
  YYSYMBOL_16_ = 16,                       /* '['  */
  YYSYMBOL_17_ = 17,                       /* '{'  */
  YYSYMBOL_18_ = 18,                       /* '}'  */
  YYSYMBOL_19_ = 19,                       /* ']'  */
  YYSYMBOL_20_ = 20,                       /* ':'  */
  YYSYMBOL_NEQ = 21,                       /* NEQ  */
  YYSYMBOL_LEQ = 22,                       /* LEQ  */
  YYSYMBOL_GEQ = 23,                       /* GEQ  */
  YYSYMBOL_EQ = 24,                        /* EQ  */
  YYSYMBOL_MAX = 25,                       /* MAX  */
  YYSYMBOL_MIN = 26,                       /* MIN  */
  YYSYMBOL_INC = 27,                       /* INC  */
  YYSYMBOL_DEC = 28,                       /* DEC  */
  YYSYMBOL_AND = 29,                       /* AND  */
  YYSYMBOL_OR = 30,                        /* OR  */
  YYSYMBOL_NOT = 31,                       /* NOT  */
  YYSYMBOL_PRECOMPILER = 32,               /* PRECOMPILER  */
  YYSYMBOL_NUMCONST = 33,                  /* NUMCONST  */
  YYSYMBOL_ERROR = 34,                     /* ERROR  */
  YYSYMBOL_COMMENT = 35,                   /* COMMENT  */
  YYSYMBOL_ID = 36,                        /* ID  */
  YYSYMBOL_INT = 37,                       /* INT  */
  YYSYMBOL_CHAR = 38,                      /* CHAR  */
  YYSYMBOL_IF = 39,                        /* IF  */
  YYSYMBOL_THEN = 40,                      /* THEN  */
  YYSYMBOL_ELSE = 41,                      /* ELSE  */
  YYSYMBOL_WHILE = 42,                     /* WHILE  */
  YYSYMBOL_DO = 43,                        /* DO  */
  YYSYMBOL_FOR = 44,                       /* FOR  */
  YYSYMBOL_TO = 45,                        /* TO  */
  YYSYMBOL_BY = 46,                        /* BY  */
  YYSYMBOL_STRINGCONST = 47,               /* STRINGCONST  */
  YYSYMBOL_CHARCONST = 48,                 /* CHARCONST  */
  YYSYMBOL_BOOL = 49,                      /* BOOL  */
  YYSYMBOL_BOOLCONST = 50,                 /* BOOLCONST  */
  YYSYMBOL_STATIC = 51,                    /* STATIC  */
  YYSYMBOL_RETURN = 52,                    /* RETURN  */
  YYSYMBOL_BREAK = 53,                     /* BREAK  */
  YYSYMBOL_SUBASS = 54,                    /* SUBASS  */
  YYSYMBOL_ADDASS = 55,                    /* ADDASS  */
  YYSYMBOL_MULASS = 56,                    /* MULASS  */
  YYSYMBOL_DIVASS = 57,                    /* DIVASS  */
  YYSYMBOL_FIRSTSTOP = 58,                 /* FIRSTSTOP  */
  YYSYMBOL_LASTSTOP = 59,                  /* LASTSTOP  */
  YYSYMBOL_LASTTERM = 60,                  /* LASTTERM  */
  YYSYMBOL_YYACCEPT = 61,                  /* $accept  */
  YYSYMBOL_program = 62,                   /* program  */
  YYSYMBOL_precomList = 63,                /* precomList  */
  YYSYMBOL_declList = 64,                  /* declList  */
  YYSYMBOL_decl = 65,                      /* decl  */
  YYSYMBOL_varDecl = 66,                   /* varDecl  */
  YYSYMBOL_scopedVarDecl = 67,             /* scopedVarDecl  */
  YYSYMBOL_varDeclList = 68,               /* varDeclList  */
  YYSYMBOL_varDeclInit = 69,               /* varDeclInit  */
  YYSYMBOL_varDeclId = 70,                 /* varDeclId  */
  YYSYMBOL_typeSpec = 71,                  /* typeSpec  */
  YYSYMBOL_funDecl = 72,                   /* funDecl  */
  YYSYMBOL_parms = 73,                     /* parms  */
  YYSYMBOL_parmList = 74,                  /* parmList  */
  YYSYMBOL_parmTypeList = 75,              /* parmTypeList  */
  YYSYMBOL_parmIdList = 76,                /* parmIdList  */
  YYSYMBOL_parmId = 77,                    /* parmId  */
  YYSYMBOL_stmt = 78,                      /* stmt  */
  YYSYMBOL_matched = 79,                   /* matched  */
  YYSYMBOL_iterRange = 80,                 /* iterRange  */
  YYSYMBOL_unmatched = 81,                 /* unmatched  */
  YYSYMBOL_expstmt = 82,                   /* expstmt  */
  YYSYMBOL_compoundstmt = 83,              /* compoundstmt  */
  YYSYMBOL_localDecls = 84,                /* localDecls  */
  YYSYMBOL_stmtList = 85,                  /* stmtList  */
  YYSYMBOL_returnstmt = 86,                /* returnstmt  */
  YYSYMBOL_breakstmt = 87,                 /* breakstmt  */
  YYSYMBOL_exp = 88,                       /* exp  */
  YYSYMBOL_assignop = 89,                  /* assignop  */
  YYSYMBOL_simpleExp = 90,                 /* simpleExp  */
  YYSYMBOL_andExp = 91,                    /* andExp  */
  YYSYMBOL_unaryRelExp = 92,               /* unaryRelExp  */
  YYSYMBOL_relExp = 93,                    /* relExp  */
  YYSYMBOL_relop = 94,                     /* relop  */
  YYSYMBOL_minmaxExp = 95,                 /* minmaxExp  */
  YYSYMBOL_minmaxop = 96,                  /* minmaxop  */
  YYSYMBOL_sumExp = 97,                    /* sumExp  */
  YYSYMBOL_sumop = 98,                     /* sumop  */
  YYSYMBOL_mulExp = 99,                    /* mulExp  */
  YYSYMBOL_mulop = 100,                    /* mulop  */
  YYSYMBOL_unaryExp = 101,                 /* unaryExp  */
  YYSYMBOL_unaryop = 102,                  /* unaryop  */
  YYSYMBOL_factor = 103,                   /* factor  */
  YYSYMBOL_mutable = 104,                  /* mutable  */
  YYSYMBOL_immutable = 105,                /* immutable  */
  YYSYMBOL_call = 106,                     /* call  */
  YYSYMBOL_args = 107,                     /* args  */
  YYSYMBOL_argList = 108,                  /* argList  */
  YYSYMBOL_constant = 109                  /* constant  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   266

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  61
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  116
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  177

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   297


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     7,     2,     2,
      12,    13,     4,     5,    14,     8,     2,     6,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    20,    15,
       9,     3,    10,    11,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    16,     2,    19,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    17,     2,    18,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   121,   121,   124,   125,   126,   129,   130,   133,   134,
     137,   140,   141,   144,   145,   148,   149,   152,   153,   157,
     158,   159,   162,   163,   166,   167,   170,   171,   174,   177,
     178,   181,   183,   187,   188,   191,   192,   193,   195,   196,
     197,   198,   201,   202,   205,   206,   207,   208,   212,   213,
     216,   217,   221,   222,   225,   226,   229,   230,   233,   236,
     237,   238,   239,   240,   243,   244,   245,   246,   247,   250,
     251,   254,   255,   258,   259,   262,   263,   266,   267,   268,
     269,   270,   271,   274,   275,   278,   279,   282,   283,   286,
     287,   290,   291,   294,   295,   296,   299,   300,   303,   304,
     305,   308,   309,   312,   313,   316,   317,   318,   321,   324,
     325,   328,   329,   332,   337,   342,   347
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "'='", "'*'", "'+'",
  "'/'", "'%'", "'-'", "'<'", "'>'", "'?'", "'('", "')'", "','", "';'",
  "'['", "'{'", "'}'", "']'", "':'", "NEQ", "LEQ", "GEQ", "EQ", "MAX",
  "MIN", "INC", "DEC", "AND", "OR", "NOT", "PRECOMPILER", "NUMCONST",
  "ERROR", "COMMENT", "ID", "INT", "CHAR", "IF", "THEN", "ELSE", "WHILE",
  "DO", "FOR", "TO", "BY", "STRINGCONST", "CHARCONST", "BOOL", "BOOLCONST",
  "STATIC", "RETURN", "BREAK", "SUBASS", "ADDASS", "MULASS", "DIVASS",
  "FIRSTSTOP", "LASTSTOP", "LASTTERM", "$accept", "program", "precomList",
  "declList", "decl", "varDecl", "scopedVarDecl", "varDeclList",
  "varDeclInit", "varDeclId", "typeSpec", "funDecl", "parms", "parmList",
  "parmTypeList", "parmIdList", "parmId", "stmt", "matched", "iterRange",
  "unmatched", "expstmt", "compoundstmt", "localDecls", "stmtList",
  "returnstmt", "breakstmt", "exp", "assignop", "simpleExp", "andExp",
  "unaryRelExp", "relExp", "relop", "minmaxExp", "minmaxop", "sumExp",
  "sumop", "mulExp", "mulop", "unaryExp", "unaryop", "factor", "mutable",
  "immutable", "call", "args", "argList", "constant", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-140)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -15,  -140,    23,   -17,  -140,  -140,    25,  -140,  -140,  -140,
       7,  -140,  -140,    16,  -140,    55,  -140,    61,    91,  -140,
      39,    32,    71,    85,  -140,    55,    37,    58,  -140,   210,
      86,    96,  -140,   159,    55,    99,   103,   109,  -140,  -140,
    -140,  -140,   210,   210,  -140,    79,  -140,  -140,  -140,    98,
      97,  -140,  -140,    57,    17,    92,  -140,   216,  -140,  -140,
    -140,  -140,  -140,   113,    32,  -140,  -140,   210,   210,    95,
     169,   118,  -140,  -140,  -140,  -140,   119,  -140,  -140,   120,
      98,     6,  -140,   159,  -140,   127,  -140,   210,   210,   210,
     210,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,   216,
     216,  -140,  -140,   216,  -140,  -140,  -140,   216,  -140,  -140,
    -140,    52,    11,   -19,   138,  -140,   129,  -140,  -140,  -140,
    -140,  -140,  -140,  -140,  -140,  -140,  -140,    38,  -140,  -140,
    -140,   134,   128,   130,    97,  -140,    50,    17,    92,  -140,
      55,  -140,    58,   112,   159,   159,   210,  -140,  -140,  -140,
    -140,   210,  -140,    58,    93,  -140,  -140,  -140,   111,  -140,
    -140,   107,   -14,  -140,   104,  -140,   159,   159,   210,  -140,
    -140,  -140,  -140,  -140,   -20,   210,    98
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       5,     4,     0,     0,     1,     3,     0,    19,    21,    20,
       2,     7,     8,     0,     9,    25,     6,    17,     0,    14,
      15,     0,     0,    24,    27,    25,     0,     0,    10,     0,
      31,    28,    30,     0,     0,     0,     0,    17,    13,    99,
      98,   100,     0,     0,   113,   103,   115,   114,   116,    16,
      70,    72,    74,    76,    84,    88,    92,     0,    97,   102,
     101,   106,   107,     0,     0,    49,    53,     0,     0,     0,
       0,     0,    23,    33,    34,    38,    39,    40,    41,     0,
      62,   102,    26,     0,    18,     0,    73,   110,     0,     0,
       0,    78,    79,    82,    77,    80,    81,    85,    86,     0,
       0,    89,    90,     0,    93,    94,    95,     0,    96,    32,
      29,    55,     0,     0,     0,    56,     0,    58,    51,    48,
      64,    60,    61,    66,    65,    67,    68,     0,    22,   105,
     112,     0,   109,     0,    69,    71,    75,    83,    87,    91,
       0,    52,     0,     0,     0,     0,     0,    57,    63,    59,
     108,     0,   104,     0,     0,    50,    54,    44,    33,    36,
      46,     0,     0,   111,     0,    12,     0,     0,     0,    11,
      35,    45,    37,    47,    42,     0,    43
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -140,  -140,  -140,  -140,   143,  -140,  -140,  -124,   131,  -140,
      -2,  -140,   132,  -140,   121,  -140,   102,   -79,  -131,  -140,
    -139,  -140,  -140,  -140,  -140,  -140,  -140,   -40,  -140,   -29,
      72,   -36,  -140,  -140,    69,  -140,    75,  -140,    66,  -140,
     -52,  -140,  -140,   -30,  -140,  -140,  -140,  -140,  -140
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     3,    10,    11,    12,   141,    18,    19,    20,
      21,    14,    22,    23,    24,    31,    32,    72,    73,   161,
      74,    75,    76,   111,   143,    77,    78,    79,   127,    80,
      50,    51,    52,    99,    53,   100,    54,   103,    55,   107,
      56,    57,    58,    59,    60,    61,   131,   132,    62
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      49,    13,    85,    81,   128,   108,   160,    86,    13,   120,
      89,    89,    81,   158,   159,     5,    89,     1,   154,     6,
       7,     8,   101,     4,   145,   102,   175,   171,   173,   164,
     116,   168,     9,   121,   122,   170,   172,    15,   112,   113,
      81,    89,    39,     6,     7,     8,    40,   130,   133,    41,
      42,   144,    17,    81,   135,   139,     9,    81,    81,    29,
     123,   124,   125,   126,   156,   157,    91,    92,    30,    43,
      36,    44,   148,    25,    45,    97,    98,    26,    93,    94,
      95,    96,    97,    98,    33,    46,    47,   149,    48,     7,
       8,    87,     7,     8,    37,    88,   104,    81,   105,   106,
      34,     9,    63,   140,     9,    27,    28,    27,   165,   142,
      64,   163,    83,    81,    81,    81,    39,   162,    27,   169,
      40,    81,    84,    41,    42,    26,    90,    65,    89,    66,
     155,   114,   109,   117,   118,   119,    81,    81,   153,   174,
     129,   146,   151,    43,   147,    44,   176,   150,    45,   152,
     167,    67,   166,    16,    68,    82,    69,    35,    38,    46,
      47,   134,    48,    39,    70,    71,   110,    40,   136,   138,
      41,    42,     0,    39,    65,   137,    66,    40,     0,     0,
      41,    42,     0,     0,   115,     0,     0,     0,     0,     0,
      43,     0,    44,     0,     0,    45,     0,     0,    67,     0,
      43,    68,    44,    69,     0,    45,    46,    47,     0,    48,
       0,    70,    71,     0,    39,     0,    46,    47,    40,    48,
      39,    41,    42,     0,    40,     0,     0,    41,    42,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    43,     0,    44,     0,     0,    45,     0,     0,    44,
       0,     0,    45,     0,     0,     0,     0,    46,    47,     0,
      48,     0,     0,    46,    47,     0,    48
};

static const yytype_int16 yycheck[] =
{
      29,     3,    42,    33,    83,    57,   145,    43,    10,     3,
      30,    30,    42,   144,   145,    32,    30,    32,   142,    36,
      37,    38,     5,     0,    43,     8,    46,   166,   167,   153,
      70,    45,    49,    27,    28,   166,   167,    12,    67,    68,
      70,    30,     4,    36,    37,    38,     8,    87,    88,    11,
      12,    40,    36,    83,    90,   107,    49,    87,    88,    20,
      54,    55,    56,    57,   143,   144,     9,    10,    36,    31,
      33,    33,    34,    12,    36,    25,    26,    16,    21,    22,
      23,    24,    25,    26,    13,    47,    48,   127,    50,    37,
      38,    12,    37,    38,    36,    16,     4,   127,     6,     7,
      15,    49,    16,    51,    49,    14,    15,    14,    15,   111,
      14,   151,    13,   143,   144,   145,     4,   146,    14,    15,
       8,   151,    19,    11,    12,    16,    29,    15,    30,    17,
      18,    36,    19,    15,    15,    15,   166,   167,   140,   168,
      13,     3,    14,    31,    15,    33,   175,    13,    36,    19,
      43,    39,    41,    10,    42,    34,    44,    25,    27,    47,
      48,    89,    50,     4,    52,    53,    64,     8,    99,   103,
      11,    12,    -1,     4,    15,   100,    17,     8,    -1,    -1,
      11,    12,    -1,    -1,    15,    -1,    -1,    -1,    -1,    -1,
      31,    -1,    33,    -1,    -1,    36,    -1,    -1,    39,    -1,
      31,    42,    33,    44,    -1,    36,    47,    48,    -1,    50,
      -1,    52,    53,    -1,     4,    -1,    47,    48,     8,    50,
       4,    11,    12,    -1,     8,    -1,    -1,    11,    12,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    -1,    33,    -1,    -1,    36,    -1,    -1,    33,
      -1,    -1,    36,    -1,    -1,    -1,    -1,    47,    48,    -1,
      50,    -1,    -1,    47,    48,    -1,    50
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    32,    62,    63,     0,    32,    36,    37,    38,    49,
      64,    65,    66,    71,    72,    12,    65,    36,    68,    69,
      70,    71,    73,    74,    75,    12,    16,    14,    15,    20,
      36,    76,    77,    13,    15,    73,    33,    36,    69,     4,
       8,    11,    12,    31,    33,    36,    47,    48,    50,    90,
      91,    92,    93,    95,    97,    99,   101,   102,   103,   104,
     105,   106,   109,    16,    14,    15,    17,    39,    42,    44,
      52,    53,    78,    79,    81,    82,    83,    86,    87,    88,
      90,   104,    75,    13,    19,    88,    92,    12,    16,    30,
      29,     9,    10,    21,    22,    23,    24,    25,    26,    94,
      96,     5,     8,    98,     4,     6,     7,   100,   101,    19,
      77,    84,    90,    90,    36,    15,    88,    15,    15,    15,
       3,    27,    28,    54,    55,    56,    57,    89,    78,    13,
      88,   107,   108,    88,    91,    92,    95,    97,    99,   101,
      51,    67,    71,    85,    40,    43,     3,    15,    34,    88,
      13,    14,    19,    71,    68,    18,    78,    78,    79,    79,
      81,    80,    90,    88,    68,    15,    41,    43,    45,    15,
      79,    81,    79,    81,    90,    46,    90
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    61,    62,    63,    63,    63,    64,    64,    65,    65,
      66,    67,    67,    68,    68,    69,    69,    70,    70,    71,
      71,    71,    72,    72,    73,    73,    74,    74,    75,    76,
      76,    77,    77,    78,    78,    79,    79,    79,    79,    79,
      79,    79,    80,    80,    81,    81,    81,    81,    82,    82,
      83,    83,    84,    84,    85,    85,    86,    86,    87,    88,
      88,    88,    88,    88,    89,    89,    89,    89,    89,    90,
      90,    91,    91,    92,    92,    93,    93,    94,    94,    94,
      94,    94,    94,    95,    95,    96,    96,    97,    97,    98,
      98,    99,    99,   100,   100,   100,   101,   101,   102,   102,
     102,   103,   103,   104,   104,   105,   105,   105,   106,   107,
     107,   108,   108,   109,   109,   109,   109
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     1,     0,     2,     1,     1,     1,
       3,     4,     3,     3,     1,     1,     3,     1,     4,     1,
       1,     1,     6,     5,     1,     0,     3,     1,     2,     3,
       1,     1,     3,     1,     1,     6,     4,     6,     1,     1,
       1,     1,     3,     5,     4,     6,     4,     6,     2,     1,
       4,     2,     2,     0,     2,     0,     2,     3,     2,     3,
       2,     2,     1,     3,     1,     1,     1,     1,     1,     3,
       1,     3,     1,     2,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     1,     3,     1,     1,
       1,     3,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     4,     3,     1,     1,     4,     1,
       0,     3,     1,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: precomList declList  */
#line 121 "parser.y"
                                             { syntaxTree = (yyvsp[0].tree); printDebug("start"); }
#line 1393 "parser.tab.c"
    break;

  case 3: /* precomList: precomList PRECOMPILER  */
#line 124 "parser.y"
                                             { cout << yylval.tinfo->tokenstr << "\n"; (yyval.tree) = nullptr; printDebug("precompile list"); }
#line 1399 "parser.tab.c"
    break;

  case 4: /* precomList: PRECOMPILER  */
#line 125 "parser.y"
                                             { cout << yylval.tinfo->tokenstr << "\n"; (yyval.tree) = nullptr; printDebug("start2"); }
#line 1405 "parser.tab.c"
    break;

  case 5: /* precomList: %empty  */
#line 126 "parser.y"
                                             { (yyval.tree) = nullptr; }
#line 1411 "parser.tab.c"
    break;

  case 6: /* declList: declList decl  */
#line 129 "parser.y"
                                             { (yyval.tree) = addSibling((yyvsp[-1].tree), (yyvsp[0].tree)); printDebug("declList"); }
#line 1417 "parser.tab.c"
    break;

  case 7: /* declList: decl  */
#line 130 "parser.y"
                                             { (yyval.tree) = (yyvsp[0].tree); printDebug("decl"); }
#line 1423 "parser.tab.c"
    break;

  case 8: /* decl: varDecl  */
#line 133 "parser.y"
                                             { (yyval.tree) = (yyvsp[0].tree); printDebug("varDecl"); }
#line 1429 "parser.tab.c"
    break;

  case 9: /* decl: funDecl  */
#line 134 "parser.y"
                                             { (yyval.tree) = (yyvsp[0].tree); printDebug("funDecl"); }
#line 1435 "parser.tab.c"
    break;

  case 10: /* varDecl: typeSpec varDeclList ';'  */
#line 137 "parser.y"
                                             { (yyval.tree) = (yyvsp[-1].tree); setType((yyvsp[-1].tree), (yyvsp[-2].type), false); printDebug("typespec varDeclL"); }
#line 1441 "parser.tab.c"
    break;

  case 11: /* scopedVarDecl: STATIC typeSpec varDeclList ';'  */
#line 140 "parser.y"
                                                   { (yyval.tree) = (yyvsp[-1].tree); setType((yyvsp[-1].tree), (yyvsp[-2].type), true); (yyval.tree)->isStatic = true; printDebug("scopedVarDecl"); }
#line 1447 "parser.tab.c"
    break;

  case 12: /* scopedVarDecl: typeSpec varDeclList ';'  */
#line 141 "parser.y"
                                             { (yyval.tree) = (yyvsp[-1].tree); setType((yyvsp[-1].tree), (yyvsp[-2].type), false); (yyval.tree)->isStatic = false; printDebug("type varDeclList"); }
#line 1453 "parser.tab.c"
    break;

  case 13: /* varDeclList: varDeclList ',' varDeclInit  */
#line 144 "parser.y"
                                             { (yyval.tree) = addSibling((yyvsp[-2].tree), (yyvsp[0].tree)); printDebug("varDeclList"); }
#line 1459 "parser.tab.c"
    break;

  case 14: /* varDeclList: varDeclInit  */
#line 145 "parser.y"
                                             { (yyval.tree) = (yyvsp[0].tree); printDebug("varDeclInit"); }
#line 1465 "parser.tab.c"
    break;

  case 15: /* varDeclInit: varDeclId  */
#line 148 "parser.y"
                                             { (yyval.tree) = (yyvsp[0].tree); printDebug("varDeclId"); }
#line 1471 "parser.tab.c"
    break;

  case 16: /* varDeclInit: varDeclId ':' simpleExp  */
#line 149 "parser.y"
                                             { (yyval.tree) = (yyvsp[-2].tree); (yyvsp[-2].tree)->child[0] = (yyvsp[0].tree); }
#line 1477 "parser.tab.c"
    break;

  case 17: /* varDeclId: ID  */
#line 152 "parser.y"
                                             { (yyval.tree) = newDeclNode(DeclKind::VarK, UndefinedType, (yyvsp[0].tinfo)); (yyval.tree)->isArray = false;}
#line 1483 "parser.tab.c"
    break;

  case 18: /* varDeclId: ID '[' NUMCONST ']'  */
#line 153 "parser.y"
                                             { (yyval.tree) = newDeclNode(DeclKind::VarK, UndefinedType, (yyvsp[-3].tinfo)); (yyval.tree)->isArray = true;
                                               (yyval.tree)->size = (yyvsp[-1].tinfo)->nvalue + 1;}
#line 1490 "parser.tab.c"
    break;

  case 19: /* typeSpec: INT  */
#line 157 "parser.y"
                                             { (yyval.type) = ExpType::Integer;}
#line 1496 "parser.tab.c"
    break;

  case 20: /* typeSpec: BOOL  */
#line 158 "parser.y"
                                             { (yyval.type) = ExpType::Boolean;}
#line 1502 "parser.tab.c"
    break;

  case 21: /* typeSpec: CHAR  */
#line 159 "parser.y"
                                             { (yyval.type) = ExpType::Char;}
#line 1508 "parser.tab.c"
    break;

  case 22: /* funDecl: typeSpec ID '(' parms ')' stmt  */
#line 162 "parser.y"
                                             { (yyval.tree) = newDeclNode(DeclKind::FuncK, (yyvsp[-5].type), (yyvsp[-4].tinfo), (yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1514 "parser.tab.c"
    break;

  case 23: /* funDecl: ID '(' parms ')' stmt  */
#line 163 "parser.y"
                                             { (yyval.tree) = newDeclNode(DeclKind::FuncK, ExpType::Void, (yyvsp[-4].tinfo), (yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1520 "parser.tab.c"
    break;

  case 24: /* parms: parmList  */
#line 166 "parser.y"
                                             { (yyval.tree) = (yyvsp[0].tree);}
#line 1526 "parser.tab.c"
    break;

  case 25: /* parms: %empty  */
#line 167 "parser.y"
                                             { (yyval.tree) = nullptr;}
#line 1532 "parser.tab.c"
    break;

  case 26: /* parmList: parmList ';' parmTypeList  */
#line 170 "parser.y"
                                             { (yyval.tree) = addSibling((yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1538 "parser.tab.c"
    break;

  case 27: /* parmList: parmTypeList  */
#line 171 "parser.y"
                                             { (yyval.tree) = (yyvsp[0].tree);}
#line 1544 "parser.tab.c"
    break;

  case 28: /* parmTypeList: typeSpec parmIdList  */
#line 174 "parser.y"
                                             { (yyval.tree) = (yyvsp[0].tree); setType((yyvsp[0].tree), (yyvsp[-1].type), false);}
#line 1550 "parser.tab.c"
    break;

  case 29: /* parmIdList: parmIdList ',' parmId  */
#line 177 "parser.y"
                                             { (yyval.tree) = addSibling((yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1556 "parser.tab.c"
    break;

  case 30: /* parmIdList: parmId  */
#line 178 "parser.y"
                                             { (yyval.tree) = (yyvsp[0].tree);}
#line 1562 "parser.tab.c"
    break;

  case 31: /* parmId: ID  */
#line 181 "parser.y"
                                             { (yyval.tree) = newDeclNode(DeclKind::ParamK, ExpType::UndefinedType, (yyvsp[0].tinfo)); 
                                               (yyval.tree)->isArray = false; (yyval.tree)->isStatic = false;}
#line 1569 "parser.tab.c"
    break;

  case 32: /* parmId: ID '[' ']'  */
#line 183 "parser.y"
                                             { (yyval.tree) = newDeclNode(DeclKind::ParamK, ExpType::UndefinedType, (yyvsp[-2].tinfo)); 
                                               (yyval.tree)->isArray = true; (yyval.tree)->isStatic = false;}
#line 1576 "parser.tab.c"
    break;

  case 33: /* stmt: matched  */
#line 187 "parser.y"
                                             { (yyval.tree) = (yyvsp[0].tree); printDebug("matched stmt"); }
#line 1582 "parser.tab.c"
    break;

  case 34: /* stmt: unmatched  */
#line 188 "parser.y"
                                             { (yyval.tree) = (yyvsp[0].tree); }
#line 1588 "parser.tab.c"
    break;

  case 35: /* matched: IF simpleExp THEN matched ELSE matched  */
#line 191 "parser.y"
                                                   { (yyval.tree) = newStmtNode(StmtKind::IfK, (yyvsp[-5].tinfo), (yyvsp[-4].tree), (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 1594 "parser.tab.c"
    break;

  case 36: /* matched: WHILE simpleExp DO matched  */
#line 192 "parser.y"
                                             { (yyval.tree) = newStmtNode(StmtKind::WhileK, (yyvsp[-3].tinfo), (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 1600 "parser.tab.c"
    break;

  case 37: /* matched: FOR ID '=' iterRange DO matched  */
#line 193 "parser.y"
                                             { (yyval.tree) = newStmtNode(StmtKind::ForK, (yyvsp[-5].tinfo), nullptr, (yyvsp[-2].tree), (yyvsp[0].tree)); 
                                               (yyval.tree)->child[0] = newDeclNode(DeclKind::VarK, ExpType::Integer, (yyvsp[-4].tinfo));}
#line 1607 "parser.tab.c"
    break;

  case 38: /* matched: expstmt  */
#line 195 "parser.y"
                                             { (yyval.tree) = (yyvsp[0].tree); printDebug("matched exp"); }
#line 1613 "parser.tab.c"
    break;

  case 39: /* matched: compoundstmt  */
#line 196 "parser.y"
                                             { (yyval.tree) = (yyvsp[0].tree); }
#line 1619 "parser.tab.c"
    break;

  case 40: /* matched: returnstmt  */
#line 197 "parser.y"
                                             { (yyval.tree) = (yyvsp[0].tree); }
#line 1625 "parser.tab.c"
    break;

  case 41: /* matched: breakstmt  */
#line 198 "parser.y"
                                             { (yyval.tree) = (yyvsp[0].tree); }
#line 1631 "parser.tab.c"
    break;

  case 42: /* iterRange: simpleExp TO simpleExp  */
#line 201 "parser.y"
                                             {  (yyval.tree) = newStmtNode(StmtKind::RangeK, (yyvsp[-1].tinfo), (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 1637 "parser.tab.c"
    break;

  case 43: /* iterRange: simpleExp TO simpleExp BY simpleExp  */
#line 202 "parser.y"
                                             {  (yyval.tree) = newStmtNode(StmtKind::RangeK, (yyvsp[-3].tinfo), (yyvsp[-4].tree), (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 1643 "parser.tab.c"
    break;

  case 44: /* unmatched: IF simpleExp THEN stmt  */
#line 205 "parser.y"
                                             { (yyval.tree) = newStmtNode(StmtKind::IfK, (yyvsp[-3].tinfo), (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 1649 "parser.tab.c"
    break;

  case 45: /* unmatched: IF simpleExp THEN matched ELSE unmatched  */
#line 206 "parser.y"
                                                { (yyval.tree) = newStmtNode(StmtKind::IfK, (yyvsp[-5].tinfo), (yyvsp[-4].tree), (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 1655 "parser.tab.c"
    break;

  case 46: /* unmatched: WHILE simpleExp DO unmatched  */
#line 207 "parser.y"
                                             { (yyval.tree) = newStmtNode(StmtKind::WhileK, (yyvsp[-3].tinfo), (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 1661 "parser.tab.c"
    break;

  case 47: /* unmatched: FOR ID '=' iterRange DO unmatched  */
#line 208 "parser.y"
                                             { (yyval.tree) = newStmtNode(StmtKind::ForK, (yyvsp[-5].tinfo), nullptr, (yyvsp[-2].tree), (yyvsp[0].tree)); 
                                               (yyval.tree)->child[0] = newDeclNode(DeclKind::VarK, ExpType::Integer, (yyvsp[-4].tinfo));}
#line 1668 "parser.tab.c"
    break;

  case 48: /* expstmt: exp ';'  */
#line 212 "parser.y"
                                             { (yyval.tree) = (yyvsp[-1].tree); printDebug("expstmt"); }
#line 1674 "parser.tab.c"
    break;

  case 49: /* expstmt: ';'  */
#line 213 "parser.y"
                                             { (yyval.tree) = nullptr; }
#line 1680 "parser.tab.c"
    break;

  case 50: /* compoundstmt: '{' localDecls stmtList '}'  */
#line 216 "parser.y"
                                             { (yyval.tree) = newStmtNode(StmtKind::CompoundK, (yyvsp[-3].tinfo), (yyvsp[-2].tree), (yyvsp[-1].tree)); printDebug("compound stmt"); }
#line 1686 "parser.tab.c"
    break;

  case 51: /* compoundstmt: compoundstmt ';'  */
#line 217 "parser.y"
                                             { (yyval.tree) = (yyvsp[-1].tree); }
#line 1692 "parser.tab.c"
    break;

  case 52: /* localDecls: localDecls scopedVarDecl  */
#line 221 "parser.y"
                                             { (yyval.tree) = addSibling((yyvsp[-1].tree), (yyvsp[0].tree));}
#line 1698 "parser.tab.c"
    break;

  case 53: /* localDecls: %empty  */
#line 222 "parser.y"
                                             { (yyval.tree) = nullptr;}
#line 1704 "parser.tab.c"
    break;

  case 54: /* stmtList: stmtList stmt  */
#line 225 "parser.y"
                                             { (yyval.tree) = addSibling((yyvsp[-1].tree), (yyvsp[0].tree)); printDebug("stmtList"); }
#line 1710 "parser.tab.c"
    break;

  case 55: /* stmtList: %empty  */
#line 226 "parser.y"
                                             { (yyval.tree) = nullptr;}
#line 1716 "parser.tab.c"
    break;

  case 56: /* returnstmt: RETURN ';'  */
#line 229 "parser.y"
                                             { (yyval.tree) = newStmtNode(StmtKind::ReturnK, (yyvsp[-1].tinfo));}
#line 1722 "parser.tab.c"
    break;

  case 57: /* returnstmt: RETURN exp ';'  */
#line 230 "parser.y"
                                             { (yyval.tree) = newStmtNode(StmtKind::ReturnK, (yyvsp[-2].tinfo), (yyvsp[-1].tree));}
#line 1728 "parser.tab.c"
    break;

  case 58: /* breakstmt: BREAK ';'  */
#line 233 "parser.y"
                                             { (yyval.tree) = newStmtNode(StmtKind::BreakK, (yyvsp[-1].tinfo));}
#line 1734 "parser.tab.c"
    break;

  case 59: /* exp: mutable assignop exp  */
#line 236 "parser.y"
                                             { (yyval.tree) = newExpNode(ExpKind::AssignK, (yyvsp[-1].tinfo), (yyvsp[-2].tree), (yyvsp[0].tree)); (yyval.tree)->isAssigned = true; printDebug("mutable"); }
#line 1740 "parser.tab.c"
    break;

  case 60: /* exp: mutable INC  */
#line 237 "parser.y"
                                             { (yyval.tree) = newExpNode(ExpKind::AssignK, (yyvsp[0].tinfo), (yyvsp[-1].tree));}
#line 1746 "parser.tab.c"
    break;

  case 61: /* exp: mutable DEC  */
#line 238 "parser.y"
                                             { (yyval.tree) = newExpNode(ExpKind::AssignK, (yyvsp[0].tinfo), (yyvsp[-1].tree));}
#line 1752 "parser.tab.c"
    break;

  case 62: /* exp: simpleExp  */
#line 239 "parser.y"
                                             { (yyval.tree) = (yyvsp[0].tree); printDebug("simpleExp"); }
#line 1758 "parser.tab.c"
    break;

  case 63: /* exp: mutable assignop ERROR  */
#line 240 "parser.y"
                                             { (yyval.tree) = newExpNode(ExpKind::AssignK, (yyvsp[-1].tinfo), (yyvsp[-2].tree)); yyerror("error here is a test"); printDebug("mutable error"); }
#line 1764 "parser.tab.c"
    break;

  case 64: /* assignop: '='  */
#line 243 "parser.y"
                                             { (yyval.tinfo) = (yyvsp[0].tinfo); }
#line 1770 "parser.tab.c"
    break;

  case 65: /* assignop: ADDASS  */
#line 244 "parser.y"
                                             { (yyval.tinfo) = (yyvsp[0].tinfo); }
#line 1776 "parser.tab.c"
    break;

  case 66: /* assignop: SUBASS  */
#line 245 "parser.y"
                                             { (yyval.tinfo) = (yyvsp[0].tinfo); }
#line 1782 "parser.tab.c"
    break;

  case 67: /* assignop: MULASS  */
#line 246 "parser.y"
                                             { (yyval.tinfo) = (yyvsp[0].tinfo); }
#line 1788 "parser.tab.c"
    break;

  case 68: /* assignop: DIVASS  */
#line 247 "parser.y"
                                             { (yyval.tinfo) = (yyvsp[0].tinfo); }
#line 1794 "parser.tab.c"
    break;

  case 69: /* simpleExp: simpleExp OR andExp  */
#line 250 "parser.y"
                                             { (yyval.tree) = newExpNode(ExpKind::OpK, (yyvsp[-1].tinfo), (yyvsp[-2].tree), (yyvsp[0].tree)); printDebug("simpleexp new node"); }
#line 1800 "parser.tab.c"
    break;

  case 70: /* simpleExp: andExp  */
#line 251 "parser.y"
                                             { (yyval.tree) = (yyvsp[0].tree); printDebug("simpleexp and"); }
#line 1806 "parser.tab.c"
    break;

  case 71: /* andExp: andExp AND unaryRelExp  */
#line 254 "parser.y"
                                             { (yyval.tree) = newExpNode(ExpKind::OpK, (yyvsp[-1].tinfo), (yyvsp[-2].tree), (yyvsp[0].tree)); printDebug("and op"); }
#line 1812 "parser.tab.c"
    break;

  case 72: /* andExp: unaryRelExp  */
#line 255 "parser.y"
                                             { (yyval.tree) = (yyvsp[0].tree); printDebug("and unary"); }
#line 1818 "parser.tab.c"
    break;

  case 73: /* unaryRelExp: NOT unaryRelExp  */
#line 258 "parser.y"
                                             { (yyval.tree) = newExpNode(ExpKind::OpK, (yyvsp[-1].tinfo), (yyvsp[0].tree)); printDebug("not unary exp"); }
#line 1824 "parser.tab.c"
    break;

  case 74: /* unaryRelExp: relExp  */
#line 259 "parser.y"
                                             { (yyval.tree) = (yyvsp[0].tree); printDebug("rel exp"); }
#line 1830 "parser.tab.c"
    break;

  case 75: /* relExp: minmaxExp relop minmaxExp  */
#line 262 "parser.y"
                                             { (yyval.tree) = newExpNode(ExpKind::OpK, (yyvsp[-1].tinfo), (yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1836 "parser.tab.c"
    break;

  case 76: /* relExp: minmaxExp  */
#line 263 "parser.y"
                                             { (yyval.tree) = (yyvsp[0].tree); printDebug("minmax exp"); }
#line 1842 "parser.tab.c"
    break;

  case 77: /* relop: LEQ  */
#line 266 "parser.y"
                                             { (yyval.tinfo) = (yyvsp[0].tinfo);}
#line 1848 "parser.tab.c"
    break;

  case 78: /* relop: '<'  */
#line 267 "parser.y"
                                             { (yyval.tinfo) = (yyvsp[0].tinfo);}
#line 1854 "parser.tab.c"
    break;

  case 79: /* relop: '>'  */
#line 268 "parser.y"
                                             { (yyval.tinfo) = (yyvsp[0].tinfo);}
#line 1860 "parser.tab.c"
    break;

  case 80: /* relop: GEQ  */
#line 269 "parser.y"
                                             { (yyval.tinfo) = (yyvsp[0].tinfo);}
#line 1866 "parser.tab.c"
    break;

  case 81: /* relop: EQ  */
#line 270 "parser.y"
                                             { (yyval.tinfo) = (yyvsp[0].tinfo);}
#line 1872 "parser.tab.c"
    break;

  case 82: /* relop: NEQ  */
#line 271 "parser.y"
                                             { (yyval.tinfo) = (yyvsp[0].tinfo);}
#line 1878 "parser.tab.c"
    break;

  case 83: /* minmaxExp: minmaxExp minmaxop sumExp  */
#line 274 "parser.y"
                                             { (yyval.tree) = newExpNode(ExpKind::OpK, (yyvsp[-1].tinfo), (yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1884 "parser.tab.c"
    break;

  case 84: /* minmaxExp: sumExp  */
#line 275 "parser.y"
                                             { (yyval.tree) = (yyvsp[0].tree); printDebug("sum exp"); }
#line 1890 "parser.tab.c"
    break;

  case 85: /* minmaxop: MAX  */
#line 278 "parser.y"
                                             { (yyval.tinfo) = (yyvsp[0].tinfo);}
#line 1896 "parser.tab.c"
    break;

  case 86: /* minmaxop: MIN  */
#line 279 "parser.y"
                                             { (yyval.tinfo) = (yyvsp[0].tinfo);}
#line 1902 "parser.tab.c"
    break;

  case 87: /* sumExp: sumExp sumop mulExp  */
#line 282 "parser.y"
                                             { (yyval.tree) = newExpNode(ExpKind::OpK, (yyvsp[-1].tinfo), (yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1908 "parser.tab.c"
    break;

  case 88: /* sumExp: mulExp  */
#line 283 "parser.y"
                                             { (yyval.tree) = (yyvsp[0].tree); printDebug("muloexp"); }
#line 1914 "parser.tab.c"
    break;

  case 89: /* sumop: '+'  */
#line 286 "parser.y"
                                             { (yyval.tinfo) = (yyvsp[0].tinfo);}
#line 1920 "parser.tab.c"
    break;

  case 90: /* sumop: '-'  */
#line 287 "parser.y"
                                             { (yyval.tinfo) = (yyvsp[0].tinfo);}
#line 1926 "parser.tab.c"
    break;

  case 91: /* mulExp: mulExp mulop unaryExp  */
#line 290 "parser.y"
                                             { (yyval.tree) = newExpNode(ExpKind::OpK, (yyvsp[-1].tinfo), (yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1932 "parser.tab.c"
    break;

  case 92: /* mulExp: unaryExp  */
#line 291 "parser.y"
                                             { (yyval.tree) = (yyvsp[0].tree); printDebug("unaryexp"); }
#line 1938 "parser.tab.c"
    break;

  case 93: /* mulop: '*'  */
#line 294 "parser.y"
                                             { (yyval.tinfo) = (yyvsp[0].tinfo);}
#line 1944 "parser.tab.c"
    break;

  case 94: /* mulop: '/'  */
#line 295 "parser.y"
                                             { (yyval.tinfo) = (yyvsp[0].tinfo);}
#line 1950 "parser.tab.c"
    break;

  case 95: /* mulop: '%'  */
#line 296 "parser.y"
                                             { (yyval.tinfo) = (yyvsp[0].tinfo);}
#line 1956 "parser.tab.c"
    break;

  case 96: /* unaryExp: unaryop unaryExp  */
#line 299 "parser.y"
                                             { (yyval.tree) = newExpNode(ExpKind::OpK, (yyvsp[-1].tinfo), (yyvsp[0].tree));}
#line 1962 "parser.tab.c"
    break;

  case 97: /* unaryExp: factor  */
#line 300 "parser.y"
                                             { (yyval.tree) = (yyvsp[0].tree); printDebug("factor"); }
#line 1968 "parser.tab.c"
    break;

  case 98: /* unaryop: '-'  */
#line 303 "parser.y"
                                             { (yyval.tinfo) = (yyvsp[0].tinfo); (yyval.tinfo)->svalue = (char *)"chsign"; }
#line 1974 "parser.tab.c"
    break;

  case 99: /* unaryop: '*'  */
#line 304 "parser.y"
                                             { (yyval.tinfo) = (yyvsp[0].tinfo); (yyval.tinfo)->svalue = (char *)"sizeof"; }
#line 1980 "parser.tab.c"
    break;

  case 100: /* unaryop: '?'  */
#line 305 "parser.y"
                                             { (yyval.tinfo) = (yyvsp[0].tinfo);}
#line 1986 "parser.tab.c"
    break;

  case 101: /* factor: immutable  */
#line 308 "parser.y"
                                             { (yyval.tree) = (yyvsp[0].tree); printDebug("immutable"); }
#line 1992 "parser.tab.c"
    break;

  case 102: /* factor: mutable  */
#line 309 "parser.y"
                                             { (yyval.tree) = (yyvsp[0].tree); printDebug("mutable"); }
#line 1998 "parser.tab.c"
    break;

  case 103: /* mutable: ID  */
#line 312 "parser.y"
                                             { (yyval.tree) = newExpNode(ExpKind::IdK, (yyvsp[0].tinfo)); (yyval.tree)->isArray = false;}
#line 2004 "parser.tab.c"
    break;

  case 104: /* mutable: ID '[' exp ']'  */
#line 313 "parser.y"
                                             { (yyval.tree) = newExpNode(ExpKind::OpK, (yyvsp[-2].tinfo), nullptr, (yyvsp[-1].tree)); (yyval.tree)->child[0] = newExpNode(ExpKind::IdK, (yyvsp[-3].tinfo));}
#line 2010 "parser.tab.c"
    break;

  case 105: /* immutable: '(' exp ')'  */
#line 316 "parser.y"
                                             { (yyval.tree) = (yyvsp[-1].tree); printDebug("immutable exp"); }
#line 2016 "parser.tab.c"
    break;

  case 106: /* immutable: call  */
#line 317 "parser.y"
                                             { (yyval.tree) = (yyvsp[0].tree); printDebug("immutable call"); }
#line 2022 "parser.tab.c"
    break;

  case 107: /* immutable: constant  */
#line 318 "parser.y"
                                             { (yyval.tree) = (yyvsp[0].tree); printDebug("constant"); }
#line 2028 "parser.tab.c"
    break;

  case 108: /* call: ID '(' args ')'  */
#line 321 "parser.y"
                                             { (yyval.tree) = newExpNode(ExpKind::CallK, (yyvsp[-3].tinfo), (yyvsp[-1].tree)); printDebug("call ID"); }
#line 2034 "parser.tab.c"
    break;

  case 109: /* args: argList  */
#line 324 "parser.y"
                                             { (yyval.tree) = (yyvsp[0].tree); printDebug("arglist"); }
#line 2040 "parser.tab.c"
    break;

  case 110: /* args: %empty  */
#line 325 "parser.y"
                                             { (yyval.tree) = nullptr;}
#line 2046 "parser.tab.c"
    break;

  case 111: /* argList: argList ',' exp  */
#line 328 "parser.y"
                                             { (yyval.tree) = addSibling((yyvsp[-2].tree), (yyvsp[0].tree)); printDebug("arglist , exp"); }
#line 2052 "parser.tab.c"
    break;

  case 112: /* argList: exp  */
#line 329 "parser.y"
                                             { (yyval.tree) = (yyvsp[0].tree); printDebug("argList exp"); }
#line 2058 "parser.tab.c"
    break;

  case 113: /* constant: NUMCONST  */
#line 332 "parser.y"
                                             { (yyval.tree) = newExpNode(ExpKind::ConstantK, (yyvsp[0].tinfo)); 
                                               (yyval.tree)->type = ExpType::Integer; 
                                               (yyval.tree)->isArray = false;
                                               (yyval.tree)->size = 1;               // not needed for asn3, but asn4
                                               printDebug("numconst"); }
#line 2068 "parser.tab.c"
    break;

  case 114: /* constant: CHARCONST  */
#line 337 "parser.y"
                                             { (yyval.tree) = newExpNode(ExpKind::ConstantK, (yyvsp[0].tinfo)); 
                                               (yyval.tree)->type = ExpType::Char; 
                                               (yyval.tree)->isArray = false;
                                               (yyval.tree)->attr.cvalue = (yyvsp[0].tinfo)->cvalue;  // not needed for asn3, but asn4
                                               printDebug("charconst"); }
#line 2078 "parser.tab.c"
    break;

  case 115: /* constant: STRINGCONST  */
#line 342 "parser.y"
                                             { (yyval.tree) = newExpNode(ExpKind::ConstantK, (yyvsp[0].tinfo)); 
                                               (yyval.tree)->type = ExpType::Char; 
                                               (yyval.tree)->isArray = true; 
                                               (yyval.tree)->size = strlen((yyvsp[0].tinfo)->svalue)-1;
                                               printDebug("stringconst"); }
#line 2088 "parser.tab.c"
    break;

  case 116: /* constant: BOOLCONST  */
#line 347 "parser.y"
                                             { (yyval.tree) = newExpNode(ExpKind::ConstantK, (yyvsp[0].tinfo)); 
                                               (yyval.tree)->type = ExpType::Boolean; 
                                               (yyval.tree)->isArray = false;
                                               printDebug("boolconst"); }
#line 2097 "parser.tab.c"
    break;


#line 2101 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 354 "parser.y"

// void yyerror (const char *msg)
// { 
//    // cout << "SYNTAX ERROR(" << yylval.tinfo->linenum << "): " << msg << endl;
//    cout << "Error: " <<  msg << endl;
// }

/*
char *largerTokens[LASTTERM+1]; // used in the utils.cpp file printing routines
// create a mapping from token class enum to a printable name in a
// way that makes it easy to keep the mapping straight.
void initTokenStrings()
{
   largerTokens[ADDASS] = (char *)"+=";
   largerTokens[AND] = (char *)"and";
   largerTokens[BOOL] = (char *)"bool";
   largerTokens[BOOLCONST] = (char *)"boolconst";
   largerTokens[BREAK] = (char *)"break";
   largerTokens[BY] = (char *)"by";
   largerTokens[CHAR] = (char *)"char";
   largerTokens[CHARCONST] = (char *)"charconst";
   largerTokens[CHSIGN] = (char *)"chsign";
   largerTokens[DEC] = (char *)"--";
   largerTokens[DIVASS] = (char *)"/=";
   largerTokens[DO] = (char *)"do";
   largerTokens[ELSE] = (char *)"else";
   largerTokens[EQ] = (char *)"==";
   largerTokens[FOR] = (char *)"for";
   largerTokens[GEQ] = (char *)">=";
   largerTokens[ID] = (char *)"id";
   largerTokens[IF] = (char *)"if";
   largerTokens[INC] = (char *)"++";
   largerTokens[INT] = (char *)"int";
   largerTokens[LEQ] = (char *)"<=";
   largerTokens[MAX] = (char *)":>:";
   largerTokens[MIN] = (char *)":<:";
   largerTokens[MULASS] = (char *)"*=";
   largerTokens[NEQ] = (char *)"!=";
   largerTokens[NOT] = (char *)"not";
   largerTokens[NUMCONST] = (char *)"numconst";
   largerTokens[OR] = (char *)"or";
   largerTokens[RETURN] = (char *)"return";
   largerTokens[SIZEOF] = (char *)"sizeof";
   largerTokens[STATIC] = (char *)"static";
   largerTokens[STRINGCONST] = (char *)"stringconst";
   largerTokens[SUBASS] = (char *)"-=";
   largerTokens[THEN] = (char *)"then";
   largerTokens[TO] = (char *)"to";
   largerTokens[WHILE] = (char *)"while";
   largerTokens[LASTTERM] = (char *)"lastterm";
}
*/

int main(int argc, char **argv) 
{
   initErrorProcessing();
   yylval.tinfo = (TokenData*)malloc(sizeof(TokenData));
   yylval.tree = (TreeNode*)malloc(sizeof(TreeNode));
   yylval.tinfo->linenum = 1;

   int index;
   char *file = NULL;
   bool dotAST = false;             // make dot file of AST
   extern FILE *yyin;

   int ch;
  // initTokenStrings();

   while ((ch = getopt(argc, argv, "d")) != -1) 
   {
      switch (ch) 
      {
         case 'd':
                 dotAST = true;
                 break;
         case '?':
         default:
                 //usage();
               ;
      }
   }

   if ( optind == argc ) yyparse();
   for (index = optind; index < argc; index++)
   {
      yyin = fopen (argv[index], "r");
      yyparse();
      fclose (yyin);
   }
   bool debugSymTab = false;
   static int globalOffset = 0;

   SymbolTable *symtab;
   symtab = new SymbolTable();
   symtab->debug(debugSymTab);
   syntaxTree = semanticAnalysis(syntaxTree, true, false, symtab, globalOffset);
   treeTraverse(syntaxTree, symtab);


   if (numErrors==0) 
   {
      printTree(stdout, syntaxTree, true, true);
      if(dotAST) {
         //printDotTree(stdout, syntaxTree, false, false);
      }
   }
   else 
   {
      printf("-----------\n");
      printf("Errors: %d\n", numErrors);
      printf("-----------\n");
   }

   printf("Number of warnings: %d\n", numWarnings);
   printf("Number of errors: %d\n", numErrors);
   return 0;
}

