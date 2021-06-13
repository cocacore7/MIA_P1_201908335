#include "clmkuser.h"
#include <QString>
#include <iostream>

using namespace std;

clmkuser::clmkuser()
{

}

void clmkuser::mostrarDatos(clmkuser *solicitud){
    cout<<"----------------------CrearUsuario--------------------------"<<endl;

    cout<<"-La Contraseña Es: "<<solicitud->pwd.toStdString().c_str()<<endl;
    cout<<"-El Usuario Es: "<<solicitud->usr.toStdString().c_str()<<endl;
    cout<<"-El Grupo Es: "<<solicitud->grp.toStdString().c_str()<<endl;

    solicitud->grp = "";
    solicitud->pwd = "";
    solicitud->usr = "";
    cout<<"--------------------------------------------------------"<<endl;
}
