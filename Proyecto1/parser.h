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
    igual = 290,
    dividido = 291,
    interrogacion = 292,
    multiplicacion = 293,
    negativo = 294,
    sizee = 295,
    f = 296,
    u = 297,
    pathh = 298,
    typee = 299,
    deletee = 300,
    namee = 301,
    addd = 302,
    id = 303,
    fs = 304,
    usr = 305,
    pwd = 306,
    grp = 307,
    ugo = 308,
    rr = 309,
    cont = 310,
    filenn = 311,
    dest = 312,
    p = 313,
    BF = 314,
    FF = 315,
    WF = 316,
    K = 317,
    M = 318,
    B = 319,
    PP = 320,
    E = 321,
    L = 322,
    FAST = 323,
    FULL = 324,
    FS2 = 325,
    FS3 = 326
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 33 "sintactico.y" /* yacc.c:1909  */

    char TEXT[500];
    class clmkdisk *mdisk;
    class clrmdisk *mrdiskk;
    class clfdisk *fdiskk;
    class clmount *modiskk;
    class clunmount *unmdiskk;
    class clmkfs *mkdiskk;
    class clexec *archexec;

#line 137 "parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
