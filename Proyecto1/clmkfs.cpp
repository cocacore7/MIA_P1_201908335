#include "clmkfs.h"
#include <QString>
#include <iostream>
using namespace std;

clmkfs::clmkfs()
{

}

void clmkfs::mostrarDatos(clmkfs *disco){
    cout<<"-----------------------DATOS---------------------"<<endl;
    cout<<"El Path es: "<<disco->id.toStdString()<<endl;
    cout<<"El Name es: "<<disco->type.toStdString()<<endl;
    cout<<"El FS es: "<<disco->fs.toStdString()<<endl;
    disco->id = "";
    disco->type = "";
    disco->fs = "";
}
