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

    #include "cllogin.h"
    #include "clmkgrp.h"
    #include "clrmgrp.h"
    #include "clmkuser.h"
    #include "clrmuser.h"

    #include "clchmmod.h"
    #include "clmkfile.h"
    #include "clcat.h"
    #include "clrem.h"
    #include "cledit.h"
    #include "clren.h"
    #include "clmkdir.h"
    #include "clcp.h"
    #include "clmv.h"
    #include "clfind.h"
    #include "clchown.h"
    #include "clchgrp.h"

    #include "clexec.h"
    #include "clreportes.h"
    #include "clrecovery.h"
    #include "clloss.h"


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

    clchmmod *chmmodd = new clchmmod();
    clmkfile *mkfilee = new clmkfile();
    clcat *catt = new clcat();
    clrem *remm = new clrem();
    cledit *editt = new cledit();
    clRen *renn = new clRen();
    clmkdir *cmkdirr = new clmkdir();
    clcp *cpp = new clcp();
    clmv *mvv = new clmv();
    clfind *findd = new clfind();
    clchown *cchownn = new clchown();
    clchgrp *chgrpp = new clchgrp();

    clexec *script = new clexec();
    clReportes *reporte = new clReportes();
    clrecovery *recuperar = new clrecovery();
    clloss *perdida = new clloss();


    int yyerror(const char* mens){
        std::cout << mens << std::endl;
        return 0;
    }

#line 143 "parser.cpp" /* yacc.c:339  */

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
    rutaelim = 263,
    rutaarch = 264,
    rutacat = 265,
    ruta = 266,
    mkdisk = 267,
    rmdisk = 268,
    fdisk = 269,
    mount = 270,
    unmount = 271,
    mkfs = 272,
    login = 273,
    logout = 274,
    mkgrp = 275,
    rmgrp = 276,
    mkusr = 277,
    rmusr = 278,
    chmoddd = 279,
    mkfile = 280,
    cat = 281,
    rem = 282,
    edit = 283,
    ren = 284,
    mkdirr = 285,
    cp = 286,
    mv = 287,
    find = 288,
    chownn = 289,
    chgrp = 290,
    execc = 291,
    pausee = 292,
    comentario = 293,
    rep = 294,
    recovery = 295,
    loss = 296,
    igual = 297,
    dividido = 298,
    interrogacion = 299,
    multiplicacion = 300,
    negativo = 301,
    sizee = 302,
    f = 303,
    u = 304,
    pathh = 305,
    typee = 306,
    deletee = 307,
    namee = 308,
    addd = 309,
    id = 310,
    fs = 311,
    usr = 312,
    pwd = 313,
    grp = 314,
    ugo = 315,
    rr = 316,
    cont = 317,
    dest = 318,
    p = 319,
    file = 320,
    BF = 321,
    FF = 322,
    WF = 323,
    K = 324,
    M = 325,
    B = 326,
    PP = 327,
    E = 328,
    L = 329,
    FAST = 330,
    FULL = 331,
    FS2 = 332,
    FS3 = 333
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 80 "sintactico.y" /* yacc.c:355  */

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

    class clchmmod *cchmmod;
    class clmkfile *cmkfile;
    class clcat *ccat;
    class clrem *crem;
    class cledit *cedit;
    class clRen *cren;
    class clmkdir *cmkdir;
    class clcp *ccp;
    class clmv *cmv;
    class clfind *cfind;
    class clchown *cchown;
    class clchgrp *cchgrp;

    class clexec *archexec;
    class clReportes *creporte;
    class clrecovery *crecup;
    class clloss *cperd;

#line 296 "parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 313 "parser.cpp" /* yacc.c:358  */

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
#define YYFINAL  122
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   391

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  79
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  272
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  417

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   333

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
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   232,   232,   234,   235,   236,   237,   238,   239,   241,
     242,   243,   244,   245,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   260,   261,   262,   263,
     264,   265,   266,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   285,
     286,   287,   288,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,   327,
     328,   329,   330,   331,   332,   333,   334,   336,   337,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   350,
     351,   352,   353,   354,   355,   356,   357,   358,   359,   360,
     361,   363,   364,   365,   366,   368,   369,   370,   371,   373,
     374,   375,   376,   377,   378,   379,   380,   381,   382,   383,
     384,   385,   386,   388,   389,   390,   391,   393,   394,   395,
     396,   397,   398,   399,   400,   402,   403,   404,   405,   406,
     407,   408,   409,   410,   411,   412,   413,   414,   415,   416,
     417,   419,   420,   421,   422,   423,   424,   425,   426,   427,
     428,   429,   430,   432,   433,   434,   435,   436,   437,   439,
     440,   441,   442,   443,   444,   445,   446,   448,   449,   450,
     451,   452,   453,   455,   456,   457,   458,   459,   460,   462,
     463,   464,   465,   466,   467,   468,   469,   470,   471,   472,
     473,   475,   476,   477,   478,   479,   480,   481,   482,   483,
     484,   485,   486,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   499,   500,   501,   502,   503,   504,   505,
     506,   508,   509,   510,   511,   513,   514,   515,   516,   518,
     519,   520,   521,   522,   523,   524,   525,   526,   527,   529,
     530,   532,   533
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "digito", "ident", "cadena", "filen",
  "idp", "rutaelim", "rutaarch", "rutacat", "ruta", "mkdisk", "rmdisk",
  "fdisk", "mount", "unmount", "mkfs", "login", "logout", "mkgrp", "rmgrp",
  "mkusr", "rmusr", "chmoddd", "mkfile", "cat", "rem", "edit", "ren",
  "mkdirr", "cp", "mv", "find", "chownn", "chgrp", "execc", "pausee",
  "comentario", "rep", "recovery", "loss", "igual", "dividido",
  "interrogacion", "multiplicacion", "negativo", "sizee", "f", "u",
  "pathh", "typee", "deletee", "namee", "addd", "id", "fs", "usr", "pwd",
  "grp", "ugo", "rr", "cont", "dest", "p", "file", "BF", "FF", "WF", "K",
  "M", "B", "PP", "E", "L", "FAST", "FULL", "FS2", "FS3", "$accept",
  "INICIO", "COMANDOS", "COMMKDISK", "COMRMDISK", "COMFDISK", "COMMOUNT",
  "COMUNMOUNT", "COMFSDISK", "COMLOGIN", "COMMKGRP", "COMRMGRP",
  "COMMKUSER", "COMRMUSER", "COMCHMOD", "COMKFILE", "COMCAT", "COMREM",
  "COMEDIT", "COMREN", "COMMKDIR", "COMCP", "COMMV", "COMFIND", "COMCHOWN",
  "COMCHGRP", "COMEXEC", "COMREPORTE", "COMRECUP", "COMPERD", YY_NULLPTR
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
     325,   326,   327,   328,   329,   330,   331,   332,   333
};
# endif

#define YYPACT_NINF -194

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-194)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      19,   180,    31,    47,    30,   106,   157,    63,  -194,   115,
     148,   192,   158,    27,    14,    -2,   215,    12,   189,    15,
      22,    23,   190,    32,   221,   229,  -194,  -194,   161,   247,
     252,   310,  -194,   242,   270,   273,   274,  -194,   275,  -194,
     276,   278,   279,   280,   281,   282,   283,   285,  -194,   287,
     289,  -194,   291,  -194,   293,   294,   295,  -194,   296,   297,
     298,  -194,   299,  -194,   300,  -194,   301,   302,   303,  -194,
     304,  -194,   305,   306,    27,  -194,   307,   308,    14,   309,
      14,  -194,   311,   312,  -194,   313,  -194,   314,   315,  -194,
     316,   317,  -194,   318,    15,  -194,   319,   320,  -194,   321,
     322,  -194,   323,   324,  -194,   325,   326,    32,  -194,   327,
     328,  -194,   329,  -194,   330,   331,   332,  -194,   333,  -194,
     334,  -194,  -194,   349,   186,     1,    79,   130,   374,   191,
     193,   139,   194,    16,   174,    20,   140,   205,   371,   171,
     372,   178,   373,   256,   266,   277,   284,   286,   269,   288,
     290,   141,   378,  -194,    21,   142,  -194,   143,  -194,   112,
     114,   121,   144,   151,   152,   375,   236,  -194,   122,   123,
     131,   132,   153,    25,   240,   379,  -194,   381,   382,   154,
     155,   292,   380,   383,   384,   180,   180,   180,   180,   180,
     180,   180,   180,    31,    31,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,   385,    30,    30,    30,    30,   106,   157,   157,
     157,   157,   157,    63,    63,    63,    63,    63,    63,   115,
     115,   148,   148,   192,   192,   192,   192,   192,   192,   192,
     158,   158,    27,    27,    27,    14,   386,    14,    14,    14,
      14,    -2,    -2,    -2,    -2,    -2,    -2,   215,   215,   215,
      12,    12,    12,    12,   189,   189,   189,    15,    15,    22,
      22,    22,    22,    22,    22,    23,    23,    23,    23,    23,
      23,   190,   190,   190,   190,   190,    32,    32,    32,   221,
     221,   229,   229,   161,   161,   161,   161,   161,   247,   252,
    -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,
    -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,
    -194,  -194,  -194,  -194,  -194,  -194,  -194,    47,  -194,  -194,
    -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,
    -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,
    -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,
    -194,    14,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,
    -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,
    -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,
    -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,
    -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,
    -194,  -194,  -194,  -194,  -194,  -194,  -194
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,    30,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    31,    32,     0,     0,
       0,     0,     2,     0,     0,     0,     0,     3,     0,     4,
       0,     0,     0,     0,     0,     0,     0,     0,     5,     0,
       0,     6,     0,     7,     0,     0,     0,     8,     0,     0,
       0,     9,     0,    10,     0,    11,     0,     0,     0,    12,
       0,    13,     0,     0,   154,    14,     0,     0,   167,     0,
     168,    15,     0,     0,    16,     0,    17,     0,     0,    18,
       0,     0,    19,     0,   208,    20,     0,     0,    21,     0,
       0,    22,     0,     0,    23,     0,     0,   249,    24,     0,
       0,    25,     0,    26,     0,     0,     0,    27,     0,    28,
       0,    29,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   150,     0,     0,   159,     0,   160,     0,
       0,     0,     0,     0,     0,     0,     0,   205,     0,     0,
       0,     0,     0,     0,     0,     0,   245,     0,     0,     0,
       0,     0,     0,     0,     0,    41,    42,    43,    44,    45,
      46,    47,    48,    51,    52,    71,    80,    81,    82,    72,
      73,    74,    75,    76,    77,    78,    79,    83,    84,    86,
      85,    87,     0,    93,    94,    96,    95,    98,   105,   106,
     104,   107,   108,   120,   116,   115,   117,   119,   118,   124,
     123,   128,   127,   137,   136,   138,   140,   139,   142,   141,
     146,   145,   151,   152,   153,   165,     0,   163,   164,   169,
     170,   177,   179,   178,   180,   182,   181,   186,   187,   188,
     193,   194,   195,   196,   200,   201,   202,   206,   207,   215,
     216,   217,   218,   219,   220,   227,   228,   229,   230,   231,
     232,   238,   239,   242,   240,   241,   247,   248,   250,   253,
     254,   257,   258,   264,   265,   267,   266,   268,   270,   272,
      33,    34,    35,    36,    37,    38,    39,    40,    49,    50,
      53,    62,    63,    64,    54,    55,    56,    57,    58,    59,
      60,    61,    65,    66,    68,    67,    69,    88,    89,    90,
      92,    91,    97,   100,   101,    99,   102,   103,   114,   110,
     109,   111,   113,   112,   122,   121,   126,   125,   130,   129,
     133,   132,   131,   135,   134,   144,   143,   147,   148,   149,
     157,   166,   155,   156,   161,   162,   171,   173,   172,   174,
     176,   175,   183,   184,   185,   189,   190,   191,   192,   197,
     198,   199,   203,   204,   209,   210,   211,   212,   213,   214,
     221,   222,   223,   224,   225,   226,   233,   234,   237,   235,
     236,   243,   244,   246,   251,   252,   255,   256,   259,   260,
     262,   261,   263,   269,   271,    70,   158
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -194,  -194,  -194,   -83,   105,  -189,    18,    94,  -193,   -40,
      71,    72,  -123,    65,   -69,   -78,   -62,    28,   -25,    11,
     -91,   -74,   -73,   -64,  -106,    24,    17,   -71,    34,    29
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    31,    32,    37,    39,    48,    51,    53,    57,    61,
      63,    65,    69,    71,    75,    81,    84,    86,    89,    92,
      95,    98,   101,   104,   108,   111,   113,   117,   119,   121
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
     156,   176,   158,   167,    82,   153,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   211,   245,   333,   334,   335,   336,   337,
     283,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    76,    87,    83,    77,    93,   212,   246,   284,   285,
     189,   190,    96,    99,    88,    78,    79,    72,    80,    94,
      49,    38,   105,    50,   191,    97,   100,    73,    74,   106,
     192,   207,   208,   107,    40,    41,    42,    43,    44,    45,
      46,    47,   300,   301,   302,   303,   304,   305,   306,   307,
     348,   349,   350,   351,   352,   353,   354,   251,    58,   254,
      59,    60,   252,   253,   255,   256,   257,   269,   272,   258,
     270,   273,   259,   271,   274,   193,   275,   278,   415,   276,
     279,   194,   277,   280,   202,   213,   242,   247,   249,   260,
     203,   214,   243,   248,   250,   261,   262,   264,   281,   291,
     293,    52,   263,   265,   282,   292,   294,   360,    62,   362,
     363,   364,   365,   357,   358,   359,   382,   383,   209,   210,
     401,   402,   403,   338,   339,   340,   341,   342,   343,   366,
     367,   368,   369,   370,   371,   384,   385,   386,   387,   388,
     389,    64,   390,   391,   392,   393,   394,   395,    54,   215,
     216,   114,    55,    56,   115,    70,   116,   396,   397,   398,
     399,   400,   408,   409,   410,   411,   412,    33,    34,    35,
      36,   328,   329,   330,   331,   375,   376,   377,   378,    90,
     102,   267,    91,   103,   268,   286,   218,   219,   287,    66,
      67,    68,   186,   187,   188,   221,   222,   196,   197,   198,
     224,   225,   199,   200,   201,    85,   204,   205,   206,   226,
     227,   228,   235,   236,   237,   379,   380,   381,   109,   112,
     110,   229,   230,   416,   123,   372,   373,   374,   231,   232,
     233,   234,   238,   239,   240,   241,   295,   296,   308,   309,
     344,   345,   118,   346,   347,   355,   356,   120,   406,   407,
     122,   332,   124,   404,   405,   125,   126,   127,   128,     0,
     129,   130,   131,   132,   133,   134,     0,   135,   414,   136,
       0,   137,   413,   138,     0,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   154,
     155,   157,   185,   159,   160,   161,   162,   163,   164,   165,
     166,   168,   169,   170,   171,   172,   173,   174,   175,   177,
     178,   179,   180,   181,   182,   183,   184,   195,   217,   220,
     223,   244,     0,   288,   266,   289,   290,   297,   327,   361,
     298,   299
};

static const yytype_int16 yycheck[] =
{
      78,   107,    80,    94,     6,    74,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,     3,     3,   218,   219,   220,   221,   222,
       5,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    47,    50,    65,    50,    50,    46,    46,    43,    44,
      69,    70,    50,    50,    62,    61,    62,    50,    64,    64,
      50,    50,    50,    53,     5,    63,    63,    60,    61,    57,
      11,    75,    76,    61,    47,    48,    49,    50,    51,    52,
      53,    54,   185,   186,   187,   188,   189,   190,   191,   192,
     233,   234,   235,   236,   237,   238,   239,     5,    55,     5,
      57,    58,    10,    11,    10,    11,     5,     5,     5,     8,
       8,     8,    11,    11,    11,     5,     5,     5,   327,     8,
       8,    11,    11,    11,     5,     5,     5,     5,     5,     5,
      11,    11,    11,    11,    11,    11,     5,     5,     5,     5,
       5,    55,    11,    11,    11,    11,    11,   245,    53,   247,
     248,   249,   250,   242,   243,   244,   267,   268,     4,     5,
     286,   287,   288,   223,   224,   225,   226,   227,   228,   251,
     252,   253,   254,   255,   256,   269,   270,   271,   272,   273,
     274,    53,   275,   276,   277,   278,   279,   280,    51,     4,
       5,    50,    55,    56,    53,    57,    55,   281,   282,   283,
     284,   285,   293,   294,   295,   296,   297,    47,    48,    49,
      50,   213,   214,   215,   216,   260,   261,   262,   263,    50,
      50,     5,    53,    53,     8,     5,    75,    76,     8,    57,
      58,    59,    66,    67,    68,    77,    78,    66,    67,    68,
       4,     5,    69,    70,    71,    50,    72,    73,    74,     3,
       4,     5,     3,     4,     5,   264,   265,   266,    57,    50,
      59,     4,     5,   361,    42,   257,   258,   259,     4,     5,
       4,     5,     4,     5,     4,     5,     4,     5,   193,   194,
     229,   230,    55,   231,   232,   240,   241,    55,   291,   292,
       0,   217,    42,   289,   290,    42,    42,    42,    42,    -1,
      42,    42,    42,    42,    42,    42,    -1,    42,   299,    42,
      -1,    42,   298,    42,    -1,    42,    42,    42,    42,    42,
      42,    42,    42,    42,    42,    42,    42,    42,    42,    42,
      42,    42,     3,    42,    42,    42,    42,    42,    42,    42,
      42,    42,    42,    42,    42,    42,    42,    42,    42,    42,
      42,    42,    42,    42,    42,    42,    42,     3,     7,     7,
       7,     3,    -1,     4,     9,     4,     4,     7,     3,     3,
       7,     7
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    80,    81,    47,    48,    49,    50,    82,    50,    83,
      47,    48,    49,    50,    51,    52,    53,    54,    84,    50,
      53,    85,    55,    86,    51,    55,    56,    87,    55,    57,
      58,    88,    53,    89,    53,    90,    57,    58,    59,    91,
      57,    92,    50,    60,    61,    93,    47,    50,    61,    62,
      64,    94,     6,    65,    95,    50,    96,    50,    62,    97,
      50,    53,    98,    50,    64,    99,    50,    63,   100,    50,
      63,   101,    50,    53,   102,    50,    57,    61,   103,    57,
      59,   104,    50,   105,    50,    53,    55,   106,    55,   107,
      55,   108,     0,    42,    42,    42,    42,    42,    42,    42,
      42,    42,    42,    42,    42,    42,    42,    42,    42,    42,
      42,    42,    42,    42,    42,    42,    42,    42,    42,    42,
      42,    42,    42,    93,    42,    42,    94,    42,    94,    42,
      42,    42,    42,    42,    42,    42,    42,    99,    42,    42,
      42,    42,    42,    42,    42,    42,   103,    42,    42,    42,
      42,    42,    42,    42,    42,     3,    66,    67,    68,    69,
      70,     5,    11,     5,    11,     3,    66,    67,    68,    69,
      70,    71,     5,    11,    72,    73,    74,    75,    76,     4,
       5,     3,    46,     5,    11,     4,     5,     7,    75,    76,
       7,    77,    78,     7,     4,     5,     3,     4,     5,     4,
       5,     4,     5,     4,     5,     3,     4,     5,     4,     5,
       4,     5,     5,    11,     3,     3,    46,     5,    11,     5,
      11,     5,    10,    11,     5,    10,    11,     5,     8,    11,
       5,    11,     5,    11,     5,    11,     9,     5,     8,     5,
       8,    11,     5,     8,    11,     5,     8,    11,     5,     8,
      11,     5,    11,     5,    43,    44,     5,     8,     4,     4,
       4,     5,    11,     5,    11,     4,     5,     7,     7,     7,
      82,    82,    82,    82,    82,    82,    82,    82,    83,    83,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,     3,    85,    85,
      85,    85,    86,    87,    87,    87,    87,    87,    88,    88,
      88,    88,    88,    88,    89,    89,    90,    90,    91,    91,
      91,    91,    91,    91,    91,    92,    92,    93,    93,    93,
      94,     3,    94,    94,    94,    94,    95,    95,    95,    95,
      95,    95,    96,    96,    96,    97,    97,    97,    97,    98,
      98,    98,    99,    99,   100,   100,   100,   100,   100,   100,
     101,   101,   101,   101,   101,   101,   102,   102,   102,   102,
     102,   103,   103,   103,   104,   104,   105,   105,   106,   106,
     106,   106,   106,   107,   108,    84,    94
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    79,    80,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    83,
      83,    83,    83,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    85,
      85,    85,    85,    85,    85,    85,    85,    86,    86,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    89,    89,    89,    89,    90,    90,    90,    90,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    92,    92,    92,    92,    93,    93,    93,
      93,    93,    93,    93,    93,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    96,    96,    96,    96,    96,    96,    97,
      97,    97,    97,    97,    97,    97,    97,    98,    98,    98,
      98,    98,    98,    99,    99,    99,    99,    99,    99,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   103,   103,   103,   103,   103,   103,   103,
     103,   104,   104,   104,   104,   105,   105,   105,   105,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   107,
     107,   108,   108
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       1,     1,     1,     4,     4,     4,     4,     4,     4,     4,
       4,     3,     3,     3,     3,     3,     3,     3,     3,     4,
       4,     3,     3,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       5,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     4,     4,
       4,     4,     4,     3,     3,     3,     3,     4,     3,     4,
       4,     4,     4,     4,     3,     3,     3,     3,     3,     4,
       4,     4,     4,     4,     4,     3,     3,     3,     3,     3,
       3,     4,     4,     3,     3,     4,     4,     3,     3,     4,
       4,     4,     4,     4,     4,     4,     3,     3,     3,     3,
       3,     3,     3,     4,     4,     3,     3,     4,     4,     4,
       2,     3,     3,     3,     1,     4,     4,     4,     5,     2,
       2,     4,     4,     3,     3,     3,     4,     1,     1,     3,
       3,     4,     4,     4,     4,     4,     4,     3,     3,     3,
       3,     3,     3,     4,     4,     4,     3,     3,     3,     4,
       4,     4,     4,     3,     3,     3,     3,     4,     4,     4,
       3,     3,     3,     4,     4,     2,     3,     3,     1,     4,
       4,     4,     4,     4,     4,     3,     3,     3,     3,     3,
       3,     4,     4,     4,     4,     4,     4,     3,     3,     3,
       3,     3,     3,     4,     4,     4,     4,     4,     3,     3,
       3,     3,     3,     4,     4,     2,     4,     3,     3,     1,
       3,     4,     4,     3,     3,     4,     4,     3,     3,     4,
       4,     4,     4,     4,     3,     3,     3,     3,     3,     4,
       3,     4,     3
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
#line 232 "sintactico.y" /* yacc.c:1646  */
    { }
#line 1692 "parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 234 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].mdisk)->mostrarDatos((yyvsp[0].mdisk)); cout<<"Comando MKDISK"<<endl;}
#line 1698 "parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 235 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].mrdiskk)->mostrarDatos((yyvsp[0].mrdiskk)); cout<<"Comando RMDISK"<<endl;}
#line 1704 "parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 236 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].fdiskk)->mostrarDatos((yyvsp[0].fdiskk)); cout<<"Comando FDISK"<<endl;}
#line 1710 "parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 237 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].modiskk)->mostrarDatos((yyvsp[0].modiskk)); cout<<"Comando MOUNT"<<endl;}
#line 1716 "parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 238 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].unmdiskk)->mostrarDatos((yyvsp[0].unmdiskk)); cout<<"Comando UNMOUNT"<<endl;}
#line 1722 "parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 239 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].mkdiskk)->mostrarDatos((yyvsp[0].mkdiskk)); cout<<"Comando MKFS"<<endl;}
#line 1728 "parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 241 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].clogin)->logear((yyvsp[0].clogin));       cout<<"Comando LOGIN"<<endl;}
#line 1734 "parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 242 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].cmkgrp)->mostrarDatos((yyvsp[0].cmkgrp)); cout<<"Comando MKGRP"<<endl;}
#line 1740 "parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 243 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].crmgrp)->mostrarDatos((yyvsp[0].crmgrp)); cout<<"Comando RMGRP"<<endl;}
#line 1746 "parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 244 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].cmkuser)->mostrarDatos((yyvsp[0].cmkuser)); cout<<"Comando MKUSER"<<endl;}
#line 1752 "parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 245 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].crmuser)->mostrarDatos((yyvsp[0].crmuser)); cout<<"Comando RMUSER"<<endl;}
#line 1758 "parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 247 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].cchmmod)->mostrarDatos((yyvsp[0].cchmmod)); cout<<"Comando CHMOD"<<endl;}
#line 1764 "parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 248 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].cmkfile)->mostrarDatos((yyvsp[0].cmkfile)); cout<<"Comando MKFILE"<<endl;}
#line 1770 "parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 249 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].ccat)->mostrarDatos((yyvsp[0].ccat)); cout<<"Comando CAT"<<endl;}
#line 1776 "parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 250 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].crem)->mostrarDatos((yyvsp[0].crem)); cout<<"Comando REM"<<endl;}
#line 1782 "parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 251 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].cedit)->mostrarDatos((yyvsp[0].cedit)); cout<<"Comando EDIT"<<endl;}
#line 1788 "parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 252 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].cren)->mostrarDatos((yyvsp[0].cren)); cout<<"Comando REN"<<endl;}
#line 1794 "parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 253 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].cmkdir)->mostrarDatos((yyvsp[0].cmkdir)); cout<<"Comando MKDIR"<<endl;}
#line 1800 "parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 254 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].ccp)->mostrarDatos((yyvsp[0].ccp)); cout<<"Comando CP"<<endl;}
#line 1806 "parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 255 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].cmv)->mostrarDatos((yyvsp[0].cmv)); cout<<"Comando MV"<<endl;}
#line 1812 "parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 256 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].cfind)->mostrarDatos((yyvsp[0].cfind)); cout<<"Comando FIND"<<endl;}
#line 1818 "parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 257 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].cchown)->mostrarDatos((yyvsp[0].cchown)); cout<<"Comando CHOWN"<<endl;}
#line 1824 "parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 258 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].cchgrp)->mostrarDatos((yyvsp[0].cchgrp)); cout<<"Comando CHGRP"<<endl;}
#line 1830 "parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 260 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].archexec)->mostrarDatos((yyvsp[0].archexec)); cout<<"Comando EXEC"<<endl;}
#line 1836 "parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 261 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].creporte)->mostrarDatos((yyvsp[0].creporte)); cout<<"Comando REPORTE"<<endl;}
#line 1842 "parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 262 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].crecup)->mostrarDatos((yyvsp[0].crecup)); cout<<"Comando RECOVERY"<<endl;}
#line 1848 "parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 263 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].cperd)->mostrarDatos((yyvsp[0].cperd)); cout<<"Comando LOSS"<<endl;}
#line 1854 "parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 264 "sintactico.y" /* yacc.c:1646  */
    {(yyvsp[0].clogin)->salir();          cout<<"Comando LOGOUT"<<endl;}
#line 1860 "parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 265 "sintactico.y" /* yacc.c:1646  */
    {cout<<"Ingrese una tecla para continuar"<<endl; cin.get();}
#line 1866 "parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 266 "sintactico.y" /* yacc.c:1646  */
    {}
#line 1872 "parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 268 "sintactico.y" /* yacc.c:1646  */
    {int tam=atoi((yyvsp[-1].TEXT)); if(mkdisco->size==0){mkdisco->size=tam;} (yyval.mdisk)=mkdisco;}
#line 1878 "parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 269 "sintactico.y" /* yacc.c:1646  */
    {if(mkdisco->f==""){mkdisco->f=(yyvsp[-1].TEXT);} (yyval.mdisk)=mkdisco;}
#line 1884 "parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 270 "sintactico.y" /* yacc.c:1646  */
    {if(mkdisco->f==""){mkdisco->f=(yyvsp[-1].TEXT);} (yyval.mdisk)=mkdisco;}
#line 1890 "parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 271 "sintactico.y" /* yacc.c:1646  */
    {if(mkdisco->f==""){mkdisco->f=(yyvsp[-1].TEXT);} (yyval.mdisk)=mkdisco;}
#line 1896 "parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 272 "sintactico.y" /* yacc.c:1646  */
    {if(mkdisco->u==""){mkdisco->u=(yyvsp[-1].TEXT);} (yyval.mdisk)=mkdisco;}
#line 1902 "parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 273 "sintactico.y" /* yacc.c:1646  */
    {if(mkdisco->u==""){mkdisco->u=(yyvsp[-1].TEXT);} (yyval.mdisk)=mkdisco;}
#line 1908 "parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 274 "sintactico.y" /* yacc.c:1646  */
    {if(mkdisco->path==""){mkdisco->path=(yyvsp[-1].TEXT);} (yyval.mdisk)=mkdisco;}
#line 1914 "parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 275 "sintactico.y" /* yacc.c:1646  */
    {if(mkdisco->path==""){mkdisco->path=(yyvsp[-1].TEXT);} (yyval.mdisk)=mkdisco;}
#line 1920 "parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 276 "sintactico.y" /* yacc.c:1646  */
    {int tam=atoi((yyvsp[0].TEXT)); if(mkdisco->size!=0){mkdisco->size=tam;} (yyval.mdisk)=mkdisco;}
#line 1926 "parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 277 "sintactico.y" /* yacc.c:1646  */
    {if(mkdisco->f==""){mkdisco->f=(yyvsp[0].TEXT);} (yyval.mdisk)=mkdisco;}
#line 1932 "parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 278 "sintactico.y" /* yacc.c:1646  */
    {if(mkdisco->f==""){mkdisco->f=(yyvsp[0].TEXT);} (yyval.mdisk)=mkdisco;}
#line 1938 "parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 279 "sintactico.y" /* yacc.c:1646  */
    {if(mkdisco->f==""){mkdisco->f=(yyvsp[0].TEXT);} (yyval.mdisk)=mkdisco;}
#line 1944 "parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 280 "sintactico.y" /* yacc.c:1646  */
    {if(mkdisco->u==""){mkdisco->u=(yyvsp[0].TEXT);} (yyval.mdisk)=mkdisco;}
#line 1950 "parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 281 "sintactico.y" /* yacc.c:1646  */
    {if(mkdisco->u==""){mkdisco->u=(yyvsp[0].TEXT);} (yyval.mdisk)=mkdisco;}
#line 1956 "parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 282 "sintactico.y" /* yacc.c:1646  */
    {if(mkdisco->path==""){mkdisco->path=(yyvsp[0].TEXT);} (yyval.mdisk)=mkdisco;}
#line 1962 "parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 283 "sintactico.y" /* yacc.c:1646  */
    {if(mkdisco->path==""){mkdisco->path=(yyvsp[0].TEXT);} (yyval.mdisk)=mkdisco;}
#line 1968 "parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 285 "sintactico.y" /* yacc.c:1646  */
    {if(rmdisco->path==""){rmdisco->path=(yyvsp[-1].TEXT);} (yyval.mrdiskk)=rmdisco;}
#line 1974 "parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 286 "sintactico.y" /* yacc.c:1646  */
    {if(rmdisco->path==""){rmdisco->path=(yyvsp[-1].TEXT);} (yyval.mrdiskk)=rmdisco;}
#line 1980 "parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 287 "sintactico.y" /* yacc.c:1646  */
    {if(rmdisco->path==""){rmdisco->path=(yyvsp[0].TEXT);} (yyval.mrdiskk)=rmdisco;}
#line 1986 "parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 288 "sintactico.y" /* yacc.c:1646  */
    {if(rmdisco->path==""){rmdisco->path=(yyvsp[0].TEXT);} (yyval.mrdiskk)=rmdisco;}
#line 1992 "parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 290 "sintactico.y" /* yacc.c:1646  */
    {int tam=atoi((yyvsp[-1].TEXT)); if(ffdisco->primero==""){ffdisco->primero="s";} if(ffdisco->size==0){ffdisco->size=tam;} (yyval.fdiskk)=ffdisco;}
#line 1998 "parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 291 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->u==""){ffdisco->u=(yyvsp[-1].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 2004 "parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 292 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->u==""){ffdisco->u=(yyvsp[-1].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 2010 "parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 293 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->u==""){ffdisco->u=(yyvsp[-1].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 2016 "parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 294 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->path==""){ffdisco->path=(yyvsp[-1].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 2022 "parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 295 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->path==""){ffdisco->path=(yyvsp[-1].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 2028 "parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 296 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->typee==""){ffdisco->typee=(yyvsp[-1].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 2034 "parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 297 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->typee==""){ffdisco->typee=(yyvsp[-1].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 2040 "parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 298 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->typee==""){ffdisco->typee=(yyvsp[-1].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 2046 "parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 299 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->f==""){ffdisco->f=(yyvsp[-1].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 2052 "parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 300 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->f==""){ffdisco->f=(yyvsp[-1].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 2058 "parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 301 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->f==""){ffdisco->f=(yyvsp[-1].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 2064 "parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 302 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->deletee==""){ffdisco->deletee=(yyvsp[-1].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 2070 "parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 303 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->deletee==""){ffdisco->deletee=(yyvsp[-1].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 2076 "parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 304 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->namee==""){ffdisco->namee=(yyvsp[-1].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 2082 "parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 305 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->namee==""){ffdisco->namee=(yyvsp[-1].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 2088 "parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 306 "sintactico.y" /* yacc.c:1646  */
    {int tam=atoi((yyvsp[-1].TEXT)); if(ffdisco->primero==""){ffdisco->primero="a";} if(ffdisco->addd==0){ffdisco->addd=tam;} (yyval.fdiskk)=ffdisco;}
#line 2094 "parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 307 "sintactico.y" /* yacc.c:1646  */
    {int tam=atoi((yyvsp[-1].TEXT)); if(ffdisco->primero==""){ffdisco->primero="a";} if(ffdisco->addd==0){ffdisco->addd=tam * -1;} (yyval.fdiskk)=ffdisco;}
#line 2100 "parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 308 "sintactico.y" /* yacc.c:1646  */
    {int tam=atoi((yyvsp[0].TEXT)); if(ffdisco->primero==""){ffdisco->primero="s";} if(ffdisco->size==0){ffdisco->size=tam;} (yyval.fdiskk)=ffdisco;}
#line 2106 "parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 309 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->u==""){ffdisco->u=(yyvsp[0].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 2112 "parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 310 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->u==""){ffdisco->u=(yyvsp[0].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 2118 "parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 311 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->u==""){ffdisco->u=(yyvsp[0].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 2124 "parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 312 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->path==""){ffdisco->path=(yyvsp[0].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 2130 "parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 313 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->path==""){ffdisco->path=(yyvsp[0].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 2136 "parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 314 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->typee==""){ffdisco->typee=(yyvsp[0].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 2142 "parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 315 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->typee==""){ffdisco->typee=(yyvsp[0].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 2148 "parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 316 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->typee==""){ffdisco->typee=(yyvsp[0].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 2154 "parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 317 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->f==""){ffdisco->f=(yyvsp[0].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 2160 "parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 318 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->f==""){ffdisco->f=(yyvsp[0].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 2166 "parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 319 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->f==""){ffdisco->f=(yyvsp[0].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 2172 "parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 320 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->deletee==""){ffdisco->deletee=(yyvsp[0].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 2178 "parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 321 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->deletee==""){ffdisco->deletee=(yyvsp[0].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 2184 "parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 322 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->namee==""){ffdisco->namee=(yyvsp[0].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 2190 "parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 323 "sintactico.y" /* yacc.c:1646  */
    {if(ffdisco->namee==""){ffdisco->namee=(yyvsp[0].TEXT);} (yyval.fdiskk)=ffdisco;}
#line 2196 "parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 324 "sintactico.y" /* yacc.c:1646  */
    {int tam=atoi((yyvsp[0].TEXT)); if(ffdisco->primero==""){ffdisco->primero="a";} if(ffdisco->addd==0){ffdisco->addd=tam;} (yyval.fdiskk)=ffdisco;}
#line 2202 "parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 325 "sintactico.y" /* yacc.c:1646  */
    {int tam=atoi((yyvsp[0].TEXT)); if(ffdisco->primero==""){ffdisco->primero="a";} if(ffdisco->addd==0){ffdisco->addd=tam * -1;} (yyval.fdiskk)=ffdisco;}
#line 2208 "parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 327 "sintactico.y" /* yacc.c:1646  */
    {if(modisco->path==""){modisco->path=(yyvsp[-1].TEXT);} (yyval.modiskk)=modisco;}
#line 2214 "parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 328 "sintactico.y" /* yacc.c:1646  */
    {if(modisco->path==""){modisco->path=(yyvsp[-1].TEXT);} (yyval.modiskk)=modisco;}
#line 2220 "parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 329 "sintactico.y" /* yacc.c:1646  */
    {if(modisco->namee==""){modisco->namee=(yyvsp[-1].TEXT);} (yyval.modiskk)=modisco;}
#line 2226 "parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 330 "sintactico.y" /* yacc.c:1646  */
    {if(modisco->namee==""){modisco->namee=(yyvsp[-1].TEXT);} (yyval.modiskk)=modisco;}
#line 2232 "parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 331 "sintactico.y" /* yacc.c:1646  */
    {if(modisco->path==""){modisco->path=(yyvsp[0].TEXT);} (yyval.modiskk)=modisco;}
#line 2238 "parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 332 "sintactico.y" /* yacc.c:1646  */
    {if(modisco->path==""){modisco->path=(yyvsp[0].TEXT);} (yyval.modiskk)=modisco;}
#line 2244 "parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 333 "sintactico.y" /* yacc.c:1646  */
    {if(modisco->namee==""){modisco->namee=(yyvsp[0].TEXT);} (yyval.modiskk)=modisco;}
#line 2250 "parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 334 "sintactico.y" /* yacc.c:1646  */
    {if(modisco->namee==""){modisco->namee=(yyvsp[0].TEXT);} (yyval.modiskk)=modisco;}
#line 2256 "parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 336 "sintactico.y" /* yacc.c:1646  */
    {if(unmdisco->id==""){unmdisco->id=(yyvsp[-1].TEXT);} (yyval.unmdiskk)=unmdisco;}
#line 2262 "parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 337 "sintactico.y" /* yacc.c:1646  */
    {if(unmdisco->id==""){unmdisco->id=(yyvsp[0].TEXT);} (yyval.unmdiskk)=unmdisco;}
#line 2268 "parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 339 "sintactico.y" /* yacc.c:1646  */
    {if(mkfsdisco->id==""){mkfsdisco->id=(yyvsp[-1].TEXT);} (yyval.mkdiskk)=mkfsdisco;}
#line 2274 "parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 340 "sintactico.y" /* yacc.c:1646  */
    {if(mkfsdisco->type==""){mkfsdisco->type=(yyvsp[-1].TEXT);} (yyval.mkdiskk)=mkfsdisco;}
#line 2280 "parser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 341 "sintactico.y" /* yacc.c:1646  */
    {if(mkfsdisco->type==""){mkfsdisco->type=(yyvsp[-1].TEXT);} (yyval.mkdiskk)=mkfsdisco;}
#line 2286 "parser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 342 "sintactico.y" /* yacc.c:1646  */
    {if(mkfsdisco->fs==""){mkfsdisco->fs=(yyvsp[-1].TEXT);} (yyval.mkdiskk)=mkfsdisco;}
#line 2292 "parser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 343 "sintactico.y" /* yacc.c:1646  */
    {if(mkfsdisco->fs==""){mkfsdisco->fs=(yyvsp[-1].TEXT);} (yyval.mkdiskk)=mkfsdisco;}
#line 2298 "parser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 344 "sintactico.y" /* yacc.c:1646  */
    {if(mkfsdisco->id==""){mkfsdisco->id=(yyvsp[0].TEXT);} (yyval.mkdiskk)=mkfsdisco;}
#line 2304 "parser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 345 "sintactico.y" /* yacc.c:1646  */
    {if(mkfsdisco->type==""){mkfsdisco->type=(yyvsp[0].TEXT);} (yyval.mkdiskk)=mkfsdisco;}
#line 2310 "parser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 346 "sintactico.y" /* yacc.c:1646  */
    {if(mkfsdisco->type==""){mkfsdisco->type=(yyvsp[0].TEXT);} (yyval.mkdiskk)=mkfsdisco;}
#line 2316 "parser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 347 "sintactico.y" /* yacc.c:1646  */
    {if(mkfsdisco->fs==""){mkfsdisco->fs=(yyvsp[0].TEXT);} (yyval.mkdiskk)=mkfsdisco;}
#line 2322 "parser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 348 "sintactico.y" /* yacc.c:1646  */
    {if(mkfsdisco->fs==""){mkfsdisco->fs=(yyvsp[0].TEXT);} (yyval.mkdiskk)=mkfsdisco;}
#line 2328 "parser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 350 "sintactico.y" /* yacc.c:1646  */
    {if(loginn->usr==""){loginn->usr=(yyvsp[-1].TEXT);} (yyval.clogin)=loginn;}
#line 2334 "parser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 351 "sintactico.y" /* yacc.c:1646  */
    {if(loginn->usr==""){loginn->usr=(yyvsp[-1].TEXT);} (yyval.clogin)=loginn;}
#line 2340 "parser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 352 "sintactico.y" /* yacc.c:1646  */
    {if(loginn->pwd==""){loginn->pwd=(yyvsp[-1].TEXT);} (yyval.clogin)=loginn;}
#line 2346 "parser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 353 "sintactico.y" /* yacc.c:1646  */
    {if(loginn->pwd==""){loginn->pwd=(yyvsp[-1].TEXT);} (yyval.clogin)=loginn;}
#line 2352 "parser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 354 "sintactico.y" /* yacc.c:1646  */
    {if(loginn->pwd==""){loginn->pwd=(yyvsp[-1].TEXT);} (yyval.clogin)=loginn;}
#line 2358 "parser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 355 "sintactico.y" /* yacc.c:1646  */
    {if(loginn->id==""){loginn->id=(yyvsp[-1].TEXT);} (yyval.clogin)=loginn;}
#line 2364 "parser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 356 "sintactico.y" /* yacc.c:1646  */
    {if(loginn->usr==""){loginn->usr=(yyvsp[0].TEXT);} (yyval.clogin)=loginn;}
#line 2370 "parser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 357 "sintactico.y" /* yacc.c:1646  */
    {if(loginn->usr==""){loginn->usr=(yyvsp[0].TEXT);} (yyval.clogin)=loginn;}
#line 2376 "parser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 358 "sintactico.y" /* yacc.c:1646  */
    {if(loginn->pwd==""){loginn->pwd=(yyvsp[0].TEXT);} (yyval.clogin)=loginn;}
#line 2382 "parser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 359 "sintactico.y" /* yacc.c:1646  */
    {if(loginn->pwd==""){loginn->pwd=(yyvsp[0].TEXT);} (yyval.clogin)=loginn;}
#line 2388 "parser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 360 "sintactico.y" /* yacc.c:1646  */
    {if(loginn->pwd==""){loginn->pwd=(yyvsp[0].TEXT);} (yyval.clogin)=loginn;}
#line 2394 "parser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 361 "sintactico.y" /* yacc.c:1646  */
    {if(loginn->id==""){loginn->id=(yyvsp[0].TEXT);} (yyval.clogin)=loginn;}
#line 2400 "parser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 363 "sintactico.y" /* yacc.c:1646  */
    {if(mkgrpp->name==""){mkgrpp->name=(yyvsp[-1].TEXT);} (yyval.cmkgrp)=mkgrpp;}
#line 2406 "parser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 364 "sintactico.y" /* yacc.c:1646  */
    {if(mkgrpp->name==""){mkgrpp->name=(yyvsp[-1].TEXT);} (yyval.cmkgrp)=mkgrpp;}
#line 2412 "parser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 365 "sintactico.y" /* yacc.c:1646  */
    {if(mkgrpp->name==""){mkgrpp->name=(yyvsp[0].TEXT);} (yyval.cmkgrp)=mkgrpp;}
#line 2418 "parser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 366 "sintactico.y" /* yacc.c:1646  */
    {if(mkgrpp->name==""){mkgrpp->name=(yyvsp[0].TEXT);} (yyval.cmkgrp)=mkgrpp;}
#line 2424 "parser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 368 "sintactico.y" /* yacc.c:1646  */
    {if(rmgrpp->name==""){rmgrpp->name=(yyvsp[-1].TEXT);} (yyval.crmgrp)=rmgrpp;}
#line 2430 "parser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 369 "sintactico.y" /* yacc.c:1646  */
    {if(rmgrpp->name==""){rmgrpp->name=(yyvsp[-1].TEXT);} (yyval.crmgrp)=rmgrpp;}
#line 2436 "parser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 370 "sintactico.y" /* yacc.c:1646  */
    {if(rmgrpp->name==""){rmgrpp->name=(yyvsp[0].TEXT);} (yyval.crmgrp)=rmgrpp;}
#line 2442 "parser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 371 "sintactico.y" /* yacc.c:1646  */
    {if(rmgrpp->name==""){rmgrpp->name=(yyvsp[0].TEXT);} (yyval.crmgrp)=rmgrpp;}
#line 2448 "parser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 373 "sintactico.y" /* yacc.c:1646  */
    {if(mkuserr->usr==""){mkuserr->usr=(yyvsp[-1].TEXT);} (yyval.cmkuser)=mkuserr;}
#line 2454 "parser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 374 "sintactico.y" /* yacc.c:1646  */
    {if(mkuserr->usr==""){mkuserr->usr=(yyvsp[-1].TEXT);} (yyval.cmkuser)=mkuserr;}
#line 2460 "parser.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 375 "sintactico.y" /* yacc.c:1646  */
    {if(mkuserr->pwd==""){mkuserr->pwd=(yyvsp[-1].TEXT);} (yyval.cmkuser)=mkuserr;}
#line 2466 "parser.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 376 "sintactico.y" /* yacc.c:1646  */
    {if(mkuserr->pwd==""){mkuserr->pwd=(yyvsp[-1].TEXT);} (yyval.cmkuser)=mkuserr;}
#line 2472 "parser.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 377 "sintactico.y" /* yacc.c:1646  */
    {if(mkuserr->pwd==""){mkuserr->pwd=(yyvsp[-1].TEXT);} (yyval.cmkuser)=mkuserr;}
#line 2478 "parser.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 378 "sintactico.y" /* yacc.c:1646  */
    {if(mkuserr->pwd==""){mkuserr->pwd=(yyvsp[-1].TEXT);} (yyval.cmkuser)=mkuserr;}
#line 2484 "parser.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 379 "sintactico.y" /* yacc.c:1646  */
    {if(mkuserr->pwd==""){mkuserr->pwd=(yyvsp[-1].TEXT);} (yyval.cmkuser)=mkuserr;}
#line 2490 "parser.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 380 "sintactico.y" /* yacc.c:1646  */
    {if(mkuserr->usr==""){mkuserr->usr=(yyvsp[0].TEXT);} (yyval.cmkuser)=mkuserr;}
#line 2496 "parser.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 381 "sintactico.y" /* yacc.c:1646  */
    {if(mkuserr->usr==""){mkuserr->usr=(yyvsp[0].TEXT);} (yyval.cmkuser)=mkuserr;}
#line 2502 "parser.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 382 "sintactico.y" /* yacc.c:1646  */
    {if(mkuserr->pwd==""){mkuserr->pwd=(yyvsp[0].TEXT);} (yyval.cmkuser)=mkuserr;}
#line 2508 "parser.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 383 "sintactico.y" /* yacc.c:1646  */
    {if(mkuserr->pwd==""){mkuserr->pwd=(yyvsp[0].TEXT);} (yyval.cmkuser)=mkuserr;}
#line 2514 "parser.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 384 "sintactico.y" /* yacc.c:1646  */
    {if(mkuserr->pwd==""){mkuserr->pwd=(yyvsp[0].TEXT);} (yyval.cmkuser)=mkuserr;}
#line 2520 "parser.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 385 "sintactico.y" /* yacc.c:1646  */
    {if(mkuserr->pwd==""){mkuserr->pwd=(yyvsp[0].TEXT);} (yyval.cmkuser)=mkuserr;}
#line 2526 "parser.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 386 "sintactico.y" /* yacc.c:1646  */
    {if(mkuserr->pwd==""){mkuserr->pwd=(yyvsp[0].TEXT);} (yyval.cmkuser)=mkuserr;}
#line 2532 "parser.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 388 "sintactico.y" /* yacc.c:1646  */
    {if(rmuserr->usr==""){rmuserr->usr=(yyvsp[-1].TEXT);} (yyval.crmuser)=rmuserr;}
#line 2538 "parser.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 389 "sintactico.y" /* yacc.c:1646  */
    {if(rmuserr->usr==""){rmuserr->usr=(yyvsp[-1].TEXT);} (yyval.crmuser)=rmuserr;}
#line 2544 "parser.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 390 "sintactico.y" /* yacc.c:1646  */
    {if(rmuserr->usr==""){rmuserr->usr=(yyvsp[0].TEXT);} (yyval.crmuser)=rmuserr;}
#line 2550 "parser.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 391 "sintactico.y" /* yacc.c:1646  */
    {if(rmuserr->usr==""){rmuserr->usr=(yyvsp[0].TEXT);} (yyval.crmuser)=rmuserr;}
#line 2556 "parser.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 393 "sintactico.y" /* yacc.c:1646  */
    {if(chmmodd->path==""){chmmodd->path=(yyvsp[-1].TEXT);} (yyval.cchmmod)=chmmodd;}
#line 2562 "parser.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 394 "sintactico.y" /* yacc.c:1646  */
    {if(chmmodd->path==""){chmmodd->path=(yyvsp[-1].TEXT);} (yyval.cchmmod)=chmmodd;}
#line 2568 "parser.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 395 "sintactico.y" /* yacc.c:1646  */
    {int tam=atoi((yyvsp[-1].TEXT)); if(chmmodd->ugo==0){chmmodd->ugo=tam;} (yyval.cchmmod)=chmmodd;}
#line 2574 "parser.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 396 "sintactico.y" /* yacc.c:1646  */
    {if(chmmodd->R==""){chmmodd->R=(yyvsp[-1].TEXT);} (yyval.cchmmod)=chmmodd;}
#line 2580 "parser.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 397 "sintactico.y" /* yacc.c:1646  */
    {if(chmmodd->path==""){chmmodd->path=(yyvsp[0].TEXT);} (yyval.cchmmod)=chmmodd;}
#line 2586 "parser.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 398 "sintactico.y" /* yacc.c:1646  */
    {if(chmmodd->path==""){chmmodd->path=(yyvsp[0].TEXT);} (yyval.cchmmod)=chmmodd;}
#line 2592 "parser.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 399 "sintactico.y" /* yacc.c:1646  */
    {int tam=atoi((yyvsp[0].TEXT)); if(chmmodd->ugo==0){chmmodd->ugo=tam;} (yyval.cchmmod)=chmmodd;}
#line 2598 "parser.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 400 "sintactico.y" /* yacc.c:1646  */
    {if(chmmodd->R==""){chmmodd->R=(yyvsp[0].TEXT);} (yyval.cchmmod)=chmmodd;}
#line 2604 "parser.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 402 "sintactico.y" /* yacc.c:1646  */
    {if(mkfilee->path==""){mkfilee->path=(yyvsp[-1].TEXT);} (yyval.cmkfile)=mkfilee;}
#line 2610 "parser.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 403 "sintactico.y" /* yacc.c:1646  */
    {if(mkfilee->path==""){mkfilee->path=(yyvsp[-1].TEXT);} (yyval.cmkfile)=mkfilee;}
#line 2616 "parser.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 404 "sintactico.y" /* yacc.c:1646  */
    {int tam=atoi((yyvsp[-1].TEXT)); if(mkfilee->size==0){mkfilee->size=tam;} (yyval.cmkfile)=mkfilee;}
#line 2622 "parser.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 405 "sintactico.y" /* yacc.c:1646  */
    {int tam=atoi((yyvsp[-2].TEXT)); if(mkfilee->size==0){mkfilee->size=tam * -1;} (yyval.cmkfile)=mkfilee;}
#line 2628 "parser.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 406 "sintactico.y" /* yacc.c:1646  */
    {if(mkfilee->R==""){mkfilee->R=(yyvsp[-1].TEXT);} (yyval.cmkfile)=mkfilee;}
#line 2634 "parser.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 407 "sintactico.y" /* yacc.c:1646  */
    {if(mkfilee->P==""){mkfilee->P=(yyvsp[-1].TEXT);} (yyval.cmkfile)=mkfilee;}
#line 2640 "parser.cpp" /* yacc.c:1646  */
    break;

  case 161:
#line 408 "sintactico.y" /* yacc.c:1646  */
    {if(mkfilee->cont==""){mkfilee->cont=(yyvsp[-1].TEXT);} (yyval.cmkfile)=mkfilee;}
#line 2646 "parser.cpp" /* yacc.c:1646  */
    break;

  case 162:
#line 409 "sintactico.y" /* yacc.c:1646  */
    {if(mkfilee->cont==""){mkfilee->cont=(yyvsp[-1].TEXT);} (yyval.cmkfile)=mkfilee;}
#line 2652 "parser.cpp" /* yacc.c:1646  */
    break;

  case 163:
#line 410 "sintactico.y" /* yacc.c:1646  */
    {if(mkfilee->path==""){mkfilee->path=(yyvsp[0].TEXT);} (yyval.cmkfile)=mkfilee;}
#line 2658 "parser.cpp" /* yacc.c:1646  */
    break;

  case 164:
#line 411 "sintactico.y" /* yacc.c:1646  */
    {if(mkfilee->path==""){mkfilee->path=(yyvsp[0].TEXT);} (yyval.cmkfile)=mkfilee;}
#line 2664 "parser.cpp" /* yacc.c:1646  */
    break;

  case 165:
#line 412 "sintactico.y" /* yacc.c:1646  */
    {int tam=atoi((yyvsp[0].TEXT)); if(mkfilee->size==0){mkfilee->size=tam;} (yyval.cmkfile)=mkfilee;}
#line 2670 "parser.cpp" /* yacc.c:1646  */
    break;

  case 166:
#line 413 "sintactico.y" /* yacc.c:1646  */
    {int tam=atoi((yyvsp[-1].TEXT)); if(mkfilee->size==0){mkfilee->size=tam * -1;} (yyval.cmkfile)=mkfilee;}
#line 2676 "parser.cpp" /* yacc.c:1646  */
    break;

  case 167:
#line 414 "sintactico.y" /* yacc.c:1646  */
    {if(mkfilee->R==""){mkfilee->R=(yyvsp[0].TEXT);} (yyval.cmkfile)=mkfilee;}
#line 2682 "parser.cpp" /* yacc.c:1646  */
    break;

  case 168:
#line 415 "sintactico.y" /* yacc.c:1646  */
    {if(mkfilee->P==""){mkfilee->P=(yyvsp[0].TEXT);} (yyval.cmkfile)=mkfilee;}
#line 2688 "parser.cpp" /* yacc.c:1646  */
    break;

  case 169:
#line 416 "sintactico.y" /* yacc.c:1646  */
    {if(mkfilee->cont==""){mkfilee->cont=(yyvsp[0].TEXT);} (yyval.cmkfile)=mkfilee;}
#line 2694 "parser.cpp" /* yacc.c:1646  */
    break;

  case 170:
#line 417 "sintactico.y" /* yacc.c:1646  */
    {if(mkfilee->cont==""){mkfilee->cont=(yyvsp[0].TEXT);} (yyval.cmkfile)=mkfilee;}
#line 2700 "parser.cpp" /* yacc.c:1646  */
    break;

  case 171:
#line 419 "sintactico.y" /* yacc.c:1646  */
    {if(catt->filen==""){catt->filen=(yyvsp[-1].TEXT);} (yyval.ccat)=catt;}
#line 2706 "parser.cpp" /* yacc.c:1646  */
    break;

  case 172:
#line 420 "sintactico.y" /* yacc.c:1646  */
    {if(catt->filen==""){catt->filen=(yyvsp[-1].TEXT);} (yyval.ccat)=catt;}
#line 2712 "parser.cpp" /* yacc.c:1646  */
    break;

  case 173:
#line 421 "sintactico.y" /* yacc.c:1646  */
    {if(catt->filen==""){catt->filen=(yyvsp[-1].TEXT);} (yyval.ccat)=catt;}
#line 2718 "parser.cpp" /* yacc.c:1646  */
    break;

  case 174:
#line 422 "sintactico.y" /* yacc.c:1646  */
    {if(catt->filen==""){catt->filen=(yyvsp[-1].TEXT);} (yyval.ccat)=catt;}
#line 2724 "parser.cpp" /* yacc.c:1646  */
    break;

  case 175:
#line 423 "sintactico.y" /* yacc.c:1646  */
    {if(catt->filen==""){catt->filen=(yyvsp[-1].TEXT);} (yyval.ccat)=catt;}
#line 2730 "parser.cpp" /* yacc.c:1646  */
    break;

  case 176:
#line 424 "sintactico.y" /* yacc.c:1646  */
    {if(catt->filen==""){catt->filen=(yyvsp[-1].TEXT);} (yyval.ccat)=catt;}
#line 2736 "parser.cpp" /* yacc.c:1646  */
    break;

  case 177:
#line 425 "sintactico.y" /* yacc.c:1646  */
    {if(catt->filen==""){catt->filen=(yyvsp[0].TEXT);} (yyval.ccat)=catt;}
#line 2742 "parser.cpp" /* yacc.c:1646  */
    break;

  case 178:
#line 426 "sintactico.y" /* yacc.c:1646  */
    {if(catt->filen==""){catt->filen=(yyvsp[0].TEXT);} (yyval.ccat)=catt;}
#line 2748 "parser.cpp" /* yacc.c:1646  */
    break;

  case 179:
#line 427 "sintactico.y" /* yacc.c:1646  */
    {if(catt->filen==""){catt->filen=(yyvsp[0].TEXT);} (yyval.ccat)=catt;}
#line 2754 "parser.cpp" /* yacc.c:1646  */
    break;

  case 180:
#line 428 "sintactico.y" /* yacc.c:1646  */
    {if(catt->filen==""){catt->filen=(yyvsp[0].TEXT);} (yyval.ccat)=catt;}
#line 2760 "parser.cpp" /* yacc.c:1646  */
    break;

  case 181:
#line 429 "sintactico.y" /* yacc.c:1646  */
    {if(catt->filen==""){catt->filen=(yyvsp[0].TEXT);} (yyval.ccat)=catt;}
#line 2766 "parser.cpp" /* yacc.c:1646  */
    break;

  case 182:
#line 430 "sintactico.y" /* yacc.c:1646  */
    {if(catt->filen==""){catt->filen=(yyvsp[0].TEXT);} (yyval.ccat)=catt;}
#line 2772 "parser.cpp" /* yacc.c:1646  */
    break;

  case 183:
#line 432 "sintactico.y" /* yacc.c:1646  */
    {if(remm->path==""){remm->path=(yyvsp[-1].TEXT);} (yyval.crem)=remm;}
#line 2778 "parser.cpp" /* yacc.c:1646  */
    break;

  case 184:
#line 433 "sintactico.y" /* yacc.c:1646  */
    {if(remm->path==""){remm->path=(yyvsp[-1].TEXT);} (yyval.crem)=remm;}
#line 2784 "parser.cpp" /* yacc.c:1646  */
    break;

  case 185:
#line 434 "sintactico.y" /* yacc.c:1646  */
    {if(remm->path==""){remm->path=(yyvsp[-1].TEXT);} (yyval.crem)=remm;}
#line 2790 "parser.cpp" /* yacc.c:1646  */
    break;

  case 186:
#line 435 "sintactico.y" /* yacc.c:1646  */
    {if(remm->path==""){remm->path=(yyvsp[0].TEXT);} (yyval.crem)=remm;}
#line 2796 "parser.cpp" /* yacc.c:1646  */
    break;

  case 187:
#line 436 "sintactico.y" /* yacc.c:1646  */
    {if(remm->path==""){remm->path=(yyvsp[0].TEXT);} (yyval.crem)=remm;}
#line 2802 "parser.cpp" /* yacc.c:1646  */
    break;

  case 188:
#line 437 "sintactico.y" /* yacc.c:1646  */
    {if(remm->path==""){remm->path=(yyvsp[0].TEXT);} (yyval.crem)=remm;}
#line 2808 "parser.cpp" /* yacc.c:1646  */
    break;

  case 189:
#line 439 "sintactico.y" /* yacc.c:1646  */
    {if(editt->path==""){editt->path=(yyvsp[-1].TEXT);} (yyval.cedit)=editt;}
#line 2814 "parser.cpp" /* yacc.c:1646  */
    break;

  case 190:
#line 440 "sintactico.y" /* yacc.c:1646  */
    {if(editt->path==""){editt->path=(yyvsp[-1].TEXT);} (yyval.cedit)=editt;}
#line 2820 "parser.cpp" /* yacc.c:1646  */
    break;

  case 191:
#line 441 "sintactico.y" /* yacc.c:1646  */
    {if(editt->cont==""){editt->cont=(yyvsp[-1].TEXT);} (yyval.cedit)=editt;}
#line 2826 "parser.cpp" /* yacc.c:1646  */
    break;

  case 192:
#line 442 "sintactico.y" /* yacc.c:1646  */
    {if(editt->cont==""){editt->cont=(yyvsp[-1].TEXT);} (yyval.cedit)=editt;}
#line 2832 "parser.cpp" /* yacc.c:1646  */
    break;

  case 193:
#line 443 "sintactico.y" /* yacc.c:1646  */
    {if(editt->path==""){editt->path=(yyvsp[0].TEXT);} (yyval.cedit)=editt;}
#line 2838 "parser.cpp" /* yacc.c:1646  */
    break;

  case 194:
#line 444 "sintactico.y" /* yacc.c:1646  */
    {if(editt->path==""){editt->path=(yyvsp[0].TEXT);} (yyval.cedit)=editt;}
#line 2844 "parser.cpp" /* yacc.c:1646  */
    break;

  case 195:
#line 445 "sintactico.y" /* yacc.c:1646  */
    {if(editt->cont==""){editt->cont=(yyvsp[0].TEXT);} (yyval.cedit)=editt;}
#line 2850 "parser.cpp" /* yacc.c:1646  */
    break;

  case 196:
#line 446 "sintactico.y" /* yacc.c:1646  */
    {if(editt->cont==""){editt->cont=(yyvsp[0].TEXT);} (yyval.cedit)=editt;}
#line 2856 "parser.cpp" /* yacc.c:1646  */
    break;

  case 197:
#line 448 "sintactico.y" /* yacc.c:1646  */
    {if(renn->path==""){renn->path=(yyvsp[-1].TEXT);} (yyval.cren)=renn;}
#line 2862 "parser.cpp" /* yacc.c:1646  */
    break;

  case 198:
#line 449 "sintactico.y" /* yacc.c:1646  */
    {if(renn->path==""){renn->path=(yyvsp[-1].TEXT);} (yyval.cren)=renn;}
#line 2868 "parser.cpp" /* yacc.c:1646  */
    break;

  case 199:
#line 450 "sintactico.y" /* yacc.c:1646  */
    {if(renn->path==""){renn->path=(yyvsp[-1].TEXT);} (yyval.cren)=renn;}
#line 2874 "parser.cpp" /* yacc.c:1646  */
    break;

  case 200:
#line 451 "sintactico.y" /* yacc.c:1646  */
    {if(renn->path==""){renn->path=(yyvsp[0].TEXT);} (yyval.cren)=renn;}
#line 2880 "parser.cpp" /* yacc.c:1646  */
    break;

  case 201:
#line 452 "sintactico.y" /* yacc.c:1646  */
    {if(renn->path==""){renn->path=(yyvsp[0].TEXT);} (yyval.cren)=renn;}
#line 2886 "parser.cpp" /* yacc.c:1646  */
    break;

  case 202:
#line 453 "sintactico.y" /* yacc.c:1646  */
    {if(renn->path==""){renn->path=(yyvsp[0].TEXT);} (yyval.cren)=renn;}
#line 2892 "parser.cpp" /* yacc.c:1646  */
    break;

  case 203:
#line 455 "sintactico.y" /* yacc.c:1646  */
    {if(cmkdirr->path==""){cmkdirr->path=(yyvsp[-1].TEXT);} (yyval.cmkdir)=cmkdirr;}
#line 2898 "parser.cpp" /* yacc.c:1646  */
    break;

  case 204:
#line 456 "sintactico.y" /* yacc.c:1646  */
    {if(cmkdirr->path==""){cmkdirr->path=(yyvsp[-1].TEXT);} (yyval.cmkdir)=cmkdirr;}
#line 2904 "parser.cpp" /* yacc.c:1646  */
    break;

  case 205:
#line 457 "sintactico.y" /* yacc.c:1646  */
    {if(cmkdirr->P==""){cmkdirr->P=(yyvsp[-1].TEXT);} (yyval.cmkdir)=cmkdirr;}
#line 2910 "parser.cpp" /* yacc.c:1646  */
    break;

  case 206:
#line 458 "sintactico.y" /* yacc.c:1646  */
    {if(cmkdirr->path==""){cmkdirr->path=(yyvsp[0].TEXT);} (yyval.cmkdir)=cmkdirr;}
#line 2916 "parser.cpp" /* yacc.c:1646  */
    break;

  case 207:
#line 459 "sintactico.y" /* yacc.c:1646  */
    {if(cmkdirr->path==""){cmkdirr->path=(yyvsp[0].TEXT);} (yyval.cmkdir)=cmkdirr;}
#line 2922 "parser.cpp" /* yacc.c:1646  */
    break;

  case 208:
#line 460 "sintactico.y" /* yacc.c:1646  */
    {if(cmkdirr->P==""){cmkdirr->P=(yyvsp[0].TEXT);} (yyval.cmkdir)=cmkdirr;}
#line 2928 "parser.cpp" /* yacc.c:1646  */
    break;

  case 209:
#line 462 "sintactico.y" /* yacc.c:1646  */
    {if(cpp->path==""){cpp->path=(yyvsp[-1].TEXT);} (yyval.ccp)=cpp;}
#line 2934 "parser.cpp" /* yacc.c:1646  */
    break;

  case 210:
#line 463 "sintactico.y" /* yacc.c:1646  */
    {if(cpp->path==""){cpp->path=(yyvsp[-1].TEXT);} (yyval.ccp)=cpp;}
#line 2940 "parser.cpp" /* yacc.c:1646  */
    break;

  case 211:
#line 464 "sintactico.y" /* yacc.c:1646  */
    {if(cpp->path==""){cpp->path=(yyvsp[-1].TEXT);} (yyval.ccp)=cpp;}
#line 2946 "parser.cpp" /* yacc.c:1646  */
    break;

  case 212:
#line 465 "sintactico.y" /* yacc.c:1646  */
    {if(cpp->dest==""){cpp->dest=(yyvsp[-1].TEXT);} (yyval.ccp)=cpp;}
#line 2952 "parser.cpp" /* yacc.c:1646  */
    break;

  case 213:
#line 466 "sintactico.y" /* yacc.c:1646  */
    {if(cpp->dest==""){cpp->dest=(yyvsp[-1].TEXT);} (yyval.ccp)=cpp;}
#line 2958 "parser.cpp" /* yacc.c:1646  */
    break;

  case 214:
#line 467 "sintactico.y" /* yacc.c:1646  */
    {if(cpp->dest==""){cpp->dest=(yyvsp[-1].TEXT);} (yyval.ccp)=cpp;}
#line 2964 "parser.cpp" /* yacc.c:1646  */
    break;

  case 215:
#line 468 "sintactico.y" /* yacc.c:1646  */
    {if(cpp->path==""){cpp->path=(yyvsp[0].TEXT);} (yyval.ccp)=cpp;}
#line 2970 "parser.cpp" /* yacc.c:1646  */
    break;

  case 216:
#line 469 "sintactico.y" /* yacc.c:1646  */
    {if(cpp->path==""){cpp->path=(yyvsp[0].TEXT);} (yyval.ccp)=cpp;}
#line 2976 "parser.cpp" /* yacc.c:1646  */
    break;

  case 217:
#line 470 "sintactico.y" /* yacc.c:1646  */
    {if(cpp->path==""){cpp->path=(yyvsp[0].TEXT);} (yyval.ccp)=cpp;}
#line 2982 "parser.cpp" /* yacc.c:1646  */
    break;

  case 218:
#line 471 "sintactico.y" /* yacc.c:1646  */
    {if(cpp->dest==""){cpp->dest=(yyvsp[0].TEXT);} (yyval.ccp)=cpp;}
#line 2988 "parser.cpp" /* yacc.c:1646  */
    break;

  case 219:
#line 472 "sintactico.y" /* yacc.c:1646  */
    {if(cpp->dest==""){cpp->dest=(yyvsp[0].TEXT);} (yyval.ccp)=cpp;}
#line 2994 "parser.cpp" /* yacc.c:1646  */
    break;

  case 220:
#line 473 "sintactico.y" /* yacc.c:1646  */
    {if(cpp->dest==""){cpp->dest=(yyvsp[0].TEXT);} (yyval.ccp)=cpp;}
#line 3000 "parser.cpp" /* yacc.c:1646  */
    break;

  case 221:
#line 475 "sintactico.y" /* yacc.c:1646  */
    {if(mvv->path==""){mvv->path=(yyvsp[-1].TEXT);} (yyval.cmv)=mvv;}
#line 3006 "parser.cpp" /* yacc.c:1646  */
    break;

  case 222:
#line 476 "sintactico.y" /* yacc.c:1646  */
    {if(mvv->path==""){mvv->path=(yyvsp[-1].TEXT);} (yyval.cmv)=mvv;}
#line 3012 "parser.cpp" /* yacc.c:1646  */
    break;

  case 223:
#line 477 "sintactico.y" /* yacc.c:1646  */
    {if(mvv->path==""){mvv->path=(yyvsp[-1].TEXT);} (yyval.cmv)=mvv;}
#line 3018 "parser.cpp" /* yacc.c:1646  */
    break;

  case 224:
#line 478 "sintactico.y" /* yacc.c:1646  */
    {if(mvv->dest==""){mvv->dest=(yyvsp[-1].TEXT);} (yyval.cmv)=mvv;}
#line 3024 "parser.cpp" /* yacc.c:1646  */
    break;

  case 225:
#line 479 "sintactico.y" /* yacc.c:1646  */
    {if(mvv->dest==""){mvv->dest=(yyvsp[-1].TEXT);} (yyval.cmv)=mvv;}
#line 3030 "parser.cpp" /* yacc.c:1646  */
    break;

  case 226:
#line 480 "sintactico.y" /* yacc.c:1646  */
    {if(mvv->dest==""){mvv->dest=(yyvsp[-1].TEXT);} (yyval.cmv)=mvv;}
#line 3036 "parser.cpp" /* yacc.c:1646  */
    break;

  case 227:
#line 481 "sintactico.y" /* yacc.c:1646  */
    {if(mvv->path==""){mvv->path=(yyvsp[0].TEXT);} (yyval.cmv)=mvv;}
#line 3042 "parser.cpp" /* yacc.c:1646  */
    break;

  case 228:
#line 482 "sintactico.y" /* yacc.c:1646  */
    {if(mvv->path==""){mvv->path=(yyvsp[0].TEXT);} (yyval.cmv)=mvv;}
#line 3048 "parser.cpp" /* yacc.c:1646  */
    break;

  case 229:
#line 483 "sintactico.y" /* yacc.c:1646  */
    {if(mvv->path==""){mvv->path=(yyvsp[0].TEXT);} (yyval.cmv)=mvv;}
#line 3054 "parser.cpp" /* yacc.c:1646  */
    break;

  case 230:
#line 484 "sintactico.y" /* yacc.c:1646  */
    {if(mvv->dest==""){mvv->dest=(yyvsp[0].TEXT);} (yyval.cmv)=mvv;}
#line 3060 "parser.cpp" /* yacc.c:1646  */
    break;

  case 231:
#line 485 "sintactico.y" /* yacc.c:1646  */
    {if(mvv->dest==""){mvv->dest=(yyvsp[0].TEXT);} (yyval.cmv)=mvv;}
#line 3066 "parser.cpp" /* yacc.c:1646  */
    break;

  case 232:
#line 486 "sintactico.y" /* yacc.c:1646  */
    {if(mvv->dest==""){mvv->dest=(yyvsp[0].TEXT);} (yyval.cmv)=mvv;}
#line 3072 "parser.cpp" /* yacc.c:1646  */
    break;

  case 233:
#line 488 "sintactico.y" /* yacc.c:1646  */
    {if(findd->path==""){findd->path=(yyvsp[-1].TEXT);} (yyval.cfind)=findd;}
#line 3078 "parser.cpp" /* yacc.c:1646  */
    break;

  case 234:
#line 489 "sintactico.y" /* yacc.c:1646  */
    {if(findd->path==""){findd->path=(yyvsp[-1].TEXT);} (yyval.cfind)=findd;}
#line 3084 "parser.cpp" /* yacc.c:1646  */
    break;

  case 235:
#line 490 "sintactico.y" /* yacc.c:1646  */
    {if(findd->namee==""){findd->namee=(yyvsp[-1].TEXT);} (yyval.cfind)=findd;}
#line 3090 "parser.cpp" /* yacc.c:1646  */
    break;

  case 236:
#line 491 "sintactico.y" /* yacc.c:1646  */
    {if(findd->namee==""){findd->namee=(yyvsp[-1].TEXT);} (yyval.cfind)=findd;}
#line 3096 "parser.cpp" /* yacc.c:1646  */
    break;

  case 237:
#line 492 "sintactico.y" /* yacc.c:1646  */
    {if(findd->namee==""){findd->namee=(yyvsp[-1].TEXT);} (yyval.cfind)=findd;}
#line 3102 "parser.cpp" /* yacc.c:1646  */
    break;

  case 238:
#line 493 "sintactico.y" /* yacc.c:1646  */
    {if(findd->path==""){findd->path=(yyvsp[0].TEXT);} (yyval.cfind)=findd;}
#line 3108 "parser.cpp" /* yacc.c:1646  */
    break;

  case 239:
#line 494 "sintactico.y" /* yacc.c:1646  */
    {if(findd->path==""){findd->path=(yyvsp[0].TEXT);} (yyval.cfind)=findd;}
#line 3114 "parser.cpp" /* yacc.c:1646  */
    break;

  case 240:
#line 495 "sintactico.y" /* yacc.c:1646  */
    {if(findd->namee==""){findd->namee=(yyvsp[0].TEXT);} (yyval.cfind)=findd;}
#line 3120 "parser.cpp" /* yacc.c:1646  */
    break;

  case 241:
#line 496 "sintactico.y" /* yacc.c:1646  */
    {if(findd->namee==""){findd->namee=(yyvsp[0].TEXT);} (yyval.cfind)=findd;}
#line 3126 "parser.cpp" /* yacc.c:1646  */
    break;

  case 242:
#line 497 "sintactico.y" /* yacc.c:1646  */
    {if(findd->namee==""){findd->namee=(yyvsp[0].TEXT);} (yyval.cfind)=findd;}
#line 3132 "parser.cpp" /* yacc.c:1646  */
    break;

  case 243:
#line 499 "sintactico.y" /* yacc.c:1646  */
    {if(cchownn->path==""){cchownn->path=(yyvsp[-1].TEXT);} (yyval.cchown)=cchownn;}
#line 3138 "parser.cpp" /* yacc.c:1646  */
    break;

  case 244:
#line 500 "sintactico.y" /* yacc.c:1646  */
    {if(cchownn->path==""){cchownn->path=(yyvsp[-1].TEXT);} (yyval.cchown)=cchownn;}
#line 3144 "parser.cpp" /* yacc.c:1646  */
    break;

  case 245:
#line 501 "sintactico.y" /* yacc.c:1646  */
    {if(cchownn->R==""){cchownn->R=(yyvsp[-1].TEXT);} (yyval.cchown)=cchownn;}
#line 3150 "parser.cpp" /* yacc.c:1646  */
    break;

  case 246:
#line 502 "sintactico.y" /* yacc.c:1646  */
    {if(cchownn->usr==""){cchownn->usr=(yyvsp[-1].TEXT);} (yyval.cchown)=cchownn;}
#line 3156 "parser.cpp" /* yacc.c:1646  */
    break;

  case 247:
#line 503 "sintactico.y" /* yacc.c:1646  */
    {if(cchownn->path==""){cchownn->path=(yyvsp[0].TEXT);} (yyval.cchown)=cchownn;}
#line 3162 "parser.cpp" /* yacc.c:1646  */
    break;

  case 248:
#line 504 "sintactico.y" /* yacc.c:1646  */
    {if(cchownn->path==""){cchownn->path=(yyvsp[0].TEXT);} (yyval.cchown)=cchownn;}
#line 3168 "parser.cpp" /* yacc.c:1646  */
    break;

  case 249:
#line 505 "sintactico.y" /* yacc.c:1646  */
    {if(cchownn->R==""){cchownn->R=(yyvsp[0].TEXT);} (yyval.cchown)=cchownn;}
#line 3174 "parser.cpp" /* yacc.c:1646  */
    break;

  case 250:
#line 506 "sintactico.y" /* yacc.c:1646  */
    {if(cchownn->usr==""){cchownn->usr=(yyvsp[0].TEXT);} (yyval.cchown)=cchownn;}
#line 3180 "parser.cpp" /* yacc.c:1646  */
    break;

  case 251:
#line 508 "sintactico.y" /* yacc.c:1646  */
    {if(chgrpp->usr==""){chgrpp->usr=(yyvsp[-1].TEXT);} (yyval.cchgrp)=chgrpp;}
#line 3186 "parser.cpp" /* yacc.c:1646  */
    break;

  case 252:
#line 509 "sintactico.y" /* yacc.c:1646  */
    {if(chgrpp->grp==""){chgrpp->grp=(yyvsp[-1].TEXT);} (yyval.cchgrp)=chgrpp;}
#line 3192 "parser.cpp" /* yacc.c:1646  */
    break;

  case 253:
#line 510 "sintactico.y" /* yacc.c:1646  */
    {if(chgrpp->usr==""){chgrpp->usr=(yyvsp[0].TEXT);} (yyval.cchgrp)=chgrpp;}
#line 3198 "parser.cpp" /* yacc.c:1646  */
    break;

  case 254:
#line 511 "sintactico.y" /* yacc.c:1646  */
    {if(chgrpp->grp==""){chgrpp->grp=(yyvsp[0].TEXT);} (yyval.cchgrp)=chgrpp;}
#line 3204 "parser.cpp" /* yacc.c:1646  */
    break;

  case 255:
#line 513 "sintactico.y" /* yacc.c:1646  */
    {if(script->path==""){script->path=(yyvsp[-1].TEXT);} (yyval.archexec)=script;}
#line 3210 "parser.cpp" /* yacc.c:1646  */
    break;

  case 256:
#line 514 "sintactico.y" /* yacc.c:1646  */
    {if(script->path==""){script->path=(yyvsp[-1].TEXT);} (yyval.archexec)=script;}
#line 3216 "parser.cpp" /* yacc.c:1646  */
    break;

  case 257:
#line 515 "sintactico.y" /* yacc.c:1646  */
    {if(script->path==""){script->path=(yyvsp[0].TEXT);} (yyval.archexec)=script;}
#line 3222 "parser.cpp" /* yacc.c:1646  */
    break;

  case 258:
#line 516 "sintactico.y" /* yacc.c:1646  */
    {if(script->path==""){script->path=(yyvsp[0].TEXT);} (yyval.archexec)=script;}
#line 3228 "parser.cpp" /* yacc.c:1646  */
    break;

  case 259:
#line 518 "sintactico.y" /* yacc.c:1646  */
    {if(reporte->path==""){reporte->path=(yyvsp[-1].TEXT);} (yyval.creporte)=reporte;}
#line 3234 "parser.cpp" /* yacc.c:1646  */
    break;

  case 260:
#line 519 "sintactico.y" /* yacc.c:1646  */
    {if(reporte->path==""){reporte->path=(yyvsp[-1].TEXT);} (yyval.creporte)=reporte;}
#line 3240 "parser.cpp" /* yacc.c:1646  */
    break;

  case 261:
#line 520 "sintactico.y" /* yacc.c:1646  */
    {if(reporte->namee==""){reporte->namee=(yyvsp[-1].TEXT);} (yyval.creporte)=reporte;}
#line 3246 "parser.cpp" /* yacc.c:1646  */
    break;

  case 262:
#line 521 "sintactico.y" /* yacc.c:1646  */
    {if(reporte->namee==""){reporte->namee=(yyvsp[-1].TEXT);} (yyval.creporte)=reporte;}
#line 3252 "parser.cpp" /* yacc.c:1646  */
    break;

  case 263:
#line 522 "sintactico.y" /* yacc.c:1646  */
    {if(reporte->id==""){reporte->id=(yyvsp[-1].TEXT);} (yyval.creporte)=reporte;}
#line 3258 "parser.cpp" /* yacc.c:1646  */
    break;

  case 264:
#line 523 "sintactico.y" /* yacc.c:1646  */
    {if(reporte->path==""){reporte->path=(yyvsp[0].TEXT);} (yyval.creporte)=reporte;}
#line 3264 "parser.cpp" /* yacc.c:1646  */
    break;

  case 265:
#line 524 "sintactico.y" /* yacc.c:1646  */
    {if(reporte->path==""){reporte->path=(yyvsp[0].TEXT);} (yyval.creporte)=reporte;}
#line 3270 "parser.cpp" /* yacc.c:1646  */
    break;

  case 266:
#line 525 "sintactico.y" /* yacc.c:1646  */
    {if(reporte->namee==""){reporte->namee=(yyvsp[0].TEXT);} (yyval.creporte)=reporte;}
#line 3276 "parser.cpp" /* yacc.c:1646  */
    break;

  case 267:
#line 526 "sintactico.y" /* yacc.c:1646  */
    {if(reporte->namee==""){reporte->namee=(yyvsp[0].TEXT);} (yyval.creporte)=reporte;}
#line 3282 "parser.cpp" /* yacc.c:1646  */
    break;

  case 268:
#line 527 "sintactico.y" /* yacc.c:1646  */
    {if(reporte->id==""){reporte->id=(yyvsp[0].TEXT);} (yyval.creporte)=reporte;}
#line 3288 "parser.cpp" /* yacc.c:1646  */
    break;

  case 269:
#line 529 "sintactico.y" /* yacc.c:1646  */
    {if(recuperar->id==""){recuperar->id=(yyvsp[-1].TEXT);} (yyval.crecup)=recuperar;}
#line 3294 "parser.cpp" /* yacc.c:1646  */
    break;

  case 270:
#line 530 "sintactico.y" /* yacc.c:1646  */
    {if(recuperar->id==""){recuperar->id=(yyvsp[0].TEXT);} (yyval.crecup)=recuperar;}
#line 3300 "parser.cpp" /* yacc.c:1646  */
    break;

  case 271:
#line 532 "sintactico.y" /* yacc.c:1646  */
    {if(perdida->id==""){perdida->id=(yyvsp[-1].TEXT);} (yyval.cperd)=perdida;}
#line 3306 "parser.cpp" /* yacc.c:1646  */
    break;

  case 272:
#line 533 "sintactico.y" /* yacc.c:1646  */
    {if(perdida->id==""){perdida->id=(yyvsp[0].TEXT);} (yyval.cperd)=perdida;}
#line 3312 "parser.cpp" /* yacc.c:1646  */
    break;


#line 3316 "parser.cpp" /* yacc.c:1646  */
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
#line 536 "sintactico.y" /* yacc.c:1906  */

