#include "clunmount.h"
#include <QString>
#include <iostream>
using namespace std;

clunmount::clunmount()
{

}

void clunmount::mostrarDatos(clunmount *disco){
    cout<<"-----------------------DATOS---------------------"<<endl;
    cout<<"El Path es: "<<disco->id.toStdString()<<endl;
    disco->id = "";
}
