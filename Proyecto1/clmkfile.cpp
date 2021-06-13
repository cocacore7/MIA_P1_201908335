#include "clmkfile.h"
#include <QString>
#include <iostream>

using namespace std;

clmkfile::clmkfile()
{

}

void clmkfile::mostrarDatos(clmkfile *carpeta){
    cout<<"----------------------CrearArchivo--------------------------"<<endl;
    cout<<"-El R Es: "<<carpeta->R.toStdString().c_str()<<endl;
    cout<<"-El Path Es: "<<carpeta->path.toStdString().c_str()<<endl;
    cout<<"-El Size Es: "<<carpeta->size<<endl;
    cout<<"-El Cont Es: "<<carpeta->cont.toStdString().c_str()<<endl;
    cout<<"-El P Es: "<<carpeta->P.toStdString().c_str()<<endl;

    carpeta->R = "";
    carpeta->path = "";
    carpeta->size = 0;
    carpeta->cont = "";
    carpeta->P = "";
    cout<<"--------------------------------------------------------"<<endl;
}
