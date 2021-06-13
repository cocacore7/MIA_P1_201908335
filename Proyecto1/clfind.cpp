#include "clfind.h"
#include <QString>
#include <iostream>

using namespace std;

clfind::clfind()
{

}

void clfind::mostrarDatos(clfind *buscar){
    cout<<"----------------------Buscar_Archivo/Carpeta--------------------------"<<endl;
    cout<<"-El Path Es: "<<buscar->path.toStdString().c_str()<<endl;
    cout<<"-El Name Es: "<<buscar->namee.toStdString().c_str()<<endl;

    buscar->path = "";
    buscar->namee = "";
    cout<<"--------------------------------------------------------"<<endl;
}
