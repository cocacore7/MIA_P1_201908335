#ifndef CLMKUSER_H
#define CLMKUSER_H
#include <QString>

class clmkuser
{
public:
    clmkuser();

    QString usr;
    QString pwd;
    QString grp;
    void mostrarDatos(clmkuser *solicitud);
};

#endif // CLMKUSER_H
