#ifndef CLMONTADA_H
#define CLMONTADA_H

#include <iostream>
#include <QString>

using namespace std;

struct nodo{
    QString id;
    QString nombreP;
    QString nombreD;
    QString ruta;
    QString particion;
    QString tipo;
    QString fit;
    QString estado;
    int inicio;
    int tamanio;
    int nextL;
    struct nodo *sig;
};

typedef  struct nodo *ListaM ;


class clMontada
{
public:
    clMontada();

    ListaM lista;
    void insertarNodo(ListaM &lista, QString id, QString nombreP, QString nombreD,QString ruta,QString particion, QString tipo, QString fit, QString estado, int inicio, int tamanio, int nextL );
    QString eliminarNodo(ListaM &lista, QString id);
    void imprimirLista(ListaM lista);
    QString obtenerId(ListaM lista, QString nombreD, QString nombreP);
    bool comprobarId(ListaM lista, QString id);
};

#endif // CLMONTADA_H
