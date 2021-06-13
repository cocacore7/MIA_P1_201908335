#include "clmkgrp.h"
#include <QString>
#include <iostream>

using namespace std;

clmkgrp::clmkgrp()
{

}

void clmkgrp::mostrarDatos(clmkgrp *solicitud){
    cout<<"----------------------CrearGrupo--------------------------"<<endl;
    cout<<"-El Name Es: "<<solicitud->name.toStdString().c_str()<<endl;

    solicitud->name = "";
    cout<<"--------------------------------------------------------"<<endl;
}
