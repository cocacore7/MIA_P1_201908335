#include "clrmuser.h"
#include <QString>
#include <iostream>

using namespace std;

clrmuser::clrmuser()
{

}

void clrmuser::mostrarDatos(clrmuser *solicitud){
    cout<<"----------------------EliminarUsuario--------------------------"<<endl;
    cout<<"-El USER Es: "<<solicitud->usr.toStdString().c_str()<<endl;

    solicitud->usr = "";
    cout<<"--------------------------------------------------------"<<endl;
}
