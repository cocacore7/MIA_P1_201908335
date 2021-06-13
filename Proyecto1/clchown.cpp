#include "clchown.h"
#include <QString>
#include <iostream>

using namespace std;

clchown::clchown()
{

}

void clchown::mostrarDatos(clchown *propietario){
    cout<<"----------------------CambiarPropietario_Archivo/Carpeta--------------------------"<<endl;
    cout<<"-El Path Es: "<<propietario->path.toStdString().c_str()<<endl;
    cout<<"-El R Es: "<<propietario->R.toStdString().c_str()<<endl;
    cout<<"-El USR Es: "<<propietario->usr.toStdString().c_str()<<endl;

    propietario->path = "";
    propietario->usr = "";
    propietario->R = "";
    cout<<"--------------------------------------------------------"<<endl;
}

