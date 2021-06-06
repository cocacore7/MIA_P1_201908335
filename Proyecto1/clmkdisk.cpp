#include "clmkdisk.h"
#include <QString>
#include <iostream>
using namespace std;

clmkdisk::clmkdisk()
{

}


void clmkdisk::mostrarDatos(clmkdisk *disco){
    cout<<"-----------------------DATOS---------------------"<<endl;
    cout<<"El tamaño es: "<<disco->size<<endl;
    cout<<"El F es: "<<disco->f.toStdString()<<endl;
    cout<<"El U es: "<<disco->u.toStdString()<<endl;
    cout<<"El Path es: "<<disco->path.toStdString()<<endl;
    disco->size = 0;
    disco->f = "";
    disco->u = "";
    disco->path = "";
}
