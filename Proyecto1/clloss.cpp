#include "clloss.h"
#include <QString>
#include <iostream>

using namespace std;

clloss::clloss()
{

}

void clloss::mostrarDatos(clloss *perdida){
    cout<<"----------------------PerdidaInformacion--------------------------"<<endl;
    cout<<"-El Id Es: "<<perdida->id.toStdString().c_str()<<endl;

    perdida->id = "";
    cout<<"--------------------------------------------------------"<<endl;
}
