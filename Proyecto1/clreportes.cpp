#include "clreportes.h"
#include <QString>
#include <iostream>
//Necesario Para Usar Montada --------------
#include <clmontada.h>
#include <cabeceramontadas.h>
//-------------------------------------------
clReportes::clReportes()
{

}

void clReportes::mostrarDatos(clReportes *reporte){
    if(lista.comprobarId(lista.lista,reporte->id)){
        reporte->path.remove(QChar('"'), Qt::CaseInsensitive);
        if(reporte->namee.toLower() == "mbr"){
            cout<<"-----------------------ReporteMBR---------------------"<<endl;

        }else if(reporte->namee.toLower() == "disk"){
            cout<<"-----------------------ReporteDISK---------------------"<<endl;

        }else if(reporte->namee.toLower() == "inode"){
            cout<<"-----------------------ReporteINODE---------------------"<<endl;

        }else if(reporte->namee.toLower() == "journaling"){
            cout<<"-----------------------ReporteJOURNALING---------------------"<<endl;

        }else if(reporte->namee.toLower() == "block"){
            cout<<"-----------------------ReporteBLOCK---------------------"<<endl;

        }else if(reporte->namee.toLower() == "bm_inode"){
            cout<<"-----------------------ReporteBM_INODE---------------------"<<endl;

        }else if(reporte->namee.toLower() == "bm_block"){
            cout<<"-----------------------ReporteBM_BLOCK---------------------"<<endl;

        }else if(reporte->namee.toLower() == "tree"){
            cout<<"-----------------------ReporteTREE---------------------"<<endl;

        }else if(reporte->namee.toLower() == "sb"){
            cout<<"-----------------------ReporteSB---------------------"<<endl;

        }else if(reporte->namee.toLower() == "file"){
            cout<<"-----------------------ReporteFILE---------------------"<<endl;

        }else if(reporte->namee.toLower() == "ls"){
            cout<<"-----------------------ReporteLS---------------------"<<endl;

        }else{
            cout<<"-----------------------ReporteERROR---------------------"<<endl;
            cout<<"El Reporte De Tipo: "<<reporte->namee.toStdString().c_str()<<" No Existe"<<endl;
        }
    }else{
        cout<<"La Particion con Id: "<<reporte->id.toStdString().c_str()<<" No se encuentra montada"<<endl;
    }
    reporte->id = "";
    reporte->path = "";
    reporte->namee = "";
}
