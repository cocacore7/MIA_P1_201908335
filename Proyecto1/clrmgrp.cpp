#include "clrmgrp.h"
#include <QString>
#include <iostream>

using namespace std;

clrmgrp::clrmgrp()
{

}

void clrmgrp::mostrarDatos(clrmgrp *solicitud){
    cout<<"----------------------EliminarGrupo--------------------------"<<endl;
    cout<<"-El Name Es: "<<solicitud->name.toStdString().c_str()<<endl;

    solicitud->name = "";
    cout<<"--------------------------------------------------------"<<endl;
}
