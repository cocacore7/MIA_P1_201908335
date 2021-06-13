#include "clren.h"
#include <QString>
#include <iostream>

using namespace std;

clRen::clRen()
{

}

void clRen::mostrarDatos(clRen *nombre){
    cout<<"----------------------EditarNombre_Archivo/Carpeta--------------------------"<<endl;
    cout<<"-El Path Es: "<<nombre->path.toStdString().c_str()<<endl;
    cout<<"-El Name Es: "<<nombre->namee.toStdString().c_str()<<endl;

    nombre->path = "";
    nombre->namee = "";
    cout<<"--------------------------------------------------------"<<endl;
}
