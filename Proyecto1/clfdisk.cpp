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
    cout<<"El Typo De Entero es: "<<disco->primero.toStdString()<<endl;
    cout<<"El Add es: "<<disco->addd<<endl;

    if(disco->path!=""){
        if(disco->namee!=""){
            if(disco->primero=="s"){
                if(disco->deletee==""){
                    if(disco->size<0){
                        if(disco->u==""){
                            disco->u="k";
                        }
                        if(disco->f==""){
                            disco->f="wf";
                        }
                        if(disco->typee==""){
                            disco->typee="p";
                        }

                        //AQUI VA TODO EL CODIGO PARA CREAR PARTICION
                    }else{
                        cout<<"No se especifico tamaño para crear particion, o para agregar/remover espacio"<<endl;
                    }
                }else{
                    cout<<"comando size No Pertenece al comando Delete"<<endl;
                }
            }else{
                if(disco->deletee!=""){
                    if(disco->addd!=0){
                        if(disco->u==""){
                            disco->u="k";
                        }
                        if(disco->f==""){
                            disco->f="wf";
                        }
                        if(disco->typee==""){
                            disco->typee="p";
                        }

                        //AQUI VA TODO EL CODIGO PARA AGREGAR O QUITAR ESPACIO EN DISCO CON FAST O FULL
                    }else{
                        cout<<"Valor a Quitar/Agregar Espacio En Disco No Puede Ser 0, incorrecto"<<endl;
                    }
                }else{
                    cout<<"No se ingreso comando Delete Aceptado, incorrecto"<<endl;
                }
            }
        }else{
            cout<<"Nombre De La Particion No Ingresada, Incorrecto"<<endl;
        }
    }else{
        cout<<"Ruta No Ingresada, Incorrecto"<<endl;
    }

    disco->size = 0;
    disco->u = "";
    disco->path = "";
    disco->typee = "";
    disco->f = "";
    disco->deletee = "";
    disco->namee = "";
    disco->addd = 0;
}
