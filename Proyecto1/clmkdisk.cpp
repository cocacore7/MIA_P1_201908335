#include "clmkdisk.h"
#include <QString>
#include <iostream>
using namespace std;

clmkdisk::clmkdisk()
{

}


void clmkdisk::mostrarDatos(clmkdisk *disco){
    cout<<"-----------------------DATOS---------------------"<<endl;
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
