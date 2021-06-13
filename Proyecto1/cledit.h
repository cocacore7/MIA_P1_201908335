#ifndef CLEDIT_H
#define CLEDIT_H
#include <QString>

class cledit
{
public:
    cledit();

    QString path;
    QString cont;
    void mostrarDatos(cledit *editar);
};

#endif // CLEDIT_H
