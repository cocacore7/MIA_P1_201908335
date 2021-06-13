#include "clrem.h"
#include <QString>
#include <iostream>

using namespace std;

clrem::clrem()
{

}

void clrem::mostrarDatos(clrem *eliminar){
    cout<<"----------------------Eliminar_Carpeta/Archivo--------------------------"<<endl;
    cout<<"-El Path Es: "<<eliminar->path.toStdString().c_str()<<endl;

    eliminar->path = "";
    cout<<"--------------------------------------------------------"<<endl;
}
