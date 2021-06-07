#include "clrmdisk.h"
#include <QString>
#include <iostream>
using namespace std;

clrmdisk::clrmdisk()
{

}

void clrmdisk::mostrarDatos(clrmdisk *disco){
    cout<<"-----------------------DATOS---------------------"<<endl;
    cout<<"El Path es: "<<disco->path.toStdString()<<endl;
    if(disco->path!=""){
        //AQUI VA TODO EL CODIGO DE MRDISK
    }else{
        cout<<"Ruta No Ingresada, Incorrecto"<<endl;
    }
    disco->path = "";
}
