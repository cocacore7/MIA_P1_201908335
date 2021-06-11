#ifndef CLMOUNT_H
#define CLMOUNT_H
#include <QString>
using namespace std;

class clmount
{
public:
    clmount();

    QString path;
    QString namee;
    void mostrarDatos(clmount *disco);
};

#endif // CLMOUNT_H
