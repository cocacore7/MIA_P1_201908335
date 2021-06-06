#ifndef CLMKFS_H
#define CLMKFS_H
#include <QString>
using namespace std;


class clmkfs
{
public:
    clmkfs();

    QString id;
    QString type;
    QString fs;
    void mostrarDatos(clmkfs *disco);
};

#endif // CLMKFS_H
