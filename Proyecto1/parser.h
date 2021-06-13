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
#line 80 "sintactico.y" /* yacc.c:1909  */

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

#line 167 "parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
