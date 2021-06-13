#include "cledit.h"
#include <QString>
#include <iostream>

using namespace std;

cledit::cledit()
{

}

void cledit::mostrarDatos(cledit *editar){
    cout<<"----------------------EditarContArchivo--------------------------"<<endl;
    cout<<"-El Path Es: "<<editar->path.toStdString().c_str()<<endl;
    cout<<"-El Cont Es: "<<editar->cont.toStdString().c_str()<<endl;

    editar->path = "";
    editar->cont = "";
    cout<<"--------------------------------------------------------"<<endl;
}
