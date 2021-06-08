#include "clmount.h"
#include <QString>
#include <iostream>
using namespace std;

clmount::clmount()
{

}

void clmount::mostrarDatos(clmount *disco){
    cout<<"-----------------------MontarParticion---------------------"<<endl;
    cout<<"El Path es: "<<disco->path.toStdString()<<endl;
    cout<<"El Name es: "<<disco->namee.toStdString()<<endl;
    if(disco->path!=""){
        if(disco->namee!=""){
            //AQUI VA TODO EL CODIGO PARA COMANDO MOUNT
        }else{
            cout<<"Nombre De Particion No Ingresada, Incorrecto"<<endl;
        }
    }else{
        cout<<"Ruta No Ingresada, Incorrecto"<<endl;
    }
    disco->path = "";
    disco->namee = "";
    cout<<"--------------------------------------------------------"<<endl;
}
