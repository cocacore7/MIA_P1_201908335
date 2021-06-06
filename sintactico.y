%{
    #include <iostream>
    #include "scanner.h"
    #include "clmkdisk.h"

    extern int yylex(void);
    extern int resultado;

    int yyerror(const char* mens){
        std::cout << mens << std::endl;
        return 0;
    }
%}

%error-verbose

%union{
    char* TEXT;
    class clmkdisk *mdisk;
}

%token <TEXT> digito
%token <TEXT> ident
%token <TEXT> cadena
%token <TEXT> filen
%token <TEXT> idp
%token <TEXT> ruta
%token <TEXT> ugo

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
%token <TEXT> ugoo
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
%token <TEXT> PP
%token <TEXT> E
%token <TEXT> L
%token <TEXT> FAST
%token <TEXT> FULL
%token <TEXT> FS2
%token <TEXT> FS3

%type <mdisk> COMMKDISK;


%start INICIO
%%

INICIO:     COMANDOS { };

COMANDOS:   mkdisk COMMKDISK {$2->mostrarDatos($2); printf("Comando MKDISK");};

COMMKDISK: sizee igual digito {int tam=atoi($3); clmkdisk *disco = new clmkdisk(); disco->size=tam; $$=disco;};

%%
