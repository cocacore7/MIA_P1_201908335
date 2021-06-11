#include "clmontada.h"
#include <QString>
#include <iostream>
#include <QDir>

clMontada::clMontada()
{

}

void clMontada::insertarNodo(ListaM &lista, QString id, QString nombreP, QString nombreD,QString ruta,QString particion, QString tipo, QString fit, QString estado, int inicio, int tamanio, int nextL ){
    ListaM t,q = new(struct nodo);

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

QString clMontada::eliminarNodo(ListaM &lista, QString id){
    ListaM p,ant;
    p=lista;
    bool eliminada = false;
    QString retorno = "";
    if(lista!=NULL){
        while (p!=NULL) {
            if(p->id == id){
                if(p==lista){
                    QString n = QStringLiteral("%1").arg(lista->inicio);
                    retorno = lista->ruta + "," +lista->tipo + "," +lista->particion + "," +n + "," +lista->nombreP;
                    lista = lista->sig;
                }
                else{
                    QString n = QStringLiteral("%1").arg(p->inicio);
                    retorno = p->ruta + "," +p->tipo + "," +p->particion + "," +n + "," +p->nombreP;
                    ant->sig = p->sig;
                }
                delete (p);
                cout<<"Particion con id: "<<id.toStdString().c_str()<<" Eliminada"<<endl;
                return retorno;
            }
            ant = p;
            p = p->sig;
        }
        if(!eliminada){
            cout<<"Error, No Hay Montada Particion Con ID: "<<id.toStdString().c_str()<<endl;
        }
    }else{cout<<"No Hay Particiones Montadas"<<endl;}
    return retorno;
}

void clMontada::imprimirLista(ListaM lista){
    while (lista!=NULL) {
        cout<<"-----------------------------------------------------"<<endl;
        cout<<"Id: "<<lista->id.toStdString().c_str()<<endl;
        cout<<"Nombre: "<<lista->nombreP.toStdString().c_str()<<endl;
        cout<<"Ruta: "<<lista->nombreD.toStdString().c_str()<<endl;
        cout<<"Tipo: "<<lista->tipo.toStdString().c_str()<<endl;
        cout<<"Fit: "<<lista->fit.toStdString().c_str()<<endl;
        cout<<"Estado: "<<lista->estado.toStdString().c_str()<<endl;
        cout<<"Inicio: "<<lista->inicio<<endl;
        cout<<"Tamaño: "<<lista->tamanio<<endl;
        cout<<"NextLogica: "<<lista->nextL<<endl;
        lista = lista->sig;
    }
    cout<<"-----------------------------------------------------"<<endl;
}

QString clMontada::obtenerId(ListaM lista, QString nombreD, QString nombreP){
    int num = 0;
    QStringList letra;
    QString nuevo="";
    if(lista == NULL){
        nuevo = "351a";
    }else{
        ListaM auxl1 = lista;
        ListaM auxl2 = lista;
        bool discoE = false;
        while (auxl2!=NULL) {
            if(auxl2->nombreP == nombreP){
                if(auxl2->nombreD == nombreD){
                    cout<<"La Particion: "<<nombreP.toStdString().c_str()<< " Ya Se Encuentra Montada"<<endl;
                    return "";
                }else{
                    cout<<"La Nombre De La Particion: "<<nombreP.toStdString().c_str()<< " Ya Existe En Otro Disco"<<endl;
                    return "";
                }
            }
            auxl2 = auxl2->sig;
        }
        while (auxl1!=NULL) {
            if(auxl1->nombreD == nombreD){
                QStringList idChar = auxl1->id.split("");
                num = idChar[3].toInt();
                letra.append(idChar[4]);
                discoE = true;
            }
            auxl1 = auxl1->sig;
        }

        if(discoE){
            char nuevaletra = 'a';
            bool entremedias = false;
            for(int x=0;x<letra.length();x++){
                if((x+1) < letra.length()){
                    char m1 = letra[x].toStdString().c_str()[0];
                    char m2 = letra[x+1].toStdString().c_str()[0];
                    int m3 = m1;
                    int m4 = m2;
                    if((m4 -m3) > 1 ){
                        nuevaletra = m3;
                        entremedias = true;
                        break;
                    }
                }
            }
            if(entremedias){
                int numl = nuevaletra;
                nuevaletra = numl +1;
            }else{
                nuevaletra = letra.takeLast().toStdString().c_str()[0];
                int numl = nuevaletra + 1;
                nuevaletra = numl;
            }
            QString l(nuevaletra);
            QString n = QStringLiteral("%1").arg(num);
            nuevo = "35" + n[0] + l;
        }else{
            int mayor = 0;
            while (lista!=NULL) {
                if(lista->sig !=NULL){
                    QStringList numd1 = lista->id.split("");
                    QStringList numd2 = lista->sig->id.split("");
                    if(numd1[3].toInt() <= numd2[3].toInt()){
                        mayor = numd2[3].toInt();
                    }
                }
                lista = lista->sig;
            }
            mayor++;
            QString n= QStringLiteral("%1").arg(mayor);
            nuevo = "35" + n + "a";
        }

    }
    return nuevo;
}

bool clMontada::comprobarId(ListaM lista, QString id){
    while (lista!=NULL) {
        if(id == lista->id){
            return true;
        }
        lista = lista->sig;
    }
    return false;
}
