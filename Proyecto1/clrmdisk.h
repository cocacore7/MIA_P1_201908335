#ifndef CLRMDISK_H
#define CLRMDISK_H
#include <QString>
using namespace std;

class clrmdisk
{
public:
    clrmdisk();

    QString path;
    void mostrarDatos(clrmdisk *disco);
};

#endif // CLRMDISK_H
