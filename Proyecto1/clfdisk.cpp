#include "clfdisk.h"
#include <QString>
#include <iostream>
#include <QStringList>
#include <QDir>
#include <mbrstruct.h>
using namespace std;

clfdisk::clfdisk()
{

}

typedef struct{
    char                part_status;
    char                part_fit;
    int                 part_start;
    int                 part_size;
    int                 part_next;
    char                part_name[16];
} EBR;

void clfdisk::mostrarDatos(clfdisk *disco){
    cout<<"-----------------------CrearParticion---------------------"<<endl;
    cout<<"El tamaño es: "<<disco->size<<endl;
    cout<<"El U es: "<<disco->u.toStdString()<<endl;
    cout<<"El Path es: "<<disco->path.toStdString()<<endl;
    cout<<"El Type es: "<<disco->typee.toStdString()<<endl;
    cout<<"El F es: "<<disco->f.toStdString()<<endl;
    cout<<"El Delete es: "<<disco->deletee.toStdString()<<endl;
    cout<<"El Name es: "<<disco->namee.toStdString()<<endl;
    cout<<"El Typo De Entero es: "<<disco->primero.toStdString()<<endl;
    cout<<"El Add es: "<<disco->addd<<endl;

    disco->path.remove(QChar('"'), Qt::CaseInsensitive);
    if(disco->path!=""){
        if(disco->namee!=""){
            if(disco->deletee==""){
                if(disco->primero=="s"){
                    //CREAR PARTICION
                    if(disco->size<=0){
                        if(disco->u==""){
                            disco->u="k";
                        }
                        if(disco->f==""){
                            disco->f="wf";
                        }
                        if(disco->typee==""){
                            disco->typee="p";
                        }

                        QStringList direcciones = disco->path.split("/");
                        QString ruta = "";
                        bool NoCarpeta = false;
                        if(direcciones[1] == "home" && direcciones[2] == "archivos"){
                            ruta = "/home/oscar/archivos";
                            for(int x=3;x<(direcciones.length()-1);x++){
                                ruta = ruta + "/" + direcciones[x];
                                QDir direc(ruta);
                                if(!direc.exists()){
                                    QByteArray ba = direcciones[x].toLocal8Bit();
                                    const char* com = ba.data();
                                    cout<<"La carpeta: "<<com<<" No Existe"<<endl;
                                    NoCarpeta=true;
                                    break;
                                }
                            }
                        }

                        if(!NoCarpeta){
                            QString aux =direcciones[direcciones.length()-1];
                            QStringList discofisico = aux.split(".");
                            if(discofisico[1] == "dk"){
                                ruta = ruta + "/" + aux;
                                QFile archivo(ruta);
                                if(archivo.exists()){
                                    //OBTENER MBR DE DISCO
                                    FILE *Discoo;
                                    QByteArray ba = ruta.toLocal8Bit();
                                    const char* com = ba.data();
                                    Discoo=fopen(com,"rb+");
                                    fseek(Discoo,0,SEEK_SET);
                                    MBR mbr;
                                    fread(&mbr,sizeof(MBR),1,Discoo);
                                    fclose(Discoo);

                                    //COMPROBAR TIPO DE PARTICION A CREAR
                                    char extendida[] = {'.','.','.','.'};
                                    if(disco->typee=="p" || disco->typee=="e" || disco->typee=="P" || disco->typee=="E"){
                                        //COMPROBAR PARTICIONES LIBRES Y NO MAS DE UNA EXTENDIDA
                                        if(mbr.mbr_partition_1->part_type != *"."){
                                            if(mbr.mbr_partition_1->part_type == *"e" || mbr.mbr_partition_1->part_type == *"E"){
                                                   extendida[0] = 'e';
                                            }
                                            if(mbr.mbr_partition_1->part_type == *"p" || mbr.mbr_partition_1->part_type == *"P"){
                                                   extendida[0] = 'p';
                                            }
                                        }
                                        if(mbr.mbr_partition_2->part_type != *"."){
                                            if(mbr.mbr_partition_2->part_type == *"e" || mbr.mbr_partition_2->part_type == *"E"){
                                                   extendida[1] = 'e';
                                            }
                                            if(mbr.mbr_partition_2->part_type == *"p" || mbr.mbr_partition_2->part_type == *"P"){
                                                   extendida[1] = 'p';
                                            }
                                        }
                                        if(mbr.mbr_partition_3->part_type != *"."){
                                            if(mbr.mbr_partition_3->part_type == *"e" || mbr.mbr_partition_3->part_type == *"E"){
                                                   extendida[2] = 'e';
                                            }
                                            if(mbr.mbr_partition_3->part_type == *"p" || mbr.mbr_partition_3->part_type == *"P"){
                                                   extendida[2] = 'p';
                                            }
                                        }
                                        if(mbr.mbr_partition_4->part_type != *"."){
                                            if(mbr.mbr_partition_4->part_type == *"e" || mbr.mbr_partition_4->part_type == *"E"){
                                                   extendida[3] = 'e';
                                            }
                                            if(mbr.mbr_partition_4->part_type == *"p" || mbr.mbr_partition_4->part_type == *"P"){
                                                   extendida[3] = 'p';
                                            }
                                        }

                                        int cantext = 0;
                                        for(int x=0;x<4;x++){
                                            if(extendida[x]=='e'){cantext++;}
                                        }

                                        if(disco->typee == "e" || disco->typee == "E"){cantext++;}

                                        if(disco->namee != mbr.mbr_partition_1->part_name && disco->namee != mbr.mbr_partition_2->part_name && disco->namee != mbr.mbr_partition_3->part_name && disco->namee != mbr.mbr_partition_4->part_name){
                                            //1 2 3 4
                                            if(extendida[0]!='.' && extendida[1]!='.' && extendida[2]!='.' && extendida[3]!='.'){
                                                cout<<"No Hay Particiones Libres, 4 PArticiones Creadas"<<endl;
                                            }else{
                                                if (cantext <=1){
                                                    //COMPROBAR ESPACIO LIBRE CON CAPACIDAD DE ALMACENAR PARTICION
                                                    int tamDisco = mbr.mbr_tam;
                                                    int tam_mbr = sizeof(mbr);
                                                    int espsolicitado = 0;
                                                    int p1 = mbr.mbr_partition_1->part_size;
                                                    int p2 = mbr.mbr_partition_2->part_size;
                                                    int p3 = mbr.mbr_partition_3->part_size;
                                                    int p4 = mbr.mbr_partition_4->part_size;
                                                    if(disco->u == "b" || disco->u == "B"){
                                                        espsolicitado = disco->size;
                                                    }else if(disco->u == "k" || disco->u == "K"){
                                                        espsolicitado = disco->size * 1024;
                                                    }else if(disco->u == "m" || disco->u == "M"){
                                                        espsolicitado = disco->size * 1024 * 1024;
                                                    }
                                                    //. . . .
                                                    if(extendida[0]=='.' && extendida[1]=='.' && extendida[2]=='.' && extendida[3]=='.'){
                                                        if((tamDisco - tam_mbr - p1 - p2 - p3 - p4 - espsolicitado) > 0){
                                                            //INGRESAR PARTICION AL ARCHIVO FISICO
                                                            mbr.mbr_partition_1->part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                mbr.mbr_partition_1->part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                mbr.mbr_partition_1->part_type = 'P';
                                                            }
                                                            mbr.mbr_partition_1->part_type = disco->typee.toStdString().c_str()[0];
                                                            if(disco->f=="")
                                                                if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                    mbr.mbr_partition_1->part_fit = 'F';
                                                                }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                    mbr.mbr_partition_1->part_fit = 'B';
                                                                }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                    mbr.mbr_partition_1->part_fit = 'W';
                                                                }
                                                            mbr.mbr_partition_1->part_start = tam_mbr;
                                                            mbr.mbr_partition_1->part_size = espsolicitado;
                                                            memset(mbr.mbr_partition_1->part_name,0,16);
                                                            strcpy(mbr.mbr_partition_1->part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            if(disco->typee=="p" || disco->typee=="P"){
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Primaria: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }else{
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Extendida: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }
                                                        }else{
                                                            cout<<"Espacio Solicitado para la particion, Supera Tamaño del Disco"<<endl;
                                                        }
                                                    }
                                                    //1 . . .
                                                    else if(extendida[0]!='.' && extendida[1]=='.' && extendida[2]=='.' && extendida[3]=='.'){
                                                        if((tamDisco - tam_mbr - p1 - espsolicitado) > 0){
                                                            //INGRESAR PARTICION AL ARCHIVO FISICO
                                                            mbr.mbr_partition_2->part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                mbr.mbr_partition_2->part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                mbr.mbr_partition_2->part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                mbr.mbr_partition_2->part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                mbr.mbr_partition_2->part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                mbr.mbr_partition_2->part_fit = 'W';
                                                            }
                                                            mbr.mbr_partition_2->part_start = tam_mbr + p1;
                                                            mbr.mbr_partition_2->part_size = espsolicitado;
                                                            memset(mbr.mbr_partition_2->part_name,0,16);
                                                            strcpy(mbr.mbr_partition_2->part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            if(disco->typee=="p" || disco->typee=="P"){
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Primaria: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }else{
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Extendida: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }
                                                        }else{
                                                            cout<<"Espacio Solicitado para la particion, Supera Tamaño del Disco"<<endl;
                                                        }
                                                    }
                                                    //. 2 . .
                                                    else if(extendida[0]=='.' && extendida[1]!='.' && extendida[2]=='.' && extendida[3]=='.'){
                                                        if((mbr.mbr_partition_2->part_start - tam_mbr) > espsolicitado){
                                                            //INGRESAR PARTICION AL ARCHIVO FISICO
                                                            mbr.mbr_partition_1->part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                mbr.mbr_partition_1->part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                mbr.mbr_partition_1->part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                mbr.mbr_partition_1->part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                mbr.mbr_partition_1->part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                mbr.mbr_partition_1->part_fit = 'W';
                                                            }
                                                            mbr.mbr_partition_1->part_start = tam_mbr;
                                                            mbr.mbr_partition_1->part_size = espsolicitado;
                                                            memset(mbr.mbr_partition_1->part_name,0,16);
                                                            strcpy(mbr.mbr_partition_1->part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            if(disco->typee=="p" || disco->typee=="P"){
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Primaria: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }else{
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Extendida: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }
                                                        }
                                                        else if((tamDisco - tam_mbr - p1 - p2 - espsolicitado) > 0){
                                                            //INGRESAR PARTICION AL ARCHIVO FISICO
                                                            mbr.mbr_partition_3->part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                mbr.mbr_partition_3->part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                mbr.mbr_partition_3->part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                mbr.mbr_partition_3->part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                mbr.mbr_partition_3->part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                mbr.mbr_partition_3->part_fit = 'W';
                                                            }
                                                            mbr.mbr_partition_3->part_start = tam_mbr + p1 + p2;
                                                            mbr.mbr_partition_3->part_size = espsolicitado;
                                                            memset(mbr.mbr_partition_3->part_name,0,16);
                                                            strcpy(mbr.mbr_partition_3->part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            if(disco->typee=="p" || disco->typee=="P"){
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Primaria: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }else{
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Extendida: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }
                                                        }else{
                                                            cout<<"Espacio Solicitado para la particion, Supera Tamaño del Disco"<<endl;
                                                        }
                                                    }
                                                    //. . 3 .
                                                    else if(extendida[0]=='.' && extendida[1]=='.' && extendida[2]!='.' && extendida[3]=='.'){
                                                        if((mbr.mbr_partition_3->part_start - tam_mbr) > espsolicitado){
                                                            //INGRESAR PARTICION AL ARCHIVO FISICO
                                                            mbr.mbr_partition_1->part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                mbr.mbr_partition_1->part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                mbr.mbr_partition_1->part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                mbr.mbr_partition_1->part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                mbr.mbr_partition_1->part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                mbr.mbr_partition_1->part_fit = 'W';
                                                            }
                                                            mbr.mbr_partition_1->part_start = tam_mbr;
                                                            mbr.mbr_partition_1->part_size = espsolicitado;
                                                            memset(mbr.mbr_partition_1->part_name,0,16);
                                                            strcpy(mbr.mbr_partition_1->part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            if(disco->typee=="p" || disco->typee=="P"){
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Primaria: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }else{
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Extendida: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }
                                                        }
                                                        else if((tamDisco - tam_mbr - p1 - p2 - p3 - espsolicitado) > 0){
                                                            //INGRESAR PARTICION AL ARCHIVO FISICO
                                                            mbr.mbr_partition_4->part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                mbr.mbr_partition_4->part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                mbr.mbr_partition_4->part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                mbr.mbr_partition_4->part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                mbr.mbr_partition_4->part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                mbr.mbr_partition_4->part_fit = 'W';
                                                            }
                                                            mbr.mbr_partition_4->part_start = tam_mbr + p1+ p2+ p3;
                                                            mbr.mbr_partition_4->part_size = espsolicitado;
                                                            memset(mbr.mbr_partition_4->part_name,0,16);
                                                            strcpy(mbr.mbr_partition_4->part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            if(disco->typee=="p" || disco->typee=="P"){
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Primaria: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }else{
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Extendida: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }
                                                        }else{
                                                            cout<<"Espacio Solicitado para la particion, Supera Tamaño del Disco"<<endl;
                                                        }
                                                    }
                                                    //. . . 4
                                                    else if(extendida[0]=='.' && extendida[1]=='.' && extendida[2]=='.' && extendida[3]!='.'){
                                                        if((mbr.mbr_partition_4->part_start - tam_mbr) > espsolicitado){
                                                            //INGRESAR PARTICION AL ARCHIVO FISICO
                                                            mbr.mbr_partition_1->part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                mbr.mbr_partition_1->part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                mbr.mbr_partition_1->part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                mbr.mbr_partition_1->part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                mbr.mbr_partition_1->part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                mbr.mbr_partition_1->part_fit = 'W';
                                                            }
                                                            mbr.mbr_partition_1->part_start = tam_mbr;
                                                            mbr.mbr_partition_1->part_size = espsolicitado;
                                                            memset(mbr.mbr_partition_1->part_name,0,16);
                                                            strcpy(mbr.mbr_partition_1->part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            if(disco->typee=="p" || disco->typee=="P"){
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Primaria: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }else{
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Extendida: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }
                                                        }
                                                        else{
                                                            cout<<"Espacio Solicitado para la particion, Supera Tamaño del Disco"<<endl;
                                                        }
                                                    }
                                                    //1 2 . .
                                                    else if(extendida[0]!='.' && extendida[1]!='.' && extendida[2]=='.' && extendida[3]=='.'){
                                                        if((tamDisco - tam_mbr - p1 - p2 - espsolicitado) > 0){
                                                            //INGRESAR PARTICION AL ARCHIVO FISICO
                                                            mbr.mbr_partition_3->part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                mbr.mbr_partition_3->part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                mbr.mbr_partition_3->part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                mbr.mbr_partition_3->part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                mbr.mbr_partition_3->part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                mbr.mbr_partition_3->part_fit = 'W';
                                                            }
                                                            mbr.mbr_partition_3->part_start = tam_mbr + p1 + p2;
                                                            mbr.mbr_partition_3->part_size = espsolicitado;
                                                            memset(mbr.mbr_partition_3->part_name,0,16);
                                                            strcpy(mbr.mbr_partition_3->part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            if(disco->typee=="p" || disco->typee=="P"){
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Primaria: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }else{
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Extendida: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }
                                                        }else{
                                                            cout<<"Espacio Solicitado para la particion, Supera Tamaño del Disco"<<endl;
                                                        }
                                                    }
                                                    //1 . 3 .
                                                    else if(extendida[0]!='.' && extendida[1]=='.' && extendida[2]!='.' && extendida[3]=='.'){
                                                        if((mbr.mbr_partition_3->part_start - tam_mbr -p1) > espsolicitado){
                                                            //INGRESAR PARTICION AL ARCHIVO FISICO
                                                            mbr.mbr_partition_2->part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                mbr.mbr_partition_2->part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                mbr.mbr_partition_2->part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                mbr.mbr_partition_2->part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                mbr.mbr_partition_2->part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                mbr.mbr_partition_2->part_fit = 'W';
                                                            }
                                                            mbr.mbr_partition_2->part_start = tam_mbr + p1;
                                                            mbr.mbr_partition_2->part_size = espsolicitado;
                                                            memset(mbr.mbr_partition_2->part_name,0,16);
                                                            strcpy(mbr.mbr_partition_2->part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            if(disco->typee=="p" || disco->typee=="P"){
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Primaria: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }else{
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Extendida: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }
                                                        }
                                                        else if((tamDisco - tam_mbr - p1 - p2 - p3 - espsolicitado) > 0){
                                                            //INGRESAR PARTICION AL ARCHIVO FISICO
                                                            mbr.mbr_partition_4->part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                mbr.mbr_partition_4->part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                mbr.mbr_partition_4->part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                mbr.mbr_partition_4->part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                mbr.mbr_partition_4->part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                mbr.mbr_partition_4->part_fit = 'W';
                                                            }
                                                            mbr.mbr_partition_4->part_start = tam_mbr + p1 + p2 + p3;
                                                            mbr.mbr_partition_4->part_size = espsolicitado;
                                                            memset(mbr.mbr_partition_4->part_name,0,16);
                                                            strcpy(mbr.mbr_partition_4->part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            if(disco->typee=="p" || disco->typee=="P"){
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Primaria: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }else{
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Extendida: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }
                                                        }else{
                                                            cout<<"Espacio Solicitado para la particion, Supera Tamaño del Disco"<<endl;
                                                        }
                                                    }
                                                    //1 . . 4
                                                    else if(extendida[0]!='.' && extendida[1]=='.' && extendida[2]=='.' && extendida[3]!='.'){
                                                        if((mbr.mbr_partition_4->part_start - tam_mbr -p1) > espsolicitado){
                                                            //INGRESAR PARTICION AL ARCHIVO FISICO
                                                            mbr.mbr_partition_2->part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                mbr.mbr_partition_2->part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                mbr.mbr_partition_2->part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                mbr.mbr_partition_2->part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                mbr.mbr_partition_2->part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                mbr.mbr_partition_2->part_fit = 'W';
                                                            }
                                                            mbr.mbr_partition_2->part_start = tam_mbr + p1;
                                                            mbr.mbr_partition_2->part_size = espsolicitado;
                                                            memset(mbr.mbr_partition_2->part_name,0,16);
                                                            strcpy(mbr.mbr_partition_2->part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            if(disco->typee=="p" || disco->typee=="P"){
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Primaria: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }else{
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Extendida: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }
                                                        }
                                                        else{
                                                            cout<<"Espacio Solicitado para la particion, Supera Tamaño del Disco"<<endl;
                                                        }
                                                    }
                                                    //. 2 3 .
                                                    else if(extendida[0]=='.' && extendida[1]!='.' && extendida[2]!='.' && extendida[3]=='.'){
                                                        if((mbr.mbr_partition_2->part_start - tam_mbr) > espsolicitado){
                                                            //INGRESAR PARTICION AL ARCHIVO FISICO
                                                            mbr.mbr_partition_1->part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                mbr.mbr_partition_1->part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                mbr.mbr_partition_1->part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                mbr.mbr_partition_1->part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                mbr.mbr_partition_1->part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                mbr.mbr_partition_1->part_fit = 'W';
                                                            }
                                                            mbr.mbr_partition_1->part_start = tam_mbr;
                                                            mbr.mbr_partition_1->part_size = espsolicitado;
                                                            memset(mbr.mbr_partition_1->part_name,0,16);
                                                            strcpy(mbr.mbr_partition_1->part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            if(disco->typee=="p" || disco->typee=="P"){
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Primaria: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }else{
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Extendida: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }
                                                        }
                                                        else if((tamDisco - tam_mbr - p1 - p2 - p3 - espsolicitado) > 0){
                                                            //INGRESAR PARTICION AL ARCHIVO FISICO
                                                            mbr.mbr_partition_4->part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                mbr.mbr_partition_4->part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                mbr.mbr_partition_4->part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                mbr.mbr_partition_4->part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                mbr.mbr_partition_4->part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                mbr.mbr_partition_4->part_fit = 'W';
                                                            }
                                                            mbr.mbr_partition_4->part_start = tam_mbr + p1 + p2 + p3;
                                                            mbr.mbr_partition_4->part_size = espsolicitado;
                                                            memset(mbr.mbr_partition_4->part_name,0,16);
                                                            strcpy(mbr.mbr_partition_4->part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            if(disco->typee=="p" || disco->typee=="P"){
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Primaria: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }else{
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Extendida: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }
                                                        }else{
                                                            cout<<"Espacio Solicitado para la particion, Supera Tamaño del Disco"<<endl;
                                                        }
                                                    }
                                                    //. 2 . 4
                                                    else if(extendida[0]=='.' && extendida[1]!='.' && extendida[2]=='.' && extendida[3]!='.'){
                                                        if((mbr.mbr_partition_2->part_start - tam_mbr) > espsolicitado){
                                                            //INGRESAR PARTICION AL ARCHIVO FISICO
                                                            mbr.mbr_partition_1->part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                mbr.mbr_partition_1->part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                mbr.mbr_partition_1->part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                mbr.mbr_partition_1->part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                mbr.mbr_partition_1->part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                mbr.mbr_partition_1->part_fit = 'W';
                                                            }
                                                            mbr.mbr_partition_1->part_start = tam_mbr;
                                                            mbr.mbr_partition_1->part_size = espsolicitado;
                                                            memset(mbr.mbr_partition_1->part_name,0,16);
                                                            strcpy(mbr.mbr_partition_1->part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            if(disco->typee=="p" || disco->typee=="P"){
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Primaria: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }else{
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Extendida: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }
                                                        }
                                                        else if((mbr.mbr_partition_4->part_start - tam_mbr - p1 - p2) > espsolicitado){
                                                            //INGRESAR PARTICION AL ARCHIVO FISICO
                                                            mbr.mbr_partition_3->part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                mbr.mbr_partition_3->part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                mbr.mbr_partition_3->part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                mbr.mbr_partition_3->part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                mbr.mbr_partition_3->part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                mbr.mbr_partition_3->part_fit = 'W';
                                                            }
                                                            mbr.mbr_partition_3->part_start = tam_mbr + p1 + p2;
                                                            mbr.mbr_partition_3->part_size = espsolicitado;
                                                            memset(mbr.mbr_partition_3->part_name,0,16);
                                                            strcpy(mbr.mbr_partition_3->part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            if(disco->typee=="p" || disco->typee=="P"){
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Primaria: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }else{
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Extendida: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }
                                                        }else{
                                                            cout<<"Espacio Solicitado para la particion, Supera Tamaño del Disco"<<endl;
                                                        }
                                                    }
                                                    //. . 3 4
                                                    else if(extendida[0]=='.' && extendida[1]=='.' && extendida[2]!='.' && extendida[3]!='.'){
                                                        if((mbr.mbr_partition_3->part_start - tam_mbr) > espsolicitado){
                                                            //INGRESAR PARTICION AL ARCHIVO FISICO
                                                            mbr.mbr_partition_1->part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                mbr.mbr_partition_1->part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                mbr.mbr_partition_1->part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                mbr.mbr_partition_1->part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                mbr.mbr_partition_1->part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                mbr.mbr_partition_1->part_fit = 'W';
                                                            }
                                                            mbr.mbr_partition_1->part_start = tam_mbr;
                                                            mbr.mbr_partition_1->part_size = espsolicitado;
                                                            memset(mbr.mbr_partition_1->part_name,0,16);
                                                            strcpy(mbr.mbr_partition_1->part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            if(disco->typee=="p" || disco->typee=="P"){
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Primaria: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }else{
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Extendida: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }
                                                        }
                                                        else{
                                                            cout<<"Espacio Solicitado para la particion, Supera Tamaño del Disco"<<endl;
                                                        }
                                                    }
                                                    //1 2 3 .
                                                    else if(extendida[0]!='.' && extendida[1]!='.' && extendida[2]!='.' && extendida[3]=='.'){
                                                        if((tamDisco - tam_mbr - p1 - p2 - p3 - espsolicitado) > 0){
                                                            //INGRESAR PARTICION AL ARCHIVO FISICO
                                                            mbr.mbr_partition_4->part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                mbr.mbr_partition_4->part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                mbr.mbr_partition_4->part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                mbr.mbr_partition_4->part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                mbr.mbr_partition_4->part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                mbr.mbr_partition_4->part_fit = 'W';
                                                            }
                                                            mbr.mbr_partition_4->part_start = tam_mbr + p1 + p2 + p3;
                                                            mbr.mbr_partition_4->part_size = espsolicitado;
                                                            memset(mbr.mbr_partition_4->part_name,0,16);
                                                            strcpy(mbr.mbr_partition_4->part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            if(disco->typee=="p" || disco->typee=="P"){
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Primaria: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }else{
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Extendida: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }
                                                        }else{
                                                            cout<<"Espacio Solicitado para la particion, Supera Tamaño del Disco"<<endl;
                                                        }
                                                    }
                                                    //1 2 . 4
                                                    else if(extendida[0]!='.' && extendida[1]!='.' && extendida[2]=='.' && extendida[3]!='.'){
                                                        if((mbr.mbr_partition_4->part_start - tam_mbr - p1 - p2) > espsolicitado){
                                                            //INGRESAR PARTICION AL ARCHIVO FISICO
                                                            mbr.mbr_partition_3->part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                mbr.mbr_partition_3->part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                mbr.mbr_partition_3->part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                mbr.mbr_partition_3->part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                mbr.mbr_partition_3->part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                mbr.mbr_partition_3->part_fit = 'W';
                                                            }
                                                            mbr.mbr_partition_3->part_start = tam_mbr + p1 + p2;
                                                            mbr.mbr_partition_3->part_size = espsolicitado;
                                                            memset(mbr.mbr_partition_3->part_name,0,16);
                                                            strcpy(mbr.mbr_partition_3->part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            if(disco->typee=="p" || disco->typee=="P"){
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Primaria: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }else{
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Extendida: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }
                                                        }else{
                                                            cout<<"Espacio Solicitado para la particion, Supera Tamaño del Disco"<<endl;
                                                        }
                                                    }
                                                    //1 . 3 4
                                                    else if(extendida[0]!='.' && extendida[1]=='.' && extendida[2]!='.' && extendida[3]!='.'){
                                                        if((mbr.mbr_partition_3->part_start - tam_mbr - p1) > espsolicitado){
                                                            //INGRESAR PARTICION AL ARCHIVO FISICO
                                                            mbr.mbr_partition_2->part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                mbr.mbr_partition_2->part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                mbr.mbr_partition_2->part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                mbr.mbr_partition_2->part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                mbr.mbr_partition_2->part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                mbr.mbr_partition_2->part_fit = 'W';
                                                            }
                                                            mbr.mbr_partition_2->part_start = tam_mbr + p1;
                                                            mbr.mbr_partition_2->part_size = espsolicitado;
                                                            memset(mbr.mbr_partition_2->part_name,0,16);
                                                            strcpy(mbr.mbr_partition_2->part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            if(disco->typee=="p" || disco->typee=="P"){
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Primaria: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }else{
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Extendida: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }
                                                        }else{
                                                            cout<<"Espacio Solicitado para la particion, Supera Tamaño del Disco"<<endl;
                                                        }
                                                    }
                                                    //. 2 3 4
                                                    else if(extendida[0]=='.' && extendida[1]!='.' && extendida[2]!='.' && extendida[3]!='.'){
                                                        if((mbr.mbr_partition_2->part_start - tam_mbr) > espsolicitado){
                                                            //INGRESAR PARTICION AL ARCHIVO FISICO
                                                            mbr.mbr_partition_1->part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                mbr.mbr_partition_1->part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                mbr.mbr_partition_1->part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                mbr.mbr_partition_1->part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                mbr.mbr_partition_1->part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                mbr.mbr_partition_1->part_fit = 'W';
                                                            }
                                                            mbr.mbr_partition_1->part_start = tam_mbr;
                                                            mbr.mbr_partition_1->part_size = espsolicitado;
                                                            memset(mbr.mbr_partition_1->part_name,0,16);
                                                            strcpy(mbr.mbr_partition_1->part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            if(disco->typee=="p" || disco->typee=="P"){
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Primaria: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }else{
                                                                ba = disco->namee.toLocal8Bit();
                                                                com = ba.data();
                                                                cout<<"La Particion Extendida: " << com<< " Se A Creado Con Exito :D"<<endl;
                                                            }
                                                        }else{
                                                            cout<<"Espacio Solicitado para la particion, Supera Tamaño del Disco"<<endl;
                                                        }
                                                    }
                                                }else{
                                                    cout<<"Error, No Se Pueden Crear 2 Particiones Extendidas En El Disco"<<endl;
                                                }
                                            }
                                        }else{
                                            cout<<"Nombre Solicitado Ya Pertenece A Una Particion Creada"<<endl;
                                        }
                                    }else{
                                        //COMPROBAR SI EXISTE PARTICION EXTENDIDA


                                        //COMPROBAR ESPACIO LIBRE CON CAPACIDAD DE ALMACENAR LOGICA


                                        //INSERTAR PARTICION LOGICA


                                        ba = disco->namee.toLocal8Bit();
                                        com = ba.data();
                                        cout<<"La Particion Logica: " << com<< " Se A Creado Con Exito :D"<<endl;
                                    }
                                }else{
                                    QByteArray ba = aux.toLocal8Bit();
                                    const char* com = ba.data();
                                    cout<<"El Disco: " << com<< " No Existe"<<endl;
                                    archivo.close();
                                }
                            }else{
                                cout<<"Extension de Disco incorrecta, no es .dk"<<endl;
                            }
                        }
                    }else{
                        cout<<"tamaño para crear particion incorrecto, Ingrese un numero Positivo"<<endl;
                    }
                }else{
                    //AGREGAR O QUITAR ESPACIO PARTICION
                    if(disco->addd!=0){
                        if(disco->u==""){
                            disco->u="k";
                        }


                    }else{
                        cout<<"Valor a Quitar/Agregar Espacio En Disco No Puede Ser 0, incorrecto"<<endl;
                    }
                }
            }else{
                if(disco->deletee=="fast"){
                    //FORMATEO PARTICION FAST

                }else{
                    //FORMATEO PARTICION FULL

                }
            }
        }else{
            cout<<"Nombre De La Particion No Ingresada, Incorrecto"<<endl;
        }
    }else{
        cout<<"Ruta No Ingresada, Incorrecto"<<endl;
    }

    disco->size = 0;
    disco->u = "";
    disco->path = "";
    disco->typee = "";
    disco->f = "";
    disco->deletee = "";
    disco->namee = "";
    disco->addd = 0;
    cout<<"--------------------------------------------------------"<<endl;
}
