#ifndef CLCHMMOD_H
#define CLCHMMOD_H
#include <QString>


class clchmmod
{
public:
    clchmmod();

    QString path;
    int ugo;
    QString R;
    void mostrarDatos(clchmmod *permisos);
};

#endif // CLCHMMOD_H
