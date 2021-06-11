#ifndef CLREPORTES_H
#define CLREPORTES_H
#include <QString>
using namespace std;

class clReportes
{
public:
    clReportes();

    QString path;
    QString namee;
    QString id;

    void mostrarDatos(clReportes *reporte);
};

#endif // CLREPORTES_H
