#ifndef CLCHOWN_H
#define CLCHOWN_H
#include <QString>

class clchown
{
public:
    clchown();

    QString path;
    QString usr;
    QString R;
    void mostrarDatos(clchown *propietario);
};

#endif // CLCHOWN_H
