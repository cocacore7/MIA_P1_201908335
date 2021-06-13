#include "clmkuser.h"
#include <QString>
#include <iostream>

using namespace std;

clmkuser::clmkuser()
{

}

void clmkuser::mostrarDatos(clmkuser *solicitud){
    cout<<"----------------------CrearUsuario--------------------------"<<endl;

    solicitud->grp = "";
    solicitud->pwd = "";
    solicitud->usr = "";
    cout<<"--------------------------------------------------------"<<endl;
}
