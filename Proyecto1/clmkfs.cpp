#include "clmkfs.h"
#include <QString>
#include <iostream>
using namespace std;

clmkfs::clmkfs()
{

}

void clmkfs::mostrarDatos(clmkfs *disco){
    cout<<"-----------------------DATOS---------------------"<<endl;
    cout<<"El Path es: "<<disco->id.toStdString()<<endl;
    cout<<"El Name es: "<<disco->type.toStdString()<<endl;
    cout<<"El FS es: "<<disco->fs.toStdString()<<endl;
    if(disco->id!=""){
        if(disco->type!=""){
            disco->type="full";
        }
        if(disco->fs!=""){
            disco->fs="ext2";
        }

        //AQUI VA TODO EL CODIGO MKFS
    }else{
        cout<<"ID No Ingresada, Incorrecto"<<endl;
    }
    disco->id = "";
    disco->type = "";
    disco->fs = "";
}
