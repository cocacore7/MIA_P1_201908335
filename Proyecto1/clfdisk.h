#ifndef CLFDISK_H
#define CLFDISK_H
#include <QString>
using namespace std;

class clfdisk
{
public:
    clfdisk();

    int size;
    QString f;
    QString u;
    QString path;
    QString typee;
    QString deletee;
    QString namee;
    int addd;
    void mostrarDatos(clfdisk *disco);
};

#endif // CLFDISK_H
