#ifndef CLCP_H
#define CLCP_H
#include <QString>

class clcp
{
public:
    clcp();

    QString path;
    QString dest;
    void mostrarDatos(clcp *copiar);
};

#endif // CLCP_H
