#include "clexec.h"
#include <QString>
#include <iostream>
#include <fstream>
#include <qstringlist.h>
#include <QFile>
#include <QDir>
#include <qtextstream.h>
#include <parser.h>
#include <scanner.h>
using namespace std;
extern int yyparse();

clexec::clexec()
{

}

void clexec::mostrarDatos(clexec *script){
    cout<<"----------------------CargarScript--------------------------"<<endl;
    script->path.remove(QChar('"'), Qt::CaseInsensitive);
    if(script->path != ""){
        QStringList direcciones = script->path.split("/");
        QString ruta = "";
        bool NoCarpeta = false;
        if(direcciones[1] == "home" && direcciones[2] == "archivos"){
            ruta = "/home/oscar/archivos";
            for(int x=3;x<(direcciones.length()-1);x++){
                ruta = ruta + "/" + direcciones[x];
                QDir direc(ruta);
                if(!direc.exists()){
                    QByteArray ba = direcciones[x].toLocal8Bit();
                    const char* com = ba.data();
                    cout<<"La carpeta: "<<com<<" No Existe"<<endl;
                    NoCarpeta=true;
                    break;
                }
            }
        }
        if(!NoCarpeta){
            QString aux =direcciones[direcciones.length()-1];
            QStringList discofisico = aux.split(".");
            if(discofisico[1] == "script"){
                ruta = ruta + "/" + aux;
                QFile archivo(ruta);
                if(archivo.exists()){
                    //AQUI SE ABRE EL ARCHIVO Y SE PASAN TODAS LAS INSTRUCCIONES POR BISON
                    if(archivo.open(QIODevice::ReadOnly)){
                        QTextStream in(&archivo);
                        while(!in.atEnd()){
                            QString linea = in.readLine();
                            QByteArray ba = linea.toLocal8Bit();
                            const char *entrada = ba;
                            YY_BUFFER_STATE buffer = yy_scan_string(entrada);
                            if(yyparse()==0){
                                //cout<<resultado<<endl;
                            }else{
                                cout<<"Hubo Un Error"<<endl;
                            }
                        }
                    }
                    QByteArray ba = aux.toLocal8Bit();
                    const char* com = ba.data();
                    cout<<"El Script: " << com<< " Se A Cargado Con Exito :D"<<endl;
                }else{
                    QByteArray ba = aux.toLocal8Bit();
                    const char* com = ba.data();
                    cout<<"El Script: " << com<< " No Existe"<<endl;
                }
                archivo.close();
            }else{
                cout<<"Extension de Archivo Script incorrecta, no es .script"<<endl;
            }
        }
    }else{
        cout<<"Ruta No Ingresada, Incorrecto"<<endl;
    }
    cout<<"--------------------------------------------------------"<<endl;
}
