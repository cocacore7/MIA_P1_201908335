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

    class cllogin *clogin;
    class clmkgrp *cmkgrp;
    class clrmgrp *crmgrp;
    class clmkuser *cmkuser;
    class clrmuser *crmuser;

    class clexec *archexec;
    class clReportes *creporte;
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
%token <clogin> logout
%token <TEXT> mkgrp
%token <TEXT> rmgrp
%token <TEXT> mkusr
%token <TEXT> rmusr
%token <TEXT> mkfile
%token <TEXT> mkdirr
%token <TEXT> cat
%token <TEXT> rem
%token <TEXT> edit
%token <TEXT> ren
%token <TEXT> cp
%token <TEXT> mv
%token <TEXT> find
%token <TEXT> chownn
%token <TEXT> chgrp
%token <TEXT> execc
%token <TEXT> pausee
%token <TEXT> comentario
%token <TEXT> rep

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
%token <TEXT> rr
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

%type <clogin>      COMLOGIN;
%type <cmkgrp>      COMMKGRP;
%type <crmgrp>      COMRMGRP;
%type <cmkuser>     COMMKUSER;
%type <crmuser>     COMRMUSER;

%type <archexec>    COMEXEC;
%type <creporte>    COMREPORTE;

%start INICIO
%%

INICIO:     COMANDOS                                { };

COMANDOS:   mkdisk COMMKDISK                        {$2->mostrarDatos($2); cout<<"Comando MKDISK"<<endl;};
            |rmdisk COMRMDISK                       {$2->mostrarDatos($2); cout<<"Comando RMDISK"<<endl;};
            |fdisk COMFDISK                         {$2->mostrarDatos($2); cout<<"Comando FDISK"<<endl;};
            |mount COMMOUNT                         {$2->mostrarDatos($2); cout<<"Comando MOUNT"<<endl;};
            |unmount COMUNMOUNT                     {$2->mostrarDatos($2); cout<<"Comando UNMOUNT"<<endl;};
            |mkfs COMFSDISK                         {$2->mostrarDatos($2); cout<<"Comando MKFS"<<endl;};

            |login COMLOGIN                         {$2->logear($2);       cout<<"Comando LOGIN"<<endl;};
            |mkgrp COMMKGRP                         {$2->mostrarDatos($2); cout<<"Comando MKGRP"<<endl;};
            |rmgrp COMRMGRP                         {$2->mostrarDatos($2); cout<<"Comando RMGRP"<<endl;};
            |mkusr COMMKUSER                        {$2->mostrarDatos($2); cout<<"Comando MKUSER"<<endl;};
            |rmusr COMRMUSER                        {$2->mostrarDatos($2); cout<<"Comando RMUSER"<<endl;};

            |execc COMEXEC                          {$2->mostrarDatos($2); cout<<"Comando EXEC"<<endl;};
            |rep COMREPORTE                         {$2->mostrarDatos($2); cout<<"Comando REPORTE"<<endl;};
            |logout                                 {$1->salir();          cout<<"Comando LOGOUT"<<endl;};
            |pausee                                 {cout<<"Ingrese una tecla para continuar"<<endl; cin.get();};
            |comentario                             {};

COMMKDISK:  sizee igual digito COMMKDISK            {int tam=atoi($3); if(mkdisco->size==0){mkdisco->size=tam;} $$=mkdisco;};
            |f igual BF COMMKDISK                   {if(mkdisco->f==""){mkdisco->f=$3;} $$=mkdisco;};
            |f igual FF COMMKDISK                   {if(mkdisco->f==""){mkdisco->f=$3;} $$=mkdisco;};
            |f igual WF COMMKDISK                   {if(mkdisco->f==""){mkdisco->f=$3;} $$=mkdisco;};
            |u igual K  COMMKDISK                   {if(mkdisco->u==""){mkdisco->u=$3;} $$=mkdisco;};
            |u igual M  COMMKDISK                   {if(mkdisco->u==""){mkdisco->u=$3;} $$=mkdisco;};
            |pathh igual cadena COMMKDISK           {if(mkdisco->path==""){mkdisco->path=$3;} $$=mkdisco;};
            |pathh igual ruta COMMKDISK             {if(mkdisco->path==""){mkdisco->path=$3;} $$=mkdisco;};
            |sizee igual digito                     {int tam=atoi($3); if(mkdisco->size!=0){mkdisco->size=tam;} $$=mkdisco;};
            |f igual BF                             {if(mkdisco->f==""){mkdisco->f=$3;} $$=mkdisco;};
            |f igual FF                             {if(mkdisco->f==""){mkdisco->f=$3;} $$=mkdisco;};
            |f igual WF                             {if(mkdisco->f==""){mkdisco->f=$3;} $$=mkdisco;};
            |u igual K                              {if(mkdisco->u==""){mkdisco->u=$3;} $$=mkdisco;};
            |u igual M                              {if(mkdisco->u==""){mkdisco->u=$3;} $$=mkdisco;};
            |pathh igual cadena                     {if(mkdisco->path==""){mkdisco->path=$3;} $$=mkdisco;};
            |pathh igual ruta                       {if(mkdisco->path==""){mkdisco->path=$3;} $$=mkdisco;};

COMRMDISK:  pathh igual cadena COMRMDISK            {if(rmdisco->path==""){rmdisco->path=$3;} $$=rmdisco;};
            |pathh igual ruta COMRMDISK             {if(rmdisco->path==""){rmdisco->path=$3;} $$=rmdisco;};
            |pathh igual cadena                     {if(rmdisco->path==""){rmdisco->path=$3;} $$=rmdisco;};
            |pathh igual ruta                       {if(rmdisco->path==""){rmdisco->path=$3;} $$=rmdisco;};

COMFDISK:   sizee igual digito COMFDISK             {int tam=atoi($3); if(ffdisco->primero==""){ffdisco->primero="s";} if(ffdisco->size==0){ffdisco->size=tam;} $$=ffdisco;};
            |u igual K  COMFDISK                    {if(ffdisco->u==""){ffdisco->u=$3;} $$=ffdisco;};
            |u igual M  COMFDISK                    {if(ffdisco->u==""){ffdisco->u=$3;} $$=ffdisco;};
            |u igual B  COMFDISK                    {if(ffdisco->u==""){ffdisco->u=$3;} $$=ffdisco;};
            |pathh igual cadena COMFDISK            {if(ffdisco->path==""){ffdisco->path=$3;} $$=ffdisco;};
            |pathh igual ruta COMFDISK              {if(ffdisco->path==""){ffdisco->path=$3;} $$=ffdisco;};
            |typee igual PP COMFDISK                {if(ffdisco->typee==""){ffdisco->typee=$3;} $$=ffdisco;};
            |typee igual E  COMFDISK                {if(ffdisco->typee==""){ffdisco->typee=$3;} $$=ffdisco;};
            |typee igual L  COMFDISK                {if(ffdisco->typee==""){ffdisco->typee=$3;} $$=ffdisco;};
            |f igual BF COMFDISK                    {if(ffdisco->f==""){ffdisco->f=$3;} $$=ffdisco;};
            |f igual FF COMFDISK                    {if(ffdisco->f==""){ffdisco->f=$3;} $$=ffdisco;};
            |f igual WF COMFDISK                    {if(ffdisco->f==""){ffdisco->f=$3;} $$=ffdisco;};
            |deletee igual FAST COMFDISK            {if(ffdisco->deletee==""){ffdisco->deletee=$3;} $$=ffdisco;};
            |deletee igual FULL COMFDISK            {if(ffdisco->deletee==""){ffdisco->deletee=$3;} $$=ffdisco;};
            |namee igual cadena COMFDISK            {if(ffdisco->namee==""){ffdisco->namee=$3;} $$=ffdisco;};
            |namee igual ident COMFDISK             {if(ffdisco->namee==""){ffdisco->namee=$3;} $$=ffdisco;};
            |addd igual digito COMFDISK             {int tam=atoi($3); if(ffdisco->primero==""){ffdisco->primero="a";} if(ffdisco->addd==0){ffdisco->addd=tam;} $$=ffdisco;};
            |addd igual negativo digito COMFDISK    {int tam=atoi($4); if(ffdisco->primero==""){ffdisco->primero="a";} if(ffdisco->addd==0){ffdisco->addd=tam * -1;} $$=ffdisco;};
            |sizee igual digito                     {int tam=atoi($3); if(ffdisco->primero==""){ffdisco->primero="s";} if(ffdisco->size==0){ffdisco->size=tam;} $$=ffdisco;};
            |u igual K                              {if(ffdisco->u==""){ffdisco->u=$3;} $$=ffdisco;};
            |u igual M                              {if(ffdisco->u==""){ffdisco->u=$3;} $$=ffdisco;};
            |u igual B                              {if(ffdisco->u==""){ffdisco->u=$3;} $$=ffdisco;};
            |pathh igual cadena                     {if(ffdisco->path==""){ffdisco->path=$3;} $$=ffdisco;};
            |pathh igual ruta                       {if(ffdisco->path==""){ffdisco->path=$3;} $$=ffdisco;};
            |typee igual PP                         {if(ffdisco->typee==""){ffdisco->typee=$3;} $$=ffdisco;};
            |typee igual E                          {if(ffdisco->typee==""){ffdisco->typee=$3;} $$=ffdisco;};
            |typee igual L                          {if(ffdisco->typee==""){ffdisco->typee=$3;} $$=ffdisco;};
            |f igual BF                             {if(ffdisco->f==""){ffdisco->f=$3;} $$=ffdisco;};
            |f igual FF                             {if(ffdisco->f==""){ffdisco->f=$3;} $$=ffdisco;};
            |f igual WF                             {if(ffdisco->f==""){ffdisco->f=$3;} $$=ffdisco;};
            |deletee igual FAST                     {if(ffdisco->deletee==""){ffdisco->deletee=$3;} $$=ffdisco;};
            |deletee igual FULL                     {if(ffdisco->deletee==""){ffdisco->deletee=$3;} $$=ffdisco;};
            |namee igual cadena                     {if(ffdisco->namee==""){ffdisco->namee=$3;} $$=ffdisco;};
            |namee igual ident                      {if(ffdisco->namee==""){ffdisco->namee=$3;} $$=ffdisco;};
            |addd igual digito                      {int tam=atoi($3); if(ffdisco->primero==""){ffdisco->primero="a";} if(ffdisco->addd==0){ffdisco->addd=tam;} $$=ffdisco;};
            |addd igual negativo digito             {int tam=atoi($4); if(ffdisco->primero==""){ffdisco->primero="a";} if(ffdisco->addd==0){ffdisco->addd=tam * -1;} $$=ffdisco;};

COMMOUNT:   pathh igual cadena COMMOUNT             {if(modisco->path==""){modisco->path=$3;} $$=modisco;};
            |pathh igual ruta COMMOUNT              {if(modisco->path==""){modisco->path=$3;} $$=modisco;};
            |namee igual cadena COMMOUNT            {if(modisco->namee==""){modisco->namee=$3;} $$=modisco;};
            |namee igual ident COMMOUNT             {if(modisco->namee==""){modisco->namee=$3;} $$=modisco;};
            |pathh igual cadena                     {if(modisco->path==""){modisco->path=$3;} $$=modisco;};
            |pathh igual ruta                       {if(modisco->path==""){modisco->path=$3;} $$=modisco;};
            |namee igual cadena                     {if(modisco->namee==""){modisco->namee=$3;} $$=modisco;};
            |namee igual ident                      {if(modisco->namee==""){modisco->namee=$3;} $$=modisco;};

COMUNMOUNT: id igual idp COMUNMOUNT                 {if(unmdisco->id==""){unmdisco->id=$3;} $$=unmdisco;};
            |id igual idp                           {if(unmdisco->id==""){unmdisco->id=$3;} $$=unmdisco;};

COMFSDISK:  id igual idp COMFSDISK                  {if(mkfsdisco->id==""){mkfsdisco->id=$3;} $$=mkfsdisco;};
            |typee igual FAST COMFSDISK             {if(mkfsdisco->type==""){mkfsdisco->type=$3;} $$=mkfsdisco;};
            |typee igual FULL  COMFSDISK            {if(mkfsdisco->type==""){mkfsdisco->type=$3;} $$=mkfsdisco;};
            |fs igual FS2  COMFSDISK                {if(mkfsdisco->fs==""){mkfsdisco->fs=$3;} $$=mkfsdisco;};
            |fs igual FS3  COMFSDISK                {if(mkfsdisco->fs==""){mkfsdisco->fs=$3;} $$=mkfsdisco;};
            |id igual idp                           {if(mkfsdisco->id==""){mkfsdisco->id=$3;} $$=mkfsdisco;};
            |typee igual FAST                       {if(mkfsdisco->type==""){mkfsdisco->type=$3;} $$=mkfsdisco;};
            |typee igual FULL                       {if(mkfsdisco->type==""){mkfsdisco->type=$3;} $$=mkfsdisco;};
            |fs igual FS2                           {if(mkfsdisco->fs==""){mkfsdisco->fs=$3;} $$=mkfsdisco;};
            |fs igual FS3                           {if(mkfsdisco->fs==""){mkfsdisco->fs=$3;} $$=mkfsdisco;};

COMEXEC:    pathh igual cadena COMEXEC              {if(script->path==""){script->path=$3;} $$=script;};
            |pathh igual ruta COMEXEC               {if(script->path==""){script->path=$3;} $$=script;};
            |pathh igual cadena                     {if(script->path==""){script->path=$3;} $$=script;};
            |pathh igual ruta                       {if(script->path==""){script->path=$3;} $$=script;};

COMREPORTE: pathh igual cadena COMREPORTE           {if(reporte->path==""){reporte->path=$3;} $$=reporte;};
            |pathh igual ruta COMREPORTE            {if(reporte->path==""){reporte->path=$3;} $$=reporte;};
            |namee igual cadena COMREPORTE          {if(reporte->namee==""){reporte->namee=$3;} $$=reporte;};
            |namee igual ident COMREPORTE           {if(reporte->namee==""){reporte->namee=$3;} $$=reporte;};
            |id igual idp COMREPORTE                {if(reporte->id==""){reporte->id=$3;} $$=reporte;};
            |pathh igual cadena                     {if(reporte->path==""){reporte->path=$3;} $$=reporte;};
            |pathh igual ruta                       {if(reporte->path==""){reporte->path=$3;} $$=reporte;};
            |namee igual cadena                     {if(reporte->namee==""){reporte->namee=$3;} $$=reporte;};
            |namee igual ident                      {if(reporte->namee==""){reporte->namee=$3;} $$=reporte;};
            |id igual idp                           {if(reporte->id==""){reporte->id=$3;} $$=reporte;};

COMLOGIN:   usr igual cadena COMLOGIN               {if(loginn->usr==""){loginn->usr=$3;} $$=loginn;};
            |usr igual ident COMLOGIN               {if(loginn->usr==""){loginn->usr=$3;} $$=loginn;};
            |pwd igual cadena COMLOGIN              {if(loginn->pwd==""){loginn->pwd=$3;} $$=loginn;};
            |pwd igual ident COMLOGIN               {if(loginn->pwd==""){loginn->pwd=$3;} $$=loginn;};
            |pwd igual digito COMLOGIN              {if(loginn->pwd==""){loginn->pwd=$3;} $$=loginn;};
            |id igual idp COMLOGIN                  {if(loginn->id==""){loginn->id=$3;} $$=loginn;};
            |usr igual cadena                       {if(loginn->usr==""){loginn->usr=$3;} $$=loginn;};
            |usr igual ident                        {if(loginn->usr==""){loginn->usr=$3;} $$=loginn;};
            |pwd igual cadena                       {if(loginn->pwd==""){loginn->pwd=$3;} $$=loginn;};
            |pwd igual ident                        {if(loginn->pwd==""){loginn->pwd=$3;} $$=loginn;};
            |pwd igual digito                       {if(loginn->pwd==""){loginn->pwd=$3;} $$=loginn;};
            |id igual idp                           {if(loginn->id==""){loginn->id=$3;} $$=loginn;};

COMMKGRP:   namee igual cadena COMMKGRP             {if(mkgrpp->name==""){mkgrpp->name=$3;} $$=mkgrpp;};
            |namee igual ident COMMKGRP             {if(mkgrpp->name==""){mkgrpp->name=$3;} $$=mkgrpp;};
            |namee igual cadena                     {if(mkgrpp->name==""){mkgrpp->name=$3;} $$=mkgrpp;};
            |namee igual ident                      {if(mkgrpp->name==""){mkgrpp->name=$3;} $$=mkgrpp;};

COMRMGRP:   namee igual cadena COMRMGRP             {if(rmgrpp->name==""){rmgrpp->name=$3;} $$=rmgrpp;};
            |namee igual ident COMRMGRP             {if(rmgrpp->name==""){rmgrpp->name=$3;} $$=rmgrpp;};
            |namee igual cadena                     {if(rmgrpp->name==""){rmgrpp->name=$3;} $$=rmgrpp;};
            |namee igual ident                      {if(rmgrpp->name==""){rmgrpp->name=$3;} $$=rmgrpp;};

COMMKUSER:  usr igual cadena COMMKUSER              {if(mkuserr->usr==""){mkuserr->usr=$3;} $$=mkuserr;};
            |usr igual ident COMMKUSER              {if(mkuserr->usr==""){mkuserr->usr=$3;} $$=mkuserr;};
            |pwd igual cadena COMMKUSER             {if(mkuserr->pwd==""){mkuserr->pwd=$3;} $$=mkuserr;};
            |pwd igual ident COMMKUSER              {if(mkuserr->pwd==""){mkuserr->pwd=$3;} $$=mkuserr;};
            |pwd igual digito COMMKUSER             {if(mkuserr->pwd==""){mkuserr->pwd=$3;} $$=mkuserr;};
            |grp igual cadena COMMKUSER             {if(mkuserr->pwd==""){mkuserr->pwd=$3;} $$=mkuserr;};
            |grp igual ident COMMKUSER              {if(mkuserr->pwd==""){mkuserr->pwd=$3;} $$=mkuserr;};
            |usr igual cadena                       {if(mkuserr->usr==""){mkuserr->usr=$3;} $$=mkuserr;};
            |usr igual ident                        {if(mkuserr->usr==""){mkuserr->usr=$3;} $$=mkuserr;};
            |pwd igual cadena                       {if(mkuserr->pwd==""){mkuserr->pwd=$3;} $$=mkuserr;};
            |pwd igual ident                        {if(mkuserr->pwd==""){mkuserr->pwd=$3;} $$=mkuserr;};
            |pwd igual digito                        {if(mkuserr->pwd==""){mkuserr->pwd=$3;} $$=mkuserr;};
            |grp igual cadena                       {if(mkuserr->pwd==""){mkuserr->pwd=$3;} $$=mkuserr;};
            |grp igual ident                        {if(mkuserr->pwd==""){mkuserr->pwd=$3;} $$=mkuserr;};

COMRMUSER:  usr igual cadena COMRMUSER              {if(rmuserr->usr==""){rmuserr->usr=$3;} $$=rmuserr;};
            |usr igual ident COMRMUSER              {if(rmuserr->usr==""){rmuserr->usr=$3;} $$=rmuserr;};
            |usr igual cadena                       {if(rmuserr->usr==""){rmuserr->usr=$3;} $$=rmuserr;};
            |usr igual ident                        {if(rmuserr->usr==""){rmuserr->usr=$3;} $$=rmuserr;};


%%
