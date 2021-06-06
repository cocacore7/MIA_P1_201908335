#include "clfdisk.h"
#include <QString>
#include <iostream>
using namespace std;

clfdisk::clfdisk()
{

}

void clfdisk::mostrarDatos(clfdisk *disco){
    cout<<"-----------------------DATOS---------------------"<<endl;
    cout<<"El tamaño es: "<<disco->size<<endl;
    cout<<"El U es: "<<disco->u.toStdString()<<endl;
    cout<<"El Path es: "<<disco->path.toStdString()<<endl;
    cout<<"El Type es: "<<disco->typee.toStdString()<<endl;
    cout<<"El F es: "<<disco->f.toStdString()<<endl;
    cout<<"El Delete es: "<<disco->deletee.toStdString()<<endl;
    cout<<"El Name es: "<<disco->namee.toStdString()<<endl;
    cout<<"El Add es: "<<disco->addd<<endl;
    disco->size = 0;
    disco->u = "";
    disco->path = "";
    disco->typee = "";
    disco->f = "";
    disco->deletee = "";
    disco->namee = "";
    disco->addd = 0;
}
