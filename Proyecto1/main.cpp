#include <iostream>
#include <sys/stat.h>
#include <fstream>
#include <string.h>
#include <parser.h>
#include <scanner.h>
#include <clmkdisk.h>
using namespace std;

extern int yyparse();
extern int resultado;
bool menu = true;
void leerEntrada(char*);

int main()
{
    while(menu){
        cout<<"------------------------------Ingrese Un Comando----------------------------"<<endl;
        char entrada[500];
        printf(">> ");
        fgets(entrada,sizeof(entrada),stdin);
        leerEntrada(entrada);
        memset(entrada,0,500);
    }
    return 0;
}

void leerEntrada(char entrada[500]){
    YY_BUFFER_STATE buffer = yy_scan_string(entrada);
    if(yyparse()==0){
        //cout<<resultado<<endl;
    }else{
        cout<<"Hubo Un Error"<<endl;
    }
}
