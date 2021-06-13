#include "clsesion.h"

clsesion::clsesion()
{

}

void clsesion::login(ListaM &lista, QString &usuario, QString usua, QString id, QString nombreP, QString nombreD,QString ruta,QString particion, QString tipo, QString fit, QString estado, int inicio, int tamanio, int nextL ){
    ListaM q = new(struct nodo);

    q->id = id;
    q->nombreP = nombreP;
    q->nombreD = nombreD;
    q->ruta = ruta;
    q->particion = particion;
    q->tipo = tipo;
    q->fit = fit;
    q->estado = estado;
    q->inicio = inicio;
    q->tamanio = tamanio;
    q->nextL = nextL;
    q->sig = NULL;

    lista = q;
    usuario = usua;
}

void clsesion::logout(ListaM &lista, QString &usuario){
    lista = NULL;
    usuario = "";
}
