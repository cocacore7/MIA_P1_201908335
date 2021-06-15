#include "clloss.h"
#include <QString>
#include <iostream>
#include <QStringList>
#include <QDir>
#include <mbrstruct.h>
#include <ebrstruct.h>
#include <time.h>
#include <fstream>
//ESTRUCTURAS --------------
#include <sbstruct.h>
#include <journalingstruct.h>
#include <tinodosstruct.h>
#include <bloquesapstruct.h>
#include <bloquesarstruct.h>
#include <bloquescastruct.h>
//-------------------------------------------
//-------------------------------------------
//Necesario Para Usar Montada --------------
#include <clmontada.h>
#include <cabeceramontadas.h>
#include <clsesion.h>
//-------------------------------------------

using namespace std;

clloss::clloss()
{

}

void clloss::mostrarDatos(clloss *perdida){
    cout<<"----------------------PerdidaInformacion--------------------------"<<endl;
    cout<<"-El Id Es: "<<perdida->id.toStdString().c_str()<<endl;
    if(perdida->id != ""){
        if(lista.comprobarId(lista.lista,perdida->id)){
            ListaM aux = lista.obtenerNodo(lista.lista,perdida->id);
            QString nombreP = aux->nombreP;
            QStringList direcciones = aux->ruta.split("/");
            QString ruta = "/home/oscar/archivos";
            bool NoCarpeta = false;

            MBR mbr;
            struct particion part1;
            struct particion part2;
            struct particion part3;
            struct particion part4;
            QString extP = "";

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

            QString nombre1(part1.part_name);
            QString nombre2(part2.part_name);
            QString nombre3(part3.part_name);
            QString nombre4(part4.part_name);

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
                SuperBloque sb;
                FILE *Particion;
                //OBTENER SUPER BLOQUE
                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                fseek(Particion,part1.part_start,SEEK_SET);
                fread(&sb,sizeof(sb),1,Particion);
                fseek(Particion,0,SEEK_SET);
                fclose(Particion);

                //PERDER INFORMACION
                char vacio = '\0';
                int inicio = sb.s_block_start;
                while (inicio < (sb.s_block_start + sb.s_blocks_count)) {
                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,inicio,SEEK_SET);
                    fwrite(&vacio,sizeof(vacio),1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);
                    inicio+=sizeof(vacio);
                }
                inicio = sb.s_inode_start;
                while (inicio < sb.s_block_start) {
                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,inicio,SEEK_SET);
                    fwrite(&vacio,sizeof(vacio),1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);
                    inicio+=sizeof(vacio);
                }
                char vacio2 = '0';
                inicio = sb.s_bm_inode_start;
                while (inicio <= sb.s_bm_block_start) {
                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,inicio,SEEK_SET);
                    fwrite(&vacio2,sizeof(vacio2),1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);
                    inicio+=sizeof(vacio2);
                }
                inicio = sb.s_bm_block_start;
                while (inicio <= sb.s_inode_start) {
                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,inicio,SEEK_SET);
                    fwrite(&vacio2,sizeof(vacio2),1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);
                    inicio+=sizeof(vacio2);
                }
                cout<<"Loss De Particion Lista :D"<<endl;
            }else if(nombre2 == nombreP){
                SuperBloque sb;
                FILE *Particion;
                //OBTENER SUPER BLOQUE
                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                fseek(Particion,part2.part_start,SEEK_SET);
                fread(&sb,sizeof(sb),1,Particion);
                fseek(Particion,0,SEEK_SET);
                fclose(Particion);

                //PERDER INFORMACION
                char vacio = '\0';
                int inicio = sb.s_block_start;
                while (inicio < (sb.s_block_start + sb.s_blocks_count)) {
                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,inicio,SEEK_SET);
                    fwrite(&vacio,sizeof(vacio),1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);
                    inicio+=sizeof(vacio);
                }
                inicio = sb.s_inode_start;
                while (inicio < sb.s_block_start) {
                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,inicio,SEEK_SET);
                    fwrite(&vacio,sizeof(vacio),1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);
                    inicio+=sizeof(vacio);
                }
                char vacio2 = '0';
                inicio = sb.s_bm_inode_start;
                while (inicio <= sb.s_bm_block_start) {
                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,inicio,SEEK_SET);
                    fwrite(&vacio2,sizeof(vacio2),1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);
                    inicio+=sizeof(vacio2);
                }
                inicio = sb.s_bm_block_start;
                while (inicio <= sb.s_inode_start) {
                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,inicio,SEEK_SET);
                    fwrite(&vacio2,sizeof(vacio2),1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);
                    inicio+=sizeof(vacio2);
                }
                cout<<"Loss De Particion Lista :D"<<endl;
            }else if(nombre3 == nombreP){
                SuperBloque sb;
                FILE *Particion;
                //OBTENER SUPER BLOQUE
                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                fseek(Particion,part3.part_start,SEEK_SET);
                fread(&sb,sizeof(sb),1,Particion);
                fseek(Particion,0,SEEK_SET);
                fclose(Particion);

                //PERDER INFORMACION
                char vacio = '\0';
                int inicio = sb.s_block_start;
                while (inicio < (sb.s_block_start + sb.s_blocks_count)) {
                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,inicio,SEEK_SET);
                    fwrite(&vacio,sizeof(vacio),1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);
                    inicio+=sizeof(vacio);
                }
                inicio = sb.s_inode_start;
                while (inicio < sb.s_block_start) {
                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,inicio,SEEK_SET);
                    fwrite(&vacio,sizeof(vacio),1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);
                    inicio+=sizeof(vacio);
                }
                char vacio2 = '0';
                inicio = sb.s_bm_inode_start;
                while (inicio <= sb.s_bm_block_start) {
                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,inicio,SEEK_SET);
                    fwrite(&vacio2,sizeof(vacio2),1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);
                    inicio+=sizeof(vacio2);
                }
                inicio = sb.s_bm_block_start;
                while (inicio <= sb.s_inode_start) {
                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,inicio,SEEK_SET);
                    fwrite(&vacio2,sizeof(vacio2),1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);
                    inicio+=sizeof(vacio2);
                }
                cout<<"Loss De Particion Lista :D"<<endl;
            }else if(nombre4 == nombreP){
                SuperBloque sb;
                FILE *Particion;
                //OBTENER SUPER BLOQUE
                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                fseek(Particion,part4.part_start,SEEK_SET);
                fread(&sb,sizeof(sb),1,Particion);
                fseek(Particion,0,SEEK_SET);
                fclose(Particion);

                //PERDER INFORMACION
                char vacio = '\0';
                int inicio = sb.s_block_start;
                while (inicio < (sb.s_block_start + sb.s_blocks_count)) {
                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,inicio,SEEK_SET);
                    fwrite(&vacio,sizeof(vacio),1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);
                    inicio+=sizeof(vacio);
                }
                inicio = sb.s_inode_start;
                while (inicio < sb.s_block_start) {
                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,inicio,SEEK_SET);
                    fwrite(&vacio,sizeof(vacio),1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);
                    inicio+=sizeof(vacio);
                }
                char vacio2 = '0';
                inicio = sb.s_bm_inode_start;
                while (inicio <= sb.s_bm_block_start) {
                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,inicio,SEEK_SET);
                    fwrite(&vacio2,sizeof(vacio2),1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);
                    inicio+=sizeof(vacio2);
                }
                inicio = sb.s_bm_block_start;
                while (inicio <= sb.s_inode_start) {
                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,inicio,SEEK_SET);
                    fwrite(&vacio2,sizeof(vacio2),1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);
                    inicio+=sizeof(vacio2);
                }
                cout<<"Loss De Particion Lista :D"<<endl;
            }else{
                EBR ebr;
                EBR siguiente;
                if(extP == "1"){
                    FILE* Debr=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Debr,part1.part_start,SEEK_SET);
                    fread(&ebr,sizeof(EBR),1,Debr);
                    fseek(Debr,0,SEEK_SET);
                    fclose(Debr);

                    siguiente = ebr;
                    while(siguiente.part_next != -1){
                        ebr = siguiente;
                        Debr=fopen(ruta.toStdString().c_str(),"rb+");
                        fseek(Debr,siguiente.part_next,SEEK_SET);
                        fread(&siguiente,sizeof(EBR),1,Debr);
                        fseek(Debr,0,SEEK_SET);
                        fclose(Debr);
                        QString nombreChar(siguiente.part_name);
                        if(nombreP == nombreChar){
                            SuperBloque sb;
                            FILE *Particion;
                            //OBTENER SUPER BLOQUE
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,ebr.part_start + sizeof (ebr),SEEK_SET);
                            fread(&sb,sizeof(sb),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            //PERDER INFORMACION
                            char vacio = '\0';
                            int inicio = sb.s_block_start;
                            while (inicio < (sb.s_block_start + sb.s_blocks_count)) {
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,inicio,SEEK_SET);
                                fwrite(&vacio,sizeof(vacio),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);
                                inicio+=sizeof(vacio);
                            }
                            inicio = sb.s_inode_start;
                            while (inicio < sb.s_block_start) {
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,inicio,SEEK_SET);
                                fwrite(&vacio,sizeof(vacio),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);
                                inicio+=sizeof(vacio);
                            }
                            char vacio2 = '0';
                            inicio = sb.s_bm_inode_start;
                            while (inicio <= sb.s_bm_block_start) {
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,inicio,SEEK_SET);
                                fwrite(&vacio2,sizeof(vacio2),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);
                                inicio+=sizeof(vacio2);
                            }
                            inicio = sb.s_bm_block_start;
                            while (inicio <= sb.s_inode_start) {
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,inicio,SEEK_SET);
                                fwrite(&vacio2,sizeof(vacio2),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);
                                inicio+=sizeof(vacio2);
                            }
                            cout<<"Loss De Particion Lista :D"<<endl;
                            break;
                        }else{
                            Debr=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Debr,siguiente.part_next,SEEK_SET);
                            fread(&siguiente,sizeof(EBR),1,Debr);
                            fseek(Debr,0,SEEK_SET);
                            fclose(Debr);
                        }
                    }
                }else if(extP == "2"){
                    FILE* Debr=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Debr,part2.part_start,SEEK_SET);
                    fread(&ebr,sizeof(EBR),1,Debr);
                    fseek(Debr,0,SEEK_SET);
                    fclose(Debr);

                    siguiente = ebr;
                    while(siguiente.part_next != -1){
                        ebr = siguiente;
                        Debr=fopen(ruta.toStdString().c_str(),"rb+");
                        fseek(Debr,siguiente.part_next,SEEK_SET);
                        fread(&siguiente,sizeof(EBR),1,Debr);
                        fseek(Debr,0,SEEK_SET);
                        fclose(Debr);
                        QString nombreChar(siguiente.part_name);
                        if(nombreP == nombreChar){
                            SuperBloque sb;
                            FILE *Particion;
                            //OBTENER SUPER BLOQUE
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,ebr.part_start + sizeof (ebr),SEEK_SET);
                            fread(&sb,sizeof(sb),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            //PERDER INFORMACION
                            char vacio = '\0';
                            int inicio = sb.s_block_start;
                            while (inicio < (sb.s_block_start + sb.s_blocks_count)) {
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,inicio,SEEK_SET);
                                fwrite(&vacio,sizeof(vacio),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);
                                inicio+=sizeof(vacio);
                            }
                            inicio = sb.s_inode_start;
                            while (inicio < sb.s_block_start) {
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,inicio,SEEK_SET);
                                fwrite(&vacio,sizeof(vacio),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);
                                inicio+=sizeof(vacio);
                            }
                            char vacio2 = '0';
                            inicio = sb.s_bm_inode_start;
                            while (inicio <= sb.s_bm_block_start) {
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,inicio,SEEK_SET);
                                fwrite(&vacio2,sizeof(vacio2),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);
                                inicio+=sizeof(vacio2);
                            }
                            inicio = sb.s_bm_block_start;
                            while (inicio <= sb.s_inode_start) {
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,inicio,SEEK_SET);
                                fwrite(&vacio2,sizeof(vacio2),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);
                                inicio+=sizeof(vacio2);
                            }
                            cout<<"Loss De Particion Lista :D"<<endl;
                            break;
                        }else{
                            Debr=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Debr,siguiente.part_next,SEEK_SET);
                            fread(&siguiente,sizeof(EBR),1,Debr);
                            fseek(Debr,0,SEEK_SET);
                            fclose(Debr);
                        }
                    }
                }else if(extP == "3"){
                    FILE* Debr=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Debr,part3.part_start,SEEK_SET);
                    fread(&ebr,sizeof(EBR),1,Debr);
                    fseek(Debr,0,SEEK_SET);
                    fclose(Debr);

                    siguiente = ebr;
                    while(siguiente.part_next != -1){
                        ebr = siguiente;
                        Debr=fopen(ruta.toStdString().c_str(),"rb+");
                        fseek(Debr,siguiente.part_next,SEEK_SET);
                        fread(&siguiente,sizeof(EBR),1,Debr);
                        fseek(Debr,0,SEEK_SET);
                        fclose(Debr);
                        QString nombreChar(siguiente.part_name);
                        if(nombreP == nombreChar){
                            SuperBloque sb;
                            FILE *Particion;
                            //OBTENER SUPER BLOQUE
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,ebr.part_start + sizeof (ebr),SEEK_SET);
                            fread(&sb,sizeof(sb),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            //PERDER INFORMACION
                            char vacio = '\0';
                            int inicio = sb.s_block_start;
                            while (inicio < (sb.s_block_start + sb.s_blocks_count)) {
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,inicio,SEEK_SET);
                                fwrite(&vacio,sizeof(vacio),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);
                                inicio+=sizeof(vacio);
                            }
                            inicio = sb.s_inode_start;
                            while (inicio < sb.s_block_start) {
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,inicio,SEEK_SET);
                                fwrite(&vacio,sizeof(vacio),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);
                                inicio+=sizeof(vacio);
                            }
                            char vacio2 = '0';
                            inicio = sb.s_bm_inode_start;
                            while (inicio <= sb.s_bm_block_start) {
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,inicio,SEEK_SET);
                                fwrite(&vacio2,sizeof(vacio2),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);
                                inicio+=sizeof(vacio2);
                            }
                            inicio = sb.s_bm_block_start;
                            while (inicio <= sb.s_inode_start) {
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,inicio,SEEK_SET);
                                fwrite(&vacio2,sizeof(vacio2),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);
                                inicio+=sizeof(vacio2);
                            }
                            cout<<"Loss De Particion Lista :D"<<endl;
                            break;
                        }else{
                            Debr=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Debr,siguiente.part_next,SEEK_SET);
                            fread(&siguiente,sizeof(EBR),1,Debr);
                            fseek(Debr,0,SEEK_SET);
                            fclose(Debr);
                        }
                    }
                }else if(extP == "4"){
                    FILE* Debr=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Debr,part4.part_start,SEEK_SET);
                    fread(&ebr,sizeof(EBR),1,Debr);
                    fseek(Debr,0,SEEK_SET);
                    fclose(Debr);

                    siguiente = ebr;
                    while(siguiente.part_next != -1){
                        ebr = siguiente;
                        Debr=fopen(ruta.toStdString().c_str(),"rb+");
                        fseek(Debr,siguiente.part_next,SEEK_SET);
                        fread(&siguiente,sizeof(EBR),1,Debr);
                        fseek(Debr,0,SEEK_SET);
                        fclose(Debr);
                        QString nombreChar(siguiente.part_name);
                        if(nombreP == nombreChar){
                            SuperBloque sb;
                            FILE *Particion;
                            //OBTENER SUPER BLOQUE
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,ebr.part_start + sizeof (ebr),SEEK_SET);
                            fread(&sb,sizeof(sb),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            //PERDER INFORMACION
                            char vacio = '\0';
                            int inicio = sb.s_block_start;
                            while (inicio < (sb.s_block_start + sb.s_blocks_count)) {
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,inicio,SEEK_SET);
                                fwrite(&vacio,sizeof(vacio),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);
                                inicio+=sizeof(vacio);
                            }
                            inicio = sb.s_inode_start;
                            while (inicio < sb.s_block_start) {
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,inicio,SEEK_SET);
                                fwrite(&vacio,sizeof(vacio),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);
                                inicio+=sizeof(vacio);
                            }
                            char vacio2 = '0';
                            inicio = sb.s_bm_inode_start;
                            while (inicio <= sb.s_bm_block_start) {
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,inicio,SEEK_SET);
                                fwrite(&vacio2,sizeof(vacio2),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);
                                inicio+=sizeof(vacio2);
                            }
                            inicio = sb.s_bm_block_start;
                            while (inicio <= sb.s_inode_start) {
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,inicio,SEEK_SET);
                                fwrite(&vacio2,sizeof(vacio2),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);
                                inicio+=sizeof(vacio2);
                            }
                            cout<<"Loss De Particion Lista :D"<<endl;
                            break;
                        }else{
                            Debr=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Debr,siguiente.part_next,SEEK_SET);
                            fread(&siguiente,sizeof(EBR),1,Debr);
                            fseek(Debr,0,SEEK_SET);
                            fclose(Debr);
                        }
                    }
                }
            }
        }else{
            cout<<"No Se Encuentra Montada Una Particion Con El Id Especificado"<<endl;
        }
    }else{
        cout<<"Identificador Vacio"<<endl;
    }
    perdida->id = "";
    cout<<"--------------------------------------------------------"<<endl;
}
