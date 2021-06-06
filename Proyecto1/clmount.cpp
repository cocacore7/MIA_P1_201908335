#include "clmount.h"
#include <QString>
#include <iostream>
using namespace std;

clmount::clmount()
{

}

void clmount::mostrarDatos(clmount *disco){
    cout<<"-----------------------DATOS---------------------"<<endl;
    cout<<"El Path es: "<<disco->path.toStdString()<<endl;
    cout<<"El Name es: "<<disco->namee.toStdString()<<endl;
    disco->path = "";
    disco->namee = "";
}
