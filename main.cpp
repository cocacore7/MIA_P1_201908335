#include <QCoreApplication>
#include "iostream"
#include <QString>
#include <parser.h>
#include <scanner.h>
#include <QTextStream>
using namespace std;
extern int yyparse();

int menu;

extern int yylineno;

int main(int argc, char *argv[])
{

    string menu = "------------------------------Ingrese Un Comando----------------------------";

    QString line;
    QTextStream in(stdin);

    while(line!="salir"){
        cout<<menu;
        in >> line;
        //line = qtin.readLine();
        if(line!="salir"){
            if(line.isEmpty()==false){
                //YY_BUFFER_STATE buffer = yy_scan_string(line.toUtf8().constData());

                yylineno = 0;

                if(yyparse()==0){
                    printf("\n\nComando ejecutaro correctamente\n\n");
                }else{
                    printf("\n\nHay Errores\n\n");
                }
            }
        }
    }
}
