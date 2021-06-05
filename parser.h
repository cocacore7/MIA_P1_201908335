/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
    identificador = 259,
    cadena = 260,
    filen = 261,
    idp = 262,
    ruta = 263,
    ugo = 264,
    mkdisk = 265,
    rmdisk = 266,
    fdisk = 267,
    mount = 268,
    unmount = 269,
    mkfs = 270,
    login = 271,
    logout = 272,
    mkgrp = 273,
    rmgrp = 274,
    mkusr = 275,
    rmusr = 276,
    mkfile = 277,
    cat = 278,
    rem = 279,
    edit = 280,
    ren = 281,
    mkdir = 282,
    cp = 283,
    mv = 284,
    find = 285,
    chownn = 286,
    chgrp = 287,
    pausee = 288,
    igual = 289,
    dividido = 290,
    interrogacion = 291,
    multiplicacion = 292,
    sizee = 293,
    f = 294,
    u = 295,
    pathh = 296,
    typee = 297,
    deletee = 298,
    namee = 299,
    addd = 300,
    id = 301,
    fs = 302,
    usr = 303,
    pwd = 304,
    grp = 305,
    ugoo = 306,
    r = 307,
    cont = 308,
    filenn = 309,
    dest = 310,
    p = 311,
    BF = 312,
    FF = 313,
    WF = 314,
    K = 315,
    M = 316,
    PP = 317,
    E = 318,
    L = 319,
    FAST = 320,
    FULL = 321,
    FS2 = 322,
    FS3 = 323
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 23 "sintactico.y" /* yacc.c:1909  */

    char TEXT[256];
    class clmkdisk *mdisk;

#line 128 "parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
