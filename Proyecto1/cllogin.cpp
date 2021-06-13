#include "cllogin.h"
#include <QString>
#include <iostream>
#include <QDir>
#include <fstream>
#include <mbrstruct.h>
#include <ebrstruct.h>
//Necesario Para Usar Montada --------------
#include <clmontada.h>
#include <cabeceramontadas.h>
#include <clsesion.h>
//-------------------------------------------

cllogin::cllogin()
{

}

void cllogin::logear(cllogin *solicitud){
    cout<<"----------------------IniciarSesion--------------------------"<<endl;

    solicitud->id = "";
    solicitud->pwd = "";
    solicitud->usr = "";
    cout<<"--------------------------------------------------------"<<endl;
}

void cllogin::salir(){
    cout<<"----------------------CerrarSesion--------------------------"<<endl;
    sesion.logout(sesion.activaP,sesion.usuario);
    cout<<"Sesion Finalizada"<<endl;
    cout<<"--------------------------------------------------------"<<endl;
}
