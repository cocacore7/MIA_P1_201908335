#include "clmv.h"
#include <QString>
#include <iostream>

using namespace std;

clmv::clmv()
{

}

void clmv::mostrarDatos(clmv *mover){
    cout<<"----------------------Mover_Archivo/Carpeta--------------------------"<<endl;
    cout<<"-El Path Es: "<<mover->path.toStdString().c_str()<<endl;
    cout<<"-El Dest Es: "<<mover->dest.toStdString().c_str()<<endl;

    mover->path = "";
    mover->dest = "";
    cout<<"--------------------------------------------------------"<<endl;
}
