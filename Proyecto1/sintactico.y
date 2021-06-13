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
}

%token <TEXT> digito
%token <TEXT> ident
%token <TEXT> cadena
%token <TEXT> filen
%token <TEXT> idp
%token <TEXT> rutaelim
%token <TEXT> rutaarch
%token <TEXT> rutacat
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

%token <TEXT> chmoddd
%token <TEXT> mkfile
%token <TEXT> cat
%token <TEXT> rem
%token <TEXT> edit
%token <TEXT> ren
%token <TEXT> mkdirr
%token <TEXT> cp
%token <TEXT> mv
%token <TEXT> find
%token <TEXT> chownn
%token <TEXT> chgrp

%token <TEXT> execc
%token <TEXT> pausee
%token <TEXT> comentario
%token <TEXT> rep
%token <TEXT> recovery
%token <TEXT> loss

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
%token <TEXT> dest
%token <TEXT> p
%token <TEXT> file

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

%type <cchmmod>     COMCHMOD;
%type <cmkfile>     COMKFILE;
%type <ccat>        COMCAT;
%type <crem>        COMREM;
%type <cedit>       COMEDIT;
%type <cren>        COMREN;
%type <cmkdir>      COMMKDIR;
%type <ccp>         COMCP;
%type <cmv>         COMMV;
%type <cfind>       COMFIND;
%type <cchown>      COMCHOWN;
%type <cchgrp>      COMCHGRP;

%type <archexec>    COMEXEC;
%type <creporte>    COMREPORTE;
%type <crecup>      COMRECUP;
%type <cperd>       COMPERD;

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

            |chmoddd COMCHMOD                       {$2->mostrarDatos($2); cout<<"Comando CHMOD"<<endl;};
            |mkfile COMKFILE                        {$2->mostrarDatos($2); cout<<"Comando MKFILE"<<endl;};
            |cat COMCAT                             {$2->mostrarDatos($2); cout<<"Comando CAT"<<endl;};
            |rem COMREM                             {$2->mostrarDatos($2); cout<<"Comando REM"<<endl;};
            |edit COMEDIT                           {$2->mostrarDatos($2); cout<<"Comando EDIT"<<endl;};
            |ren COMREN                             {$2->mostrarDatos($2); cout<<"Comando REN"<<endl;};
            |mkdirr COMMKDIR                        {$2->mostrarDatos($2); cout<<"Comando MKDIR"<<endl;};
            |cp COMCP                               {$2->mostrarDatos($2); cout<<"Comando CP"<<endl;};
            |mv COMMV                               {$2->mostrarDatos($2); cout<<"Comando MV"<<endl;};
            |find COMFIND                           {$2->mostrarDatos($2); cout<<"Comando FIND"<<endl;};
            |chownn COMCHOWN                        {$2->mostrarDatos($2); cout<<"Comando CHOWN"<<endl;};
            |chgrp COMCHGRP                         {$2->mostrarDatos($2); cout<<"Comando CHGRP"<<endl;};

            |execc COMEXEC                          {$2->mostrarDatos($2); cout<<"Comando EXEC"<<endl;};
            |rep COMREPORTE                         {$2->mostrarDatos($2); cout<<"Comando REPORTE"<<endl;};
            |recovery COMRECUP                      {$2->mostrarDatos($2); cout<<"Comando RECOVERY"<<endl;};
            |loss COMPERD                           {$2->mostrarDatos($2); cout<<"Comando LOSS"<<endl;};
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

COMLOGIN:   usr igual cadena COMLOGIN               {if(loginn->usr==""){loginn->usr=$3;} $$=loginn;};
            |usr igual ident COMLOGIN               {if(loginn->usr==""){loginn->usr=$3;} $$=loginn;};
            |pwd igual digito COMLOGIN              {if(loginn->pwd==""){loginn->pwd=$3;} $$=loginn;};
            |pwd igual cadena COMLOGIN              {if(loginn->pwd==""){loginn->pwd=$3;} $$=loginn;};
            |pwd igual ident COMLOGIN               {if(loginn->pwd==""){loginn->pwd=$3;} $$=loginn;};
            |id igual idp COMLOGIN                  {if(loginn->id==""){loginn->id=$3;} $$=loginn;};
            |usr igual cadena                       {if(loginn->usr==""){loginn->usr=$3;} $$=loginn;};
            |usr igual ident                        {if(loginn->usr==""){loginn->usr=$3;} $$=loginn;};
            |pwd igual digito                       {if(loginn->pwd==""){loginn->pwd=$3;} $$=loginn;};
            |pwd igual cadena                       {if(loginn->pwd==""){loginn->pwd=$3;} $$=loginn;};
            |pwd igual ident                        {if(loginn->pwd==""){loginn->pwd=$3;} $$=loginn;};
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
            |pwd igual digito                       {if(mkuserr->pwd==""){mkuserr->pwd=$3;} $$=mkuserr;};
            |pwd igual cadena                       {if(mkuserr->pwd==""){mkuserr->pwd=$3;} $$=mkuserr;};
            |pwd igual ident                        {if(mkuserr->pwd==""){mkuserr->pwd=$3;} $$=mkuserr;};
            |grp igual cadena                       {if(mkuserr->pwd==""){mkuserr->pwd=$3;} $$=mkuserr;};
            |grp igual ident                        {if(mkuserr->pwd==""){mkuserr->pwd=$3;} $$=mkuserr;};

COMRMUSER:  usr igual cadena COMRMUSER              {if(rmuserr->usr==""){rmuserr->usr=$3;} $$=rmuserr;};
            |usr igual ident COMRMUSER              {if(rmuserr->usr==""){rmuserr->usr=$3;} $$=rmuserr;};
            |usr igual cadena                       {if(rmuserr->usr==""){rmuserr->usr=$3;} $$=rmuserr;};
            |usr igual ident                        {if(rmuserr->usr==""){rmuserr->usr=$3;} $$=rmuserr;};

COMCHMOD:   pathh igual cadena COMCHMOD             {if(chmmodd->path==""){chmmodd->path=$3;} $$=chmmodd;};
            |pathh igual ruta COMCHMOD              {if(chmmodd->path==""){chmmodd->path=$3;} $$=chmmodd;};
            |ugo igual digito COMCHMOD              {int tam=atoi($3); if(chmmodd->ugo==0){chmmodd->ugo=tam;} $$=chmmodd;};
            |rr COMCHMOD                            {if(chmmodd->R==""){chmmodd->R=$1;} $$=chmmodd;};
            |pathh igual cadena                     {if(chmmodd->path==""){chmmodd->path=$3;} $$=chmmodd;};
            |pathh igual ruta                       {if(chmmodd->path==""){chmmodd->path=$3;} $$=chmmodd;};
            |ugo igual digito                       {int tam=atoi($3); if(chmmodd->ugo==0){chmmodd->ugo=tam;} $$=chmmodd;};
            |rr                                     {if(chmmodd->R==""){chmmodd->R=$1;} $$=chmmodd;};

COMKFILE:   pathh igual cadena COMKFILE             {if(mkfilee->path==""){mkfilee->path=$3;} $$=mkfilee;};
            |pathh igual ruta COMKFILE              {if(mkfilee->path==""){mkfilee->path=$3;} $$=mkfilee;};
            |sizee igual digito COMKFILE            {int tam=atoi($3); if(mkfilee->size==0){mkfilee->size=tam;} $$=mkfilee;};
            |sizee igual negativo digito COMKFILE   {int tam=atoi($3); if(mkfilee->size==0){mkfilee->size=tam * -1;} $$=mkfilee;};
            |rr COMKFILE                            {if(mkfilee->R==""){mkfilee->R=$1;} $$=mkfilee;};
            |p COMKFILE                             {if(mkfilee->P==""){mkfilee->P=$1;} $$=mkfilee;};
            |cont igual cadena COMKFILE             {if(mkfilee->cont==""){mkfilee->cont=$3;} $$=mkfilee;};
            |cont igual ruta COMKFILE               {if(mkfilee->cont==""){mkfilee->cont=$3;} $$=mkfilee;};
            |pathh igual cadena                     {if(mkfilee->path==""){mkfilee->path=$3;} $$=mkfilee;};
            |pathh igual ruta                       {if(mkfilee->path==""){mkfilee->path=$3;} $$=mkfilee;};
            |sizee igual digito                     {int tam=atoi($3); if(mkfilee->size==0){mkfilee->size=tam;} $$=mkfilee;};
            |sizee igual negativo digito            {int tam=atoi($3); if(mkfilee->size==0){mkfilee->size=tam * -1;} $$=mkfilee;};
            |rr                                     {if(mkfilee->R==""){mkfilee->R=$1;} $$=mkfilee;};
            |p                                      {if(mkfilee->P==""){mkfilee->P=$1;} $$=mkfilee;};
            |cont igual cadena                      {if(mkfilee->cont==""){mkfilee->cont=$3;} $$=mkfilee;};
            |cont igual ruta                        {if(mkfilee->cont==""){mkfilee->cont=$3;} $$=mkfilee;};

COMCAT:     filen igual cadena COMCAT               {if(catt->filen==""){catt->filen=$3;} $$=catt;};
            |filen igual ruta COMCAT                {if(catt->filen==""){catt->filen=$3;} $$=catt;};
            |filen igual rutacat COMCAT             {if(catt->filen==""){catt->filen=$3;} $$=catt;};
            |file igual cadena COMCAT               {if(catt->filen==""){catt->filen=$3;} $$=catt;};
            |file igual ruta COMCAT                 {if(catt->filen==""){catt->filen=$3;} $$=catt;};
            |file igual rutacat COMCAT              {if(catt->filen==""){catt->filen=$3;} $$=catt;};
            |filen igual cadena                     {if(catt->filen==""){catt->filen=$3;} $$=catt;};
            |filen igual ruta                       {if(catt->filen==""){catt->filen=$3;} $$=catt;};
            |filen igual rutacat                    {if(catt->filen==""){catt->filen=$3;} $$=catt;};
            |file igual cadena                      {if(catt->filen==""){catt->filen=$3;} $$=catt;};
            |file igual ruta                        {if(catt->filen==""){catt->filen=$3;} $$=catt;};
            |file igual rutacat                     {if(catt->filen==""){catt->filen=$3;} $$=catt;};

COMREM:     pathh igual cadena COMREM               {if(remm->path==""){remm->path=$3;} $$=remm;};
            |pathh igual rutaelim COMREM            {if(remm->path==""){remm->path=$3;} $$=remm;};
            |pathh igual ruta COMREM                {if(remm->path==""){remm->path=$3;} $$=remm;};
            |pathh igual cadena                     {if(remm->path==""){remm->path=$3;} $$=remm;};
            |pathh igual rutaelim                   {if(remm->path==""){remm->path=$3;} $$=remm;};
            |pathh igual ruta                       {if(remm->path==""){remm->path=$3;} $$=remm;};

COMEDIT:    pathh igual cadena COMEDIT              {if(editt->path==""){editt->path=$3;} $$=editt;};
            |pathh igual ruta COMEDIT               {if(editt->path==""){editt->path=$3;} $$=editt;};
            |cont igual cadena COMEDIT              {if(editt->cont==""){editt->cont=$3;} $$=editt;};
            |cont igual ruta COMEDIT                {if(editt->cont==""){editt->cont=$3;} $$=editt;};
            |pathh igual cadena                     {if(editt->path==""){editt->path=$3;} $$=editt;};
            |pathh igual ruta                       {if(editt->path==""){editt->path=$3;} $$=editt;};
            |cont igual cadena                      {if(editt->cont==""){editt->cont=$3;} $$=editt;};
            |cont igual ruta                        {if(editt->cont==""){editt->cont=$3;} $$=editt;};

COMREN:     pathh igual cadena COMREN               {if(renn->path==""){renn->path=$3;} $$=renn;};
            |pathh igual ruta COMREN                {if(renn->path==""){renn->path=$3;} $$=renn;};
            |namee igual rutaarch COMREN            {if(renn->path==""){renn->path=$3;} $$=renn;};
            |pathh igual cadena                     {if(renn->path==""){renn->path=$3;} $$=renn;};
            |pathh igual ruta                       {if(renn->path==""){renn->path=$3;} $$=renn;};
            |namee igual rutaarch                   {if(renn->path==""){renn->path=$3;} $$=renn;};

COMMKDIR:   pathh igual cadena COMMKDIR             {if(cmkdirr->path==""){cmkdirr->path=$3;} $$=cmkdirr;};
            |pathh igual rutaelim COMMKDIR          {if(cmkdirr->path==""){cmkdirr->path=$3;} $$=cmkdirr;};
            |p COMMKDIR                             {if(cmkdirr->P==""){cmkdirr->P=$1;} $$=cmkdirr;};
            |pathh igual cadena                     {if(cmkdirr->path==""){cmkdirr->path=$3;} $$=cmkdirr;};
            |pathh igual rutaelim                   {if(cmkdirr->path==""){cmkdirr->path=$3;} $$=cmkdirr;};
            |p                                      {if(cmkdirr->P==""){cmkdirr->P=$1;} $$=cmkdirr;};

COMCP:      pathh igual cadena COMCP                {if(cpp->path==""){cpp->path=$3;} $$=cpp;};
            |pathh igual rutaelim COMCP             {if(cpp->path==""){cpp->path=$3;} $$=cpp;};
            |pathh igual ruta COMCP                 {if(cpp->path==""){cpp->path=$3;} $$=cpp;};
            |dest igual cadena COMCP                {if(cpp->dest==""){cpp->dest=$3;} $$=cpp;};
            |dest igual rutaelim COMCP              {if(cpp->dest==""){cpp->dest=$3;} $$=cpp;};
            |dest igual ruta COMCP                  {if(cpp->dest==""){cpp->dest=$3;} $$=cpp;};
            |pathh igual cadena                     {if(cpp->path==""){cpp->path=$3;} $$=cpp;};
            |pathh igual rutaelim                   {if(cpp->path==""){cpp->path=$3;} $$=cpp;};
            |pathh igual ruta                       {if(cpp->path==""){cpp->path=$3;} $$=cpp;};
            |dest igual cadena                      {if(cpp->dest==""){cpp->dest=$3;} $$=cpp;};
            |dest igual rutaelim                    {if(cpp->dest==""){cpp->dest=$3;} $$=cpp;};
            |dest igual ruta                        {if(cpp->dest==""){cpp->dest=$3;} $$=cpp;};

COMMV:      pathh igual cadena COMMV                {if(mvv->path==""){mvv->path=$3;} $$=mvv;};
            |pathh igual rutaelim COMMV             {if(mvv->path==""){mvv->path=$3;} $$=mvv;};
            |pathh igual ruta COMMV                 {if(mvv->path==""){mvv->path=$3;} $$=mvv;};
            |dest igual cadena COMMV                {if(mvv->dest==""){mvv->dest=$3;} $$=mvv;};
            |dest igual rutaelim COMMV              {if(mvv->dest==""){mvv->dest=$3;} $$=mvv;};
            |dest igual ruta COMMV                  {if(mvv->dest==""){mvv->dest=$3;} $$=mvv;};
            |pathh igual cadena                     {if(mvv->path==""){mvv->path=$3;} $$=mvv;};
            |pathh igual rutaelim                   {if(mvv->path==""){mvv->path=$3;} $$=mvv;};
            |pathh igual ruta                       {if(mvv->path==""){mvv->path=$3;} $$=mvv;};
            |dest igual cadena                      {if(mvv->dest==""){mvv->dest=$3;} $$=mvv;};
            |dest igual rutaelim                    {if(mvv->dest==""){mvv->dest=$3;} $$=mvv;};
            |dest igual ruta                        {if(mvv->dest==""){mvv->dest=$3;} $$=mvv;};

COMFIND:    pathh igual cadena COMFIND              {if(findd->path==""){findd->path=$3;} $$=findd;};
            |pathh igual ruta COMFIND               {if(findd->path==""){findd->path=$3;} $$=findd;};
            |namee igual dividido COMFIND           {if(findd->namee==""){findd->namee=$3;} $$=findd;};
            |namee igual interrogacion COMFIND      {if(findd->namee==""){findd->namee=$3;} $$=findd;};
            |namee igual cadena COMFIND             {if(findd->namee==""){findd->namee=$3;} $$=findd;};
            |pathh igual cadena                     {if(findd->path==""){findd->path=$3;} $$=findd;};
            |pathh igual ruta                       {if(findd->path==""){findd->path=$3;} $$=findd;};
            |namee igual dividido                   {if(findd->namee==""){findd->namee=$3;} $$=findd;};
            |namee igual interrogacion              {if(findd->namee==""){findd->namee=$3;} $$=findd;};
            |namee igual cadena                     {if(findd->namee==""){findd->namee=$3;} $$=findd;};

COMCHOWN:    pathh igual cadena COMCHOWN            {if(cchownn->path==""){cchownn->path=$3;} $$=cchownn;};
            |pathh igual rutaelim COMCHOWN          {if(cchownn->path==""){cchownn->path=$3;} $$=cchownn;};
            |rr COMCHOWN                            {if(cchownn->R==""){cchownn->R=$1;} $$=cchownn;};
            |usr igual ident COMCHOWN               {if(cchownn->usr==""){cchownn->usr=$3;} $$=cchownn;};
            |pathh igual cadena                     {if(cchownn->path==""){cchownn->path=$3;} $$=cchownn;};
            |pathh igual rutaelim                   {if(cchownn->path==""){cchownn->path=$3;} $$=cchownn;};
            |rr                                     {if(cchownn->R==""){cchownn->R=$1;} $$=cchownn;};
            |usr igual ident                        {if(cchownn->usr==""){cchownn->usr=$3;} $$=cchownn;};

COMCHGRP:   usr igual ident COMCHGRP                {if(chgrpp->usr==""){chgrpp->usr=$3;} $$=chgrpp;};
            |grp igual ident COMCHGRP               {if(chgrpp->grp==""){chgrpp->grp=$3;} $$=chgrpp;};
            |usr igual ident                        {if(chgrpp->usr==""){chgrpp->usr=$3;} $$=chgrpp;};
            |grp igual ident                        {if(chgrpp->grp==""){chgrpp->grp=$3;} $$=chgrpp;};

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

COMRECUP:   id igual idp COMRECUP                   {if(recuperar->id==""){recuperar->id=$3;} $$=recuperar;};
            |id igual idp                           {if(recuperar->id==""){recuperar->id=$3;} $$=recuperar;};

COMPERD:    id igual idp COMPERD                    {if(perdida->id==""){perdida->id=$3;} $$=perdida;};
            |id igual idp                           {if(perdida->id==""){perdida->id=$3;} $$=perdida;};


%%
