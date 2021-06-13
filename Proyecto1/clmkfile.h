#ifndef CLMKFILE_H
#define CLMKFILE_H
#include <QString>

class clmkfile
{
public:
    clmkfile();

    QString path;
    int size;
    QString cont;
    QString R;
    QString P;
    void mostrarDatos(clmkfile *carpeta);
};

#endif // CLMKFILE_H
