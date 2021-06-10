#ifndef LISTAMONTADAS_H
#define LISTAMONTADAS_H
#include <iostream>
#include <QString>

using namespace std;

struct nodo{
    QString id;
    QString nombre;
    QString ruta;
    QString tipo;
    QString fit;
    QString estado;
    int inicio;
    int tamanio;
    int nextL;
    struct nodo *sig;
};

typedef  struct nodo *ListaM ;

void insertar(ListaM &lista, QString id, QString estado, QString tipo, QString fit, QString nombre, QString ruta, int tamanio, int inicio, int nextL ){
    ListaM t,q = new(struct nodo);

    q->id = id;
    q->nombre = nombre;
    q->ruta = ruta;
    q->tipo = tipo;
    q->fit = fit;
    q->estado = estado;
    q->inicio = inicio;
    q->tamanio = tamanio;
    q->nextL = nextL;
    q->sig = NULL;

    if(lista == NULL){
        lista = q;
    }else{
        t=lista;
        while (t->sig!=NULL) {
            t = t->sig;
        }
        t->sig = q;
    }
    cout<<"Particion: "<<id.toStdString().c_str()<<" Montada :D"<<endl;
}

void eliminar(ListaM &lista, QString id){
    ListaM p,ant;
    p=lista;

    if(lista!=NULL){
        while (p!=NULL) {
            if(p->id == id){
                if(p==lista)
                    lista = lista->sig;
                else
                    ant->sig = p->sig;

                delete (p);
                return;
            }
            ant = p;
            p = p->sig;
        }
    }else{cout<<"No Hay Particiones Montadas"<<endl;}
}


#endif // LISTAMONTADAS_H
