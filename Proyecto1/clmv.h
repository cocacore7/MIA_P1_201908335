#ifndef CLMV_H
#define CLMV_H
#include <QString>

class clmv
{
public:
    clmv();

    QString path;
    QString dest;
    void mostrarDatos(clmv *mover);
};

#endif // CLMV_H
