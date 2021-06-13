#include "clrecovery.h"
#include <QString>
#include <iostream>

using namespace std;

clrecovery::clrecovery()
{

}

void clrecovery::mostrarDatos(clrecovery *recuperar){
    cout<<"----------------------RecuperarInformacion--------------------------"<<endl;
    cout<<"-El Id Es: "<<recuperar->id.toStdString().c_str()<<endl;

    recuperar->id = "";
    cout<<"--------------------------------------------------------"<<endl;
}
