#include "clchgrp.h"
#include <QString>
#include <iostream>

using namespace std;

clchgrp::clchgrp()
{

}

void clchgrp::mostrarDatos(clchgrp *grupo){
    cout<<"----------------------CambiarGrupo--------------------------"<<endl;
    cout<<"-El GRP Es: "<<grupo->grp.toStdString().c_str()<<endl;
    cout<<"-El USR Es: "<<grupo->usr.toStdString().c_str()<<endl;

    grupo->grp = "";
    grupo->usr = "";
    cout<<"--------------------------------------------------------"<<endl;
}
