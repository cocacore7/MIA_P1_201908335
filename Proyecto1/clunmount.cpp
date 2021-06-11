#include "clunmount.h"
#include <QString>
#include <iostream>
//Necesario Para Usar Montada --------------
#include <clmontada.h>
#include <cabeceramontadas.h>
//-------------------------------------------
using namespace std;

clunmount::clunmount()
{

}

void clunmount::mostrarDatos(clunmount *disco){
    cout<<"-----------------------DesmontarParticion---------------------"<<endl;
    if(disco->id!=""){
        //AQUI VA TODO EL CODIGO UNMOUNT
        lista.eliminarNodo(lista.lista,disco->id);
    }else{
        cout<<"ID No Ingresada, Incorrecto"<<endl;
    }
    disco->id = "";
    cout<<"--------------------------------------------------------"<<endl;
}
