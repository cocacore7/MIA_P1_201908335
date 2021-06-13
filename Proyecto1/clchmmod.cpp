#include "clchmmod.h"
#include <QString>
#include <iostream>

using namespace std;

clchmmod::clchmmod()
{

}

void clchmmod::mostrarDatos(clchmmod *permisos){
    cout<<"----------------------CambiarPermisos--------------------------"<<endl;
    cout<<"-El R Es: "<<permisos->R.toStdString().c_str()<<endl;
    cout<<"-El Path Es: "<<permisos->path.toStdString().c_str()<<endl;
    cout<<"-El UGO Es: "<<permisos->ugo<<endl;

    permisos->R = "";
    permisos->path = "";
    permisos->ugo = 0;
    cout<<"--------------------------------------------------------"<<endl;
}
