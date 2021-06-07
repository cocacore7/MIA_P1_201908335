#include "clmkdisk.h"
#include <QString>
#include <iostream>
#include <fstream>
#include <qstringlist.h>
#include <QFile>
#include <QDir>
using namespace std;

clmkdisk::clmkdisk()
{

}


void clmkdisk::mostrarDatos(clmkdisk *disco){
    cout<<"-----------------------DATOS---------------------"<<endl;
    disco->path.remove(QChar('"'), Qt::CaseInsensitive);
    cout<<"El tamaño es: "<<disco->size<<endl;
    cout<<"El F es: "<<disco->f.toStdString()<<endl;
    cout<<"El U es: "<<disco->u.toStdString()<<endl;
    cout<<"El Path es: "<<disco->path.toStdString()<<endl;
    if(disco->size > 0){
        if(disco->path != ""){
            if(disco->f == ""){
                disco->f = "ff";
            }
            if(disco->u == ""){
                disco->u="m";
            }

            //AQUI VA TODO EL CODIGO DEL MKDISK
            QStringList direcciones = disco->path.split("/");
            QString ruta = "";
            bool primera = false;
            if(direcciones[1] == "home" && direcciones[2] == "archivos"){
                ruta = "/home/oscar/archivos";
                for(int x=3;x<(direcciones.length()-1);x++){
                    if(primera){
                        QDir direc(ruta);
                        direc.mkdir(direcciones[x]);
                        ruta = ruta + direcciones[x] + "/";
                    }else{
                        QDir direc(ruta);
                        direc.mkdir(direcciones[x]);
                        ruta = ruta + "/" + direcciones[x] + "/";
                        primera = true;
                    }
                }
            }

            QString aux =direcciones[direcciones.length()-1];
            QStringList discofisico = aux.split(".");
            if(discofisico[1] == "dk"){
                //AQUI CREAMOS ARCHIVO FISICO
                if(primera){
                    ruta = ruta + aux;
                }else{
                    ruta = ruta + "/" + aux;
                }
                QFile archivo(ruta);
                if(archivo.open(QIODevice::WriteOnly | QIODevice::Text)){
                    cout<<"Abrio El  Archivo"<<endl;
                }
                archivo.close();


                //AQUI LLENAMOS EL ARCHIVO FISICO

            }else{
                cout<<"Extension de Disco incorrecta, no es .dk"<<endl;
            }
        }else{
            cout<<"Ruta No Ingresada, Incorrecto"<<endl;
        }
    } else{
     cout<<"Tamaño de disco Incorrecto"<<endl;
    }
    disco->size = 0;
    disco->f = "";
    disco->u = "";
    disco->path = "";
}
