#include "clunmount.h"
#include <QString>
#include <iostream>
using namespace std;

clunmount::clunmount()
{

}

void clunmount::mostrarDatos(clunmount *disco){
    cout<<"-----------------------DesmontarParticion---------------------"<<endl;
    cout<<"El Path es: "<<disco->id.toStdString()<<endl;
    if(disco->id!=""){
        //AQUI VA TODO EL CODIGO UNMOUNT
    }else{
        cout<<"ID No Ingresada, Incorrecto"<<endl;
    }
    disco->id = "";
    cout<<"--------------------------------------------------------"<<endl;
}
