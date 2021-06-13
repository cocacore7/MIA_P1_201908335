#ifndef CLSESION_H
#define CLSESION_H
#include <QString>
#include "clmontada.h"

class clsesion
{
public:
    clsesion();

    QString usuario;
    ListaM activaP;
    void login(ListaM &lista, QString &usuario, QString usua, QString id, QString nombreP, QString nombreD,QString ruta,QString particion, QString tipo, QString fit, QString estado, int inicio, int tamanio, int nextL );
    void logout(ListaM &lista, QString &usuario);
};

#endif // CLSESION_H
