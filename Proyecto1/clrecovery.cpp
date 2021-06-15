#include "clrecovery.h"
#include <QString>
#include <iostream>
#include <QStringList>
#include <QDir>
#include <mbrstruct.h>
#include <ebrstruct.h>
#include <time.h>
#include <fstream>
#include <parser.h>
#include <scanner.h>
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

clrecovery::clrecovery()
{

}

void clrecovery::mostrarDatos(clrecovery *recuperar){
    cout<<"----------------------RecuperarInformacion--------------------------"<<endl;
    cout<<"-El Id Es: "<<recuperar->id.toStdString().c_str()<<endl;
    if(recuperar->id != ""){
        if(lista.comprobarId(lista.lista,recuperar->id)){
            ListaM aux = lista.obtenerNodo(lista.lista,recuperar->id);
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
                Journaling vitacora;
                //OBTENER SUPER BLOQUE
                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                fseek(Particion,part1.part_start,SEEK_SET);
                fread(&sb,sizeof(sb),1,Particion);
                fseek(Particion,0,SEEK_SET);
                fclose(Particion);

                //Si es Ext3 Recuperar Informacion
                if(sb.s_filesystem_type == 3){
                    int inicio = part1.part_start + sizeof (SuperBloque);
                    while (inicio<sb.s_bm_inode_start) {
                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                        fseek(Particion,inicio,SEEK_SET);
                        fread(&vitacora,sizeof(vitacora),1,Particion);
                        fseek(Particion,0,SEEK_SET);
                        fclose(Particion);
                        QString linea(vitacora.Comando);
                        if(linea == ""){break;}
                        if(linea == "RaizYUsers.txt"){
                            //CARPETA RAIZ
                            char nuevo = '1';
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_bm_inode_start,SEEK_SET);
                            fwrite(&nuevo,sizeof(nuevo),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            TablaInodos nuevoI;
                            nuevoI.i_uid = 1;
                            nuevoI.i_gid = 1;
                            nuevoI.i_size = 0;
                            nuevoI.i_atime = time(NULL);
                            nuevoI.i_ctime = time(NULL);
                            nuevoI.i_mtime = time(NULL);
                            for(int x = 0;x<15;x++){
                                nuevoI.i_block[x] = -1;
                            }
                            nuevoI.i_block[0] = 0;
                            nuevoI.i_type = '0';
                            nuevoI.i_perm = 777;
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_inode_start,SEEK_SET);
                            fwrite(&nuevoI,sizeof(TablaInodos),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_bm_block_start,SEEK_SET);
                            fwrite(&nuevo,sizeof(nuevo),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            BloquesCarpetas nuevaC;
                            for(int x=0; x<4;x++){
                                strcpy(nuevaC.b_content[x].b_name,".");
                                nuevaC.b_content[x].b_inodo = -1;
                            }
                            strcpy(nuevaC.b_content[0].b_name,"users.txt");
                            nuevaC.b_content[0].b_inodo = 1;
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_block_start,SEEK_SET);
                            fwrite(&nuevaC,sizeof(nuevaC),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            //Archivo USERS
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_bm_inode_start + sizeof (nuevo),SEEK_SET);
                            fwrite(&nuevo,sizeof(nuevo) + sizeof(nuevo),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_bm_block_start + sizeof (nuevo),SEEK_SET);
                            fwrite(&nuevo,sizeof(nuevo),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            nuevoI.i_uid = 1;
                            nuevoI.i_gid = 1;
                            nuevoI.i_size = 27;
                            nuevoI.i_atime = time(NULL);
                            nuevoI.i_ctime = time(NULL);
                            nuevoI.i_mtime = time(NULL);
                            for(int x = 0;x<15;x++){
                                nuevoI.i_block[x] = -1;
                            }
                            nuevoI.i_block[0] = 1;
                            nuevoI.i_type = '1';
                            nuevoI.i_perm = 777;
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_inode_start + sizeof (nuevoI),SEEK_SET);
                            fwrite(&nuevoI,sizeof(nuevoI),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            BloquesArchivos usuarios;
                            strcpy(usuarios.b_content,"1,G,root\n1,U,root,root,123\n");
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_block_start + sizeof (BloquesArchivos),SEEK_SET);
                            fwrite(&usuarios,sizeof(BloquesArchivos),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);
                        }else{
                            YY_BUFFER_STATE buffer = yy_scan_string(linea.toStdString().c_str());
                            if(yyparse()==0){
                                //cout<<resultado<<endl;
                            }else{
                                cout<<"Hubo Un Error"<<endl;
                            }
                        }
                        inicio += sizeof (Journaling);
                    }
                    cout<<"Recovery De Particion Lista :D"<<endl;
                }else{
                    cout<<"El Sistema De Archivos No Es Ext3"<<endl;
                }
            }else if(nombre2 == nombreP){
                SuperBloque sb;
                FILE *Particion;
                Journaling vitacora;
                //OBTENER SUPER BLOQUE
                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                fseek(Particion,part2.part_start,SEEK_SET);
                fread(&sb,sizeof(sb),1,Particion);
                fseek(Particion,0,SEEK_SET);
                fclose(Particion);

                //Si es Ext3 Recuperar Informacion
                if(sb.s_filesystem_type == 3){
                    int inicio = part2.part_start + sizeof (SuperBloque);
                    while (inicio<sb.s_bm_inode_start) {
                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                        fseek(Particion,inicio,SEEK_SET);
                        fread(&vitacora,sizeof(vitacora),1,Particion);
                        fseek(Particion,0,SEEK_SET);
                        fclose(Particion);
                        QString linea(vitacora.Comando);
                        if(linea == ""){break;}
                        if(linea == "RaizYUsers.txt"){
                            //CARPETA RAIZ
                            char nuevo = '1';
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_bm_inode_start,SEEK_SET);
                            fwrite(&nuevo,sizeof(nuevo),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            TablaInodos nuevoI;
                            nuevoI.i_uid = 1;
                            nuevoI.i_gid = 1;
                            nuevoI.i_size = 0;
                            nuevoI.i_atime = time(NULL);
                            nuevoI.i_ctime = time(NULL);
                            nuevoI.i_mtime = time(NULL);
                            for(int x = 0;x<15;x++){
                                nuevoI.i_block[x] = -1;
                            }
                            nuevoI.i_block[0] = 0;
                            nuevoI.i_type = '0';
                            nuevoI.i_perm = 777;
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_inode_start,SEEK_SET);
                            fwrite(&nuevoI,sizeof(TablaInodos),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_bm_block_start,SEEK_SET);
                            fwrite(&nuevo,sizeof(nuevo),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            BloquesCarpetas nuevaC;
                            for(int x=0; x<4;x++){
                                strcpy(nuevaC.b_content[x].b_name,".");
                                nuevaC.b_content[x].b_inodo = -1;
                            }
                            strcpy(nuevaC.b_content[0].b_name,"users.txt");
                            nuevaC.b_content[0].b_inodo = 1;
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_block_start,SEEK_SET);
                            fwrite(&nuevaC,sizeof(nuevaC),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            //Archivo USERS
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_bm_inode_start + sizeof (nuevo),SEEK_SET);
                            fwrite(&nuevo,sizeof(nuevo) + sizeof(nuevo),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_bm_block_start + sizeof (nuevo),SEEK_SET);
                            fwrite(&nuevo,sizeof(nuevo),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            nuevoI.i_uid = 1;
                            nuevoI.i_gid = 1;
                            nuevoI.i_size = 27;
                            nuevoI.i_atime = time(NULL);
                            nuevoI.i_ctime = time(NULL);
                            nuevoI.i_mtime = time(NULL);
                            for(int x = 0;x<15;x++){
                                nuevoI.i_block[x] = -1;
                            }
                            nuevoI.i_block[0] = 1;
                            nuevoI.i_type = '1';
                            nuevoI.i_perm = 777;
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_inode_start + sizeof (nuevoI),SEEK_SET);
                            fwrite(&nuevoI,sizeof(nuevoI),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            BloquesArchivos usuarios;
                            strcpy(usuarios.b_content,"1,G,root\n1,U,root,root,123\n");
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_block_start + sizeof (BloquesArchivos),SEEK_SET);
                            fwrite(&usuarios,sizeof(BloquesArchivos),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);
                        }else{
                            YY_BUFFER_STATE buffer = yy_scan_string(linea.toStdString().c_str());
                            if(yyparse()==0){
                                //cout<<resultado<<endl;
                            }else{
                                cout<<"Hubo Un Error"<<endl;
                            }
                        }
                        inicio += sizeof (Journaling);
                    }
                    cout<<"Recovery De Particion Lista :D"<<endl;
                }else{
                    cout<<"El Sistema De Archivos No Es Ext3"<<endl;
                }
            }else if(nombre3 == nombreP){
                SuperBloque sb;
                FILE *Particion;
                Journaling vitacora;
                //OBTENER SUPER BLOQUE
                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                fseek(Particion,part3.part_start,SEEK_SET);
                fread(&sb,sizeof(sb),1,Particion);
                fseek(Particion,0,SEEK_SET);
                fclose(Particion);

                //Si es Ext3 Recuperar Informacion
                if(sb.s_filesystem_type == 3){
                    int inicio = part3.part_start + sizeof (SuperBloque);
                    while (inicio<sb.s_bm_inode_start) {
                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                        fseek(Particion,inicio,SEEK_SET);
                        fread(&vitacora,sizeof(vitacora),1,Particion);
                        fseek(Particion,0,SEEK_SET);
                        fclose(Particion);
                        QString linea(vitacora.Comando);
                        if(linea == ""){break;}
                        if(linea == "RaizYUsers.txt"){
                            //CARPETA RAIZ
                            char nuevo = '1';
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_bm_inode_start,SEEK_SET);
                            fwrite(&nuevo,sizeof(nuevo),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            TablaInodos nuevoI;
                            nuevoI.i_uid = 1;
                            nuevoI.i_gid = 1;
                            nuevoI.i_size = 0;
                            nuevoI.i_atime = time(NULL);
                            nuevoI.i_ctime = time(NULL);
                            nuevoI.i_mtime = time(NULL);
                            for(int x = 0;x<15;x++){
                                nuevoI.i_block[x] = -1;
                            }
                            nuevoI.i_block[0] = 0;
                            nuevoI.i_type = '0';
                            nuevoI.i_perm = 777;
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_inode_start,SEEK_SET);
                            fwrite(&nuevoI,sizeof(TablaInodos),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_bm_block_start,SEEK_SET);
                            fwrite(&nuevo,sizeof(nuevo),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            BloquesCarpetas nuevaC;
                            for(int x=0; x<4;x++){
                                strcpy(nuevaC.b_content[x].b_name,".");
                                nuevaC.b_content[x].b_inodo = -1;
                            }
                            strcpy(nuevaC.b_content[0].b_name,"users.txt");
                            nuevaC.b_content[0].b_inodo = 1;
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_block_start,SEEK_SET);
                            fwrite(&nuevaC,sizeof(nuevaC),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            //Archivo USERS
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_bm_inode_start + sizeof (nuevo),SEEK_SET);
                            fwrite(&nuevo,sizeof(nuevo) + sizeof(nuevo),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_bm_block_start + sizeof (nuevo),SEEK_SET);
                            fwrite(&nuevo,sizeof(nuevo),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            nuevoI.i_uid = 1;
                            nuevoI.i_gid = 1;
                            nuevoI.i_size = 27;
                            nuevoI.i_atime = time(NULL);
                            nuevoI.i_ctime = time(NULL);
                            nuevoI.i_mtime = time(NULL);
                            for(int x = 0;x<15;x++){
                                nuevoI.i_block[x] = -1;
                            }
                            nuevoI.i_block[0] = 1;
                            nuevoI.i_type = '1';
                            nuevoI.i_perm = 777;
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_inode_start + sizeof (nuevoI),SEEK_SET);
                            fwrite(&nuevoI,sizeof(nuevoI),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            BloquesArchivos usuarios;
                            strcpy(usuarios.b_content,"1,G,root\n1,U,root,root,123\n");
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_block_start + sizeof (BloquesArchivos),SEEK_SET);
                            fwrite(&usuarios,sizeof(BloquesArchivos),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);
                        }else{
                            YY_BUFFER_STATE buffer = yy_scan_string(linea.toStdString().c_str());
                            if(yyparse()==0){
                                //cout<<resultado<<endl;
                            }else{
                                cout<<"Hubo Un Error"<<endl;
                            }
                        }
                        inicio += sizeof (Journaling);
                    }
                    cout<<"Recovery De Particion Lista :D"<<endl;
                }else{
                    cout<<"El Sistema De Archivos No Es Ext3"<<endl;
                }
            }else if(nombre4 == nombreP){
                SuperBloque sb;
                FILE *Particion;
                Journaling vitacora;
                //OBTENER SUPER BLOQUE
                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                fseek(Particion,part4.part_start,SEEK_SET);
                fread(&sb,sizeof(sb),1,Particion);
                fseek(Particion,0,SEEK_SET);
                fclose(Particion);

                //Si es Ext3 Recuperar Informacion
                if(sb.s_filesystem_type == 3){
                    int inicio = part4.part_start + sizeof (SuperBloque);
                    while (inicio<sb.s_bm_inode_start) {
                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                        fseek(Particion,inicio,SEEK_SET);
                        fread(&vitacora,sizeof(vitacora),1,Particion);
                        fseek(Particion,0,SEEK_SET);
                        fclose(Particion);
                        QString linea(vitacora.Comando);
                        if(linea == ""){break;}
                        if(linea == "RaizYUsers.txt"){
                            //CARPETA RAIZ
                            char nuevo = '1';
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_bm_inode_start,SEEK_SET);
                            fwrite(&nuevo,sizeof(nuevo),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            TablaInodos nuevoI;
                            nuevoI.i_uid = 1;
                            nuevoI.i_gid = 1;
                            nuevoI.i_size = 0;
                            nuevoI.i_atime = time(NULL);
                            nuevoI.i_ctime = time(NULL);
                            nuevoI.i_mtime = time(NULL);
                            for(int x = 0;x<15;x++){
                                nuevoI.i_block[x] = -1;
                            }
                            nuevoI.i_block[0] = 0;
                            nuevoI.i_type = '0';
                            nuevoI.i_perm = 777;
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_inode_start,SEEK_SET);
                            fwrite(&nuevoI,sizeof(TablaInodos),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_bm_block_start,SEEK_SET);
                            fwrite(&nuevo,sizeof(nuevo),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            BloquesCarpetas nuevaC;
                            for(int x=0; x<4;x++){
                                strcpy(nuevaC.b_content[x].b_name,".");
                                nuevaC.b_content[x].b_inodo = -1;
                            }
                            strcpy(nuevaC.b_content[0].b_name,"users.txt");
                            nuevaC.b_content[0].b_inodo = 1;
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_block_start,SEEK_SET);
                            fwrite(&nuevaC,sizeof(nuevaC),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            //Archivo USERS
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_bm_inode_start + sizeof (nuevo),SEEK_SET);
                            fwrite(&nuevo,sizeof(nuevo) + sizeof(nuevo),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_bm_block_start + sizeof (nuevo),SEEK_SET);
                            fwrite(&nuevo,sizeof(nuevo),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            nuevoI.i_uid = 1;
                            nuevoI.i_gid = 1;
                            nuevoI.i_size = 27;
                            nuevoI.i_atime = time(NULL);
                            nuevoI.i_ctime = time(NULL);
                            nuevoI.i_mtime = time(NULL);
                            for(int x = 0;x<15;x++){
                                nuevoI.i_block[x] = -1;
                            }
                            nuevoI.i_block[0] = 1;
                            nuevoI.i_type = '1';
                            nuevoI.i_perm = 777;
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_inode_start + sizeof (nuevoI),SEEK_SET);
                            fwrite(&nuevoI,sizeof(nuevoI),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            BloquesArchivos usuarios;
                            strcpy(usuarios.b_content,"1,G,root\n1,U,root,root,123\n");
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_block_start + sizeof (BloquesArchivos),SEEK_SET);
                            fwrite(&usuarios,sizeof(BloquesArchivos),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);
                        }else{
                            YY_BUFFER_STATE buffer = yy_scan_string(linea.toStdString().c_str());
                            if(yyparse()==0){
                                //cout<<resultado<<endl;
                            }else{
                                cout<<"Hubo Un Error"<<endl;
                            }
                        }
                        inicio += sizeof (Journaling);
                    }
                    cout<<"Recovery De Particion Lista :D"<<endl;
                }else{
                    cout<<"El Sistema De Archivos No Es Ext3"<<endl;
                }
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
                            Journaling vitacora;
                            //OBTENER SUPER BLOQUE
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,ebr.part_start + sizeof (ebr),SEEK_SET);
                            fread(&sb,sizeof(sb),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            //Si es Ext3 Recuperar Informacion
                            if(sb.s_filesystem_type == 3){
                                int inicio = ebr.part_start + sizeof (ebr) + sizeof (SuperBloque);
                                while (inicio<sb.s_bm_inode_start) {
                                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                    fseek(Particion,inicio,SEEK_SET);
                                    fread(&vitacora,sizeof(vitacora),1,Particion);
                                    fseek(Particion,0,SEEK_SET);
                                    fclose(Particion);
                                    QString linea(vitacora.Comando);
                                    if(linea == ""){break;}
                                    if(linea == "RaizYUsers.txt"){
                                        //CARPETA RAIZ
                                        char nuevo = '1';
                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_bm_inode_start,SEEK_SET);
                                        fwrite(&nuevo,sizeof(nuevo),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);

                                        TablaInodos nuevoI;
                                        nuevoI.i_uid = 1;
                                        nuevoI.i_gid = 1;
                                        nuevoI.i_size = 0;
                                        nuevoI.i_atime = time(NULL);
                                        nuevoI.i_ctime = time(NULL);
                                        nuevoI.i_mtime = time(NULL);
                                        for(int x = 0;x<15;x++){
                                            nuevoI.i_block[x] = -1;
                                        }
                                        nuevoI.i_block[0] = 0;
                                        nuevoI.i_type = '0';
                                        nuevoI.i_perm = 777;
                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_inode_start,SEEK_SET);
                                        fwrite(&nuevoI,sizeof(TablaInodos),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);

                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_bm_block_start,SEEK_SET);
                                        fwrite(&nuevo,sizeof(nuevo),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);

                                        BloquesCarpetas nuevaC;
                                        for(int x=0; x<4;x++){
                                            strcpy(nuevaC.b_content[x].b_name,".");
                                            nuevaC.b_content[x].b_inodo = -1;
                                        }
                                        strcpy(nuevaC.b_content[0].b_name,"users.txt");
                                        nuevaC.b_content[0].b_inodo = 1;
                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_block_start,SEEK_SET);
                                        fwrite(&nuevaC,sizeof(nuevaC),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);

                                        //Archivo USERS
                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_bm_inode_start + sizeof (nuevo),SEEK_SET);
                                        fwrite(&nuevo,sizeof(nuevo) + sizeof(nuevo),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);

                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_bm_block_start + sizeof (nuevo),SEEK_SET);
                                        fwrite(&nuevo,sizeof(nuevo),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);

                                        nuevoI.i_uid = 1;
                                        nuevoI.i_gid = 1;
                                        nuevoI.i_size = 27;
                                        nuevoI.i_atime = time(NULL);
                                        nuevoI.i_ctime = time(NULL);
                                        nuevoI.i_mtime = time(NULL);
                                        for(int x = 0;x<15;x++){
                                            nuevoI.i_block[x] = -1;
                                        }
                                        nuevoI.i_block[0] = 1;
                                        nuevoI.i_type = '1';
                                        nuevoI.i_perm = 777;
                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_inode_start + sizeof (nuevoI),SEEK_SET);
                                        fwrite(&nuevoI,sizeof(nuevoI),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);

                                        BloquesArchivos usuarios;
                                        strcpy(usuarios.b_content,"1,G,root\n1,U,root,root,123\n");
                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_block_start + sizeof (BloquesArchivos),SEEK_SET);
                                        fwrite(&usuarios,sizeof(BloquesArchivos),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);
                                    }else{
                                        YY_BUFFER_STATE buffer = yy_scan_string(linea.toStdString().c_str());
                                        if(yyparse()==0){
                                            //cout<<resultado<<endl;
                                        }else{
                                            cout<<"Hubo Un Error"<<endl;
                                        }
                                    }
                                    inicio += sizeof (Journaling);
                                }
                                cout<<"Recovery De Particion Lista :D"<<endl;
                            }else{
                                cout<<"El Sistema De Archivos No Es Ext3"<<endl;
                            }
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
                            Journaling vitacora;
                            //OBTENER SUPER BLOQUE
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,ebr.part_start + sizeof (ebr),SEEK_SET);
                            fread(&sb,sizeof(sb),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            //Si es Ext3 Recuperar Informacion
                            if(sb.s_filesystem_type == 3){
                                int inicio = ebr.part_start + sizeof (ebr) + sizeof (SuperBloque);
                                while (inicio<sb.s_bm_inode_start) {
                                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                    fseek(Particion,inicio,SEEK_SET);
                                    fread(&vitacora,sizeof(vitacora),1,Particion);
                                    fseek(Particion,0,SEEK_SET);
                                    fclose(Particion);
                                    QString linea(vitacora.Comando);
                                    if(linea == ""){break;}
                                    if(linea == "RaizYUsers.txt"){
                                        //CARPETA RAIZ
                                        char nuevo = '1';
                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_bm_inode_start,SEEK_SET);
                                        fwrite(&nuevo,sizeof(nuevo),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);

                                        TablaInodos nuevoI;
                                        nuevoI.i_uid = 1;
                                        nuevoI.i_gid = 1;
                                        nuevoI.i_size = 0;
                                        nuevoI.i_atime = time(NULL);
                                        nuevoI.i_ctime = time(NULL);
                                        nuevoI.i_mtime = time(NULL);
                                        for(int x = 0;x<15;x++){
                                            nuevoI.i_block[x] = -1;
                                        }
                                        nuevoI.i_block[0] = 0;
                                        nuevoI.i_type = '0';
                                        nuevoI.i_perm = 777;
                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_inode_start,SEEK_SET);
                                        fwrite(&nuevoI,sizeof(TablaInodos),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);

                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_bm_block_start,SEEK_SET);
                                        fwrite(&nuevo,sizeof(nuevo),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);

                                        BloquesCarpetas nuevaC;
                                        for(int x=0; x<4;x++){
                                            strcpy(nuevaC.b_content[x].b_name,".");
                                            nuevaC.b_content[x].b_inodo = -1;
                                        }
                                        strcpy(nuevaC.b_content[0].b_name,"users.txt");
                                        nuevaC.b_content[0].b_inodo = 1;
                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_block_start,SEEK_SET);
                                        fwrite(&nuevaC,sizeof(nuevaC),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);

                                        //Archivo USERS
                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_bm_inode_start + sizeof (nuevo),SEEK_SET);
                                        fwrite(&nuevo,sizeof(nuevo) + sizeof(nuevo),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);

                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_bm_block_start + sizeof (nuevo),SEEK_SET);
                                        fwrite(&nuevo,sizeof(nuevo),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);

                                        nuevoI.i_uid = 1;
                                        nuevoI.i_gid = 1;
                                        nuevoI.i_size = 27;
                                        nuevoI.i_atime = time(NULL);
                                        nuevoI.i_ctime = time(NULL);
                                        nuevoI.i_mtime = time(NULL);
                                        for(int x = 0;x<15;x++){
                                            nuevoI.i_block[x] = -1;
                                        }
                                        nuevoI.i_block[0] = 1;
                                        nuevoI.i_type = '1';
                                        nuevoI.i_perm = 777;
                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_inode_start + sizeof (nuevoI),SEEK_SET);
                                        fwrite(&nuevoI,sizeof(nuevoI),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);

                                        BloquesArchivos usuarios;
                                        strcpy(usuarios.b_content,"1,G,root\n1,U,root,root,123\n");
                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_block_start + sizeof (BloquesArchivos),SEEK_SET);
                                        fwrite(&usuarios,sizeof(BloquesArchivos),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);
                                    }else{
                                        YY_BUFFER_STATE buffer = yy_scan_string(linea.toStdString().c_str());
                                        if(yyparse()==0){
                                            //cout<<resultado<<endl;
                                        }else{
                                            cout<<"Hubo Un Error"<<endl;
                                        }
                                    }
                                    inicio += sizeof (Journaling);
                                }
                                cout<<"Recovery De Particion Lista :D"<<endl;
                            }else{
                                cout<<"El Sistema De Archivos No Es Ext3"<<endl;
                            }
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
                            Journaling vitacora;
                            //OBTENER SUPER BLOQUE
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,ebr.part_start + sizeof (ebr),SEEK_SET);
                            fread(&sb,sizeof(sb),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            //Si es Ext3 Recuperar Informacion
                            if(sb.s_filesystem_type == 3){
                                int inicio = ebr.part_start + sizeof (ebr) + sizeof (SuperBloque);
                                while (inicio<sb.s_bm_inode_start) {
                                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                    fseek(Particion,inicio,SEEK_SET);
                                    fread(&vitacora,sizeof(vitacora),1,Particion);
                                    fseek(Particion,0,SEEK_SET);
                                    fclose(Particion);
                                    QString linea(vitacora.Comando);
                                    if(linea == ""){break;}
                                    if(linea == "RaizYUsers.txt"){
                                        //CARPETA RAIZ
                                        char nuevo = '1';
                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_bm_inode_start,SEEK_SET);
                                        fwrite(&nuevo,sizeof(nuevo),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);

                                        TablaInodos nuevoI;
                                        nuevoI.i_uid = 1;
                                        nuevoI.i_gid = 1;
                                        nuevoI.i_size = 0;
                                        nuevoI.i_atime = time(NULL);
                                        nuevoI.i_ctime = time(NULL);
                                        nuevoI.i_mtime = time(NULL);
                                        for(int x = 0;x<15;x++){
                                            nuevoI.i_block[x] = -1;
                                        }
                                        nuevoI.i_block[0] = 0;
                                        nuevoI.i_type = '0';
                                        nuevoI.i_perm = 777;
                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_inode_start,SEEK_SET);
                                        fwrite(&nuevoI,sizeof(TablaInodos),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);

                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_bm_block_start,SEEK_SET);
                                        fwrite(&nuevo,sizeof(nuevo),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);

                                        BloquesCarpetas nuevaC;
                                        for(int x=0; x<4;x++){
                                            strcpy(nuevaC.b_content[x].b_name,".");
                                            nuevaC.b_content[x].b_inodo = -1;
                                        }
                                        strcpy(nuevaC.b_content[0].b_name,"users.txt");
                                        nuevaC.b_content[0].b_inodo = 1;
                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_block_start,SEEK_SET);
                                        fwrite(&nuevaC,sizeof(nuevaC),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);

                                        //Archivo USERS
                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_bm_inode_start + sizeof (nuevo),SEEK_SET);
                                        fwrite(&nuevo,sizeof(nuevo) + sizeof(nuevo),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);

                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_bm_block_start + sizeof (nuevo),SEEK_SET);
                                        fwrite(&nuevo,sizeof(nuevo),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);

                                        nuevoI.i_uid = 1;
                                        nuevoI.i_gid = 1;
                                        nuevoI.i_size = 27;
                                        nuevoI.i_atime = time(NULL);
                                        nuevoI.i_ctime = time(NULL);
                                        nuevoI.i_mtime = time(NULL);
                                        for(int x = 0;x<15;x++){
                                            nuevoI.i_block[x] = -1;
                                        }
                                        nuevoI.i_block[0] = 1;
                                        nuevoI.i_type = '1';
                                        nuevoI.i_perm = 777;
                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_inode_start + sizeof (nuevoI),SEEK_SET);
                                        fwrite(&nuevoI,sizeof(nuevoI),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);

                                        BloquesArchivos usuarios;
                                        strcpy(usuarios.b_content,"1,G,root\n1,U,root,root,123\n");
                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_block_start + sizeof (BloquesArchivos),SEEK_SET);
                                        fwrite(&usuarios,sizeof(BloquesArchivos),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);
                                    }else{
                                        YY_BUFFER_STATE buffer = yy_scan_string(linea.toStdString().c_str());
                                        if(yyparse()==0){
                                            //cout<<resultado<<endl;
                                        }else{
                                            cout<<"Hubo Un Error"<<endl;
                                        }
                                    }
                                    inicio += sizeof (Journaling);
                                }
                                cout<<"Recovery De Particion Lista :D"<<endl;
                            }else{
                                cout<<"El Sistema De Archivos No Es Ext3"<<endl;
                            }
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
                            Journaling vitacora;
                            //OBTENER SUPER BLOQUE
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,ebr.part_start + sizeof (ebr),SEEK_SET);
                            fread(&sb,sizeof(sb),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            //Si es Ext3 Recuperar Informacion
                            if(sb.s_filesystem_type == 3){
                                int inicio = ebr.part_start + sizeof (ebr) + sizeof (SuperBloque);
                                while (inicio<sb.s_bm_inode_start) {
                                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                    fseek(Particion,inicio,SEEK_SET);
                                    fread(&vitacora,sizeof(vitacora),1,Particion);
                                    fseek(Particion,0,SEEK_SET);
                                    fclose(Particion);
                                    QString linea(vitacora.Comando);
                                    if(linea == ""){break;}
                                    if(linea == "RaizYUsers.txt"){
                                        //CARPETA RAIZ
                                        char nuevo = '1';
                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_bm_inode_start,SEEK_SET);
                                        fwrite(&nuevo,sizeof(nuevo),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);

                                        TablaInodos nuevoI;
                                        nuevoI.i_uid = 1;
                                        nuevoI.i_gid = 1;
                                        nuevoI.i_size = 0;
                                        nuevoI.i_atime = time(NULL);
                                        nuevoI.i_ctime = time(NULL);
                                        nuevoI.i_mtime = time(NULL);
                                        for(int x = 0;x<15;x++){
                                            nuevoI.i_block[x] = -1;
                                        }
                                        nuevoI.i_block[0] = 0;
                                        nuevoI.i_type = '0';
                                        nuevoI.i_perm = 777;
                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_inode_start,SEEK_SET);
                                        fwrite(&nuevoI,sizeof(TablaInodos),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);

                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_bm_block_start,SEEK_SET);
                                        fwrite(&nuevo,sizeof(nuevo),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);

                                        BloquesCarpetas nuevaC;
                                        for(int x=0; x<4;x++){
                                            strcpy(nuevaC.b_content[x].b_name,".");
                                            nuevaC.b_content[x].b_inodo = -1;
                                        }
                                        strcpy(nuevaC.b_content[0].b_name,"users.txt");
                                        nuevaC.b_content[0].b_inodo = 1;
                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_block_start,SEEK_SET);
                                        fwrite(&nuevaC,sizeof(nuevaC),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);

                                        //Archivo USERS
                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_bm_inode_start + sizeof (nuevo),SEEK_SET);
                                        fwrite(&nuevo,sizeof(nuevo) + sizeof(nuevo),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);

                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_bm_block_start + sizeof (nuevo),SEEK_SET);
                                        fwrite(&nuevo,sizeof(nuevo),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);

                                        nuevoI.i_uid = 1;
                                        nuevoI.i_gid = 1;
                                        nuevoI.i_size = 27;
                                        nuevoI.i_atime = time(NULL);
                                        nuevoI.i_ctime = time(NULL);
                                        nuevoI.i_mtime = time(NULL);
                                        for(int x = 0;x<15;x++){
                                            nuevoI.i_block[x] = -1;
                                        }
                                        nuevoI.i_block[0] = 1;
                                        nuevoI.i_type = '1';
                                        nuevoI.i_perm = 777;
                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_inode_start + sizeof (nuevoI),SEEK_SET);
                                        fwrite(&nuevoI,sizeof(nuevoI),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);

                                        BloquesArchivos usuarios;
                                        strcpy(usuarios.b_content,"1,G,root\n1,U,root,root,123\n");
                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_block_start + sizeof (BloquesArchivos),SEEK_SET);
                                        fwrite(&usuarios,sizeof(BloquesArchivos),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);
                                    }else{
                                        YY_BUFFER_STATE buffer = yy_scan_string(linea.toStdString().c_str());
                                        if(yyparse()==0){
                                            //cout<<resultado<<endl;
                                        }else{
                                            cout<<"Hubo Un Error"<<endl;
                                        }
                                    }
                                    inicio += sizeof (Journaling);
                                }
                                cout<<"Recovery De Particion Lista :D"<<endl;
                            }else{
                                cout<<"El Sistema De Archivos No Es Ext3"<<endl;
                            }
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

    recuperar->id = "";
    cout<<"--------------------------------------------------------"<<endl;
}
