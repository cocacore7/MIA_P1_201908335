#ifndef CLLOGIN_H
#define CLLOGIN_H
#include <QString>


class cllogin
{
public:
    cllogin();

    QString usr;
    QString pwd;
    QString id;
    void logear(cllogin *solicitud);
    void salir();
};

#endif // CLLOGIN_H
