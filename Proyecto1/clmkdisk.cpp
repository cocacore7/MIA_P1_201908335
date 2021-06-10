#include "clmkdisk.h"
#include <QString>
#include <iostream>
#include <fstream>
#include <qstringlist.h>
#include <QFile>
#include <QDir>
#include <mbrstruct.h>
using namespace std;

clmkdisk::clmkdisk()
{

}


void clmkdisk::mostrarDatos(clmkdisk *disco){
    cout<<"-----------------------CrearDisco---------------------"<<endl;
    disco->path.remove(QChar('"'), Qt::CaseInsensitive);
    if(disco->size > 0){
        if(disco->path != ""){
            if(disco->f == ""){
                disco->f = "ff";
            }
            if(disco->u == ""){
                disco->u="m";
            }

            //AQUI VA TODO EL CODIGO DEL MKDISK
            QStringList direcciones = disco->path.split("/");
            QString ruta = "";
            bool primera = false;
            if(direcciones[1] == "home" && direcciones[2] == "archivos"){
                ruta = "/home/oscar/archivos";
                for(int x=3;x<(direcciones.length()-1);x++){
                    if(primera){
                        QDir direc(ruta);
                        direc.mkdir(direcciones[x]);
                        ruta = ruta + direcciones[x] + "/";
                    }else{
                        QDir direc(ruta);
                        direc.mkdir(direcciones[x]);
                        ruta = ruta + "/" + direcciones[x] + "/";
                        primera = true;
                    }
                }
            }

            QString aux =direcciones[direcciones.length()-1];
            QStringList discofisico = aux.split(".");
            if(discofisico[1] == "dk"){
                //AQUI CREAMOS ARCHIVO FISICO
                if(primera){
                    ruta = ruta + aux;
                }else{
                    ruta = ruta + "/" + aux;
                }
                QFile archivo(ruta);
                if(archivo.exists()){
                    QByteArray ba = aux.toLocal8Bit();
                    const char* com = ba.data();
                    cout<<"El Disco: " << com<< " Ya Existe"<<endl;
                    archivo.close();
                }else{
                    archivo.close();
                    //AQUI LLENAMOS EL ARCHIVO FISICO
                    struct MBR nuevo_mbr;
                    nuevo_mbr.mbr_fecha_creacion = time(NULL);
                    nuevo_mbr.mbr_disk_signature = rand();
                    if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                        nuevo_mbr.disk_fit = 'F';
                    }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                        nuevo_mbr.disk_fit = 'B';
                    }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                        nuevo_mbr.disk_fit = 'W';
                    }
                    struct particion p1;
                    struct particion p2;
                    struct particion p3;
                    struct particion p4;
                    p1 = nuevo_mbr.mbr_partition_1;
                    p2 = nuevo_mbr.mbr_partition_2;
                    p3 = nuevo_mbr.mbr_partition_3;
                    p4 = nuevo_mbr.mbr_partition_4;
                    p1.part_status = '.';
                    p2.part_status = '.';
                    p3.part_status = '.';
                    p4.part_status = '.';
                    p1.part_type = '.';
                    p2.part_type = '.';
                    p3.part_type = '.';
                    p4.part_type = '.';
                    p1.part_fit = '.';
                    p2.part_fit = '.';
                    p3.part_fit = '.';
                    p4.part_fit = '.';
                    p1.part_size = 0;
                    p2.part_size = 0;
                    p3.part_size = 0;
                    p4.part_size = 0;
                    p1.part_start = 0;
                    p2.part_start = 0;
                    p3.part_start = 0;
                    p4.part_start = 0;
                    nuevo_mbr.mbr_partition_1 = p1;
                    nuevo_mbr.mbr_partition_2 = p2;
                    nuevo_mbr.mbr_partition_3 = p3;
                    nuevo_mbr.mbr_partition_4 = p4;

                    QString comando="";
                    if(disco->u == "m" || disco->u == "M"){
                        nuevo_mbr.mbr_tam = 1048576 * disco->size;
                        comando="dd if=/dev/zero of=\"" + ruta + "\" bs=1048576 count=" + QStringLiteral("%1").arg(disco->size);
                    }else{
                        nuevo_mbr.mbr_tam = 1024 * disco->size;
                        comando="dd if=/dev/zero of=\"" + ruta + "\" bs=1024 count=" + QStringLiteral("%1").arg(disco->size);
                    }
                    QByteArray ba = comando.toLocal8Bit();
                    const char* com = ba.data();
                    system(com);
                    FILE *nuevoDisco;
                    ba = ruta.toLocal8Bit();
                    com = ba.data();
                    nuevoDisco=fopen(com,"rb+");
                    fseek(nuevoDisco,0,SEEK_SET);
                    //INGRESAR EL MBR AL DISCO
                    fwrite(&nuevo_mbr,sizeof (MBR),1,nuevoDisco);
                    fseek(nuevoDisco,0,SEEK_SET);
                    fclose(nuevoDisco);
                    ba = aux.toLocal8Bit();
                    com = ba.data();
                    cout<<"El Disco: " << com<< " Se Creo Exitosamente :D"<<endl;
                }
            }else{
                cout<<"Extension de Disco incorrecta, no es .dk"<<endl;
            }
        }else{
            cout<<"Ruta No Ingresada, Incorrecto"<<endl;
        }
    } else{
     cout<<"Tamaño de disco Incorrecto"<<endl;
    }
    disco->size = 0;
    disco->f = "";
    disco->u = "";
    disco->path = "";
    cout<<"--------------------------------------------------------"<<endl;
}
