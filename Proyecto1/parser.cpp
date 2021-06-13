/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "sintactico.y" /* yacc.c:339  */

    #include <iostream>
    #include <QString>
    #include "scanner.h"
    #include "clmkdisk.h"
    #include "clrmdisk.h"
    #include "clfdisk.h"
    #include "clmount.h"
    #include "clunmount.h"
    #include "clmkfs.h"
    #include "clexec.h"
    #include "clreportes.h"
    #include "cllogin.h"
    #include "clmkgrp.h"
    #include "clrmgrp.h"
    #include "clmkuser.h"
    #include "clrmuser.h"


    extern int yylex(void);
    extern int resultado;
    clmkdisk *mkdisco = new clmkdisk();
    clrmdisk *rmdisco = new clrmdisk();
    clfdisk *ffdisco = new clfdisk();
    clmount *modisco = new clmount();
    clunmount *unmdisco = new clunmount();
    clmkfs *mkfsdisco = new clmkfs();

    cllogin *loginn = new cllogin();
    clmkgrp *mkgrpp = new clmkgrp();
    clrmgrp *rmgrpp = new clrmgrp();
    clmkuser *mkuserr = new clmkuser();
    clrmuser *rmuserr = new clrmuser();

    clexec *script = new clexec();
    clReportes *reporte = new clReportes();


    int yyerror(const char* mens){
        std::cout << mens << std::endl;
        return 0;
    }

#line 110 "parser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.h".  */
#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    digito = 258,
    ident = 259,
    cadena = 260,
    filen = 261,
    idp = 262,
    ruta = 263,
    mkdisk = 264,
    rmdisk = 265,
    fdisk = 266,
    mount = 267,
    unmount = 268,
    mkfs = 269,
    login = 270,
    logout = 271,
    mkgrp = 272,
    rmgrp = 273,
    mkusr = 274,
    rmusr = 275,
    mkfile = 276,
    mkdirr = 277,
    cat = 278,
    rem = 279,
    edit = 280,
    ren = 281,
    cp = 282,
    mv = 283,
    find = 284,
    chownn = 285,
    chgrp = 286,
    execc = 287,
    pausee = 288,
    comentario = 289,
    rep = 290,
    igual = 291,
    dividido = 292,
    interrogacion = 293,
    multiplicacion = 294,
    negativo = 295,
    sizee = 296,
    f = 297,
    u = 298,
    pathh = 299,
    typee = 300,
    deletee = 301,
    namee = 302,
    addd = 303,
    id = 304,
    fs = 305,
    usr = 306,
    pwd = 307,
    grp = 308,
    ugo = 309,
    rr = 310,
    cont = 311,
    filenn = 312,
    dest = 313,
    p = 314,
    BF = 315,
    FF = 316,
    WF = 317,
    K = 318,
    M = 319,
    B = 320,
    PP = 321,
    E = 322,
    L = 323,
    FAST = 324,
    FULL = 325,
    FS2 = 326,
    FS3 = 327
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 47 "sintactico.y" /* yacc.c:355  */

    char TEXT[500];
    class clmkdisk *mdisk;
    class clrmdisk *mrdiskk;
    class clfdisk *fdiskk;
    class clmount *modiskk;
    class clunmount *unmdiskk;
    class clmkfs *mkdiskk;

    class cllogin *clogin;
    class clmkgrp *cmkgrp;
    class clrmgrp *crmgrp;
    class clmkuser *cmkuser;
    class clrmuser *crmuser;

    class clexec *archexec;
    class clReportes *creporte;

#line 242 "parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 259 "parser.cpp" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

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
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  64
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   211

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  73
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  16
/* YYNRULES -- Number of rules.  */
#define YYNRULES  146
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  226

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   327

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   160,   160,   162,   163,   164,   165,   166,   167,   169,
     170,   171,   172,   173,   175,   176,   177,   178,   179,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   198,   199,   200,   201,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   240,   241,   242,   243,   244,
     245,   246,   247,   249,   250,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   263,   264,   265,   266,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   292,   293,   294,   295,   297,   298,   299,   300,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   317,   318,   319,   320
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "digito", "ident", "cadena", "filen",
  "idp", "ruta", "mkdisk", "rmdisk", "fdisk", "mount", "unmount", "mkfs",
  "login", "logout", "mkgrp", "rmgrp", "mkusr", "rmusr", "mkfile",
  "mkdirr", "cat", "rem", "edit", "ren", "cp", "mv", "find", "chownn",
  "chgrp", "execc", "pausee", "comentario", "rep", "igual", "dividido",
  "interrogacion", "multiplicacion", "negativo", "sizee", "f", "u",
  "pathh", "typee", "deletee", "namee", "addd", "id", "fs", "usr", "pwd",
  "grp", "ugo", "rr", "cont", "filenn", "dest", "p", "BF", "FF", "WF", "K",
  "M", "B", "PP", "E", "L", "FAST", "FULL", "FS2", "FS3", "$accept",
  "INICIO", "COMANDOS", "COMMKDISK", "COMRMDISK", "COMFDISK", "COMMOUNT",
  "COMUNMOUNT", "COMFSDISK", "COMEXEC", "COMREPORTE", "COMLOGIN",
  "COMMKGRP", "COMRMGRP", "COMMKUSER", "COMRMUSER", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327
};
# endif

#define YYPACT_NINF -108

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-108)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       9,    36,    31,   -11,    53,     4,    23,    47,  -108,    66,
      73,   -13,    91,    80,  -108,  -108,    27,   159,  -108,   131,
     136,   137,   138,  -108,   139,  -108,   140,   142,   144,   146,
     148,   150,   152,   154,  -108,   155,   156,  -108,   157,  -108,
     158,   160,   161,  -108,   162,   163,   164,  -108,   165,  -108,
     166,  -108,   167,   168,   169,  -108,   170,  -108,   171,  -108,
     172,   173,   174,  -108,  -108,   176,    54,     6,    96,    97,
     178,    57,    58,    98,    59,    65,   132,    14,   102,   134,
     180,    71,   182,    72,   179,   141,   125,   143,   145,   147,
     128,   149,   151,   103,   104,   153,   188,    36,    36,    36,
      36,    36,    36,    36,    36,    31,    31,   -11,   -11,   -11,
     -11,   -11,   -11,   -11,   -11,   -11,   -11,   -11,   -11,   -11,
     -11,   -11,   -11,   -11,   208,    53,    53,    53,    53,     4,
      23,    23,    23,    23,    23,    47,    47,    47,    47,    47,
      47,    66,    66,    73,    73,   -13,   -13,   -13,   -13,   -13,
     -13,   -13,    91,    91,    80,    80,    27,    27,    27,    27,
      27,  -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,
    -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,
    -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,   -11,  -108,
    -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,
    -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,
    -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,
    -108,  -108,  -108,  -108,  -108,  -108
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,    16,     0,
       0,     0,     0,     0,    17,    18,     0,     0,     2,     0,
       0,     0,     0,     3,     0,     4,     0,     0,     0,     0,
       0,     0,     0,     0,     5,     0,     0,     6,     0,     7,
       0,     0,     0,     8,     0,     0,     0,     9,     0,    10,
       0,    11,     0,     0,     0,    12,     0,    13,     0,    14,
       0,     0,     0,    15,     1,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    27,    28,    29,
      30,    31,    32,    33,    34,    37,    38,    57,    66,    67,
      68,    58,    59,    60,    61,    62,    63,    64,    65,    69,
      70,    72,    71,    73,     0,    79,    80,    82,    81,    84,
      91,    92,    90,    93,    94,   120,   116,   115,   119,   118,
     117,   124,   123,   128,   127,   137,   136,   140,   139,   138,
     142,   141,   146,   145,    97,    98,   104,   105,   107,   106,
     108,    19,    20,    21,    22,    23,    24,    25,    26,    35,
      36,    39,    48,    49,    50,    40,    41,    42,    43,    44,
      45,    46,    47,    51,    52,    54,    53,    55,    74,    75,
      76,    78,    77,    83,    86,    87,    85,    88,    89,   114,
     110,   109,   113,   112,   111,   122,   121,   126,   125,   130,
     129,   133,   132,   131,   135,   134,   144,   143,    95,    96,
      99,   100,   102,   101,   103,    56
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -108,  -108,  -108,   -52,    55,  -107,   -33,    35,   -48,     8,
     -69,   -73,    24,    25,   -90,    18
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    17,    18,    23,    25,    34,    37,    39,    43,    59,
      63,    47,    49,    51,    55,    57
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   123,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      26,    27,    28,    29,    30,    31,    32,    33,    52,    53,
      54,    13,    14,    15,    16,   161,   162,   163,   164,   165,
     166,   167,   168,    38,   124,   209,   210,   211,   212,   213,
     214,   215,   199,   200,   201,   202,   203,   204,    40,   101,
     102,    60,    41,    42,    61,    24,    62,    19,    20,    21,
      22,   225,   194,   195,   196,   197,   198,   220,   221,   222,
     223,   224,   189,   190,   191,   192,    44,    35,    45,    46,
      36,   103,   105,   114,   104,   106,   115,   125,   154,   156,
     126,   155,   157,    48,    98,    99,   100,   108,   109,   110,
      50,   111,   112,   113,    58,   116,   117,   118,   138,   139,
     140,   147,   148,   149,   119,   120,   121,   122,   127,   128,
     130,   131,    56,   133,   134,   136,   137,   141,   142,   143,
     144,   145,   146,   150,   151,   152,   153,   158,   159,    64,
     169,   170,   218,   219,   193,   205,   206,    65,   207,   208,
     216,   217,    66,    67,    68,    69,    70,     0,    71,    97,
      72,   107,    73,   135,    74,     0,    75,   129,    76,   132,
      77,    78,    79,    80,    81,   160,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,   188
};

static const yytype_int16 yycheck[] =
{
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,     3,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      41,    42,    43,    44,    45,    46,    47,    48,    51,    52,
      53,    32,    33,    34,    35,    97,    98,    99,   100,   101,
     102,   103,   104,    49,    40,   145,   146,   147,   148,   149,
     150,   151,   135,   136,   137,   138,   139,   140,    45,    63,
      64,    44,    49,    50,    47,    44,    49,    41,    42,    43,
      44,   188,   130,   131,   132,   133,   134,   156,   157,   158,
     159,   160,   125,   126,   127,   128,    49,    44,    51,    52,
      47,     5,     5,     5,     8,     8,     8,     5,     5,     5,
       8,     8,     8,    47,    60,    61,    62,    60,    61,    62,
      47,    63,    64,    65,    44,    66,    67,    68,     3,     4,
       5,     3,     4,     5,    69,    70,     4,     5,     4,     5,
      69,    70,    51,    71,    72,     4,     5,     4,     5,     4,
       5,     4,     5,     4,     5,     4,     5,     4,     5,     0,
     105,   106,   154,   155,   129,   141,   142,    36,   143,   144,
     152,   153,    36,    36,    36,    36,    36,    -1,    36,     3,
      36,     3,    36,     4,    36,    -1,    36,     7,    36,     7,
      36,    36,    36,    36,    36,     7,    36,    36,    36,    36,
      36,    36,    36,    36,    36,    36,    36,    36,    36,    36,
      36,     3
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    32,    33,    34,    35,    74,    75,    41,
      42,    43,    44,    76,    44,    77,    41,    42,    43,    44,
      45,    46,    47,    48,    78,    44,    47,    79,    49,    80,
      45,    49,    50,    81,    49,    51,    52,    84,    47,    85,
      47,    86,    51,    52,    53,    87,    51,    88,    44,    82,
      44,    47,    49,    83,     0,    36,    36,    36,    36,    36,
      36,    36,    36,    36,    36,    36,    36,    36,    36,    36,
      36,    36,    36,    36,    36,    36,    36,    36,    36,    36,
      36,    36,    36,    36,    36,    36,    36,     3,    60,    61,
      62,    63,    64,     5,     8,     5,     8,     3,    60,    61,
      62,    63,    64,    65,     5,     8,    66,    67,    68,    69,
      70,     4,     5,     3,    40,     5,     8,     4,     5,     7,
      69,    70,     7,    71,    72,     4,     4,     5,     3,     4,
       5,     4,     5,     4,     5,     4,     5,     3,     4,     5,
       4,     5,     4,     5,     5,     8,     5,     8,     4,     5,
       7,    76,    76,    76,    76,    76,    76,    76,    76,    77,
      77,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,     3,    79,
      79,    79,    79,    80,    81,    81,    81,    81,    81,    84,
      84,    84,    84,    84,    84,    85,    85,    86,    86,    87,
      87,    87,    87,    87,    87,    87,    88,    88,    82,    82,
      83,    83,    83,    83,    83,    78
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    73,    74,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    77,    77,    77,    77,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    79,    79,    79,    79,    79,
      79,    79,    79,    80,    80,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    82,    82,    82,    82,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    85,    85,    85,    85,    86,    86,    86,    86,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    88,    88,    88,    88
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     1,     1,     4,
       4,     4,     4,     4,     4,     4,     4,     3,     3,     3,
       3,     3,     3,     3,     3,     4,     4,     3,     3,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     5,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     4,     4,     4,     4,     4,     3,
       3,     3,     3,     4,     3,     4,     4,     4,     4,     4,
       3,     3,     3,     3,     3,     4,     4,     3,     3,     4,
       4,     4,     4,     4,     3,     3,     3,     3,     3,     4,
       4,     4,     4,     4,     4,     3,     3,     3,     3,     3,
       3,     4,     4,     3,     3,     4,     4,     3,     3,     4,
       4,     4,     4,     4,     4,     4,     3,     3,     3,     3,
       3,     3,     3,     4,     4,     3,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

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
      yychar = yylex ();
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
        case 2:
#line 160 "sintactico.y" /* yacc.c:1646  */
    { }
#line 1500 "parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 162 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].mdisk)->mostrarDatos((yyvsp[0].mdisk)); cout<<"Comando MKDISK"<<endl;}
#line 1506 "parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 163 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].mrdiskk)->mostrarDatos((yyvsp[0].mrdiskk)); cout<<"Comando RMDISK"<<endl;}
#line 1512 "parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 164 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].fdiskk)->mostrarDatos((yyvsp[0].fdiskk)); cout<<"Comando FDISK"<<endl;}
#line 1518 "parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 165 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].modiskk)->mostrarDatos((yyvsp[0].modiskk)); cout<<"Comando MOUNT"<<endl;}
#line 1524 "parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 166 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].unmdiskk)->mostrarDatos((yyvsp[0].unmdiskk)); cout<<"Comando UNMOUNT"<<endl;}
#line 1530 "parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 167 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].mkdiskk)->mostrarDatos((yyvsp[0].mkdiskk)); cout<<"Comando MKFS"<<endl;}
#line 1536 "parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 169 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].clogin)->logear((yyvsp[0].clogin));       cout<<"Comando LOGIN"<<endl;}
#line 1542 "parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 170 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].cmkgrp)->mostrarDatos((yyvsp[0].cmkgrp)); cout<<"Comando MKGRP"<<endl;}
#line 1548 "parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 171 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].crmgrp)->mostrarDatos((yyvsp[0].crmgrp)); cout<<"Comando RMGRP"<<endl;}
#line 1554 "parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 172 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].cmkuser)->mostrarDatos((yyvsp[0].cmkuser)); cout<<"Comando MKUSER"<<endl;}
#line 1560 "parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 173 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].crmuser)->mostrarDatos((yyvsp[0].crmuser)); cout<<"Comando RMUSER"<<endl;}
#line 1566 "parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 175 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].archexec)->mostrarDatos((yyvsp[0].archexec)); cout<<"Comando EXEC"<<endl;}
#line 1572 "parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 176 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].creporte)->mostrarDatos((yyvsp[0].creporte)); cout<<"Comando REPORTE"<<endl;}
#line 1578 "parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 177 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].clogin)->salir();          cout<<"Comando LOGOUT"<<endl;}
#line 1584 "parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 178 "sintactico.y" /* yacc.c:1646  */
    {cout<<"Ingrese una tecla para continuar"<<endl; cin.get();}
#line 1590 "parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 179 "sintactico.y" /* yacc.c:1646  */
    {}
#line 1596 "parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 181 "sintactico.y" /* yacc.c:1646  */
    {int tam=atoi((yyvsp[-1].TEXT)); if(mkdisco->size==0){mkdisco->size=tam;} (yyval.mdisk)=mkdisco;}
#line 1602 "parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 182 "sintactico.y" /* yacc.c:1646  */
    {if(mkdisco->f==""){mkdisco->f=(yyvsp[-1].TEXT);} (yyval.mdisk)=mkdisco;}
#line 1608 "parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 183 "sintactico.y" /* yacc.c:1646  */
    {if(mkdisco->f==""){mkdisco->f=(yyvsp[-1].TEXT);} (yyval.mdisk)=mkdisco;}
#line 1614 "parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 184 "sintactico.y" /* yacc.c:1646  */
    {if(mkdisco->f==""){mkdisco->f=(yyvsp[-1].TEXT);} (yyval.mdisk)=mkdisco;}
#line 1620 "parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 185 "sintactico.y" /* yacc.c:1646  */
    {if(mkdisco->u==""){mkdisco->u=(yyvsp[-1].TEXT);} (yyval.mdisk)=mkdisco;}
#line 1626 "parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 186 "sintactico.y" /* yacc.c:1646  */
    {if(mkdisco->u==""){mkdisco->u=(yyvsp[-1].TEXT);} (yyval.mdisk)=mkdisco;}
#line 1632 "parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 187 "sintactico.y" /* yacc.c:1646  */
    {if(mkdisco->path==""){mkdisco->path=(yyvsp[-1].TEXT);} (yyval.mdisk)=mkdisco;}
#line 1638 "parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 188 "sintactico.y" /* yacc.c:1646  */
    {if(mkdisco->path==""){mkdisco->path=(yyvsp[-1].TEXT);} (yyval.mdisk)=mkdisco;}
#line 1644 "parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 189 "sintactico.y" /* yacc.c:1646  */
    {int tam=atoi((yyvsp[0].TEXT)); if(mkdisco->size!=0){mkdisco->size=tam;} (yyval.mdisk)=mkdisco;}
#line 1650 "parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 190 "sintactico.y" /* yacc.c:1646  */
    {if(mkdisco->f==""){mkdisco->f=(yyvsp[0].TEXT);} (yyval.mdisk)=mkdisco;}
#line 1656 "parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 191 "sintactico.y" /* yacc.c:1646  */
    {if(mkdisco->f==""){mkdisco->f=(yyvsp[0].TEXT);} (yyval.mdisk)=mkdisco;}
#line 1662 "parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 192 "sintactico.y" /* yacc.c:1646  */
    {if(mkdisco->f==""){mkdisco->f=(yyvsp[0].TEXT);} (yyval.mdisk)=mkdisco;}
#line 1668 "parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 193 "sintactico.y" /* yacc.c:1646  */
    {if(mkdisco->u==""){mkdisco->u=(yyvsp[0].TEXT);} (yyval.mdisk)=mkdisco;}
#line 1674 "parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 194 "sintactico.y" /* yacc.c:1646  */
    {if(mkdisco->u==""){mkdisco->u=(yyvsp[0].TEXT);} (yyval.mdisk)=mkdisco;}
#line 1680 "parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 195 "sintactico.y" /* yacc.c:1646  */
    {if(mkdisco->path==""){mkdisco->path=(yyvsp[0].TEXT);} (yyval.mdisk)=mkdisco;}
#line 1686 "parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 196 "sintactico.y" /* yacc.c:1646  */
    {if(mkdisco->path==""){mkdisco->path=(yyvsp[0].TEXT);} (yyval.mdisk)=mkdisco;}
#line 1692 "parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 198 "sintactico.y" /* yacc.c:1646  */
    {if(rmdisco->path==""){rmdisco->path=(yyvsp[-1].TEXT);} (yyval.mrdiskk)=rmdisco;}
#line 1698 "parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 199 "sintactico.y" /* yacc.c:1646  */
    {if(rmdisco->path==""){rmdisco->path=(yyvsp[-1].TEXT);} (yyval.mrdiskk)=rmdisco;}
#line 1704 "parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 200 "sintactico.y" /* yacc.c:1646  */
    {if(rmdisco->path==""){rmdisco->path=(yyvsp[0].TEXT);} (yyval.mrdiskk)=rmdisco;}
#line 1710 "parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 201 "sintactico.y" /* yacc.c:1646  */
    {if(rmdisco->path==""){rmdisco->path=(yyvsp[0].TEXT);} (yyval.mrdiskk)=rmdisco;}
#line 1716 "parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 203 "sintactico.y" /* yacc.c:1646  */
    {int tam=atoi((yyvsp[-1].TEXT)); if(ffdisco->primero==""){ffdisco->primero="s";} if(ffdisco->size==0){ffdisco->size=tam;} (yyval.fdiskk)=ffdisco;}
#line 1722 "parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 204 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->u==""){ffdisco->u=(yyvsp[-1].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 1728 "parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 205 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->u==""){ffdisco->u=(yyvsp[-1].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 1734 "parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 206 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->u==""){ffdisco->u=(yyvsp[-1].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 1740 "parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 207 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->path==""){ffdisco->path=(yyvsp[-1].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 1746 "parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 208 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->path==""){ffdisco->path=(yyvsp[-1].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 1752 "parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 209 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->typee==""){ffdisco->typee=(yyvsp[-1].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 1758 "parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 210 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->typee==""){ffdisco->typee=(yyvsp[-1].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 1764 "parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 211 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->typee==""){ffdisco->typee=(yyvsp[-1].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 1770 "parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 212 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->f==""){ffdisco->f=(yyvsp[-1].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 1776 "parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 213 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->f==""){ffdisco->f=(yyvsp[-1].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 1782 "parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 214 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->f==""){ffdisco->f=(yyvsp[-1].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 1788 "parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 215 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->deletee==""){ffdisco->deletee=(yyvsp[-1].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 1794 "parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 216 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->deletee==""){ffdisco->deletee=(yyvsp[-1].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 1800 "parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 217 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->namee==""){ffdisco->namee=(yyvsp[-1].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 1806 "parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 218 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->namee==""){ffdisco->namee=(yyvsp[-1].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 1812 "parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 219 "sintactico.y" /* yacc.c:1646  */
    {int tam=atoi((yyvsp[-1].TEXT)); if(ffdisco->primero==""){ffdisco->primero="a";} if(ffdisco->addd==0){ffdisco->addd=tam;} (yyval.fdiskk)=ffdisco;}
#line 1818 "parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 220 "sintactico.y" /* yacc.c:1646  */
    {int tam=atoi((yyvsp[-1].TEXT)); if(ffdisco->primero==""){ffdisco->primero="a";} if(ffdisco->addd==0){ffdisco->addd=tam * -1;} (yyval.fdiskk)=ffdisco;}
#line 1824 "parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 221 "sintactico.y" /* yacc.c:1646  */
    {int tam=atoi((yyvsp[0].TEXT)); if(ffdisco->primero==""){ffdisco->primero="s";} if(ffdisco->size==0){ffdisco->size=tam;} (yyval.fdiskk)=ffdisco;}
#line 1830 "parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 222 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->u==""){ffdisco->u=(yyvsp[0].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 1836 "parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 223 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->u==""){ffdisco->u=(yyvsp[0].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 1842 "parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 224 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->u==""){ffdisco->u=(yyvsp[0].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 1848 "parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 225 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->path==""){ffdisco->path=(yyvsp[0].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 1854 "parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 226 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->path==""){ffdisco->path=(yyvsp[0].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 1860 "parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 227 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->typee==""){ffdisco->typee=(yyvsp[0].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 1866 "parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 228 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->typee==""){ffdisco->typee=(yyvsp[0].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 1872 "parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 229 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->typee==""){ffdisco->typee=(yyvsp[0].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 1878 "parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 230 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->f==""){ffdisco->f=(yyvsp[0].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 1884 "parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 231 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->f==""){ffdisco->f=(yyvsp[0].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 1890 "parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 232 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->f==""){ffdisco->f=(yyvsp[0].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 1896 "parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 233 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->deletee==""){ffdisco->deletee=(yyvsp[0].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 1902 "parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 234 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->deletee==""){ffdisco->deletee=(yyvsp[0].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 1908 "parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 235 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->namee==""){ffdisco->namee=(yyvsp[0].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 1914 "parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 236 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->namee==""){ffdisco->namee=(yyvsp[0].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 1920 "parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 237 "sintactico.y" /* yacc.c:1646  */
    {int tam=atoi((yyvsp[0].TEXT)); if(ffdisco->primero==""){ffdisco->primero="a";} if(ffdisco->addd==0){ffdisco->addd=tam;} (yyval.fdiskk)=ffdisco;}
#line 1926 "parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 238 "sintactico.y" /* yacc.c:1646  */
    {int tam=atoi((yyvsp[0].TEXT)); if(ffdisco->primero==""){ffdisco->primero="a";} if(ffdisco->addd==0){ffdisco->addd=tam * -1;} (yyval.fdiskk)=ffdisco;}
#line 1932 "parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 240 "sintactico.y" /* yacc.c:1646  */
    {if(modisco->path==""){modisco->path=(yyvsp[-1].TEXT);} (yyval.modiskk)=modisco;}
#line 1938 "parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 241 "sintactico.y" /* yacc.c:1646  */
    {if(modisco->path==""){modisco->path=(yyvsp[-1].TEXT);} (yyval.modiskk)=modisco;}
#line 1944 "parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 242 "sintactico.y" /* yacc.c:1646  */
    {if(modisco->namee==""){modisco->namee=(yyvsp[-1].TEXT);} (yyval.modiskk)=modisco;}
#line 1950 "parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 243 "sintactico.y" /* yacc.c:1646  */
    {if(modisco->namee==""){modisco->namee=(yyvsp[-1].TEXT);} (yyval.modiskk)=modisco;}
#line 1956 "parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 244 "sintactico.y" /* yacc.c:1646  */
    {if(modisco->path==""){modisco->path=(yyvsp[0].TEXT);} (yyval.modiskk)=modisco;}
#line 1962 "parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 245 "sintactico.y" /* yacc.c:1646  */
    {if(modisco->path==""){modisco->path=(yyvsp[0].TEXT);} (yyval.modiskk)=modisco;}
#line 1968 "parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 246 "sintactico.y" /* yacc.c:1646  */
    {if(modisco->namee==""){modisco->namee=(yyvsp[0].TEXT);} (yyval.modiskk)=modisco;}
#line 1974 "parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 247 "sintactico.y" /* yacc.c:1646  */
    {if(modisco->namee==""){modisco->namee=(yyvsp[0].TEXT);} (yyval.modiskk)=modisco;}
#line 1980 "parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 249 "sintactico.y" /* yacc.c:1646  */
    {if(unmdisco->id==""){unmdisco->id=(yyvsp[-1].TEXT);} (yyval.unmdiskk)=unmdisco;}
#line 1986 "parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 250 "sintactico.y" /* yacc.c:1646  */
    {if(unmdisco->id==""){unmdisco->id=(yyvsp[0].TEXT);} (yyval.unmdiskk)=unmdisco;}
#line 1992 "parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 252 "sintactico.y" /* yacc.c:1646  */
    {if(mkfsdisco->id==""){mkfsdisco->id=(yyvsp[-1].TEXT);} (yyval.mkdiskk)=mkfsdisco;}
#line 1998 "parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 253 "sintactico.y" /* yacc.c:1646  */
    {if(mkfsdisco->type==""){mkfsdisco->type=(yyvsp[-1].TEXT);} (yyval.mkdiskk)=mkfsdisco;}
#line 2004 "parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 254 "sintactico.y" /* yacc.c:1646  */
    {if(mkfsdisco->type==""){mkfsdisco->type=(yyvsp[-1].TEXT);} (yyval.mkdiskk)=mkfsdisco;}
#line 2010 "parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 255 "sintactico.y" /* yacc.c:1646  */
    {if(mkfsdisco->fs==""){mkfsdisco->fs=(yyvsp[-1].TEXT);} (yyval.mkdiskk)=mkfsdisco;}
#line 2016 "parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 256 "sintactico.y" /* yacc.c:1646  */
    {if(mkfsdisco->fs==""){mkfsdisco->fs=(yyvsp[-1].TEXT);} (yyval.mkdiskk)=mkfsdisco;}
#line 2022 "parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 257 "sintactico.y" /* yacc.c:1646  */
    {if(mkfsdisco->id==""){mkfsdisco->id=(yyvsp[0].TEXT);} (yyval.mkdiskk)=mkfsdisco;}
#line 2028 "parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 258 "sintactico.y" /* yacc.c:1646  */
    {if(mkfsdisco->type==""){mkfsdisco->type=(yyvsp[0].TEXT);} (yyval.mkdiskk)=mkfsdisco;}
#line 2034 "parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 259 "sintactico.y" /* yacc.c:1646  */
    {if(mkfsdisco->type==""){mkfsdisco->type=(yyvsp[0].TEXT);} (yyval.mkdiskk)=mkfsdisco;}
#line 2040 "parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 260 "sintactico.y" /* yacc.c:1646  */
    {if(mkfsdisco->fs==""){mkfsdisco->fs=(yyvsp[0].TEXT);} (yyval.mkdiskk)=mkfsdisco;}
#line 2046 "parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 261 "sintactico.y" /* yacc.c:1646  */
    {if(mkfsdisco->fs==""){mkfsdisco->fs=(yyvsp[0].TEXT);} (yyval.mkdiskk)=mkfsdisco;}
#line 2052 "parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 263 "sintactico.y" /* yacc.c:1646  */
    {if(script->path==""){script->path=(yyvsp[-1].TEXT);} (yyval.archexec)=script;}
#line 2058 "parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 264 "sintactico.y" /* yacc.c:1646  */
    {if(script->path==""){script->path=(yyvsp[-1].TEXT);} (yyval.archexec)=script;}
#line 2064 "parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 265 "sintactico.y" /* yacc.c:1646  */
    {if(script->path==""){script->path=(yyvsp[0].TEXT);} (yyval.archexec)=script;}
#line 2070 "parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 266 "sintactico.y" /* yacc.c:1646  */
    {if(script->path==""){script->path=(yyvsp[0].TEXT);} (yyval.archexec)=script;}
#line 2076 "parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 268 "sintactico.y" /* yacc.c:1646  */
    {if(reporte->path==""){reporte->path=(yyvsp[-1].TEXT);} (yyval.creporte)=reporte;}
#line 2082 "parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 269 "sintactico.y" /* yacc.c:1646  */
    {if(reporte->path==""){reporte->path=(yyvsp[-1].TEXT);} (yyval.creporte)=reporte;}
#line 2088 "parser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 270 "sintactico.y" /* yacc.c:1646  */
    {if(reporte->namee==""){reporte->namee=(yyvsp[-1].TEXT);} (yyval.creporte)=reporte;}
#line 2094 "parser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 271 "sintactico.y" /* yacc.c:1646  */
    {if(reporte->namee==""){reporte->namee=(yyvsp[-1].TEXT);} (yyval.creporte)=reporte;}
#line 2100 "parser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 272 "sintactico.y" /* yacc.c:1646  */
    {if(reporte->id==""){reporte->id=(yyvsp[-1].TEXT);} (yyval.creporte)=reporte;}
#line 2106 "parser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 273 "sintactico.y" /* yacc.c:1646  */
    {if(reporte->path==""){reporte->path=(yyvsp[0].TEXT);} (yyval.creporte)=reporte;}
#line 2112 "parser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 274 "sintactico.y" /* yacc.c:1646  */
    {if(reporte->path==""){reporte->path=(yyvsp[0].TEXT);} (yyval.creporte)=reporte;}
#line 2118 "parser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 275 "sintactico.y" /* yacc.c:1646  */
    {if(reporte->namee==""){reporte->namee=(yyvsp[0].TEXT);} (yyval.creporte)=reporte;}
#line 2124 "parser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 276 "sintactico.y" /* yacc.c:1646  */
    {if(reporte->namee==""){reporte->namee=(yyvsp[0].TEXT);} (yyval.creporte)=reporte;}
#line 2130 "parser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 277 "sintactico.y" /* yacc.c:1646  */
    {if(reporte->id==""){reporte->id=(yyvsp[0].TEXT);} (yyval.creporte)=reporte;}
#line 2136 "parser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 279 "sintactico.y" /* yacc.c:1646  */
    {if(loginn->usr==""){loginn->usr=(yyvsp[-1].TEXT);} (yyval.clogin)=loginn;}
#line 2142 "parser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 280 "sintactico.y" /* yacc.c:1646  */
    {if(loginn->usr==""){loginn->usr=(yyvsp[-1].TEXT);} (yyval.clogin)=loginn;}
#line 2148 "parser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 281 "sintactico.y" /* yacc.c:1646  */
    {if(loginn->pwd==""){loginn->pwd=(yyvsp[-1].TEXT);} (yyval.clogin)=loginn;}
#line 2154 "parser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 282 "sintactico.y" /* yacc.c:1646  */
    {if(loginn->pwd==""){loginn->pwd=(yyvsp[-1].TEXT);} (yyval.clogin)=loginn;}
#line 2160 "parser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 283 "sintactico.y" /* yacc.c:1646  */
    {if(loginn->pwd==""){loginn->pwd=(yyvsp[-1].TEXT);} (yyval.clogin)=loginn;}
#line 2166 "parser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 284 "sintactico.y" /* yacc.c:1646  */
    {if(loginn->id==""){loginn->id=(yyvsp[-1].TEXT);} (yyval.clogin)=loginn;}
#line 2172 "parser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 285 "sintactico.y" /* yacc.c:1646  */
    {if(loginn->usr==""){loginn->usr=(yyvsp[0].TEXT);} (yyval.clogin)=loginn;}
#line 2178 "parser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 286 "sintactico.y" /* yacc.c:1646  */
    {if(loginn->usr==""){loginn->usr=(yyvsp[0].TEXT);} (yyval.clogin)=loginn;}
#line 2184 "parser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 287 "sintactico.y" /* yacc.c:1646  */
    {if(loginn->pwd==""){loginn->pwd=(yyvsp[0].TEXT);} (yyval.clogin)=loginn;}
#line 2190 "parser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 288 "sintactico.y" /* yacc.c:1646  */
    {if(loginn->pwd==""){loginn->pwd=(yyvsp[0].TEXT);} (yyval.clogin)=loginn;}
#line 2196 "parser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 289 "sintactico.y" /* yacc.c:1646  */
    {if(loginn->pwd==""){loginn->pwd=(yyvsp[0].TEXT);} (yyval.clogin)=loginn;}
#line 2202 "parser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 290 "sintactico.y" /* yacc.c:1646  */
    {if(loginn->id==""){loginn->id=(yyvsp[0].TEXT);} (yyval.clogin)=loginn;}
#line 2208 "parser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 292 "sintactico.y" /* yacc.c:1646  */
    {if(mkgrpp->name==""){mkgrpp->name=(yyvsp[-1].TEXT);} (yyval.cmkgrp)=mkgrpp;}
#line 2214 "parser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 293 "sintactico.y" /* yacc.c:1646  */
    {if(mkgrpp->name==""){mkgrpp->name=(yyvsp[-1].TEXT);} (yyval.cmkgrp)=mkgrpp;}
#line 2220 "parser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 294 "sintactico.y" /* yacc.c:1646  */
    {if(mkgrpp->name==""){mkgrpp->name=(yyvsp[0].TEXT);} (yyval.cmkgrp)=mkgrpp;}
#line 2226 "parser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 295 "sintactico.y" /* yacc.c:1646  */
    {if(mkgrpp->name==""){mkgrpp->name=(yyvsp[0].TEXT);} (yyval.cmkgrp)=mkgrpp;}
#line 2232 "parser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 297 "sintactico.y" /* yacc.c:1646  */
    {if(rmgrpp->name==""){rmgrpp->name=(yyvsp[-1].TEXT);} (yyval.crmgrp)=rmgrpp;}
#line 2238 "parser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 298 "sintactico.y" /* yacc.c:1646  */
    {if(rmgrpp->name==""){rmgrpp->name=(yyvsp[-1].TEXT);} (yyval.crmgrp)=rmgrpp;}
#line 2244 "parser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 299 "sintactico.y" /* yacc.c:1646  */
    {if(rmgrpp->name==""){rmgrpp->name=(yyvsp[0].TEXT);} (yyval.crmgrp)=rmgrpp;}
#line 2250 "parser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 300 "sintactico.y" /* yacc.c:1646  */
    {if(rmgrpp->name==""){rmgrpp->name=(yyvsp[0].TEXT);} (yyval.crmgrp)=rmgrpp;}
#line 2256 "parser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 302 "sintactico.y" /* yacc.c:1646  */
    {if(mkuserr->usr==""){mkuserr->usr=(yyvsp[-1].TEXT);} (yyval.cmkuser)=mkuserr;}
#line 2262 "parser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 303 "sintactico.y" /* yacc.c:1646  */
    {if(mkuserr->usr==""){mkuserr->usr=(yyvsp[-1].TEXT);} (yyval.cmkuser)=mkuserr;}
#line 2268 "parser.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 304 "sintactico.y" /* yacc.c:1646  */
    {if(mkuserr->pwd==""){mkuserr->pwd=(yyvsp[-1].TEXT);} (yyval.cmkuser)=mkuserr;}
#line 2274 "parser.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 305 "sintactico.y" /* yacc.c:1646  */
    {if(mkuserr->pwd==""){mkuserr->pwd=(yyvsp[-1].TEXT);} (yyval.cmkuser)=mkuserr;}
#line 2280 "parser.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 306 "sintactico.y" /* yacc.c:1646  */
    {if(mkuserr->pwd==""){mkuserr->pwd=(yyvsp[-1].TEXT);} (yyval.cmkuser)=mkuserr;}
#line 2286 "parser.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 307 "sintactico.y" /* yacc.c:1646  */
    {if(mkuserr->pwd==""){mkuserr->pwd=(yyvsp[-1].TEXT);} (yyval.cmkuser)=mkuserr;}
#line 2292 "parser.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 308 "sintactico.y" /* yacc.c:1646  */
    {if(mkuserr->pwd==""){mkuserr->pwd=(yyvsp[-1].TEXT);} (yyval.cmkuser)=mkuserr;}
#line 2298 "parser.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 309 "sintactico.y" /* yacc.c:1646  */
    {if(mkuserr->usr==""){mkuserr->usr=(yyvsp[0].TEXT);} (yyval.cmkuser)=mkuserr;}
#line 2304 "parser.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 310 "sintactico.y" /* yacc.c:1646  */
    {if(mkuserr->usr==""){mkuserr->usr=(yyvsp[0].TEXT);} (yyval.cmkuser)=mkuserr;}
#line 2310 "parser.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 311 "sintactico.y" /* yacc.c:1646  */
    {if(mkuserr->pwd==""){mkuserr->pwd=(yyvsp[0].TEXT);} (yyval.cmkuser)=mkuserr;}
#line 2316 "parser.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 312 "sintactico.y" /* yacc.c:1646  */
    {if(mkuserr->pwd==""){mkuserr->pwd=(yyvsp[0].TEXT);} (yyval.cmkuser)=mkuserr;}
#line 2322 "parser.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 313 "sintactico.y" /* yacc.c:1646  */
    {if(mkuserr->pwd==""){mkuserr->pwd=(yyvsp[0].TEXT);} (yyval.cmkuser)=mkuserr;}
#line 2328 "parser.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 314 "sintactico.y" /* yacc.c:1646  */
    {if(mkuserr->pwd==""){mkuserr->pwd=(yyvsp[0].TEXT);} (yyval.cmkuser)=mkuserr;}
#line 2334 "parser.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 315 "sintactico.y" /* yacc.c:1646  */
    {if(mkuserr->pwd==""){mkuserr->pwd=(yyvsp[0].TEXT);} (yyval.cmkuser)=mkuserr;}
#line 2340 "parser.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 317 "sintactico.y" /* yacc.c:1646  */
    {if(rmuserr->usr==""){rmuserr->usr=(yyvsp[-1].TEXT);} (yyval.crmuser)=rmuserr;}
#line 2346 "parser.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 318 "sintactico.y" /* yacc.c:1646  */
    {if(rmuserr->usr==""){rmuserr->usr=(yyvsp[-1].TEXT);} (yyval.crmuser)=rmuserr;}
#line 2352 "parser.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 319 "sintactico.y" /* yacc.c:1646  */
    {if(rmuserr->usr==""){rmuserr->usr=(yyvsp[0].TEXT);} (yyval.crmuser)=rmuserr;}
#line 2358 "parser.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 320 "sintactico.y" /* yacc.c:1646  */
    {if(rmuserr->usr==""){rmuserr->usr=(yyvsp[0].TEXT);} (yyval.crmuser)=rmuserr;}
#line 2364 "parser.cpp" /* yacc.c:1646  */
    break;


#line 2368 "parser.cpp" /* yacc.c:1646  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
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
        yyerror (yymsgp);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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
                  yystos[yystate], yyvsp);
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
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
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
  return yyresult;
}
#line 323 "sintactico.y" /* yacc.c:1906  */

