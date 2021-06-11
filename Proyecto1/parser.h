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
#line 35 "sintactico.y" /* yacc.c:1909  */

    char TEXT[500];
    class clmkdisk *mdisk;
    class clrmdisk *mrdiskk;
    class clfdisk *fdiskk;
    class clmount *modiskk;
    class clunmount *unmdiskk;
    class clmkfs *mkdiskk;
    class clexec *archexec;
    class clReportes *creporte;

#line 139 "parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
