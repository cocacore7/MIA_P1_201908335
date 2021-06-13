#include "clmkdir.h"
#include <QString>
#include <iostream>

using namespace std;

clmkdir::clmkdir()
{

}

void clmkdir::mostrarDatos(clmkdir *carpeta){
    cout<<"----------------------CrearCarpeta--------------------------"<<endl;
    cout<<"-El Path Es: "<<carpeta->path.toStdString().c_str()<<endl;
    cout<<"-El P Es: "<<carpeta->P.toStdString().c_str()<<endl;

    carpeta->path = "";
    carpeta->P = "";
    cout<<"--------------------------------------------------------"<<endl;
}
