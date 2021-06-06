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
    cat = 277,
    rem = 278,
    edit = 279,
    ren = 280,
    cp = 281,
    mv = 282,
    find = 283,
    chownn = 284,
    chgrp = 285,
    pausee = 286,
    igual = 287,
    dividido = 288,
    interrogacion = 289,
    multiplicacion = 290,
    negativo = 291,
    sizee = 292,
    f = 293,
    u = 294,
    pathh = 295,
    typee = 296,
    deletee = 297,
    namee = 298,
    addd = 299,
    id = 300,
    fs = 301,
    usr = 302,
    pwd = 303,
    grp = 304,
    ugo = 305,
    r = 306,
    cont = 307,
    filenn = 308,
    dest = 309,
    p = 310,
    BF = 311,
    FF = 312,
    WF = 313,
    K = 314,
    M = 315,
    B = 316,
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
#line 29 "sintactico.y" /* yacc.c:1909  */

    char TEXT[500];
    class clmkdisk *mdisk;
    class clrmdisk *mrdiskk;
    class clfdisk *fdiskk;
    class clmount *modiskk;
    class clunmount *unmdiskk;
    class clmkfs *mkdiskk;

#line 133 "parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
