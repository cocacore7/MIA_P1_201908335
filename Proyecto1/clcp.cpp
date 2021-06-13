#include "clcp.h"
#include <QString>
#include <iostream>

using namespace std;

clcp::clcp()
{

}

void clcp::mostrarDatos(clcp *copiar){
    cout<<"----------------------Copiar_Archivo/Carpeta--------------------------"<<endl;
    cout<<"-El Path Es: "<<copiar->path.toStdString().c_str()<<endl;
    cout<<"-El Dest Es: "<<copiar->dest.toStdString().c_str()<<endl;

    copiar->path = "";
    copiar->dest = "";
    cout<<"--------------------------------------------------------"<<endl;
}

