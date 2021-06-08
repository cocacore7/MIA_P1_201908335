#include "clrmdisk.h"
#include <QString>
#include <iostream>
#include <QFile>
#include <QDir>
#include <fstream>
#include <qstringlist.h>
using namespace std;

clrmdisk::clrmdisk()
{

}

void clrmdisk::mostrarDatos(clrmdisk *disco){
    cout<<"-----------------------EliminarDisco---------------------"<<endl;
    disco->path.remove(QChar('"'), Qt::CaseInsensitive);
    if(disco->path!=""){
        //AQUI VA TODO EL CODIGO DE RMDISK
        QStringList direcciones = disco->path.split("/");
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
            if(discofisico[1] == "dk"){
                ruta = ruta + "/" + aux;
                QFile archivo(ruta);
                if(archivo.exists()){
                    //AQUI SE BORRA EL ARCHIVO QUE SIMULA UN DISCO
                    archivo.remove();
                    archivo.close();
                    QByteArray ba = aux.toLocal8Bit();
                    const char* com = ba.data();
                    cout<<"El Disco: " << com<< " Se A Eliminado Con Exito :D"<<endl;
                }else{
                    QByteArray ba = aux.toLocal8Bit();
                    const char* com = ba.data();
                    cout<<"El Disco: " << com<< " No Existe"<<endl;
                }
            }else{
                cout<<"Extension de Disco incorrecta, no es .dk"<<endl;
            }
        }
    }else{
        cout<<"Ruta No Ingresada, Incorrecto"<<endl;
    }
    disco->path = "";
    cout<<"--------------------------------------------------------"<<endl;
}
