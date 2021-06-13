#include "clmkfs.h"
#include <QString>
#include <iostream>
#include <QDir>
#include <QStringList>
#include <mbrstruct.h>
#include <ebrstruct.h>
//Necesario Para Usar Montada --------------
#include <clmontada.h>
#include <cabeceramontadas.h>
//-------------------------------------------
using namespace std;

clmkfs::clmkfs()
{

}

void clmkfs::mostrarDatos(clmkfs *disco){
    cout<<"-----------------------ComandoMKFS---------------------"<<endl;
    cout<<"El Id es: "<<disco->id.toStdString()<<endl;
    cout<<"El Type es: "<<disco->type.toStdString()<<endl;
    cout<<"El FS es: "<<disco->fs.toStdString()<<endl;
    if(disco->id!=""){
        if(lista.comprobarId(lista.lista,disco->id)){
            ListaM aux = lista.obtenerNodo(lista.lista,disco->id);
            QString nombreP = aux->nombreP;
            QStringList direcciones = aux->ruta.split("/");
            QString ruta = "/home/oscar/archivos";
            bool NoCarpeta = false;

            MBR mbr;
            struct particion part1;
            struct particion part2;
            struct particion part3;
            struct particion part4;
            QString nombre1(part1.part_name);
            QString nombre2(part2.part_name);
            QString nombre3(part3.part_name);
            QString nombre4(part4.part_name);
            QString extP = "";

            if(disco->type!=""){
                disco->type="full";
            }
            if(disco->fs!=""){
                disco->fs="ext2";
            }

            for(int x=4;x<(direcciones.length()-1);x++){
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
            if(!NoCarpeta){
                QString aux =direcciones[direcciones.length()-1];
                QStringList discofisico = aux.split(".");
                if(discofisico[1] == "dk"){
                    ruta = ruta + "/" + aux;
                    QFile archivo(ruta);
                    if(archivo.exists()){
                        archivo.close();
                        //OBTENER MBR DE DISCO
                        FILE *Discoo;
                        Discoo=fopen(ruta.toStdString().c_str(),"rb+");
                        fseek(Discoo,0,SEEK_SET);
                        fread(&mbr,sizeof(MBR),1,Discoo);
                        fseek(Discoo,0,SEEK_SET);
                        fclose(Discoo);

                        //OBTENER PARTICIONES DEL MBR
                        part1 = mbr.mbr_partition_1;
                        part2 = mbr.mbr_partition_2;
                        part3 = mbr.mbr_partition_3;
                        part4 = mbr.mbr_partition_4;
                    }else{
                        cout<<"Extension de Disco incorrecta, no es .dk"<<endl;
                    }
                }else{
                    cout<<"Extension de Disco incorrecta, no es .dk"<<endl;
                }
            }

            if(part1.part_type == 'e' || part1.part_type == 'E'){
                extP = "1";
            }else if(part2.part_type == 'e' || part2.part_type == 'E'){
                extP = "2";
            }else if(part3.part_type == 'e' || part3.part_type == 'E'){
                extP = "3";
            }else if(part4.part_type == 'e' || part4.part_type == 'E'){
                extP = "4";
            }

            //ENCONTRAR PARTICION A FORMATEAR
            if(nombre1 == nombreP){
                //REALIZAR FORMATEO
                if(disco->type.toLower() == "fast"){

                }else if(disco->type.toLower() == "full"){

                }
                //ASIGNAR ESTRUCTURA EXT2 O EXT3
                if(disco->fs.toLower() == "2fs"){

                }else if(disco->fs.toLower() == "3fs"){

                }
            }else if(nombre2 == nombreP){
                //REALIZAR FORMATEO
                if(disco->type.toLower() == "fast"){

                }else if(disco->type.toLower() == "full"){

                }
                //ASIGNAR ESTRUCTURA EXT2 O EXT3
                if(disco->fs.toLower() == "2fs"){

                }else if(disco->fs.toLower() == "3fs"){

                }
            }else if(nombre3 == nombreP){
                //REALIZAR FORMATEO
                if(disco->type.toLower() == "fast"){

                }else if(disco->type.toLower() == "full"){

                }
                //ASIGNAR ESTRUCTURA EXT2 O EXT3
                if(disco->fs.toLower() == "2fs"){

                }else if(disco->fs.toLower() == "3fs"){

                }
            }else if(nombre4 == nombreP){
                //REALIZAR FORMATEO
                if(disco->type.toLower() == "fast"){

                }else if(disco->type.toLower() == "full"){

                }
                //ASIGNAR ESTRUCTURA EXT2 O EXT3
                if(disco->fs.toLower() == "2fs"){

                }else if(disco->fs.toLower() == "3fs"){

                }
            }else{
                EBR ebr;
                if(extP == "1"){
                    FILE* Debr=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Debr,part1.part_start,SEEK_SET);
                    fread(&ebr,sizeof(EBR),1,Debr);
                    fseek(Debr,0,SEEK_SET);
                    fclose(Debr);

                    int partOcupado = 0;
                    int nuevoinicio = part1.part_start;
                    int tam_Particion = part1.part_size;
                    int tam_ebr = sizeof (ebr);
                    bool encontrado = false;
                    while(ebr.part_next != -1){
                        Debr=fopen(ruta.toStdString().c_str(),"rb+");
                        fseek(Debr,nuevoinicio,SEEK_SET);
                        fread(&ebr,sizeof(EBR),1,Debr);
                        fseek(Debr,0,SEEK_SET);
                        fclose(Debr);

                        QString NombreEbr(ebr.part_name);
                        if(NombreEbr == nombre1){
                            encontrado = true;
                            break;
                        }

                        if(ebr.part_next != -1){
                            nuevoinicio = ebr.part_next;
                            partOcupado = partOcupado + tam_ebr + ebr.part_size;
                        }
                        if(partOcupado >= tam_Particion){break;}
                    }

                    if(encontrado){
                        //IMPORTANTE NO VOLARSE EL EBR, SUMAR EL TAMAÑO DE EBR AL DELETE
                        //REALIZAR FORMATEO
                        if(disco->type.toLower() == "fast"){

                        }else if(disco->type.toLower() == "full"){

                        }
                        //ASIGNAR ESTRUCTURA EXT2 O EXT3
                        if(disco->fs.toLower() == "2fs"){

                        }else if(disco->fs.toLower() == "3fs"){

                        }
                    }
                }else if(extP == "2"){
                    FILE* Debr=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Debr,part2.part_start,SEEK_SET);
                    fread(&ebr,sizeof(EBR),1,Debr);
                    fseek(Debr,0,SEEK_SET);
                    fclose(Debr);

                    int partOcupado = 0;
                    int nuevoinicio = part2.part_start;
                    int tam_Particion = part2.part_size;
                    int tam_ebr = sizeof (ebr);
                    bool encontrado = false;
                    while(ebr.part_next != -1){
                        Debr=fopen(ruta.toStdString().c_str(),"rb+");
                        fseek(Debr,nuevoinicio,SEEK_SET);
                        fread(&ebr,sizeof(EBR),1,Debr);
                        fseek(Debr,0,SEEK_SET);
                        fclose(Debr);

                        QString NombreEbr(ebr.part_name);
                        if(NombreEbr == nombre1){
                            encontrado = true;
                            break;
                        }

                        if(ebr.part_next != -1){
                            nuevoinicio = ebr.part_next;
                            partOcupado = partOcupado + tam_ebr + ebr.part_size;
                        }
                        if(partOcupado >= tam_Particion){break;}
                    }

                    if(encontrado){
                        //IMPORTANTE NO VOLARSE EL EBR, SUMAR EL TAMAÑO DE EBR AL DELETE
                        //REALIZAR FORMATEO
                        if(disco->type.toLower() == "fast"){

                        }else if(disco->type.toLower() == "full"){

                        }
                        //ASIGNAR ESTRUCTURA EXT2 O EXT3
                        if(disco->fs.toLower() == "2fs"){

                        }else if(disco->fs.toLower() == "3fs"){

                        }
                    }
                }else if(extP == "3"){
                    FILE* Debr=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Debr,part3.part_start,SEEK_SET);
                    fread(&ebr,sizeof(EBR),1,Debr);
                    fseek(Debr,0,SEEK_SET);
                    fclose(Debr);

                    int partOcupado = 0;
                    int nuevoinicio = part3.part_start;
                    int tam_Particion = part3.part_size;
                    int tam_ebr = sizeof (ebr);
                    bool encontrado = false;
                    while(ebr.part_next != -1){
                        Debr=fopen(ruta.toStdString().c_str(),"rb+");
                        fseek(Debr,nuevoinicio,SEEK_SET);
                        fread(&ebr,sizeof(EBR),1,Debr);
                        fseek(Debr,0,SEEK_SET);
                        fclose(Debr);

                        QString NombreEbr(ebr.part_name);
                        if(NombreEbr == nombre1){
                            encontrado = true;
                            break;
                        }

                        if(ebr.part_next != -1){
                            nuevoinicio = ebr.part_next;
                            partOcupado = partOcupado + tam_ebr + ebr.part_size;
                        }
                        if(partOcupado >= tam_Particion){break;}
                    }

                    if(encontrado){
                        //IMPORTANTE NO VOLARSE EL EBR, SUMAR EL TAMAÑO DE EBR AL DELETE
                        //REALIZAR FORMATEO
                        if(disco->type.toLower() == "fast"){

                        }else if(disco->type.toLower() == "full"){

                        }
                        //ASIGNAR ESTRUCTURA EXT2 O EXT3
                        if(disco->fs.toLower() == "2fs"){

                        }else if(disco->fs.toLower() == "3fs"){

                        }
                    }
                }else if(extP == "4"){
                    FILE* Debr=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Debr,part4.part_start,SEEK_SET);
                    fread(&ebr,sizeof(EBR),1,Debr);
                    fseek(Debr,0,SEEK_SET);
                    fclose(Debr);

                    int partOcupado = 0;
                    int nuevoinicio = part4.part_start;
                    int tam_Particion = part4.part_size;
                    int tam_ebr = sizeof (ebr);
                    bool encontrado = false;
                    while(ebr.part_next != -1){
                        Debr=fopen(ruta.toStdString().c_str(),"rb+");
                        fseek(Debr,nuevoinicio,SEEK_SET);
                        fread(&ebr,sizeof(EBR),1,Debr);
                        fseek(Debr,0,SEEK_SET);
                        fclose(Debr);

                        QString NombreEbr(ebr.part_name);
                        if(NombreEbr == nombre1){
                            encontrado = true;
                            break;
                        }

                        if(ebr.part_next != -1){
                            nuevoinicio = ebr.part_next;
                            partOcupado = partOcupado + tam_ebr + ebr.part_size;
                        }
                        if(partOcupado >= tam_Particion){break;}
                    }

                    if(encontrado){
                        //IMPORTANTE NO VOLARSE EL EBR, SUMAR EL TAMAÑO DE EBR AL DELETE
                        //REALIZAR FORMATEO
                        if(disco->type.toLower() == "fast"){

                        }else if(disco->type.toLower() == "full"){

                        }
                        //ASIGNAR ESTRUCTURA EXT2 O EXT3
                        if(disco->fs.toLower() == "2fs"){

                        }else if(disco->fs.toLower() == "3fs"){

                        }
                    }
                }
            }
        }else{
            cout<<"No Hay Montada Particion Con Id: "<<disco->id.toStdString().c_str()<<endl;
        }
    }else{
        cout<<"ID No Ingresada, Incorrecto"<<endl;
    }
    disco->id = "";
    disco->type = "";
    disco->fs = "";
}
