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
    cout<<"El Path es: "<<disco->path.toStdString()<<endl;
    cout<<"El Name es: "<<disco->namee.toStdString()<<endl;

    disco->path.remove(QChar('"'), Qt::CaseInsensitive);
    if(disco->path!=""){
        if(disco->namee!=""){
            if(disco->deletee==""){
                if(disco->primero=="s"){
                    //CREAR PARTICION
                    if(disco->size>0){
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
                                    fseek(Discoo,0,SEEK_SET);
                                    fclose(Discoo);

                                    //COMPROBAR TIPO DE PARTICION A CREAR
                                    char extendida[] = {'.','.','.','.'};
                                    struct particion part1;
                                    struct particion part2;
                                    struct particion part3;
                                    struct particion part4;
                                    part1 = mbr.mbr_partition_1;
                                    part2 = mbr.mbr_partition_2;
                                    part3 = mbr.mbr_partition_3;
                                    part4 = mbr.mbr_partition_4;
                                    if(disco->typee=="p" || disco->typee=="e" || disco->typee=="P" || disco->typee=="E"){
                                        //COMPROBAR PARTICIONES LIBRES Y NO MAS DE UNA EXTENDIDA
                                        if(part1.part_type != '.'){
                                            if(part1.part_type == 'e' || part1.part_type == 'E'){
                                                   extendida[0] = 'e';
                                            }
                                            if(part1.part_type == 'p' || part1.part_type == 'P'){
                                                   extendida[0] = 'p';
                                            }
                                        }
                                        if(part2.part_type != '.'){
                                            if(part2.part_type == 'e' || part2.part_type == 'E'){
                                                   extendida[1] = 'e';
                                            }
                                            if(part2.part_type == 'p' || part2.part_type == 'P'){
                                                   extendida[1] = 'p';
                                            }
                                        }
                                        if(part3.part_type !='.'){
                                            if(part3.part_type == 'e' || part3.part_type == 'E'){
                                                   extendida[2] = 'e';
                                            }
                                            if(part3.part_type == 'p' || part3.part_type == 'P'){
                                                   extendida[2] = 'p';
                                            }
                                        }
                                        if(part4.part_type != '.'){
                                            if(part4.part_type == 'e' || part4.part_type == 'E'){
                                                   extendida[3] = 'e';
                                            }
                                            if(part4.part_type == 'p' || part4.part_type == 'P'){
                                                   extendida[3] = 'p';
                                            }
                                        }

                                        int cantext = 0;
                                        for(int x=0;x<4;x++){
                                            if(extendida[x]=='e'){cantext++;}
                                        }

                                        if(disco->typee == "e" || disco->typee == "E"){cantext++;}

                                        if(disco->namee != part1.part_name && disco->namee != part2.part_name && disco->namee != part3.part_name && disco->namee != part4.part_name){
                                            //1 2 3 4
                                            if(extendida[0]!='.' && extendida[1]!='.' && extendida[2]!='.' && extendida[3]!='.'){
                                                cout<<"No Hay Particiones Libres, 4 PArticiones Creadas"<<endl;
                                            }else{
                                                if (cantext <=1){
                                                    //COMPROBAR ESPACIO LIBRE CON CAPACIDAD DE ALMACENAR PARTICION
                                                    int tamDisco = mbr.mbr_tam;
                                                    int tam_mbr = sizeof(mbr);
                                                    int espsolicitado = 0;
                                                    int p1 = part1.part_size;
                                                    int p2 = part2.part_size;
                                                    int p3 = part3.part_size;
                                                    if(disco->u == "b" || disco->u == "B"){
                                                        espsolicitado = disco->size;
                                                    }else if(disco->u == "k" || disco->u == "K"){
                                                        espsolicitado = disco->size * 1024;
                                                    }else if(disco->u == "m" || disco->u == "M"){
                                                        espsolicitado = disco->size * 1024 * 1024;
                                                    }
                                                    //. . . .
                                                    if(extendida[0]=='.' && extendida[1]=='.' && extendida[2]=='.' && extendida[3]=='.'){
                                                        if((tamDisco - tam_mbr - espsolicitado) > 0){
                                                            //INGRESAR PARTICION AL ARCHIVO FISICO
                                                            part1.part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                part1.part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                part1.part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                part1.part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                part1.part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                part1.part_fit = 'W';
                                                            }
                                                            part1.part_start = tam_mbr;
                                                            part1.part_size = espsolicitado;
                                                            memset(part1.part_name,0,16);
                                                            strcpy(part1.part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            mbr.mbr_partition_1 = part1;
                                                            mbr.mbr_partition_2 = part2;
                                                            mbr.mbr_partition_3 = part3;
                                                            mbr.mbr_partition_4 = part4;
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            //CREAR EBR INICIAL DE EXTENDIDA
                                                            if(disco->typee=="e" || disco->typee=="E"){
                                                                EBR ebr;
                                                                ebr.part_fit ='.';
                                                                ebr.part_next = -1;
                                                                ebr.part_size = 0;
                                                                ebr.part_start = part1.part_start;
                                                                ebr.part_status = '.';
                                                                Discoo=fopen(com,"rb+");
                                                                fseek(Discoo,part1.part_start,SEEK_SET);
                                                                fwrite(&ebr,sizeof (EBR),1,Discoo);
                                                                fseek(Discoo,0,SEEK_SET);
                                                                fclose(Discoo);
                                                            }

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
                                                            part2.part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                part2.part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                part2.part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                part2.part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                part2.part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                part2.part_fit = 'W';
                                                            }
                                                            part2.part_start = tam_mbr + p1;
                                                            part2.part_size = espsolicitado;
                                                            memset(part2.part_name,0,16);

                                                            strcpy(part2.part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            mbr.mbr_partition_1 = part1;
                                                            mbr.mbr_partition_2 = part2;
                                                            mbr.mbr_partition_3 = part3;
                                                            mbr.mbr_partition_4 = part4;
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            //CREAR EBR INICIAL DE EXTENDIDA
                                                            if(disco->typee=="e" || disco->typee=="E"){
                                                                EBR ebr;
                                                                ebr.part_fit ='.';
                                                                ebr.part_next = -1;
                                                                ebr.part_size = 0;
                                                                ebr.part_start = part2.part_start;
                                                                ebr.part_status = '.';
                                                                Discoo=fopen(com,"rb+");
                                                                fseek(Discoo,part2.part_start,SEEK_SET);
                                                                fwrite(&ebr,sizeof (EBR),1,Discoo);
                                                                fseek(Discoo,0,SEEK_SET);
                                                                fclose(Discoo);
                                                            }

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
                                                        if((part2.part_start - tam_mbr) > espsolicitado){
                                                            //INGRESAR PARTICION AL ARCHIVO FISICO
                                                            part1.part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                part1.part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                part1.part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                part1.part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                part1.part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                part1.part_fit = 'W';
                                                            }
                                                            part1.part_start = tam_mbr;
                                                            part1.part_size = espsolicitado;
                                                            memset(part1.part_name,0,16);
                                                            strcpy(part1.part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            mbr.mbr_partition_1 = part1;
                                                            mbr.mbr_partition_2 = part2;
                                                            mbr.mbr_partition_3 = part3;
                                                            mbr.mbr_partition_4 = part4;
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            //CREAR EBR INICIAL DE EXTENDIDA
                                                            if(disco->typee=="e" || disco->typee=="E"){
                                                                EBR ebr;
                                                                ebr.part_fit ='.';
                                                                ebr.part_next = -1;
                                                                ebr.part_size = 0;
                                                                ebr.part_start = part1.part_start;
                                                                ebr.part_status = '.';
                                                                Discoo=fopen(com,"rb+");
                                                                fseek(Discoo,part1.part_start,SEEK_SET);
                                                                fwrite(&ebr,sizeof (EBR),1,Discoo);
                                                                fseek(Discoo,0,SEEK_SET);
                                                                fclose(Discoo);
                                                            }

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
                                                            part3.part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                part3.part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                part3.part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                part3.part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                part3.part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                part3.part_fit = 'W';
                                                            }
                                                            part3.part_start = tam_mbr + p1 + p2;
                                                            part3.part_size = espsolicitado;
                                                            memset(part3.part_name,0,16);
                                                            strcpy(part3.part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            mbr.mbr_partition_1 = part1;
                                                            mbr.mbr_partition_2 = part2;
                                                            mbr.mbr_partition_3 = part3;
                                                            mbr.mbr_partition_4 = part4;
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            //CREAR EBR INICIAL DE EXTENDIDA
                                                            if(disco->typee=="e" || disco->typee=="E"){
                                                                EBR ebr;
                                                                ebr.part_fit ='.';
                                                                ebr.part_next = -1;
                                                                ebr.part_size = 0;
                                                                ebr.part_start = part3.part_start;
                                                                ebr.part_status = '.';
                                                                Discoo=fopen(com,"rb+");
                                                                fseek(Discoo,part3.part_start,SEEK_SET);
                                                                fwrite(&ebr,sizeof (EBR),1,Discoo);
                                                                fseek(Discoo,0,SEEK_SET);
                                                                fclose(Discoo);
                                                            }

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
                                                        if((part3.part_start - tam_mbr) > espsolicitado){
                                                            //INGRESAR PARTICION AL ARCHIVO FISICO
                                                            part1.part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                part1.part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                part1.part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                part1.part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                part1.part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                part1.part_fit = 'W';
                                                            }
                                                            part1.part_start = tam_mbr;
                                                            part1.part_size = espsolicitado;
                                                            memset(part1.part_name,0,16);
                                                            strcpy(part1.part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            mbr.mbr_partition_1 = part1;
                                                            mbr.mbr_partition_2 = part2;
                                                            mbr.mbr_partition_3 = part3;
                                                            mbr.mbr_partition_4 = part4;
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            //CREAR EBR INICIAL DE EXTENDIDA
                                                            if(disco->typee=="e" || disco->typee=="E"){
                                                                EBR ebr;
                                                                ebr.part_fit ='.';
                                                                ebr.part_next = -1;
                                                                ebr.part_size = 0;
                                                                ebr.part_start = part1.part_start;
                                                                ebr.part_status = '.';
                                                                Discoo=fopen(com,"rb+");
                                                                fseek(Discoo,part1.part_start,SEEK_SET);
                                                                fwrite(&ebr,sizeof (EBR),1,Discoo);
                                                                fseek(Discoo,0,SEEK_SET);
                                                                fclose(Discoo);
                                                            }

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
                                                            part4.part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                part4.part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                part4.part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                part4.part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                part4.part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                part4.part_fit = 'W';
                                                            }
                                                            part4.part_start = tam_mbr + p1+ p2+ p3;
                                                            part4.part_size = espsolicitado;
                                                            memset(part4.part_name,0,16);
                                                            strcpy(part4.part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            mbr.mbr_partition_1 = part1;
                                                            mbr.mbr_partition_2 = part2;
                                                            mbr.mbr_partition_3 = part3;
                                                            mbr.mbr_partition_4 = part4;
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            //CREAR EBR INICIAL DE EXTENDIDA
                                                            if(disco->typee=="e" || disco->typee=="E"){
                                                                EBR ebr;
                                                                ebr.part_fit ='.';
                                                                ebr.part_next = -1;
                                                                ebr.part_size = 0;
                                                                ebr.part_start = part4.part_start;
                                                                ebr.part_status = '.';
                                                                Discoo=fopen(com,"rb+");
                                                                fseek(Discoo,part4.part_start,SEEK_SET);
                                                                fwrite(&ebr,sizeof (EBR),1,Discoo);
                                                                fseek(Discoo,0,SEEK_SET);
                                                                fclose(Discoo);
                                                            }

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
                                                        if((part4.part_start - tam_mbr) > espsolicitado){
                                                            //INGRESAR PARTICION AL ARCHIVO FISICO
                                                            part1.part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                part1.part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                part1.part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                part1.part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                part1.part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                part1.part_fit = 'W';
                                                            }
                                                            part1.part_start = tam_mbr;
                                                            part1.part_size = espsolicitado;
                                                            memset(part1.part_name,0,16);
                                                            strcpy(part1.part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            mbr.mbr_partition_1 = part1;
                                                            mbr.mbr_partition_2 = part2;
                                                            mbr.mbr_partition_3 = part3;
                                                            mbr.mbr_partition_4 = part4;
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            //CREAR EBR INICIAL DE EXTENDIDA
                                                            if(disco->typee=="e" || disco->typee=="E"){
                                                                EBR ebr;
                                                                ebr.part_fit ='.';
                                                                ebr.part_next = -1;
                                                                ebr.part_size = 0;
                                                                ebr.part_start = part1.part_start;
                                                                ebr.part_status = '.';
                                                                Discoo=fopen(com,"rb+");
                                                                fseek(Discoo,part1.part_start,SEEK_SET);
                                                                fwrite(&ebr,sizeof (EBR),1,Discoo);
                                                                fseek(Discoo,0,SEEK_SET);
                                                                fclose(Discoo);
                                                            }

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
                                                            part3.part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                part3.part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                part3.part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                part3.part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                part3.part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                part3.part_fit = 'W';
                                                            }
                                                            part3.part_start = tam_mbr + p1 + p2;
                                                            part3.part_size = espsolicitado;
                                                            memset(part3.part_name,0,16);
                                                            strcpy(part3.part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            mbr.mbr_partition_1 = part1;
                                                            mbr.mbr_partition_2 = part2;
                                                            mbr.mbr_partition_3 = part3;
                                                            mbr.mbr_partition_4 = part4;
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            //CREAR EBR INICIAL DE EXTENDIDA
                                                            if(disco->typee=="e" || disco->typee=="E"){
                                                                EBR ebr;
                                                                ebr.part_fit ='.';
                                                                ebr.part_next = -1;
                                                                ebr.part_size = 0;
                                                                ebr.part_start = part3.part_start;
                                                                ebr.part_status = '.';
                                                                Discoo=fopen(com,"rb+");
                                                                fseek(Discoo,part3.part_start,SEEK_SET);
                                                                fwrite(&ebr,sizeof (EBR),1,Discoo);
                                                                fseek(Discoo,0,SEEK_SET);
                                                                fclose(Discoo);
                                                            }

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
                                                        if((part3.part_start - tam_mbr -p1) > espsolicitado){
                                                            //INGRESAR PARTICION AL ARCHIVO FISICO
                                                            part2.part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                part2.part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                part2.part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                part2.part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                part2.part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                part2.part_fit = 'W';
                                                            }
                                                            part2.part_start = tam_mbr + p1;
                                                            part2.part_size = espsolicitado;
                                                            memset(part2.part_name,0,16);
                                                            strcpy(part2.part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            mbr.mbr_partition_1 = part1;
                                                            mbr.mbr_partition_2 = part2;
                                                            mbr.mbr_partition_3 = part3;
                                                            mbr.mbr_partition_4 = part4;
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            //CREAR EBR INICIAL DE EXTENDIDA
                                                            if(disco->typee=="e" || disco->typee=="E"){
                                                                EBR ebr;
                                                                ebr.part_fit ='.';
                                                                ebr.part_next = -1;
                                                                ebr.part_size = 0;
                                                                ebr.part_start = part2.part_start;
                                                                ebr.part_status = '.';
                                                                Discoo=fopen(com,"rb+");
                                                                fseek(Discoo,part2.part_start,SEEK_SET);
                                                                fwrite(&ebr,sizeof (EBR),1,Discoo);
                                                                fseek(Discoo,0,SEEK_SET);
                                                                fclose(Discoo);
                                                            }

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
                                                            part4.part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                part4.part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                part4.part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                part4.part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                part4.part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                part4.part_fit = 'W';
                                                            }
                                                            part4.part_start = tam_mbr + p1 + p2 + p3;
                                                            part4.part_size = espsolicitado;
                                                            memset(part4.part_name,0,16);
                                                            strcpy(part4.part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            mbr.mbr_partition_1 = part1;
                                                            mbr.mbr_partition_2 = part2;
                                                            mbr.mbr_partition_3 = part3;
                                                            mbr.mbr_partition_4 = part4;
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            //CREAR EBR INICIAL DE EXTENDIDA
                                                            if(disco->typee=="e" || disco->typee=="E"){
                                                                EBR ebr;
                                                                ebr.part_fit ='.';
                                                                ebr.part_next = -1;
                                                                ebr.part_size = 0;
                                                                ebr.part_start = part4.part_start;
                                                                ebr.part_status = '.';
                                                                Discoo=fopen(com,"rb+");
                                                                fseek(Discoo,part4.part_start,SEEK_SET);
                                                                fwrite(&ebr,sizeof (EBR),1,Discoo);
                                                                fseek(Discoo,0,SEEK_SET);
                                                                fclose(Discoo);
                                                            }

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
                                                        if((part4.part_start - tam_mbr -p1) > espsolicitado){
                                                            //INGRESAR PARTICION AL ARCHIVO FISICO
                                                            part2.part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                part2.part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                part2.part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                part2.part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                part2.part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                part2.part_fit = 'W';
                                                            }
                                                            part2.part_start = tam_mbr + p1;
                                                            part2.part_size = espsolicitado;
                                                            memset(part2.part_name,0,16);
                                                            strcpy(part2.part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            mbr.mbr_partition_1 = part1;
                                                            mbr.mbr_partition_2 = part2;
                                                            mbr.mbr_partition_3 = part3;
                                                            mbr.mbr_partition_4 = part4;
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            //CREAR EBR INICIAL DE EXTENDIDA
                                                            if(disco->typee=="e" || disco->typee=="E"){
                                                                EBR ebr;
                                                                ebr.part_fit ='.';
                                                                ebr.part_next = -1;
                                                                ebr.part_size = 0;
                                                                ebr.part_start = part2.part_start;
                                                                ebr.part_status = '.';
                                                                Discoo=fopen(com,"rb+");
                                                                fseek(Discoo,part2.part_start,SEEK_SET);
                                                                fwrite(&ebr,sizeof (EBR),1,Discoo);
                                                                fseek(Discoo,0,SEEK_SET);
                                                                fclose(Discoo);
                                                            }

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
                                                        if((part2.part_start - tam_mbr) > espsolicitado){
                                                            //INGRESAR PARTICION AL ARCHIVO FISICO
                                                            part1.part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                part1.part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                part1.part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                part1.part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                part1.part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                part1.part_fit = 'W';
                                                            }
                                                            part1.part_start = tam_mbr;
                                                            part1.part_size = espsolicitado;
                                                            memset(part1.part_name,0,16);
                                                            strcpy(part1.part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            mbr.mbr_partition_1 = part1;
                                                            mbr.mbr_partition_2 = part2;
                                                            mbr.mbr_partition_3 = part3;
                                                            mbr.mbr_partition_4 = part4;
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            //CREAR EBR INICIAL DE EXTENDIDA
                                                            if(disco->typee=="e" || disco->typee=="E"){
                                                                EBR ebr;
                                                                ebr.part_fit ='.';
                                                                ebr.part_next = -1;
                                                                ebr.part_size = 0;
                                                                ebr.part_start = part1.part_start;
                                                                ebr.part_status = '.';
                                                                Discoo=fopen(com,"rb+");
                                                                fseek(Discoo,part1.part_start,SEEK_SET);
                                                                fwrite(&ebr,sizeof (EBR),1,Discoo);
                                                                fseek(Discoo,0,SEEK_SET);
                                                                fclose(Discoo);
                                                            }

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
                                                            part4.part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                part4.part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                part4.part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                part4.part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                part4.part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                part4.part_fit = 'W';
                                                            }
                                                            part4.part_start = tam_mbr + p1 + p2 + p3;
                                                            part4.part_size = espsolicitado;
                                                            memset(part4.part_name,0,16);
                                                            strcpy(part4.part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            mbr.mbr_partition_1 = part1;
                                                            mbr.mbr_partition_2 = part2;
                                                            mbr.mbr_partition_3 = part3;
                                                            mbr.mbr_partition_4 = part4;
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            //CREAR EBR INICIAL DE EXTENDIDA
                                                            if(disco->typee=="e" || disco->typee=="E"){
                                                                EBR ebr;
                                                                ebr.part_fit ='.';
                                                                ebr.part_next = -1;
                                                                ebr.part_size = 0;
                                                                ebr.part_start = part4.part_start;
                                                                ebr.part_status = '.';
                                                                Discoo=fopen(com,"rb+");
                                                                fseek(Discoo,part4.part_start,SEEK_SET);
                                                                fwrite(&ebr,sizeof (EBR),1,Discoo);
                                                                fseek(Discoo,0,SEEK_SET);
                                                                fclose(Discoo);
                                                            }

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
                                                        if((part2.part_start - tam_mbr) > espsolicitado){
                                                            //INGRESAR PARTICION AL ARCHIVO FISICO
                                                            part1.part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                part1.part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                part1.part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                part1.part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                part1.part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                part1.part_fit = 'W';
                                                            }
                                                            part1.part_start = tam_mbr;
                                                            part1.part_size = espsolicitado;
                                                            memset(part1.part_name,0,16);
                                                            strcpy(part1.part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            mbr.mbr_partition_1 = part1;
                                                            mbr.mbr_partition_2 = part2;
                                                            mbr.mbr_partition_3 = part3;
                                                            mbr.mbr_partition_4 = part4;
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            //CREAR EBR INICIAL DE EXTENDIDA
                                                            if(disco->typee=="e" || disco->typee=="E"){
                                                                EBR ebr;
                                                                ebr.part_fit ='.';
                                                                ebr.part_next = -1;
                                                                ebr.part_size = 0;
                                                                ebr.part_start = part1.part_start;
                                                                ebr.part_status = '.';
                                                                Discoo=fopen(com,"rb+");
                                                                fseek(Discoo,part1.part_start,SEEK_SET);
                                                                fwrite(&ebr,sizeof (EBR),1,Discoo);
                                                                fseek(Discoo,0,SEEK_SET);
                                                                fclose(Discoo);
                                                            }

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
                                                        else if((part4.part_start - tam_mbr - p1 - p2) > espsolicitado){
                                                            //INGRESAR PARTICION AL ARCHIVO FISICO
                                                            part3.part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                part3.part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                part3.part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                part3.part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                part3.part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                part3.part_fit = 'W';
                                                            }
                                                            part3.part_start = tam_mbr + p1 + p2;
                                                            part3.part_size = espsolicitado;
                                                            memset(part3.part_name,0,16);
                                                            strcpy(part3.part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            mbr.mbr_partition_1 = part1;
                                                            mbr.mbr_partition_2 = part2;
                                                            mbr.mbr_partition_3 = part3;
                                                            mbr.mbr_partition_4 = part4;
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            //CREAR EBR INICIAL DE EXTENDIDA
                                                            if(disco->typee=="e" || disco->typee=="E"){
                                                                EBR ebr;
                                                                ebr.part_fit ='.';
                                                                ebr.part_next = -1;
                                                                ebr.part_size = 0;
                                                                ebr.part_start = part3.part_start;
                                                                ebr.part_status = '.';
                                                                Discoo=fopen(com,"rb+");
                                                                fseek(Discoo,part3.part_start,SEEK_SET);
                                                                fwrite(&ebr,sizeof (EBR),1,Discoo);
                                                                fseek(Discoo,0,SEEK_SET);
                                                                fclose(Discoo);
                                                            }

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
                                                        if((part3.part_start - tam_mbr) > espsolicitado){
                                                            //INGRESAR PARTICION AL ARCHIVO FISICO
                                                            part1.part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                part1.part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                part1.part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                part1.part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                part1.part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                part1.part_fit = 'W';
                                                            }
                                                            part1.part_start = tam_mbr;
                                                            part1.part_size = espsolicitado;
                                                            memset(part1.part_name,0,16);
                                                            strcpy(part1.part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            mbr.mbr_partition_1 = part1;
                                                            mbr.mbr_partition_2 = part2;
                                                            mbr.mbr_partition_3 = part3;
                                                            mbr.mbr_partition_4 = part4;
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            //CREAR EBR INICIAL DE EXTENDIDA
                                                            if(disco->typee=="e" || disco->typee=="E"){
                                                                EBR ebr;
                                                                ebr.part_fit ='.';
                                                                ebr.part_next = -1;
                                                                ebr.part_size = 0;
                                                                ebr.part_start = part1.part_start;
                                                                ebr.part_status = '.';
                                                                Discoo=fopen(com,"rb+");
                                                                fseek(Discoo,part1.part_start,SEEK_SET);
                                                                fwrite(&ebr,sizeof (EBR),1,Discoo);
                                                                fseek(Discoo,0,SEEK_SET);
                                                                fclose(Discoo);
                                                            }

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
                                                            part4.part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                part4.part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                part4.part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                part4.part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                part4.part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                part4.part_fit = 'W';
                                                            }
                                                            part4.part_start = tam_mbr + p1 + p2 + p3;
                                                            part4.part_size = espsolicitado;
                                                            memset(part4.part_name,0,16);
                                                            strcpy(part4.part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            mbr.mbr_partition_1 = part1;
                                                            mbr.mbr_partition_2 = part2;
                                                            mbr.mbr_partition_3 = part3;
                                                            mbr.mbr_partition_4 = part4;
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            //CREAR EBR INICIAL DE EXTENDIDA
                                                            if(disco->typee=="e" || disco->typee=="E"){
                                                                EBR ebr;
                                                                ebr.part_fit ='.';
                                                                ebr.part_next = -1;
                                                                ebr.part_size = 0;
                                                                ebr.part_start = part4.part_start;
                                                                ebr.part_status = '.';
                                                                Discoo=fopen(com,"rb+");
                                                                fseek(Discoo,part4.part_start,SEEK_SET);
                                                                fwrite(&ebr,sizeof (EBR),1,Discoo);
                                                                fseek(Discoo,0,SEEK_SET);
                                                                fclose(Discoo);
                                                            }

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
                                                        if((part4.part_start - tam_mbr - p1 - p2) > espsolicitado){
                                                            //INGRESAR PARTICION AL ARCHIVO FISICO
                                                            part3.part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                part3.part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                part3.part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                part3.part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                part3.part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                part3.part_fit = 'W';
                                                            }
                                                            part3.part_start = tam_mbr + p1 + p2;
                                                            part3.part_size = espsolicitado;
                                                            memset(part3.part_name,0,16);
                                                            strcpy(part3.part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            mbr.mbr_partition_1 = part1;
                                                            mbr.mbr_partition_2 = part2;
                                                            mbr.mbr_partition_3 = part3;
                                                            mbr.mbr_partition_4 = part4;
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            //CREAR EBR INICIAL DE EXTENDIDA
                                                            if(disco->typee=="e" || disco->typee=="E"){
                                                                EBR ebr;
                                                                ebr.part_fit ='.';
                                                                ebr.part_next = -1;
                                                                ebr.part_size = 0;
                                                                ebr.part_start = part3.part_start;
                                                                ebr.part_status = '.';
                                                                Discoo=fopen(com,"rb+");
                                                                fseek(Discoo,part3.part_start,SEEK_SET);
                                                                fwrite(&ebr,sizeof (EBR),1,Discoo);
                                                                fseek(Discoo,0,SEEK_SET);
                                                                fclose(Discoo);
                                                            }

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
                                                        if((part3.part_start - tam_mbr - p1) > espsolicitado){
                                                            //INGRESAR PARTICION AL ARCHIVO FISICO
                                                            part2.part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                part2.part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                part2.part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                part2.part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                part2.part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                part2.part_fit = 'W';
                                                            }
                                                            part2.part_start = tam_mbr + p1;
                                                            part2.part_size = espsolicitado;
                                                            memset(part2.part_name,0,16);
                                                            strcpy(part2.part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            mbr.mbr_partition_1 = part1;
                                                            mbr.mbr_partition_2 = part2;
                                                            mbr.mbr_partition_3 = part3;
                                                            mbr.mbr_partition_4 = part4;
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            //CREAR EBR INICIAL DE EXTENDIDA
                                                            if(disco->typee=="e" || disco->typee=="E"){
                                                                EBR ebr;
                                                                ebr.part_fit ='.';
                                                                ebr.part_next = -1;
                                                                ebr.part_size = 0;
                                                                ebr.part_start = part2.part_start;
                                                                ebr.part_status = '.';
                                                                Discoo=fopen(com,"rb+");
                                                                fseek(Discoo,part2.part_start,SEEK_SET);
                                                                fwrite(&ebr,sizeof (EBR),1,Discoo);
                                                                fseek(Discoo,0,SEEK_SET);
                                                                fclose(Discoo);
                                                            }

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
                                                        if((part2.part_start - tam_mbr) > espsolicitado){
                                                            //INGRESAR PARTICION AL ARCHIVO FISICO
                                                            part1.part_status = 'N';
                                                            if(disco->typee.toStdString().c_str()[0] == 'e' || disco->typee.toStdString().c_str()[0] == 'E'){
                                                                part1.part_type = 'E';
                                                            }else if(disco->typee.toStdString().c_str()[0] == 'p' || disco->typee.toStdString().c_str()[0] == 'P'){
                                                                part1.part_type = 'P';
                                                            }
                                                            if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                                part1.part_fit = 'F';
                                                            }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                                part1.part_fit = 'B';
                                                            }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                                part1.part_fit = 'W';
                                                            }
                                                            part1.part_start = tam_mbr;
                                                            part1.part_size = espsolicitado;
                                                            memset(part1.part_name,0,16);
                                                            strcpy(part1.part_name,disco->namee.toStdString().c_str());

                                                            //EDITAR MBR CON CAMBIOS
                                                            mbr.mbr_partition_1 = part1;
                                                            mbr.mbr_partition_2 = part2;
                                                            mbr.mbr_partition_3 = part3;
                                                            mbr.mbr_partition_4 = part4;
                                                            Discoo=fopen(com,"rb+");
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fwrite(&mbr,sizeof (MBR),1,Discoo);
                                                            fseek(Discoo,0,SEEK_SET);
                                                            fclose(Discoo);

                                                            //CREAR EBR INICIAL DE EXTENDIDA
                                                            if(disco->typee=="e" || disco->typee=="E"){
                                                                EBR ebr;
                                                                ebr.part_fit ='.';
                                                                ebr.part_next = -1;
                                                                ebr.part_size = 0;
                                                                ebr.part_start = part1.part_start;
                                                                ebr.part_status = '.';
                                                                Discoo=fopen(com,"rb+");
                                                                fseek(Discoo,part1.part_start,SEEK_SET);
                                                                fwrite(&ebr,sizeof (EBR),1,Discoo);
                                                                fseek(Discoo,0,SEEK_SET);
                                                                fclose(Discoo);
                                                            }
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
                                        bool nombreR = false;
                                        bool existe=false;
                                        char ext = '.';
                                        if(part1.part_type == 'e' || part1.part_type == 'E'){existe = true; ext = '1';}
                                        else if(part2.part_type == 'e' || part2.part_type == 'E'){existe = true; ext = '2';}
                                        else if(part3.part_type == 'e' || part3.part_type == 'E'){existe = true; ext = '3';}
                                        else if(part4.part_type == 'e' || part4.part_type == 'E'){existe = true; ext = '4';}
                                        if(part1.part_name == disco->namee){nombreR = true;}
                                        else if(part2.part_name == disco->namee){nombreR = true;}
                                        else if(part3.part_name == disco->namee){nombreR = true;}
                                        else if(part4.part_name == disco->namee){nombreR = true;}

                                        if(existe){
                                            //OBTENER EBR INCIAL Y ESPACIO SOLICITADO
                                            int ebrnext = 0;
                                            int tam_Particion = 0;
                                            int partOcupado = 0;
                                            int nuevoinicio = 0;
                                            int espacioSolicitado = 0;
                                            if(disco->u == "b" || disco->u == "B"){
                                                espacioSolicitado = disco->size;
                                            }else if(disco->u == "k" || disco->u == "K"){
                                                espacioSolicitado = disco->size * 1024;
                                            }else if(disco->u == "m" || disco->u == "M"){
                                                espacioSolicitado = disco->size * 1024 * 1024;
                                            }
                                            EBR ebr;
                                            if(ext == '1'){
                                                nuevoinicio = part1.part_start;
                                                Discoo=fopen(com,"rb+");
                                                fseek(Discoo,part1.part_start,SEEK_SET);
                                                fread(&ebr,sizeof(EBR),1,Discoo);
                                                fseek(Discoo,0,SEEK_SET);
                                                fclose(Discoo);
                                                ebrnext = ebr.part_next;
                                                tam_Particion = part1.part_size;
                                            }else if(ext == '2'){
                                                nuevoinicio = part2.part_start;
                                                Discoo=fopen(com,"rb+");
                                                fseek(Discoo,part2.part_start,SEEK_SET);
                                                fread(&ebr,sizeof(EBR),1,Discoo);
                                                fseek(Discoo,0,SEEK_SET);
                                                fclose(Discoo);
                                                ebrnext = ebr.part_next;
                                                tam_Particion = part2.part_size;
                                            }else if(ext == '3'){
                                                nuevoinicio = part3.part_start;
                                                Discoo=fopen(com,"rb+");
                                                fseek(Discoo,part3.part_start,SEEK_SET);
                                                fread(&ebr,sizeof(EBR),1,Discoo);
                                                fseek(Discoo,0,SEEK_SET);
                                                fclose(Discoo);
                                                ebrnext = ebr.part_next;
                                                tam_Particion = part3.part_size;
                                            }else if(ext == '4'){
                                                nuevoinicio = part4.part_start;
                                                Discoo=fopen(com,"rb+");
                                                fseek(Discoo,part4.part_start,SEEK_SET);
                                                fread(&ebr,sizeof(EBR),1,Discoo);
                                                fseek(Discoo,0,SEEK_SET);
                                                fclose(Discoo);
                                                ebrnext = ebr.part_next;
                                                tam_Particion = part4.part_size;
                                            }


                                            //OBTENER ESPACIO OCUPADO Y EBR ACTUAL

                                            int tam_ebr = sizeof(ebr);
                                            while(ebrnext != -1){
                                                Discoo=fopen(com,"rb+");
                                                fseek(Discoo,nuevoinicio,SEEK_SET);
                                                fread(&ebr,sizeof(EBR),1,Discoo);
                                                fseek(Discoo,0,SEEK_SET);
                                                fclose(Discoo);
                                                ebrnext = ebr.part_next;
                                                QString nombreChar(ebr.part_name);
                                                if(ebrnext != -1){
                                                    if(disco->namee == nombreChar){
                                                        nombreR = true;
                                                        break;
                                                    }
                                                    nuevoinicio = ebr.part_next;
                                                    partOcupado = partOcupado + tam_ebr + ebr.part_size;
                                                }
                                                if(partOcupado >= tam_Particion){break;}
                                            }

                                            if(!nombreR){
                                                //COMPROBAR ESPARCIO E INSERTAR LOGICA
                                                if((partOcupado + espacioSolicitado + tam_ebr) <= tam_Particion){
                                                    //SOBRE ESCRIBIR EBR ACTUAL
                                                    QByteArray ba2 = disco->namee.toLocal8Bit();
                                                    const char *com2 = ba2.data();
                                                    memset(ebr.part_name,0,16);
                                                    strcpy(ebr.part_name,com2);
                                                    if(disco->f == "FF" || disco->f == "ff" || disco->f == "fF" || disco->f == "Ff"){
                                                        ebr.part_fit = 'F';
                                                    }else if(disco->f == "BF" || disco->f == "bf" || disco->f == "bF" || disco->f == "Bf"){
                                                        ebr.part_fit = 'B';
                                                    }else if(disco->f == "WF" || disco->f == "wf" || disco->f == "wF" || disco->f == "Wf"){
                                                        ebr.part_fit = 'W';
                                                    }
                                                    ebr.part_next = ebr.part_start + sizeof(ebr) + espacioSolicitado;
                                                    ebr.part_size = espacioSolicitado;
                                                    ebr.part_status = 'N';
                                                    int inicio = ebr.part_start;
                                                    Discoo=fopen(com,"rb+");
                                                    fseek(Discoo,inicio,SEEK_SET);
                                                    fwrite(&ebr,sizeof (EBR),1,Discoo);
                                                    fseek(Discoo,0,SEEK_SET);
                                                    fclose(Discoo);

                                                    //INGRESAR NUEVA EBR SI CABE
                                                    EBR nueva;
                                                    nueva.part_fit = '.';
                                                    nueva.part_next = -1;
                                                    nueva.part_size = 0;
                                                    nueva.part_status = '.';
                                                    nueva.part_start = ebr.part_next;
                                                    cout<<"La Particion Logica: " << com2<< " Se A Creado Con Exito :D"<<endl;

                                                    inicio = nueva.part_start;
                                                    if((partOcupado + tam_ebr + ebr.part_size + tam_ebr)<tam_Particion){
                                                        Discoo=fopen(com,"rb+");
                                                        fseek(Discoo,inicio,SEEK_SET);
                                                        fwrite(&nueva,sizeof (EBR),1,Discoo);
                                                        fseek(Discoo,0,SEEK_SET);
                                                        fclose(Discoo);

                                                    }else{
                                                        cout<<"Esta es la ultima particion logica posible a ingresar"<<endl;
                                                    }
                                                }else{
                                                    ba = disco->namee.toLocal8Bit();
                                                    com = ba.data();
                                                    cout<<"Tamaño De Logica, Supera El Tamaño De Extendida: "<<com<<endl;
                                                }
                                            }else{
                                                cout<<"Nombre De Particion Solicitado Ya Existe"<<endl;
                                            }
                                        }else{
                                            cout<<"No existe Una Particion Extendida En Disco"<<endl;
                                        }
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
