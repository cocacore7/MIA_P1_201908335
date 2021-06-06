#ifndef CLMKDISK_H
#define CLMKDISK_H
#include <QString>
using namespace std;


class clmkdisk
{
public:
    clmkdisk();

    int size;
    QString f;
    QString u;
    QString path;
    void mostrarDatos(clmkdisk *disco);
};

#endif // CLMKDISK_H
