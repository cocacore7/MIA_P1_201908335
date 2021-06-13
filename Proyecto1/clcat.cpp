#include "clcat.h"
#include <QString>
#include <iostream>

using namespace std;

clcat::clcat()
{

}

void clcat::mostrarDatos(clcat *archivo){
    cout<<"----------------------MostrarContArchivo--------------------------"<<endl;
    cout<<"El Filen Es: "<<archivo->filen.toStdString().c_str()<<endl;

    archivo->filen = "";
    cout<<"--------------------------------------------------------"<<endl;
}
