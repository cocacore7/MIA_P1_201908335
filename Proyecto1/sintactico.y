%{
    #include <iostream>
    #include <QString>
    #include "scanner.h"
    #include "clmkdisk.h"
    #include "clrmdisk.h"
    #include "clfdisk.h"
    #include "clmount.h"
    #include "clunmount.h"
    #include "clmkfs.h"

    extern int yylex(void);
    extern int resultado;
    clmkdisk *mkdisco = new clmkdisk();
    clrmdisk *rmdisco = new clrmdisk();
    clfdisk *ffdisco = new clfdisk();
    clmount *modisco = new clmount();
    clunmount *unmdisco = new clunmount();
    clmkfs *mkfsdisco = new clmkfs();

    int yyerror(const char* mens){
        std::cout << mens << std::endl;
        return 0;
    }
%}

%error-verbose

%union{
    char TEXT[500];
    class clmkdisk *mdisk;
    class clrmdisk *mrdiskk;
    class clfdisk *fdiskk;
    class clmount *modiskk;
    class clunmount *unmdiskk;
    class clmkfs *mkdiskk;
}

%token <TEXT> digito
%token <TEXT> ident
%token <TEXT> cadena
%token <TEXT> filen
%token <TEXT> idp
%token <TEXT> ruta

%token <TEXT> mkdisk
%token <TEXT> rmdisk
%token <TEXT> fdisk
%token <TEXT> mount
%token <TEXT> unmount
%token <TEXT> mkfs
%token <TEXT> login
%token <TEXT> logout
%token <TEXT> mkgrp
%token <TEXT> rmgrp
%token <TEXT> mkusr
%token <TEXT> rmusr
%token <TEXT> mkfile
%token <TEXT> cat
%token <TEXT> rem
%token <TEXT> edit
%token <TEXT> ren
%token <TEXT> cp
%token <TEXT> mv
%token <TEXT> find
%token <TEXT> chownn
%token <TEXT> chgrp
%token <TEXT> pausee

%token <TEXT> igual
%token <TEXT> dividido
%token <TEXT> interrogacion
%token <TEXT> multiplicacion
%token <TEXT> negativo

%token <TEXT> sizee
%token <TEXT> f
%token <TEXT> u
%token <TEXT> pathh
%token <TEXT> typee
%token <TEXT> deletee
%token <TEXT> namee
%token <TEXT> addd
%token <TEXT> id
%token <TEXT> fs
%token <TEXT> usr
%token <TEXT> pwd
%token <TEXT> grp
%token <TEXT> ugo
%token <TEXT> r
%token <TEXT> cont
%token <TEXT> filenn
%token <TEXT> dest
%token <TEXT> p

%token <TEXT> BF
%token <TEXT> FF
%token <TEXT> WF
%token <TEXT> K
%token <TEXT> M
%token <TEXT> B
%token <TEXT> PP
%token <TEXT> E
%token <TEXT> L
%token <TEXT> FAST
%token <TEXT> FULL
%token <TEXT> FS2
%token <TEXT> FS3

%type <mdisk>       COMMKDISK;
%type <mrdiskk>     COMRMDISK;
%type <fdiskk>      COMFDISK;
%type <modiskk>     COMMOUNT;
%type <unmdiskk>    COMUNMOUNT;
%type <mkdiskk>     COMFSDISK;


%start INICIO
%%

INICIO:     COMANDOS                        { };

COMANDOS:   mkdisk COMMKDISK                        {$2->mostrarDatos($2); printf("Comando MKDISK");};
            |rmdisk COMRMDISK                       {$2->mostrarDatos($2); printf("Comando RMDISK");};
            |fdisk COMFDISK                         {$2->mostrarDatos($2); printf("Comando FDISK");};
            |mount COMMOUNT                         {$2->mostrarDatos($2); printf("Comando MOUT");};
            |unmount COMUNMOUNT                     {$2->mostrarDatos($2); printf("Comando UNMOUNT");};
            |mkfs COMFSDISK                         {$2->mostrarDatos($2); printf("Comando MKFS");};

COMMKDISK:  sizee igual digito COMMKDISK            {int tam=atoi($3); mkdisco->size=tam; $$=mkdisco;};
            |f igual BF COMMKDISK                   {mkdisco->f=$3; $$=mkdisco;};
            |f igual FF COMMKDISK                   {mkdisco->f=$3; $$=mkdisco;};
            |f igual WF COMMKDISK                   {mkdisco->f=$3; $$=mkdisco;};
            |u igual K  COMMKDISK                   {mkdisco->u=$3; $$=mkdisco;};
            |u igual M  COMMKDISK                   {mkdisco->u=$3; $$=mkdisco;};
            |pathh igual cadena COMMKDISK           {mkdisco->path=$3; $$=mkdisco;};
            |pathh igual ruta COMMKDISK             {mkdisco->path=$3; $$=mkdisco;};
            |sizee igual digito                     {int tam=atoi($3); mkdisco->size=tam; $$=mkdisco;};
            |f igual BF                             {mkdisco->f=$3; $$=mkdisco;};
            |f igual FF                             {mkdisco->f=$3; $$=mkdisco;};
            |f igual WF                             {mkdisco->f=$3; $$=mkdisco;};
            |u igual K                              {mkdisco->u=$3; $$=mkdisco;};
            |u igual M                              {mkdisco->u=$3; $$=mkdisco;};
            |pathh igual cadena                     {mkdisco->path=$3; $$=mkdisco;};
            |pathh igual ruta                       {mkdisco->path=$3; $$=mkdisco;};

COMRMDISK:  pathh igual cadena COMRMDISK            {rmdisco->path=$3; $$=rmdisco;};
            |pathh igual ruta COMRMDISK             {rmdisco->path=$3; $$=rmdisco;};
            |pathh igual cadena                     {rmdisco->path=$3; $$=rmdisco;};
            |pathh igual ruta                       {rmdisco->path=$3; $$=rmdisco;};

COMFDISK:   sizee igual digito COMFDISK             {int tam=atoi($3); if(ffdisco->primero!=""){ffdisco->primero="s"}; ffdisco->size=tam; $$=ffdisco;};
            |u igual K  COMFDISK                    {ffdisco->u=$3; $$=ffdisco;};
            |u igual M  COMFDISK                    {ffdisco->u=$3; $$=ffdisco;};
            |u igual B  COMFDISK                    {ffdisco->u=$3; $$=ffdisco;};
            |pathh igual cadena COMFDISK            {ffdisco->path=$3; $$=ffdisco;};
            |pathh igual ruta COMFDISK              {ffdisco->path=$3; $$=ffdisco;};
            |typee igual PP COMFDISK                {ffdisco->typee=$3; $$=ffdisco;};
            |typee igual E  COMFDISK                {ffdisco->typee=$3; $$=ffdisco;};
            |typee igual L  COMFDISK                {ffdisco->typee=$3; $$=ffdisco;};
            |f igual BF COMFDISK                    {ffdisco->f=$3; $$=ffdisco;};
            |f igual FF COMFDISK                    {ffdisco->f=$3; $$=ffdisco;};
            |f igual WF COMFDISK                    {ffdisco->f=$3; $$=ffdisco;};
            |deletee igual FAST COMFDISK            {ffdisco->deletee=$3; $$=ffdisco;};
            |deletee igual FULL COMFDISK            {ffdisco->deletee=$3; $$=ffdisco;};
            |namee igual cadena COMFDISK            {ffdisco->namee=$3; $$=ffdisco;};
            |namee igual ident COMFDISK             {ffdisco->namee=$3; $$=ffdisco;};
            |addd igual digito COMFDISK             {int tam=atoi($3); if(ffdisco->primero!=""){ffdisco->primero="a"}; ffdisco->addd=tam; $$=ffdisco;};
            |addd igual negativo digito COMFDISK    {int tam=atoi($4); if(ffdisco->primero!=""){ffdisco->primero="a"}; ffdisco->addd=tam * -1; $$=ffdisco;};
            |sizee igual digito                     {int tam=atoi($3); if(ffdisco->primero!=""){ffdisco->primero="s"}; ffdisco->size=tam; $$=ffdisco;};
            |u igual K                              {ffdisco->u=$3; $$=ffdisco;};
            |u igual M                              {ffdisco->u=$3; $$=ffdisco;};
            |u igual B                              {ffdisco->u=$3; $$=ffdisco;};
            |pathh igual cadena                     {ffdisco->path=$3; $$=ffdisco;};
            |pathh igual ruta                       {ffdisco->path=$3; $$=ffdisco;};
            |typee igual PP                         {ffdisco->typee=$3; $$=ffdisco;};
            |typee igual E                          {ffdisco->typee=$3; $$=ffdisco;};
            |typee igual L                          {ffdisco->typee=$3; $$=ffdisco;};
            |f igual BF                             {ffdisco->f=$3; $$=ffdisco;};
            |f igual FF                             {ffdisco->f=$3; $$=ffdisco;};
            |f igual WF                             {ffdisco->f=$3; $$=ffdisco;};
            |deletee igual FAST                     {ffdisco->deletee=$3; $$=ffdisco;};
            |deletee igual FULL                     {ffdisco->deletee=$3; $$=ffdisco;};
            |namee igual cadena                     {ffdisco->namee=$3; $$=ffdisco;};
            |namee igual ident                      {ffdisco->namee=$3; $$=ffdisco;};
            |addd igual digito                      {int tam=atoi($3); if(ffdisco->primero!=""){ffdisco->primero="a"}; ffdisco->addd=tam; $$=ffdisco;};
            |addd igual negativo digito             {int tam=atoi($4); if(ffdisco->primero!=""){ffdisco->primero="a"}; ffdisco->addd=tam*-1; $$=ffdisco;};

COMMOUNT:   pathh igual cadena COMMOUNT             {modisco->path=$3; $$=modisco;};
            |pathh igual ruta COMMOUNT              {modisco->path=$3; $$=modisco;};
            |namee igual cadena COMMOUNT            {modisco->namee=$3; $$=modisco;};
            |namee igual ident COMMOUNT             {modisco->namee=$3; $$=modisco;};
            |pathh igual cadena                     {modisco->path=$3; $$=modisco;};
            |pathh igual ruta                       {modisco->path=$3; $$=modisco;};
            |namee igual cadena                     {modisco->namee=$3; $$=modisco;};
            |namee igual ident                      {modisco->namee=$3; $$=modisco;};

COMUNMOUNT: id igual idp COMUNMOUNT                 {unmdisco->id=$3; $$=unmdisco;};
            |id igual idp                           {unmdisco->id=$3; $$=unmdisco;};

COMFSDISK:  id igual idp COMFSDISK                  {mkfsdisco->id=$3; $$=mkfsdisco;};
            |typee igual FAST COMFSDISK             {mkfsdisco->type=$3; $$=mkfsdisco;};
            |typee igual FULL  COMFSDISK            {mkfsdisco->type=$3; $$=mkfsdisco;};
            |fs igual FS2  COMFSDISK                {mkfsdisco->fs=$3; $$=mkfsdisco;};
            |fs igual FS3  COMFSDISK                {mkfsdisco->fs=$3; $$=mkfsdisco;};
            |id igual idp                           {mkfsdisco->id=$3; $$=mkfsdisco;};
            |typee igual FAST                       {mkfsdisco->type=$3; $$=mkfsdisco;};
            |typee igual FULL                       {mkfsdisco->type=$3; $$=mkfsdisco;};
            |fs igual FS2                           {mkfsdisco->fs=$3; $$=mkfsdisco;};
            |fs igual FS3                           {mkfsdisco->fs=$3; $$=mkfsdisco;};

%%
