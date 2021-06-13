#ifndef CLRMUSER_H
#define CLRMUSER_H
#include <QString>

class clrmuser
{
public:
    clrmuser();

    QString usr;
    void mostrarDatos(clrmuser *solicitud);
};

#endif // CLRMUSER_H
