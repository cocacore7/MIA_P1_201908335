%{
    #include <iostream>
    #include "parser.h"
    int resultado;
%}

%option case-insensitive
%option noyywrap

digito [0-9]+
letra [a-zA-Z]+

identificador ({letra})({letra}|{digito}|"_")*
cadena [\"][^\"\n]*[\"\n]

filen "file"{digito}
idp "35"{digito}{letra}
ruta ("/"{identificador})+("/"{identificador}"."{identificador})
ugo [0-7][0-7][0-7]

%%

{ugo}           {yylval.TEXT = yytext; return(ugo);}
{digito}        {yylval.TEXT = yytext; return(digito);}
{cadena}        {yylval.TEXT = yytext; return(cadena);}
{filen}         {yylval.TEXT = yytext; return(filen);}
{idp}           {yylval.TEXT = yytext; return(idp);}
{ruta}          {yylval.TEXT = yytext; return(ruta);}



"mkdisk"        {yylval.TEXT = yytext; return(mkdisk);}
"rmdisk"        {yylval.TEXT = yytext; return(rmdisk);}
"fdisk"         {yylval.TEXT = yytext; return(fdisk);}
"mount"         {yylval.TEXT = yytext; return(mount);}
"unmount"       {yylval.TEXT = yytext; return(unmount);}
"mkfs"          {yylval.TEXT = yytext; return(mkfs);}
"login"         {yylval.TEXT = yytext; return(login);}
"logout"        {yylval.TEXT = yytext; return(logout);}
"mkgrp"         {yylval.TEXT = yytext; return(mkgrp);}
"rmgrp"         {yylval.TEXT = yytext; return(rmgrp);}
"mkusr"         {yylval.TEXT = yytext; return(mkusr);}
"rmusr"         {yylval.TEXT = yytext; return(rmusr);}
"mkfile"        {yylval.TEXT = yytext; return(mkfile);}
"cat"           {yylval.TEXT = yytext; return(cat);}
"rem"           {yylval.TEXT = yytext; return(rem);}
"edit"          {yylval.TEXT = yytext; return(edit);}
"ren"           {yylval.TEXT = yytext; return(ren);}
"cp"            {yylval.TEXT = yytext; return(cp);}
"mv"            {yylval.TEXT = yytext; return(mv);}
"find"          {yylval.TEXT = yytext; return(find);}
"chown"         {yylval.TEXT = yytext; return(chownn);}
"chgrp"         {yylval.TEXT = yytext; return(chgrp);}
"pause"         {yylval.TEXT = yytext; return(pausee);}

"="             {yylval.TEXT = yytext; return(igual);}
"/"             {yylval.TEXT = yytext; return(dividido);}
"?"             {yylval.TEXT = yytext; return(interrogacion);}
"*"             {yylval.TEXT = yytext; return(multiplicacion);}

"-size"         {yylval.TEXT = yytext; return(sizee);}
"-f"            {yylval.TEXT = yytext; return(f);}
"-u"            {yylval.TEXT = yytext; return(u);}
"-path"         {yylval.TEXT = yytext; return(pathh);}
"-type"         {yylval.TEXT = yytext; return(typee);}
"-delete"       {yylval.TEXT = yytext; return(deletee);}
"-name"         {yylval.TEXT = yytext; return(namee);}
"-add"          {yylval.TEXT = yytext; return(addd);}
"-id"           {yylval.TEXT = yytext; return(id);}
"-fs"           {yylval.TEXT = yytext; return(fs);}
"-usr"          {yylval.TEXT = yytext; return(usr);}
"-pwd"          {yylval.TEXT = yytext; return(pwd);}
"-grp"          {yylval.TEXT = yytext; return(grp);}
"-ugo"          {yylval.TEXT = yytext; return(ugoo);}
"-r"            {yylval.TEXT = yytext; return(r);}
"-cont"         {yylval.TEXT = yytext; return(cont);}
"-filen"        {yylval.TEXT = yytext; return(filenn);}
"-dest"         {yylval.TEXT = yytext; return(dest);}
"-p"            {yylval.TEXT = yytext; return(p);}

"BF"            {yylval.TEXT = yytext; return(BF);}
"FF"            {yylval.TEXT = yytext; return(FF);}
"WF"            {yylval.TEXT = yytext; return(WF);}
"k"             {yylval.TEXT = yytext; return(K);}
"m"             {yylval.TEXT = yytext; return(M);}
"P"             {yylval.TEXT = yytext; return(PP);}
"E"             {yylval.TEXT = yytext; return(E);}
"L"             {yylval.TEXT = yytext; return(L);}
"fast"          {yylval.TEXT = yytext; return(FAST);}
"full"          {yylval.TEXT = yytext; return(FULL);}
"2fs"           {yylval.TEXT = yytext; return(FS2);}
"3fs"           {yylval.TEXT = yytext; return(FS3);}

[a-zA-Z]+([a-zA-Z]+|[0-9]+|"_")* {yylval.TEXT = yytext; return(ident);}
[ \t\r\f\n]      {}

.               {std::cout<<"Error Lexico"<<std::endl;}
%%
