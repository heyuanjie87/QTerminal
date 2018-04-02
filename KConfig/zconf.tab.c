/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */


/*
 * Copyright (C) 2002 Roman Zippel <zippel@linux-m68k.org>
 * Released under the terms of the GNU GPL v2.0.
 */

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "lkc.h"

#define printd(mask, fmt...) if (cdebug & (mask)) zconfoutmsg(kcm, fmt)
#define ZCONFFILE zconf_curname(kcm->yyscanner), zconf_lineno(kcm->yyscanner)

#define YYLEX_PARAM    (kcm->yyscanner)

#define PRINTD      0x0001
#define DEBUG_PARSE 0x0002
#define yylex zconflex

int cdebug = PRINTD;

static void zconfprint(kcmenu_t *kcm, const char *err, ...);
static void zconf_error(kcmenu_t *kcm, const char *err, ...);
static bool zconf_endtoken(const struct kconf_id *id, int starttoken, int endtoken, kcmenu_t *kcm);
static void zconfoutmsg(kcmenu_t *kcm, const char *fmt, ...);

#define yyerror zconf_error

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_MAINMENU = 258,
     T_MENU = 259,
     T_ENDMENU = 260,
     T_SOURCE = 261,
     T_CHOICE = 262,
     T_ENDCHOICE = 263,
     T_COMMENT = 264,
     T_CONFIG = 265,
     T_MENUCONFIG = 266,
     T_HELP = 267,
     T_HELPTEXT = 268,
     T_IF = 269,
     T_ENDIF = 270,
     T_DEPENDS = 271,
     T_OPTIONAL = 272,
     T_PROMPT = 273,
     T_TYPE = 274,
     T_DEFAULT = 275,
     T_SELECT = 276,
     T_IMPLY = 277,
     T_RANGE = 278,
     T_VISIBLE = 279,
     T_OPTION = 280,
     T_ON = 281,
     T_WORD = 282,
     T_WORD_QUOTE = 283,
     T_UNEQUAL = 284,
     T_LESS = 285,
     T_LESS_EQUAL = 286,
     T_GREATER = 287,
     T_GREATER_EQUAL = 288,
     T_CLOSE_PAREN = 289,
     T_OPEN_PAREN = 290,
     T_EOL = 291,
     T_OR = 292,
     T_AND = 293,
     T_EQUAL = 294,
     T_NOT = 295
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{


    char *string;
    struct file *file;
    struct symbol *symbol;
    struct expr *expr;
    struct menu *menu;
    const struct kconf_id *id;



} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (kcmenu_t *kcm);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* Copy the second part of user declarations.  */


/* Include zconf.hash.c here so it can see the token constants. */
#include "zconf.hash.c"



#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   301

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  50
/* YYNRULES -- Number of rules.  */
#define YYNRULES  124
/* YYNRULES -- Number of states.  */
#define YYNSTATES  204

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   295

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     8,    11,    13,    14,    17,    20,
      23,    26,    31,    36,    40,    42,    44,    46,    48,    50,
      52,    54,    56,    58,    60,    62,    64,    66,    68,    70,
      74,    77,    81,    84,    88,    91,    92,    95,    98,   101,
     104,   107,   110,   114,   119,   124,   129,   134,   140,   144,
     145,   149,   150,   153,   157,   160,   162,   166,   167,   170,
     173,   176,   179,   182,   187,   191,   194,   199,   200,   203,
     207,   209,   213,   214,   217,   220,   223,   227,   231,   235,
     237,   241,   242,   245,   248,   251,   255,   259,   262,   265,
     268,   269,   272,   275,   278,   283,   284,   287,   290,   293,
     294,   297,   299,   301,   304,   307,   310,   312,   315,   316,
     319,   321,   325,   329,   333,   337,   341,   345,   349,   352,
     356,   360,   362,   364,   365
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      42,     0,    -1,    86,    43,    -1,    43,    -1,    68,    44,
      -1,    44,    -1,    -1,    44,    46,    -1,    44,    60,    -1,
      44,    72,    -1,    44,    85,    -1,    44,    27,     1,    36,
      -1,    44,    45,     1,    36,    -1,    44,     1,    36,    -1,
      16,    -1,    18,    -1,    19,    -1,    21,    -1,    22,    -1,
      17,    -1,    23,    -1,    20,    -1,    24,    -1,    36,    -1,
      66,    -1,    76,    -1,    49,    -1,    51,    -1,    74,    -1,
      27,     1,    36,    -1,     1,    36,    -1,    10,    27,    36,
      -1,    48,    52,    -1,    11,    27,    36,    -1,    50,    52,
      -1,    -1,    52,    53,    -1,    52,    54,    -1,    52,    80,
      -1,    52,    78,    -1,    52,    47,    -1,    52,    36,    -1,
      19,    83,    36,    -1,    18,    84,    87,    36,    -1,    20,
      88,    87,    36,    -1,    21,    27,    87,    36,    -1,    22,
      27,    87,    36,    -1,    23,    89,    89,    87,    36,    -1,
      25,    55,    36,    -1,    -1,    55,    27,    56,    -1,    -1,
      39,    84,    -1,     7,    90,    36,    -1,    57,    61,    -1,
      85,    -1,    58,    63,    59,    -1,    -1,    61,    62,    -1,
      61,    80,    -1,    61,    78,    -1,    61,    36,    -1,    61,
      47,    -1,    18,    84,    87,    36,    -1,    19,    83,    36,
      -1,    17,    36,    -1,    20,    27,    87,    36,    -1,    -1,
      63,    46,    -1,    14,    88,    86,    -1,    85,    -1,    64,
      67,    65,    -1,    -1,    67,    46,    -1,    67,    72,    -1,
      67,    60,    -1,     3,    84,    86,    -1,     4,    84,    36,
      -1,    69,    81,    79,    -1,    85,    -1,    70,    73,    71,
      -1,    -1,    73,    46,    -1,    73,    72,    -1,    73,    60,
      -1,     6,    84,    36,    -1,     9,    84,    36,    -1,    75,
      79,    -1,    12,    36,    -1,    77,    13,    -1,    -1,    79,
      80,    -1,    79,    36,    -1,    79,    47,    -1,    16,    26,
      88,    36,    -1,    -1,    81,    82,    -1,    81,    36,    -1,
      24,    87,    -1,    -1,    84,    87,    -1,    27,    -1,    28,
      -1,     5,    36,    -1,     8,    36,    -1,    15,    36,    -1,
      36,    -1,    86,    36,    -1,    -1,    14,    88,    -1,    89,
      -1,    89,    30,    89,    -1,    89,    31,    89,    -1,    89,
      32,    89,    -1,    89,    33,    89,    -1,    89,    39,    89,
      -1,    89,    29,    89,    -1,    35,    88,    34,    -1,    40,
      88,    -1,    88,    37,    88,    -1,    88,    38,    88,    -1,
      27,    -1,    28,    -1,    -1,    27,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   115,   115,   115,   117,   117,   119,   121,   122,   123,
     124,   125,   126,   130,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   138,   139,   140,   141,   142,   143,   147,
     148,   154,   162,   168,   176,   186,   188,   189,   190,   191,
     192,   193,   196,   204,   210,   220,   226,   232,   238,   241,
     243,   254,   255,   260,   269,   274,   282,   285,   287,   288,
     289,   290,   291,   294,   300,   311,   317,   327,   329,   334,
     342,   350,   353,   355,   356,   357,   362,   369,   376,   381,
     389,   392,   394,   395,   396,   399,   408,   415,   422,   428,
     435,   437,   438,   439,   442,   450,   452,   453,   456,   463,
     465,   470,   471,   474,   475,   476,   480,   481,   484,   485,
     488,   489,   490,   491,   492,   493,   494,   495,   496,   497,
     498,   501,   502,   505,   506
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_MAINMENU", "T_MENU", "T_ENDMENU",
  "T_SOURCE", "T_CHOICE", "T_ENDCHOICE", "T_COMMENT", "T_CONFIG",
  "T_MENUCONFIG", "T_HELP", "T_HELPTEXT", "T_IF", "T_ENDIF", "T_DEPENDS",
  "T_OPTIONAL", "T_PROMPT", "T_TYPE", "T_DEFAULT", "T_SELECT", "T_IMPLY",
  "T_RANGE", "T_VISIBLE", "T_OPTION", "T_ON", "T_WORD", "T_WORD_QUOTE",
  "T_UNEQUAL", "T_LESS", "T_LESS_EQUAL", "T_GREATER", "T_GREATER_EQUAL",
  "T_CLOSE_PAREN", "T_OPEN_PAREN", "T_EOL", "T_OR", "T_AND", "T_EQUAL",
  "T_NOT", "$accept", "input", "start", "stmt_list", "option_name",
  "common_stmt", "option_error", "config_entry_start", "config_stmt",
  "menuconfig_entry_start", "menuconfig_stmt", "config_option_list",
  "config_option", "symbol_option", "symbol_option_list",
  "symbol_option_arg", "choice", "choice_entry", "choice_end",
  "choice_stmt", "choice_option_list", "choice_option", "choice_block",
  "if_entry", "if_end", "if_stmt", "if_block", "mainmenu_stmt", "menu",
  "menu_entry", "menu_end", "menu_stmt", "menu_block", "source_stmt",
  "comment", "comment_stmt", "help_start", "help", "depends_list",
  "depends", "visibility_list", "visible", "prompt_stmt_opt", "prompt",
  "end", "nl", "if_expr", "expr", "symbol", "word_opt", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    41,    42,    42,    43,    43,    44,    44,    44,    44,
      44,    44,    44,    44,    45,    45,    45,    45,    45,    45,
      45,    45,    45,    46,    46,    46,    46,    46,    46,    47,
      47,    48,    49,    50,    51,    52,    52,    52,    52,    52,
      52,    52,    53,    53,    53,    53,    53,    53,    54,    55,
      55,    56,    56,    57,    58,    59,    60,    61,    61,    61,
      61,    61,    61,    62,    62,    62,    62,    63,    63,    64,
      65,    66,    67,    67,    67,    67,    68,    69,    70,    71,
      72,    73,    73,    73,    73,    74,    75,    76,    77,    78,
      79,    79,    79,    79,    80,    81,    81,    81,    82,    83,
      83,    84,    84,    85,    85,    85,    86,    86,    87,    87,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    89,    89,    90,    90
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     2,     1,     0,     2,     2,     2,
       2,     4,     4,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     3,     2,     3,     2,     0,     2,     2,     2,     2,
       2,     2,     3,     4,     4,     4,     4,     5,     3,     0,
       3,     0,     2,     3,     2,     1,     3,     0,     2,     2,
       2,     2,     2,     4,     3,     2,     4,     0,     2,     3,
       1,     3,     0,     2,     2,     2,     3,     3,     3,     1,
       3,     0,     2,     2,     2,     3,     3,     2,     2,     2,
       0,     2,     2,     2,     4,     0,     2,     2,     2,     0,
       2,     1,     1,     2,     2,     2,     1,     2,     0,     2,
       1,     3,     3,     3,     3,     3,     3,     3,     2,     3,
       3,     1,     1,     0,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       6,     0,   106,     0,     3,     0,     6,     6,   101,   102,
       0,     1,     0,     0,     0,     0,   123,     0,     0,     0,
       0,     0,     0,    14,    19,    15,    16,    21,    17,    18,
      20,    22,     0,    23,     0,     7,    35,    26,    35,    27,
      57,    67,     8,    72,    24,    95,    81,     9,    28,    90,
      25,    10,     0,   107,     2,    76,    13,     0,   103,     0,
     124,     0,   104,     0,     0,     0,   121,   122,     0,     0,
       0,   110,   105,     0,     0,     0,     0,     0,     0,     0,
      90,     0,     0,    77,    85,    53,    86,    31,    33,     0,
     118,     0,     0,    69,     0,     0,     0,     0,     0,     0,
      11,    12,     0,     0,     0,     0,    99,     0,     0,     0,
       0,    49,     0,    41,    40,    36,    37,     0,    39,    38,
       0,     0,    99,     0,    61,    62,    58,    60,    59,    68,
      56,    55,    73,    75,    71,    74,    70,   108,    97,     0,
      96,    82,    84,    80,    83,    79,    92,    93,    91,   117,
     119,   120,   116,   111,   112,   113,   114,   115,    30,    88,
       0,   108,     0,   108,   108,   108,   108,     0,     0,     0,
      89,    65,   108,     0,   108,     0,    98,     0,     0,    42,
     100,     0,     0,     0,   108,    51,    48,    29,     0,    64,
       0,   109,    94,    43,    44,    45,    46,     0,     0,    50,
      63,    66,    47,    52
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     5,    34,    35,   114,    36,    37,    38,
      39,    75,   115,   116,   168,   199,    40,    41,   130,    42,
      77,   126,    78,    43,   134,    44,    79,     6,    45,    46,
     143,    47,    81,    48,    49,    50,   117,   118,    82,   119,
      80,   140,   162,   163,    51,     7,   176,    70,    71,    61
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -92
static const yytype_int16 yypact[] =
{
      17,    41,   -92,    15,   -92,   150,   -92,    19,   -92,   -92,
     -13,   -92,    28,    41,    38,    41,    50,    47,    41,    79,
      82,    44,    76,   -92,   -92,   -92,   -92,   -92,   -92,   -92,
     -92,   -92,   118,   -92,   129,   -92,   -92,   -92,   -92,   -92,
     -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,
     -92,   -92,   184,   -92,   -92,   107,   -92,   111,   -92,   113,
     -92,   116,   -92,   139,   140,   151,   -92,   -92,    44,    44,
     142,   256,   -92,   160,   173,    27,   117,    80,    51,   255,
     -15,   255,   217,   -92,   -92,   -92,   -92,   -92,   -92,    -8,
     -92,    44,    44,   107,    87,    87,    87,    87,    87,    87,
     -92,   -92,   174,   176,   187,    41,    41,    44,   188,   189,
      87,   -92,   213,   -92,   -92,   -92,   -92,   206,   -92,   -92,
     193,    41,    41,   203,   -92,   -92,   -92,   -92,   -92,   -92,
     -92,   -92,   -92,   -92,   -92,   -92,   -92,   229,   -92,   241,
     -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,
     216,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,
      44,   229,   222,   229,    64,   229,   229,    87,    31,   231,
     -92,   -92,   229,   236,   229,    44,   -92,   145,   242,   -92,
     -92,   243,   244,   245,   229,   251,   -92,   -92,   247,   -92,
     257,   125,   -92,   -92,   -92,   -92,   -92,   260,    41,   -92,
     -92,   -92,   -92,   -92
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -92,   -92,   285,   291,   -92,    32,   -66,   -92,   -92,   -92,
     -92,   261,   -92,   -92,   -92,   -92,   -92,   -92,   -92,     1,
     -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,
     -92,    24,   -92,   -92,   -92,   -92,   -92,   221,   220,   -64,
     -92,   -92,   179,    -1,    67,     0,   110,   -67,   -91,   -92
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -88
static const yytype_int16 yytable[] =
{
      10,    89,    90,   152,   153,   154,   155,   156,   157,   137,
      55,   125,    57,   128,    59,    11,   147,    63,   148,   167,
       1,   138,     1,     2,   150,   151,   149,   -32,   102,    91,
      92,   -32,   -32,   -32,   -32,   -32,   -32,   -32,   -32,   103,
     164,   -32,   -32,   104,   -32,   105,   106,   107,   108,   109,
     110,   -32,   111,     2,   112,    53,    14,    15,   185,    17,
      18,    19,    20,   113,    56,    21,    22,   186,     8,     9,
      93,    66,    67,   147,    58,   148,   184,    60,   175,    68,
     133,   102,   142,    62,    69,   -54,   -54,    33,   -54,   -54,
     -54,   -54,   103,   177,   -54,   -54,   104,   120,   121,   122,
     123,    91,    92,   135,   161,   144,    64,   112,   191,    65,
     129,   132,    72,   141,    66,    67,   124,   -34,   102,    73,
     172,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   103,
      74,   -34,   -34,   104,   -34,   105,   106,   107,   108,   109,
     110,   -34,   111,    53,   112,   131,   136,    83,   145,    84,
      -5,    12,    85,   113,    13,    14,    15,    16,    17,    18,
      19,    20,    91,    92,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    86,    87,    32,     2,    91,
      92,   192,    91,    92,    -4,    12,    33,    88,    13,    14,
      15,    16,    17,    18,    19,    20,   100,   203,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,   101,
     158,    32,   159,   160,   169,   165,   166,   -87,   102,   170,
      33,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   171,
     174,   -87,   -87,   104,   -87,   -87,   -87,   -87,   -87,   -87,
     -87,   -87,   102,   175,   112,   -78,   -78,   -78,   -78,   -78,
     -78,   -78,   -78,   146,    92,   -78,   -78,   104,   179,    13,
      14,    15,    16,    17,    18,    19,    20,   187,   112,    21,
      22,   178,   189,   180,   181,   182,   183,   146,   193,   194,
     195,   196,   188,   200,   190,    94,    95,    96,    97,    98,
     198,    33,    54,   201,   197,    99,   202,    52,   127,    76,
     139,   173
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-92)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_uint8 yycheck[] =
{
       1,    68,    69,    94,    95,    96,    97,    98,    99,    24,
      10,    77,    13,    77,    15,     0,    82,    18,    82,   110,
       3,    36,     3,    36,    91,    92,    34,     0,     1,    37,
      38,     4,     5,     6,     7,     8,     9,    10,    11,    12,
     107,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    36,    27,    36,     5,     6,    27,     8,
       9,    10,    11,    36,    36,    14,    15,    36,    27,    28,
      70,    27,    28,   139,    36,   139,   167,    27,    14,    35,
      79,     1,    81,    36,    40,     5,     6,    36,     8,     9,
      10,    11,    12,   160,    14,    15,    16,    17,    18,    19,
      20,    37,    38,    79,   105,    81,    27,    27,   175,    27,
      78,    79,    36,    81,    27,    28,    36,     0,     1,     1,
     121,     4,     5,     6,     7,     8,     9,    10,    11,    12,
       1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    36,    27,    78,    79,    36,    81,    36,
       0,     1,    36,    36,     4,     5,     6,     7,     8,     9,
      10,    11,    37,    38,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    36,    36,    27,    36,    37,
      38,    36,    37,    38,     0,     1,    36,    36,     4,     5,
       6,     7,     8,     9,    10,    11,    36,   198,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    36,
      36,    27,    36,    26,     1,    27,    27,     0,     1,    13,
      36,     4,     5,     6,     7,     8,     9,    10,    11,    36,
      27,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,     1,    14,    27,     4,     5,     6,     7,     8,
       9,    10,    11,    36,    38,    14,    15,    16,    36,     4,
       5,     6,     7,     8,     9,    10,    11,    36,    27,    14,
      15,   161,    36,   163,   164,   165,   166,    36,    36,    36,
      36,    36,   172,    36,   174,    29,    30,    31,    32,    33,
      39,    36,     7,    36,   184,    39,    36,     6,    77,    38,
      80,   122
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    36,    42,    43,    44,    68,    86,    27,    28,
      84,     0,     1,     4,     5,     6,     7,     8,     9,    10,
      11,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    27,    36,    45,    46,    48,    49,    50,    51,
      57,    58,    60,    64,    66,    69,    70,    72,    74,    75,
      76,    85,    44,    36,    43,    86,    36,    84,    36,    84,
      27,    90,    36,    84,    27,    27,    27,    28,    35,    40,
      88,    89,    36,     1,     1,    52,    52,    61,    63,    67,
      81,    73,    79,    36,    36,    36,    36,    36,    36,    88,
      88,    37,    38,    86,    29,    30,    31,    32,    33,    39,
      36,    36,     1,    12,    16,    18,    19,    20,    21,    22,
      23,    25,    27,    36,    47,    53,    54,    77,    78,    80,
      17,    18,    19,    20,    36,    47,    62,    78,    80,    46,
      59,    85,    46,    60,    65,    72,    85,    24,    36,    79,
      82,    46,    60,    71,    72,    85,    36,    47,    80,    34,
      88,    88,    89,    89,    89,    89,    89,    89,    36,    36,
      26,    84,    83,    84,    88,    27,    27,    89,    55,     1,
      13,    36,    84,    83,    27,    14,    87,    88,    87,    36,
      87,    87,    87,    87,    89,    27,    36,    36,    87,    36,
      87,    88,    36,    36,    36,    36,    36,    87,    39,    56,
      36,    36,    36,    84
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      yyerror (kcm, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, kcm); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, kcmenu_t *kcm)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, kcm)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    kcmenu_t *kcm;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
  YYUSE (kcm);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, kcmenu_t *kcm)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, kcm)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    kcmenu_t *kcm;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, kcm);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, kcmenu_t *kcm)
#else
static void
yy_reduce_print (yyvsp, yyrule, kcm)
    YYSTYPE *yyvsp;
    int yyrule;
    kcmenu_t *kcm;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       , kcm);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, kcm); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, kcmenu_t *kcm)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, kcm)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    kcmenu_t *kcm;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (kcm);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {
      case 58: /* choice_entry */

        {
    zconfoutmsg(kcm, "%s:%d: missing end statement for this entry\n",
        ((*yyvaluep).menu)->file->name, ((*yyvaluep).menu)->lineno);
    if (kcm->current_menu == ((*yyvaluep).menu))
        menu_end_menu(kcm);
};

        break;
      case 64: /* if_entry */

        {
    zconfoutmsg(kcm, "%s:%d: missing end statement for this entry\n",
        ((*yyvaluep).menu)->file->name, ((*yyvaluep).menu)->lineno);
    if (kcm->current_menu == ((*yyvaluep).menu))
        menu_end_menu(kcm);
};

        break;
      case 70: /* menu_entry */

        {
    zconfoutmsg(kcm, "%s:%d: missing end statement for this entry\n",
        ((*yyvaluep).menu)->file->name, ((*yyvaluep).menu)->lineno);
    if (kcm->current_menu == ((*yyvaluep).menu))
        menu_end_menu(kcm);
};

        break;

      default:
        break;
    }
}




/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (kcmenu_t *kcm)
#else
int
yyparse (kcm)
    kcmenu_t *kcm;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;


#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
static YYSTYPE yyval_default;
# define YY_INITIAL_VALUE(Value) = Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 10:

    { zconf_error(kcm, "unexpected end statement"); }
    break;

  case 11:

    { zconf_error(kcm, "unknown statement \"%s\"", (yyvsp[(2) - (4)].string)); }
    break;

  case 12:

    {
    zconf_error(kcm, "unexpected option \"%s\"", kconf_id_strings + (yyvsp[(2) - (4)].id)->name);
}
    break;

  case 13:

    { zconf_error(kcm, "invalid statement"); }
    break;

  case 29:

    { zconf_error(kcm, "unknown option \"%s\"", (yyvsp[(1) - (3)].string)); }
    break;

  case 30:

    { zconf_error(kcm, "invalid option"); }
    break;

  case 31:

    {
    struct symbol *sym = sym_lookup((yyvsp[(2) - (3)].string), 0, kcm);
    sym->flags |= SYMBOL_OPTIONAL;
    menu_add_entry(sym, kcm);
    printd(DEBUG_PARSE, "%s:%d:config %s\n", ZCONFFILE, (yyvsp[(2) - (3)].string));
}
    break;

  case 32:

    {
    menu_end_entry();
    printd(DEBUG_PARSE, "%s:%d:endconfig\n", ZCONFFILE);
}
    break;

  case 33:

    {
    struct symbol *sym = sym_lookup((yyvsp[(2) - (3)].string), 0, kcm);
    sym->flags |= SYMBOL_OPTIONAL;
    menu_add_entry(sym, kcm);
    printd(DEBUG_PARSE, "%s:%d:menuconfig %s\n", ZCONFFILE, (yyvsp[(2) - (3)].string));
}
    break;

  case 34:

    {
    if (kcm->current_entry->prompt)
        kcm->current_entry->prompt->type = P_MENU;
    else
        zconfprint(kcm, "warning: menuconfig statement without prompt");
    menu_end_entry();
    printd(DEBUG_PARSE, "%s:%d:endconfig\n", ZCONFFILE);
}
    break;

  case 42:

    {
    menu_set_type((yyvsp[(1) - (3)].id)->stype, kcm);
    printd(DEBUG_PARSE, "%s:%d:type(%u)\n",
        ZCONFFILE,
        (yyvsp[(1) - (3)].id)->stype);
}
    break;

  case 43:

    {
    menu_add_prompt(P_PROMPT, (yyvsp[(2) - (4)].string), (yyvsp[(3) - (4)].expr), kcm);
    printd(DEBUG_PARSE, "%s:%d:prompt\n", ZCONFFILE);
}
    break;

  case 44:

    {
    menu_add_expr(P_DEFAULT, (yyvsp[(2) - (4)].expr), (yyvsp[(3) - (4)].expr), kcm);
    if ((yyvsp[(1) - (4)].id)->stype != S_UNKNOWN)
        menu_set_type((yyvsp[(1) - (4)].id)->stype, kcm);
    printd(DEBUG_PARSE, "%s:%d:default(%u)\n",
        ZCONFFILE,
        (yyvsp[(1) - (4)].id)->stype);
}
    break;

  case 45:

    {
    menu_add_symbol(P_SELECT, sym_lookup((yyvsp[(2) - (4)].string), 0, kcm), (yyvsp[(3) - (4)].expr), kcm);
    printd(DEBUG_PARSE, "%s:%d:select\n", ZCONFFILE);
}
    break;

  case 46:

    {
    menu_add_symbol(P_IMPLY, sym_lookup((yyvsp[(2) - (4)].string), 0, kcm), (yyvsp[(3) - (4)].expr), kcm);
    printd(DEBUG_PARSE, "%s:%d:imply\n", ZCONFFILE);
}
    break;

  case 47:

    {
    menu_add_expr(P_RANGE, expr_alloc_comp(E_RANGE,(yyvsp[(2) - (5)].symbol), (yyvsp[(3) - (5)].symbol)), (yyvsp[(4) - (5)].expr), kcm);
    printd(DEBUG_PARSE, "%s:%d:range\n", ZCONFFILE);
}
    break;

  case 50:

    {
    const struct kconf_id *id = kconf_id_lookup((yyvsp[(2) - (3)].string), strlen((yyvsp[(2) - (3)].string)));
    if (id && id->flags & TF_OPTION)
        menu_add_option(id->token, (yyvsp[(3) - (3)].string), kcm);
    else
        zconfprint(kcm, "warning: ignoring unknown option %s", (yyvsp[(2) - (3)].string));
    free((yyvsp[(2) - (3)].string));
}
    break;

  case 51:

    { (yyval.string) = NULL; }
    break;

  case 52:

    { (yyval.string) = (yyvsp[(2) - (2)].string); }
    break;

  case 53:

    {
    struct symbol *sym = sym_lookup((yyvsp[(2) - (3)].string), SYMBOL_CHOICE, kcm);
    sym->flags |= SYMBOL_AUTO;
    menu_add_entry(sym, kcm);
    menu_add_expr(P_CHOICE, NULL, NULL, kcm);
    printd(DEBUG_PARSE, "%s:%d:choice\n", ZCONFFILE);
}
    break;

  case 54:

    {
    (yyval.menu) = menu_add_menu(kcm);
}
    break;

  case 55:

    {
    if (zconf_endtoken((yyvsp[(1) - (1)].id), T_CHOICE, T_ENDCHOICE, kcm)) {
                menu_end_menu(kcm);
        printd(DEBUG_PARSE, "%s:%d:endchoice\n", ZCONFFILE);
    }
}
    break;

  case 63:

    {
    menu_add_prompt(P_PROMPT, (yyvsp[(2) - (4)].string), (yyvsp[(3) - (4)].expr), kcm);
    printd(DEBUG_PARSE, "%s:%d:prompt\n", ZCONFFILE);
}
    break;

  case 64:

    {
    if ((yyvsp[(1) - (3)].id)->stype == S_BOOLEAN || (yyvsp[(1) - (3)].id)->stype == S_TRISTATE) {
        menu_set_type((yyvsp[(1) - (3)].id)->stype, kcm);
        printd(DEBUG_PARSE, "%s:%d:type(%u)\n",
            ZCONFFILE,
            (yyvsp[(1) - (3)].id)->stype);
    } else
        YYERROR;
}
    break;

  case 65:

    {
    kcm->current_entry->sym->flags |= SYMBOL_OPTIONAL;
    printd(DEBUG_PARSE, "%s:%d:optional\n", ZCONFFILE);
}
    break;

  case 66:

    {
    if ((yyvsp[(1) - (4)].id)->stype == S_UNKNOWN) {
        menu_add_symbol(P_DEFAULT, sym_lookup((yyvsp[(2) - (4)].string), 0, kcm), (yyvsp[(3) - (4)].expr), kcm);
        printd(DEBUG_PARSE, "%s:%d:default\n",
            ZCONFFILE);
    } else
        YYERROR;
}
    break;

  case 69:

    {
    printd(DEBUG_PARSE, "%s:%d:if\n", ZCONFFILE);
    menu_add_entry(NULL, kcm);
    menu_add_dep((yyvsp[(2) - (3)].expr), kcm);
    (yyval.menu) = menu_add_menu(kcm);
}
    break;

  case 70:

    {
    if (zconf_endtoken((yyvsp[(1) - (1)].id), T_IF, T_ENDIF, kcm)) {
                menu_end_menu(kcm);
        printd(DEBUG_PARSE, "%s:%d:endif\n", ZCONFFILE);
    }
}
    break;

  case 76:

    {
    menu_add_prompt(P_MENU, (yyvsp[(2) - (3)].string), NULL, kcm);
}
    break;

  case 77:

    {
    menu_add_entry(NULL, kcm);
    menu_add_prompt(P_MENU, (yyvsp[(2) - (3)].string), NULL, kcm);
    printd(DEBUG_PARSE, "%s:%d:menu\n", ZCONFFILE);
}
    break;

  case 78:

    {
    (yyval.menu) = menu_add_menu(kcm);
}
    break;

  case 79:

    {
    if (zconf_endtoken((yyvsp[(1) - (1)].id), T_MENU, T_ENDMENU, kcm)) {
                menu_end_menu(kcm);
        printd(DEBUG_PARSE, "%s:%d:endmenu\n", ZCONFFILE);
    }
}
    break;

  case 85:

    {
    printd(DEBUG_PARSE, "%s:%d:source %s\n", ZCONFFILE, (yyvsp[(2) - (3)].string));
    if (!zconf_nextfile((yyvsp[(2) - (3)].string), kcm->yyscanner))
	    return -1;
}
    break;

  case 86:

    {
    menu_add_entry(NULL, kcm);
    menu_add_prompt(P_COMMENT, (yyvsp[(2) - (3)].string), NULL, kcm);
    printd(DEBUG_PARSE, "%s:%d:comment\n", ZCONFFILE);
}
    break;

  case 87:

    {
    menu_end_entry();
}
    break;

  case 88:

    {
    printd(DEBUG_PARSE, "%s:%d:help\n", ZCONFFILE);
    zconf_starthelp(kcm->yyscanner);
}
    break;

  case 89:

    {
    kcm->current_entry->help = (yyvsp[(2) - (2)].string);
}
    break;

  case 94:

    {
    menu_add_dep((yyvsp[(3) - (4)].expr), kcm);
    printd(DEBUG_PARSE, "%s:%d:depends on\n", ZCONFFILE);
}
    break;

  case 98:

    {
    menu_add_visibility((yyvsp[(2) - (2)].expr), kcm);
}
    break;

  case 100:

    {
    menu_add_prompt(P_PROMPT, (yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].expr), kcm);
}
    break;

  case 103:

    { (yyval.id) = (yyvsp[(1) - (2)].id); }
    break;

  case 104:

    { (yyval.id) = (yyvsp[(1) - (2)].id); }
    break;

  case 105:

    { (yyval.id) = (yyvsp[(1) - (2)].id); }
    break;

  case 108:

    { (yyval.expr) = NULL; }
    break;

  case 109:

    { (yyval.expr) = (yyvsp[(2) - (2)].expr); }
    break;

  case 110:

    { (yyval.expr) = expr_alloc_symbol((yyvsp[(1) - (1)].symbol)); }
    break;

  case 111:

    { (yyval.expr) = expr_alloc_comp(E_LTH, (yyvsp[(1) - (3)].symbol), (yyvsp[(3) - (3)].symbol)); }
    break;

  case 112:

    { (yyval.expr) = expr_alloc_comp(E_LEQ, (yyvsp[(1) - (3)].symbol), (yyvsp[(3) - (3)].symbol)); }
    break;

  case 113:

    { (yyval.expr) = expr_alloc_comp(E_GTH, (yyvsp[(1) - (3)].symbol), (yyvsp[(3) - (3)].symbol)); }
    break;

  case 114:

    { (yyval.expr) = expr_alloc_comp(E_GEQ, (yyvsp[(1) - (3)].symbol), (yyvsp[(3) - (3)].symbol)); }
    break;

  case 115:

    { (yyval.expr) = expr_alloc_comp(E_EQUAL, (yyvsp[(1) - (3)].symbol), (yyvsp[(3) - (3)].symbol)); }
    break;

  case 116:

    { (yyval.expr) = expr_alloc_comp(E_UNEQUAL, (yyvsp[(1) - (3)].symbol), (yyvsp[(3) - (3)].symbol)); }
    break;

  case 117:

    { (yyval.expr) = (yyvsp[(2) - (3)].expr); }
    break;

  case 118:

    { (yyval.expr) = expr_alloc_one(E_NOT, (yyvsp[(2) - (2)].expr)); }
    break;

  case 119:

    { (yyval.expr) = expr_alloc_two(E_OR, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr)); }
    break;

  case 120:

    { (yyval.expr) = expr_alloc_two(E_AND, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr)); }
    break;

  case 121:

    { (yyval.symbol) = sym_lookup((yyvsp[(1) - (1)].string), 0, kcm); free((yyvsp[(1) - (1)].string)); }
    break;

  case 122:

    { (yyval.symbol) = sym_lookup((yyvsp[(1) - (1)].string), SYMBOL_CONST, kcm); free((yyvsp[(1) - (1)].string)); }
    break;

  case 123:

    { (yyval.string) = NULL; }
    break;



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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (kcm, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (kcm, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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
		      yytoken, &yylval, kcm);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp, kcm);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (kcm, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, kcm);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, kcm);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}





static const char *zconf_tokenname(int token)
{
    switch (token) {
    case T_MENU:        return "menu";
    case T_ENDMENU:     return "endmenu";
    case T_CHOICE:      return "choice";
    case T_ENDCHOICE:   return "endchoice";
    case T_IF:      return "if";
    case T_ENDIF:       return "endif";
    case T_DEPENDS:     return "depends";
    case T_VISIBLE:     return "visible";
    }
    return "<token>";
}

static bool zconf_endtoken(const struct kconf_id *id, int starttoken, int endtoken, kcmenu_t *kcm)
{
    if (id->token != endtoken)
    {
        zconf_error(kcm, "unexpected '%s' within %s block",
            kconf_id_strings + id->name, zconf_tokenname(starttoken));

        return false;
    }
    if (kcm->current_menu->file != zconf_current_file(kcm->yyscanner))
    {
        zconf_error(kcm, "'%s' in different file than '%s'",
            kconf_id_strings + id->name, zconf_tokenname(starttoken));
        zconf_error(kcm, "%s:%d: location of the '%s'\n",
            kcm->current_menu->file->name, kcm->current_menu->lineno,
            zconf_tokenname(starttoken));

        return false;
    }

    return true;
}

static void zconfoutmsg(kcmenu_t *kcm, const char *fmt, ...)
{
   va_list ap;

   va_start(ap, fmt);
   if (kcm->msgout.print)
   {
       kcm->msgout.print(&kcm->msgout, 0, fmt, ap);
   }
   va_end(ap);
}


static void zconfprint(kcmenu_t *kcm, const char *err, ...)
{
    va_list ap;

    va_start(ap, err);
    zconfoutmsg(kcm, "%s:%d: ", zconf_curname(kcm->yyscanner), zconf_lineno(kcm->yyscanner));

    if (kcm->msgout.print)
    {
        kcm->msgout.print(&kcm->msgout, 0, err, ap);
    }
    va_end(ap);
}

static void zconf_error(kcmenu_t *kcm, const char *err, ...)
{
    va_list ap;

    va_start(ap, err);
    kcm->zconfnerrs++;
    zconfoutmsg(kcm, "%s:%d: ", zconf_curname(kcm->yyscanner), zconf_lineno(kcm->yyscanner));

    if (kcm->msgout.print)
    {
        kcm->msgout.print(&kcm->msgout, 0, err, ap);
    }
    va_end(ap);
}

static void print_quoted_string(FILE *out, const char *str)
{
    const char *p;
    int len;

    putc('"', out);
    while ((p = strchr(str, '"'))) {
        len = p - str;
        if (len)
            fprintf(out, "%.*s", len, str);
        fputs("\\\"", out);
        str = p + 1;
    }
    fputs(str, out);
    putc('"', out);
}

static void print_symbol(FILE *out, struct menu *menu)
{
    struct symbol *sym = menu->sym;
    struct property *prop;

    if (sym_is_choice(sym))
        fprintf(out, "\nchoice\n");
    else
        fprintf(out, "\nconfig %s\n", sym->name);
    switch (sym->type) {
    case S_BOOLEAN:
        fputs("  boolean\n", out);
        break;
    case S_TRISTATE:
        fputs("  tristate\n", out);
        break;
    case S_STRING:
        fputs("  string\n", out);
        break;
    case S_INT:
        fputs("  integer\n", out);
        break;
    case S_HEX:
        fputs("  hex\n", out);
        break;
    default:
        fputs("  ???\n", out);
        break;
    }
    for (prop = sym->prop; prop; prop = prop->next) {
        if (prop->menu != menu)
            continue;
        switch (prop->type) {
        case P_PROMPT:
            fputs("  prompt ", out);
            print_quoted_string(out, prop->text);
            if (!expr_is_yes(prop->visible.expr)) {
                fputs(" if ", out);
                expr_fprint(prop->visible.expr, out);
            }
            fputc('\n', out);
            break;
        case P_DEFAULT:
            fputs( "  default ", out);
            expr_fprint(prop->expr, out);
            if (!expr_is_yes(prop->visible.expr)) {
                fputs(" if ", out);
                expr_fprint(prop->visible.expr, out);
            }
            fputc('\n', out);
            break;
        case P_CHOICE:
            fputs("  #choice value\n", out);
            break;
        case P_SELECT:
            fputs( "  select ", out);
            expr_fprint(prop->expr, out);
            fputc('\n', out);
            break;
        case P_IMPLY:
            fputs( "  imply ", out);
            expr_fprint(prop->expr, out);
            fputc('\n', out);
            break;
        case P_RANGE:
            fputs( "  range ", out);
            expr_fprint(prop->expr, out);
            fputc('\n', out);
            break;
        case P_MENU:
            fputs( "  menu ", out);
            print_quoted_string(out, prop->text);
            fputc('\n', out);
            break;
        default:
            fprintf(out, "  unknown prop %d!\n", prop->type);
            break;
        }
    }
    if (menu->help) {
        int len = strlen(menu->help);
        while (menu->help[--len] == '\n')
            menu->help[len] = 0;
        fprintf(out, "  help\n%s\n", menu->help);
    }
}

#include "zconf.lex.c"
#include "util.c"
#include "confdata.c"
#include "expr.c"
#include "symbol.c"
#include "menu.c"
