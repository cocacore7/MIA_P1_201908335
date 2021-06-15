#include "clmkfs.h"
#include <QString>
#include <iostream>
#include <QDir>
#include <QStringList>
#include <mbrstruct.h>
#include <ebrstruct.h>
#include <tgmath.h>
//ESTRUCTURAS --------------
#include <sbstruct.h>
#include <journalingstruct.h>
#include <tinodosstruct.h>
#include <bloquesapstruct.h>
#include <bloquesarstruct.h>
#include <bloquescastruct.h>
//-------------------------------------------
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
            QString extP = "";

            if(disco->type==""){
                disco->type="full";
            }
            if(disco->fs==""){
                disco->fs="2fs";
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
                TablaInodos inodoT;
                Journaling vitacora;
                //ASIGNAR ESTRUCTURA EXT2 O EXT3
                if(disco->fs.toLower() == "2fs"){
                    float n1 = (part1.part_size - sizeof (sb)) / (sizeof (inodoT) + 196);
                    int n = floor(n1);
                    sb.s_filesystem_type = 2;
                    sb.s_inodes_count = n;
                    sb.s_blocks_count = n*3;
                    sb.s_free_blocks_count = (n*3)-2;
                    sb.s_free_inodes_count = n-2;
                    sb.s_mtime = time(NULL);
                    sb.s_umtime = time(NULL);
                    sb.s_mnt_count = 1;
                    sb.s_magic = 0xEF53;
                    sb.s_inode_size = sizeof (inodoT);
                    sb.s_block_size = 64;
                    sb.s_first_ino = part1.part_start + sizeof (sb) + n + (n*3) + sizeof (TablaInodos) + sizeof (TablaInodos);
                    sb.s_first_blo = part1.part_start + sizeof (sb) + n + (n*3) + (n*sizeof (inodoT)) + 128;
                    sb.s_bm_inode_start = part1.part_start + sizeof (sb);
                    sb.s_bm_block_start = part1.part_start + sizeof (sb) + n;
                    sb.s_inode_start = part1.part_start + sizeof (sb) + n + (n*3);
                    sb.s_block_start = part1.part_start + sizeof (sb) + n + (n*3) + (n*sizeof (inodoT));

                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,part1.part_start,SEEK_SET);
                    fwrite(&sb,sizeof(SuperBloque),1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);
                }else if(disco->fs.toLower() == "3fs"){
                    int n = (part1.part_size - sizeof (sb)) / (sizeof (vitacora) + sizeof (inodoT) + 196);
                    n = floor(n);
                    sb.s_filesystem_type = 3;
                    sb.s_inodes_count = n;
                    sb.s_blocks_count = n*3;
                    sb.s_free_blocks_count = (n*3)-2;
                    sb.s_free_inodes_count = n-2;
                    sb.s_mtime = time(NULL);
                    sb.s_umtime = time(NULL);
                    sb.s_mnt_count = 1;
                    sb.s_magic = 0xEF53;
                    sb.s_inode_size = sizeof (inodoT);
                    sb.s_block_size = 64;
                    sb.s_first_ino = part1.part_start + sizeof (sb) + (n* sizeof (vitacora)) + n + (n*3) + sizeof (TablaInodos) + sizeof (TablaInodos);
                    sb.s_first_blo = part1.part_start + sizeof (sb) + (n* sizeof (vitacora)) + n + (n*3) + (n*sizeof (inodoT)) + 128;
                    sb.s_bm_inode_start = part1.part_start + sizeof (sb) + (n* sizeof (vitacora));
                    sb.s_bm_block_start = part1.part_start + sizeof (sb) + (n* sizeof (vitacora)) + n;
                    sb.s_inode_start = part1.part_start + sizeof (sb) + (n* sizeof (vitacora)) + n + (n*3);
                    sb.s_block_start = part1.part_start + sizeof (sb) + (n* sizeof (vitacora)) + n + (n*3) + (n*sizeof (inodoT));

                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,part1.part_start,SEEK_SET);
                    fwrite(&sb,sizeof(SuperBloque),1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);
                }
                //REALIZAR FORMATEO
                if(disco->type.toLower() == "fast"){
                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,part1.part_start,SEEK_SET);
                    fread(&sb,sizeof(SuperBloque),1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);

                    char vacio = '0';
                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,sb.s_bm_inode_start,SEEK_SET);
                    fwrite(&vacio,sb.s_inodes_count,1,Particion);
                    fseek(Particion,sb.s_bm_block_start,SEEK_SET);
                    fwrite(&vacio,sb.s_blocks_count,1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);
                }else if(disco->type.toLower() == "full"){
                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,part1.part_start,SEEK_SET);
                    fread(&sb,sizeof(SuperBloque),1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);

                    char vacio = '0';
                    char vacio2 = '\0';
                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,sb.s_bm_inode_start,SEEK_SET);
                    fwrite(&vacio,sb.s_inodes_count,1,Particion);
                    fseek(Particion,sb.s_bm_block_start,SEEK_SET);
                    fwrite(&vacio,sb.s_blocks_count,1,Particion);
                    fseek(Particion,sb.s_inode_start,SEEK_SET);
                    fwrite(&vacio2,sb.s_inodes_count * sizeof(inodoT),1,Particion);
                    fseek(Particion,sb.s_block_start,SEEK_SET);
                    fwrite(&vacio2,sb.s_blocks_count * 64,1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);
                }

                //JOURNALING SI ES EXT 3
                if(sb.s_filesystem_type == 3){
                    strcpy(vitacora.Comando,"RaizYUsers.txt");
                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,part1.part_start + sizeof (sb),SEEK_SET);
                    fwrite(&vitacora,sizeof(vitacora),1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);
                }
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

                cout<<"Formateo De Particion Lista :D"<<endl;
            }else if(nombre2 == nombreP){
                SuperBloque sb;
                FILE *Particion;
                TablaInodos inodoT;
                Journaling vitacora;
                //ASIGNAR ESTRUCTURA EXT2 O EXT3
                if(disco->fs.toLower() == "2fs"){
                    int n = (part2.part_size - sizeof (sb)) / (sizeof (inodoT) + 196);
                    n = floor(n);
                    sb.s_filesystem_type = 2;
                    sb.s_inodes_count = n;
                    sb.s_blocks_count = n*3;
                    sb.s_free_blocks_count = (n*3)-2;
                    sb.s_free_inodes_count = n-2;
                    sb.s_mtime = time(NULL);
                    sb.s_umtime = time(NULL);
                    sb.s_mnt_count = 1;
                    sb.s_magic = 0xEF53;
                    sb.s_inode_size = sizeof (inodoT);
                    sb.s_block_size = 64;
                    sb.s_first_ino = part2.part_start + sizeof (sb) + n + (n*3) + sizeof (TablaInodos) + sizeof (TablaInodos);
                    sb.s_first_blo = part2.part_start + sizeof (sb) + n + (n*3) + (n*sizeof (inodoT)) + 128;
                    sb.s_bm_inode_start = part2.part_start + sizeof (sb);
                    sb.s_bm_block_start = part2.part_start + sizeof (sb) + n;
                    sb.s_inode_start = part2.part_start + sizeof (sb) + n + (n*3);
                    sb.s_block_start = part2.part_start + sizeof (sb) + n + (n*3) + (n*sizeof (inodoT));

                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,part2.part_start,SEEK_SET);
                    fwrite(&sb,sizeof(SuperBloque),1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);
                }else if(disco->fs.toLower() == "3fs"){
                    int n = (part2.part_size - sizeof (sb)) / (sizeof (vitacora) + sizeof (inodoT) + 196);
                    n = floor(n);
                    sb.s_filesystem_type = 3;
                    sb.s_inodes_count = n;
                    sb.s_blocks_count = n*3;
                    sb.s_free_blocks_count = (n*3)-2;
                    sb.s_free_inodes_count = n-2;
                    sb.s_mtime = time(NULL);
                    sb.s_umtime = time(NULL);
                    sb.s_mnt_count = 1;
                    sb.s_magic = 0xEF53;
                    sb.s_inode_size = sizeof (inodoT);
                    sb.s_block_size = 64;
                    sb.s_first_ino = part2.part_start + sizeof (sb) + (n* sizeof (vitacora)) + n + (n*3) + sizeof (TablaInodos) + sizeof (TablaInodos);
                    sb.s_first_blo = part2.part_start + sizeof (sb) + (n* sizeof (vitacora)) + n + (n*3) + (n*sizeof (inodoT)) + 128;
                    sb.s_bm_inode_start = part2.part_start + sizeof (sb) + (n* sizeof (vitacora));
                    sb.s_bm_block_start = part2.part_start + sizeof (sb) + (n* sizeof (vitacora)) + n;
                    sb.s_inode_start = part2.part_start + sizeof (sb) + (n* sizeof (vitacora)) + n + (n*3);
                    sb.s_block_start = part2.part_start + sizeof (sb) + (n* sizeof (vitacora)) + n + (n*3) + (n*sizeof (inodoT));

                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,part2.part_start,SEEK_SET);
                    fwrite(&sb,sizeof(SuperBloque),1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);
                }
                //REALIZAR FORMATEO
                if(disco->type.toLower() == "fast"){
                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,part2.part_start,SEEK_SET);
                    fread(&sb,sizeof(SuperBloque),1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);

                    char vacio = '0';
                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,sb.s_bm_inode_start,SEEK_SET);
                    fwrite(&vacio,sb.s_inodes_count,1,Particion);
                    fseek(Particion,sb.s_bm_block_start,SEEK_SET);
                    fwrite(&vacio,sb.s_blocks_count,1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);
                }else if(disco->type.toLower() == "full"){
                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,part2.part_start,SEEK_SET);
                    fread(&sb,sizeof(SuperBloque),1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);

                    char vacio = '0';
                    char vacio2 = '\0';
                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,sb.s_bm_inode_start,SEEK_SET);
                    fwrite(&vacio,sb.s_inodes_count,1,Particion);
                    fseek(Particion,sb.s_bm_block_start,SEEK_SET);
                    fwrite(&vacio,sb.s_blocks_count,1,Particion);
                    fseek(Particion,sb.s_inode_start,SEEK_SET);
                    fwrite(&vacio2,sb.s_inodes_count * sizeof(inodoT),1,Particion);
                    fseek(Particion,sb.s_block_start,SEEK_SET);
                    fwrite(&vacio2,sb.s_blocks_count * 64,1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);
                }

                //JOURNALING SI ES EXT 3
                if(sb.s_filesystem_type == 3){
                    strcpy(vitacora.Comando,"RaizYUsers.txt");
                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,part2.part_start + sizeof (sb),SEEK_SET);
                    fwrite(&vitacora,sizeof(vitacora),1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);
                }
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

                cout<<"Formateo De Particion Lista :D"<<endl;
            }else if(nombre3 == nombreP){
                SuperBloque sb;
                FILE *Particion;
                TablaInodos inodoT;
                Journaling vitacora;
                //ASIGNAR ESTRUCTURA EXT2 O EXT3
                if(disco->fs.toLower() == "2fs"){
                    int n = (part3.part_size - sizeof (sb)) / (sizeof (inodoT) + 196);
                    n = floor(n);
                    sb.s_filesystem_type = 2;
                    sb.s_inodes_count = n;
                    sb.s_blocks_count = n*3;
                    sb.s_free_blocks_count = (n*3)-2;
                    sb.s_free_inodes_count = n-2;
                    sb.s_mtime = time(NULL);
                    sb.s_umtime = time(NULL);
                    sb.s_mnt_count = 1;
                    sb.s_magic = 0xEF53;
                    sb.s_inode_size = sizeof (inodoT);
                    sb.s_block_size = 64;
                    sb.s_first_ino = part3.part_start + sizeof (sb) + n + (n*3) + sizeof (TablaInodos) + sizeof (TablaInodos);
                    sb.s_first_blo = part3.part_start + sizeof (sb) + n + (n*3) + (n*sizeof (inodoT)) + 128;
                    sb.s_bm_inode_start = part3.part_start + sizeof (sb);
                    sb.s_bm_block_start = part3.part_start + sizeof (sb) + n;
                    sb.s_inode_start = part3.part_start + sizeof (sb) + n + (n*3);
                    sb.s_block_start = part3.part_start + sizeof (sb) + n + (n*3) + (n*sizeof (inodoT));

                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,part3.part_start,SEEK_SET);
                    fwrite(&sb,sizeof(SuperBloque),1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);
                }else if(disco->fs.toLower() == "3fs"){
                    int n = (part3.part_size - sizeof (sb)) / (sizeof (vitacora) + sizeof (inodoT) + 196);
                    n = floor(n);
                    sb.s_filesystem_type = 3;
                    sb.s_inodes_count = n;
                    sb.s_blocks_count = n*3;
                    sb.s_free_blocks_count = (n*3)-2;
                    sb.s_free_inodes_count = n-2;
                    sb.s_mtime = time(NULL);
                    sb.s_umtime = time(NULL);
                    sb.s_mnt_count = 1;
                    sb.s_magic = 0xEF53;
                    sb.s_inode_size = sizeof (inodoT);
                    sb.s_block_size = 64;
                    sb.s_first_ino = part3.part_start + sizeof (sb) + (n* sizeof (vitacora)) + n + (n*3) + sizeof (TablaInodos) + sizeof (TablaInodos);
                    sb.s_first_blo = part3.part_start + sizeof (sb) + (n* sizeof (vitacora)) + n + (n*3) + (n*sizeof (inodoT)) + 128;
                    sb.s_bm_inode_start = part3.part_start + sizeof (sb) + (n* sizeof (vitacora));
                    sb.s_bm_block_start = part3.part_start + sizeof (sb) + (n* sizeof (vitacora)) + n;
                    sb.s_inode_start = part3.part_start + sizeof (sb) + (n* sizeof (vitacora)) + n + (n*3);
                    sb.s_block_start = part3.part_start + sizeof (sb) + (n* sizeof (vitacora)) + n + (n*3) + (n*sizeof (inodoT));

                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,part3.part_start,SEEK_SET);
                    fwrite(&sb,sizeof(SuperBloque),1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);
                }
                //REALIZAR FORMATEO
                if(disco->type.toLower() == "fast"){
                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,part3.part_start,SEEK_SET);
                    fread(&sb,sizeof(SuperBloque),1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);

                    char vacio = '0';
                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,sb.s_bm_inode_start,SEEK_SET);
                    fwrite(&vacio,sb.s_inodes_count,1,Particion);
                    fseek(Particion,sb.s_bm_block_start,SEEK_SET);
                    fwrite(&vacio,sb.s_blocks_count,1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);
                }else if(disco->type.toLower() == "full"){
                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,part3.part_start,SEEK_SET);
                    fread(&sb,sizeof(SuperBloque),1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);

                    char vacio = '0';
                    char vacio2 = '\0';
                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,sb.s_bm_inode_start,SEEK_SET);
                    fwrite(&vacio,sb.s_inodes_count,1,Particion);
                    fseek(Particion,sb.s_bm_block_start,SEEK_SET);
                    fwrite(&vacio,sb.s_blocks_count,1,Particion);
                    fseek(Particion,sb.s_inode_start,SEEK_SET);
                    fwrite(&vacio2,sb.s_inodes_count * sizeof(inodoT),1,Particion);
                    fseek(Particion,sb.s_block_start,SEEK_SET);
                    fwrite(&vacio2,sb.s_blocks_count * 64,1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);
                }

                //JOURNALING SI ES EXT 3
                if(sb.s_filesystem_type == 3){
                    strcpy(vitacora.Comando,"RaizYUsers.txt");
                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,part3.part_start + sizeof (sb),SEEK_SET);
                    fwrite(&vitacora,sizeof(vitacora),1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);
                }
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

                cout<<"Formateo De Particion Lista :D"<<endl;
            }else if(nombre4 == nombreP){
                SuperBloque sb;
                FILE *Particion;
                TablaInodos inodoT;
                Journaling vitacora;
                //ASIGNAR ESTRUCTURA EXT2 O EXT3
                if(disco->fs.toLower() == "2fs"){
                    int n = (part4.part_size - sizeof (sb)) / (sizeof (inodoT) + 196);
                    n = floor(n);
                    sb.s_filesystem_type = 2;
                    sb.s_inodes_count = n;
                    sb.s_blocks_count = n*3;
                    sb.s_free_blocks_count = (n*3)-2;
                    sb.s_free_inodes_count = n-2;
                    sb.s_mtime = time(NULL);
                    sb.s_umtime = time(NULL);
                    sb.s_mnt_count = 1;
                    sb.s_magic = 0xEF53;
                    sb.s_inode_size = sizeof (inodoT);
                    sb.s_block_size = 64;
                    sb.s_first_ino = part4.part_start + sizeof (sb) + n + (n*3) + sizeof (TablaInodos) + sizeof (TablaInodos);
                    sb.s_first_blo = part4.part_start + sizeof (sb) + n + (n*3) + (n*sizeof (inodoT)) + 128;
                    sb.s_bm_inode_start = part4.part_start + sizeof (sb);
                    sb.s_bm_block_start = part4.part_start + sizeof (sb) + n;
                    sb.s_inode_start = part4.part_start + sizeof (sb) + n + (n*3);
                    sb.s_block_start = part4.part_start + sizeof (sb) + n + (n*3) + (n*sizeof (inodoT));

                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,part4.part_start,SEEK_SET);
                    fwrite(&sb,sizeof(SuperBloque),1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);
                }else if(disco->fs.toLower() == "3fs"){
                    int n = (part4.part_size - sizeof (sb)) / (sizeof (vitacora) + sizeof (inodoT) + 196);
                    n = floor(n);
                    sb.s_filesystem_type = 3;
                    sb.s_inodes_count = n;
                    sb.s_blocks_count = n*3;
                    sb.s_free_blocks_count = (n*3)-2;
                    sb.s_free_inodes_count = n-2;
                    sb.s_mtime = time(NULL);
                    sb.s_umtime = time(NULL);
                    sb.s_mnt_count = 1;
                    sb.s_magic = 0xEF53;
                    sb.s_inode_size = sizeof (inodoT);
                    sb.s_block_size = 64;
                    sb.s_first_ino = part4.part_start + sizeof (sb) + (n* sizeof (vitacora)) + n + (n*3) + sizeof (TablaInodos) + sizeof (TablaInodos);
                    sb.s_first_blo = part4.part_start + sizeof (sb) + (n* sizeof (vitacora)) + n + (n*3) + (n*sizeof (inodoT)) + 128;
                    sb.s_bm_inode_start = part4.part_start + sizeof (sb) + (n* sizeof (vitacora));
                    sb.s_bm_block_start = part4.part_start + sizeof (sb) + (n* sizeof (vitacora)) + n;
                    sb.s_inode_start = part4.part_start + sizeof (sb) + (n* sizeof (vitacora)) + n + (n*3);
                    sb.s_block_start = part4.part_start + sizeof (sb) + (n* sizeof (vitacora)) + n + (n*3) + (n*sizeof (inodoT));

                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,part4.part_start,SEEK_SET);
                    fwrite(&sb,sizeof(SuperBloque),1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);
                }
                //REALIZAR FORMATEO
                if(disco->type.toLower() == "fast"){
                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,part4.part_start,SEEK_SET);
                    fread(&sb,sizeof(SuperBloque),1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);

                    char vacio = '0';
                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,sb.s_bm_inode_start,SEEK_SET);
                    fwrite(&vacio,sb.s_inodes_count,1,Particion);
                    fseek(Particion,sb.s_bm_block_start,SEEK_SET);
                    fwrite(&vacio,sb.s_blocks_count,1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);
                }else if(disco->type.toLower() == "full"){
                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,part4.part_start,SEEK_SET);
                    fread(&sb,sizeof(SuperBloque),1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);

                    char vacio = '\0';
                    char vacio2 = '\0';
                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,sb.s_bm_inode_start,SEEK_SET);
                    fwrite(&vacio,sb.s_inodes_count,1,Particion);
                    fseek(Particion,sb.s_bm_block_start,SEEK_SET);
                    fwrite(&vacio,sb.s_blocks_count,1,Particion);
                    fseek(Particion,sb.s_inode_start,SEEK_SET);
                    fwrite(&vacio2,sb.s_inodes_count * sizeof(inodoT),1,Particion);
                    fseek(Particion,sb.s_block_start,SEEK_SET);
                    fwrite(&vacio2,sb.s_blocks_count * 64,1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);
                }

                //JOURNALING SI ES EXT 3
                if(sb.s_filesystem_type == 3){
                    strcpy(vitacora.Comando,"RaizYUsers.txt");
                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,part4.part_start + sizeof (sb),SEEK_SET);
                    fwrite(&vitacora,sizeof(vitacora),1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);
                }
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

                cout<<"Formateo De Particion Lista :D"<<endl;
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
                            cout<<"Configurando Sistema De Archivos Para: "<<nombreP.toStdString().c_str()<<endl;
                            SuperBloque sb;
                            FILE *Particion;
                            TablaInodos inodoT;
                            Journaling vitacora;
                            //ASIGNAR ESTRUCTURA EXT2 O EXT3
                            if(disco->fs.toLower() == "2fs"){
                                //SOBRE ESCRIBIR SITEMA EXT2 SOBRE PARTICION EBR
                                int n = (ebr.part_size - sizeof (sb)) / (sizeof (inodoT) + 196);
                                n = floor(n);
                                sb.s_filesystem_type = 2;
                                sb.s_inodes_count = n;
                                sb.s_blocks_count = n*3;
                                sb.s_free_blocks_count = (n*3)-2;
                                sb.s_free_inodes_count = n-2;
                                sb.s_mtime = time(NULL);
                                sb.s_umtime = time(NULL);
                                sb.s_mnt_count = 1;
                                sb.s_magic = 0xEF53;
                                sb.s_inode_size = sizeof (inodoT);
                                sb.s_block_size = 64;
                                sb.s_first_ino = ebr.part_start + sizeof (ebr) + sizeof (sb) + n + (n*3) + sizeof (TablaInodos) + sizeof (TablaInodos);
                                sb.s_first_blo = ebr.part_start + sizeof (ebr) + sizeof (sb) + n + (n*3) + (n*sizeof (inodoT)) + 128;
                                sb.s_bm_inode_start = ebr.part_start + sizeof (ebr) + sizeof (sb);
                                sb.s_bm_block_start = ebr.part_start + sizeof (ebr) + n;
                                sb.s_inode_start = ebr.part_start + sizeof (ebr) + n + (n*3);
                                sb.s_block_start = ebr.part_start + sizeof (ebr) + n + (n*3) + (n*sizeof (inodoT));

                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,ebr.part_start + sizeof (ebr),SEEK_SET);
                                fwrite(&sb,sizeof(SuperBloque),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);
                                cout<<"Sistema De Archivos Ext2 Creado Con Exito: "<<endl;
                            }else if(disco->fs.toLower() == "3fs"){
                                //SOBRE ESCRIBIR SITEMA EXT3 SOBRE PARTICION EBR
                                int n = (ebr.part_size - sizeof (sb)) / (sizeof (vitacora) + sizeof (inodoT) + 196);
                                n = floor(n);
                                sb.s_filesystem_type = 3;
                                sb.s_inodes_count = n;
                                sb.s_blocks_count = n*3;
                                sb.s_free_blocks_count = (n*3)-2;
                                sb.s_free_inodes_count = n-2;
                                sb.s_mtime = time(NULL);
                                sb.s_umtime = time(NULL);
                                sb.s_mnt_count = 1;
                                sb.s_magic = 0xEF53;
                                sb.s_inode_size = sizeof (inodoT);
                                sb.s_block_size = 64;
                                sb.s_first_ino = ebr.part_start + sizeof (ebr) + sizeof (sb) + sizeof (sb) + (n* sizeof (vitacora)) + n + (n*3) + sizeof (TablaInodos) + sizeof (TablaInodos);
                                sb.s_first_blo = ebr.part_start + sizeof (ebr) + sizeof (sb) + sizeof (sb) + (n* sizeof (vitacora)) + n + (n*3) + (n*sizeof (inodoT)) + 128;
                                sb.s_bm_inode_start = ebr.part_start + sizeof (ebr) + sizeof (sb) + (n* sizeof (vitacora));
                                sb.s_bm_block_start = ebr.part_start + sizeof (ebr) + sizeof (sb) + (n* sizeof (vitacora)) + n;
                                sb.s_inode_start = ebr.part_start + sizeof (ebr) + sizeof (sb) + (n* sizeof (vitacora)) + n + (n*3);
                                sb.s_block_start = ebr.part_start + sizeof (ebr) + sizeof (sb) + (n* sizeof (vitacora)) + n + (n*3) + (n*sizeof (inodoT));

                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,ebr.part_start + sizeof (ebr),SEEK_SET);
                                fwrite(&sb,sizeof(SuperBloque),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);
                                cout<<"Sistema De Archivos Ext3 Creado Con Exito: "<<endl;
                            }
                            //REALIZAR FORMATEO
                            if(disco->type.toLower() == "fast"){
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,ebr.part_start,SEEK_SET);
                                fread(&sb,sizeof(SuperBloque),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);

                                char vacio = '0';
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,sb.s_bm_inode_start,SEEK_SET);
                                fwrite(&vacio,sb.s_inodes_count,1,Particion);
                                fseek(Particion,sb.s_bm_block_start,SEEK_SET);
                                fwrite(&vacio,sb.s_blocks_count,1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);
                            }else if(disco->type.toLower() == "full"){
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,ebr.part_start,SEEK_SET);
                                fread(&sb,sizeof(SuperBloque),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);

                                char vacio = '0';
                                char vacio2 = '\0';
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,sb.s_bm_inode_start,SEEK_SET);
                                fwrite(&vacio,sb.s_inodes_count,1,Particion);
                                fseek(Particion,sb.s_bm_block_start,SEEK_SET);
                                fwrite(&vacio,sb.s_blocks_count,1,Particion);
                                fseek(Particion,sb.s_inode_start,SEEK_SET);
                                fwrite(&vacio2,sb.s_inodes_count * sizeof(inodoT),1,Particion);
                                fseek(Particion,sb.s_block_start,SEEK_SET);
                                fwrite(&vacio2,sb.s_blocks_count * 64,1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);
                            }

                            //JOURNALING SI ES EXT 3
                            if(sb.s_filesystem_type == 3){
                                strcpy(vitacora.Comando,"RaizYUsers.txt");
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,ebr.part_start + sizeof (ebr) + sizeof (sb),SEEK_SET);
                                fwrite(&vitacora,sizeof(vitacora),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);
                            }
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

                            cout<<"Formateo De Particion Lista :D"<<endl;
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
                            cout<<"Configurando Sistema De Archivos Para: "<<nombreP.toStdString().c_str()<<endl;
                            SuperBloque sb;
                            FILE *Particion;
                            TablaInodos inodoT;
                            Journaling vitacora;
                            //ASIGNAR ESTRUCTURA EXT2 O EXT3
                            if(disco->fs.toLower() == "2fs"){
                                //SOBRE ESCRIBIR SITEMA EXT2 SOBRE PARTICION EBR
                                int n = (ebr.part_size - sizeof (sb)) / (sizeof (inodoT) + 196);
                                n = floor(n);
                                sb.s_filesystem_type = 2;
                                sb.s_inodes_count = n;
                                sb.s_blocks_count = n*3;
                                sb.s_free_blocks_count = (n*3)-2;
                                sb.s_free_inodes_count = n-2;
                                sb.s_mtime = time(NULL);
                                sb.s_umtime = time(NULL);
                                sb.s_mnt_count = 1;
                                sb.s_magic = 0xEF53;
                                sb.s_inode_size = sizeof (inodoT);
                                sb.s_block_size = 64;
                                sb.s_first_ino = ebr.part_start + sizeof (ebr) + sizeof (sb) + n + (n*3) + sizeof (TablaInodos) + sizeof (TablaInodos);
                                sb.s_first_blo = ebr.part_start + sizeof (ebr) + sizeof (sb) + n + (n*3) + (n*sizeof (inodoT)) + 128;
                                sb.s_bm_inode_start = ebr.part_start + sizeof (ebr) + sizeof (sb);
                                sb.s_bm_block_start = ebr.part_start + sizeof (ebr) + n;
                                sb.s_inode_start = ebr.part_start + sizeof (ebr) + n + (n*3);
                                sb.s_block_start = ebr.part_start + sizeof (ebr) + n + (n*3) + (n*sizeof (inodoT));

                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,ebr.part_start + sizeof (ebr),SEEK_SET);
                                fwrite(&sb,sizeof(SuperBloque),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);
                                cout<<"Sistema De Archivos Ext2 Creado Con Exito: "<<endl;
                            }else if(disco->fs.toLower() == "3fs"){
                                //SOBRE ESCRIBIR SITEMA EXT3 SOBRE PARTICION EBR
                                int n = (ebr.part_size - sizeof (sb)) / (sizeof (vitacora) + sizeof (inodoT) + 196);
                                n = floor(n);
                                sb.s_filesystem_type = 3;
                                sb.s_inodes_count = n;
                                sb.s_blocks_count = n*3;
                                sb.s_free_blocks_count = (n*3)-2;
                                sb.s_free_inodes_count = n-2;
                                sb.s_mtime = time(NULL);
                                sb.s_umtime = time(NULL);
                                sb.s_mnt_count = 1;
                                sb.s_magic = 0xEF53;
                                sb.s_inode_size = sizeof (inodoT);
                                sb.s_block_size = 64;
                                sb.s_first_ino = ebr.part_start + sizeof (ebr) + sizeof (sb) + sizeof (sb) + (n* sizeof (vitacora)) + n + (n*3) + sizeof (TablaInodos) + sizeof (TablaInodos);
                                sb.s_first_blo = ebr.part_start + sizeof (ebr) + sizeof (sb) + sizeof (sb) + (n* sizeof (vitacora)) + n + (n*3) + (n*sizeof (inodoT)) + 128;
                                sb.s_bm_inode_start = ebr.part_start + sizeof (ebr) + sizeof (sb) + (n* sizeof (vitacora));
                                sb.s_bm_block_start = ebr.part_start + sizeof (ebr) + sizeof (sb) + (n* sizeof (vitacora)) + n;
                                sb.s_inode_start = ebr.part_start + sizeof (ebr) + sizeof (sb) + (n* sizeof (vitacora)) + n + (n*3);
                                sb.s_block_start = ebr.part_start + sizeof (ebr) + sizeof (sb) + (n* sizeof (vitacora)) + n + (n*3) + (n*sizeof (inodoT));

                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,ebr.part_start + sizeof (ebr),SEEK_SET);
                                fwrite(&sb,sizeof(SuperBloque),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);
                                cout<<"Sistema De Archivos Ext3 Creado Con Exito: "<<endl;
                            }
                            //REALIZAR FORMATEO
                            if(disco->type.toLower() == "fast"){
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,ebr.part_start,SEEK_SET);
                                fread(&sb,sizeof(SuperBloque),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);

                                char vacio = '0';
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,sb.s_bm_inode_start,SEEK_SET);
                                fwrite(&vacio,sb.s_inodes_count,1,Particion);
                                fseek(Particion,sb.s_bm_block_start,SEEK_SET);
                                fwrite(&vacio,sb.s_blocks_count,1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);
                            }else if(disco->type.toLower() == "full"){
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,ebr.part_start,SEEK_SET);
                                fread(&sb,sizeof(SuperBloque),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);

                                char vacio = '0';
                                char vacio2 = '\0';
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,sb.s_bm_inode_start,SEEK_SET);
                                fwrite(&vacio,sb.s_inodes_count,1,Particion);
                                fseek(Particion,sb.s_bm_block_start,SEEK_SET);
                                fwrite(&vacio,sb.s_blocks_count,1,Particion);
                                fseek(Particion,sb.s_inode_start,SEEK_SET);
                                fwrite(&vacio2,sb.s_inodes_count * sizeof(inodoT),1,Particion);
                                fseek(Particion,sb.s_block_start,SEEK_SET);
                                fwrite(&vacio2,sb.s_blocks_count * 64,1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);
                            }

                            //JOURNALING SI ES EXT 3
                            if(sb.s_filesystem_type == 3){
                                strcpy(vitacora.Comando,"RaizYUsers.txt");
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,ebr.part_start + sizeof (ebr) + sizeof (sb),SEEK_SET);
                                fwrite(&vitacora,sizeof(vitacora),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);
                            }
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

                            cout<<"Formateo De Particion Lista :D"<<endl;
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
                            cout<<"Configurando Sistema De Archivos Para: "<<nombreP.toStdString().c_str()<<endl;
                            SuperBloque sb;
                            FILE *Particion;
                            TablaInodos inodoT;
                            Journaling vitacora;
                            //ASIGNAR ESTRUCTURA EXT2 O EXT3
                            if(disco->fs.toLower() == "2fs"){
                                //SOBRE ESCRIBIR SITEMA EXT2 SOBRE PARTICION EBR
                                int n = (ebr.part_size - sizeof (sb)) / (sizeof (inodoT) + 196);
                                n = floor(n);
                                sb.s_filesystem_type = 2;
                                sb.s_inodes_count = n;
                                sb.s_blocks_count = n*3;
                                sb.s_free_blocks_count = (n*3)-2;
                                sb.s_free_inodes_count = n-2;
                                sb.s_mtime = time(NULL);
                                sb.s_umtime = time(NULL);
                                sb.s_mnt_count = 1;
                                sb.s_magic = 0xEF53;
                                sb.s_inode_size = sizeof (inodoT);
                                sb.s_block_size = 64;
                                sb.s_first_ino = ebr.part_start + sizeof (ebr) + sizeof (sb) + n + (n*3) + sizeof (TablaInodos) + sizeof (TablaInodos);
                                sb.s_first_blo = ebr.part_start + sizeof (ebr) + sizeof (sb) + n + (n*3) + (n*sizeof (inodoT)) + 128;
                                sb.s_bm_inode_start = ebr.part_start + sizeof (ebr) + sizeof (sb);
                                sb.s_bm_block_start = ebr.part_start + sizeof (ebr) + n;
                                sb.s_inode_start = ebr.part_start + sizeof (ebr) + n + (n*3);
                                sb.s_block_start = ebr.part_start + sizeof (ebr) + n + (n*3) + (n*sizeof (inodoT));

                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,ebr.part_start + sizeof (ebr),SEEK_SET);
                                fwrite(&sb,sizeof(SuperBloque),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);
                                cout<<"Sistema De Archivos Ext2 Creado Con Exito: "<<endl;
                            }else if(disco->fs.toLower() == "3fs"){
                                //SOBRE ESCRIBIR SITEMA EXT3 SOBRE PARTICION EBR
                                int n = (ebr.part_size - sizeof (sb)) / (sizeof (vitacora) + sizeof (inodoT) + 196);
                                n = floor(n);
                                sb.s_filesystem_type = 3;
                                sb.s_inodes_count = n;
                                sb.s_blocks_count = n*3;
                                sb.s_free_blocks_count = (n*3)-2;
                                sb.s_free_inodes_count = n-2;
                                sb.s_mtime = time(NULL);
                                sb.s_umtime = time(NULL);
                                sb.s_mnt_count = 1;
                                sb.s_magic = 0xEF53;
                                sb.s_inode_size = sizeof (inodoT);
                                sb.s_block_size = 64;
                                sb.s_first_ino = ebr.part_start + sizeof (ebr) + sizeof (sb) + sizeof (sb) + (n* sizeof (vitacora)) + n + (n*3) + sizeof (TablaInodos) + sizeof (TablaInodos);
                                sb.s_first_blo = ebr.part_start + sizeof (ebr) + sizeof (sb) + sizeof (sb) + (n* sizeof (vitacora)) + n + (n*3) + (n*sizeof (inodoT)) + 128;
                                sb.s_bm_inode_start = ebr.part_start + sizeof (ebr) + sizeof (sb) + (n* sizeof (vitacora));
                                sb.s_bm_block_start = ebr.part_start + sizeof (ebr) + sizeof (sb) + (n* sizeof (vitacora)) + n;
                                sb.s_inode_start = ebr.part_start + sizeof (ebr) + sizeof (sb) + (n* sizeof (vitacora)) + n + (n*3);
                                sb.s_block_start = ebr.part_start + sizeof (ebr) + sizeof (sb) + (n* sizeof (vitacora)) + n + (n*3) + (n*sizeof (inodoT));

                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,ebr.part_start + sizeof (ebr),SEEK_SET);
                                fwrite(&sb,sizeof(SuperBloque),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);
                                cout<<"Sistema De Archivos Ext3 Creado Con Exito: "<<endl;
                            }
                            //REALIZAR FORMATEO
                            if(disco->type.toLower() == "fast"){
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,ebr.part_start,SEEK_SET);
                                fread(&sb,sizeof(SuperBloque),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);

                                char vacio = '0';
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,sb.s_bm_inode_start,SEEK_SET);
                                fwrite(&vacio,sb.s_inodes_count,1,Particion);
                                fseek(Particion,sb.s_bm_block_start,SEEK_SET);
                                fwrite(&vacio,sb.s_blocks_count,1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);
                            }else if(disco->type.toLower() == "full"){
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,ebr.part_start,SEEK_SET);
                                fread(&sb,sizeof(SuperBloque),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);

                                char vacio = '0';
                                char vacio2 = '\0';
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,sb.s_bm_inode_start,SEEK_SET);
                                fwrite(&vacio,sb.s_inodes_count,1,Particion);
                                fseek(Particion,sb.s_bm_block_start,SEEK_SET);
                                fwrite(&vacio,sb.s_blocks_count,1,Particion);
                                fseek(Particion,sb.s_inode_start,SEEK_SET);
                                fwrite(&vacio2,sb.s_inodes_count * sizeof(inodoT),1,Particion);
                                fseek(Particion,sb.s_block_start,SEEK_SET);
                                fwrite(&vacio2,sb.s_blocks_count * 64,1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);
                            }

                            //JOURNALING SI ES EXT 3
                            if(sb.s_filesystem_type == 3){
                                strcpy(vitacora.Comando,"RaizYUsers.txt");
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,ebr.part_start + sizeof (ebr) + sizeof (sb),SEEK_SET);
                                fwrite(&vitacora,sizeof(vitacora),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);
                            }
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

                            cout<<"Formateo De Particion Lista :D"<<endl;
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
                            cout<<"Configurando Sistema De Archivos Para: "<<nombreP.toStdString().c_str()<<endl;
                            SuperBloque sb;
                            FILE *Particion;
                            TablaInodos inodoT;
                            Journaling vitacora;
                            //ASIGNAR ESTRUCTURA EXT2 O EXT3
                            if(disco->fs.toLower() == "2fs"){
                                //SOBRE ESCRIBIR SITEMA EXT2 SOBRE PARTICION EBR
                                int n = (ebr.part_size - sizeof (sb)) / (sizeof (inodoT) + 196);
                                n = floor(n);
                                sb.s_filesystem_type = 2;
                                sb.s_inodes_count = n;
                                sb.s_blocks_count = n*3;
                                sb.s_free_blocks_count = (n*3)-2;
                                sb.s_free_inodes_count = n-2;
                                sb.s_mtime = time(NULL);
                                sb.s_umtime = time(NULL);
                                sb.s_mnt_count = 1;
                                sb.s_magic = 0xEF53;
                                sb.s_inode_size = sizeof (inodoT);
                                sb.s_block_size = 64;
                                sb.s_first_ino = ebr.part_start + sizeof (ebr) + sizeof (sb) + n + (n*3) + sizeof (TablaInodos) + sizeof (TablaInodos);
                                sb.s_first_blo = ebr.part_start + sizeof (ebr) + sizeof (sb) + n + (n*3) + (n*sizeof (inodoT)) + 128;
                                sb.s_bm_inode_start = ebr.part_start + sizeof (ebr) + sizeof (sb);
                                sb.s_bm_block_start = ebr.part_start + sizeof (ebr) + n;
                                sb.s_inode_start = ebr.part_start + sizeof (ebr) + n + (n*3);
                                sb.s_block_start = ebr.part_start + sizeof (ebr) + n + (n*3) + (n*sizeof (inodoT));

                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,ebr.part_start + sizeof (ebr),SEEK_SET);
                                fwrite(&sb,sizeof(SuperBloque),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);
                                cout<<"Sistema De Archivos Ext2 Creado Con Exito: "<<endl;
                            }else if(disco->fs.toLower() == "3fs"){
                                //SOBRE ESCRIBIR SITEMA EXT3 SOBRE PARTICION EBR
                                int n = (ebr.part_size - sizeof (sb)) / (sizeof (vitacora) + sizeof (inodoT) + 196);
                                n = floor(n);
                                sb.s_filesystem_type = 3;
                                sb.s_inodes_count = n;
                                sb.s_blocks_count = n*3;
                                sb.s_free_blocks_count = (n*3)-2;
                                sb.s_free_inodes_count = n-2;
                                sb.s_mtime = time(NULL);
                                sb.s_umtime = time(NULL);
                                sb.s_mnt_count = 1;
                                sb.s_magic = 0xEF53;
                                sb.s_inode_size = sizeof (inodoT);
                                sb.s_block_size = 64;
                                sb.s_first_ino = ebr.part_start + sizeof (ebr) + sizeof (sb) + sizeof (sb) + (n* sizeof (vitacora)) + n + (n*3) + sizeof (TablaInodos) + sizeof (TablaInodos);
                                sb.s_first_blo = ebr.part_start + sizeof (ebr) + sizeof (sb) + sizeof (sb) + (n* sizeof (vitacora)) + n + (n*3) + (n*sizeof (inodoT)) + 128;
                                sb.s_bm_inode_start = ebr.part_start + sizeof (ebr) + sizeof (sb) + (n* sizeof (vitacora));
                                sb.s_bm_block_start = ebr.part_start + sizeof (ebr) + sizeof (sb) + (n* sizeof (vitacora)) + n;
                                sb.s_inode_start = ebr.part_start + sizeof (ebr) + sizeof (sb) + (n* sizeof (vitacora)) + n + (n*3);
                                sb.s_block_start = ebr.part_start + sizeof (ebr) + sizeof (sb) + (n* sizeof (vitacora)) + n + (n*3) + (n*sizeof (inodoT));

                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,ebr.part_start + sizeof (ebr),SEEK_SET);
                                fwrite(&sb,sizeof(SuperBloque),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);
                                cout<<"Sistema De Archivos Ext3 Creado Con Exito: "<<endl;
                            }
                            //REALIZAR FORMATEO
                            if(disco->type.toLower() == "fast"){
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,ebr.part_start,SEEK_SET);
                                fread(&sb,sizeof(SuperBloque),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);

                                char vacio = '0';
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,sb.s_bm_inode_start,SEEK_SET);
                                fwrite(&vacio,sb.s_inodes_count,1,Particion);
                                fseek(Particion,sb.s_bm_block_start,SEEK_SET);
                                fwrite(&vacio,sb.s_blocks_count,1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);
                            }else if(disco->type.toLower() == "full"){
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,ebr.part_start,SEEK_SET);
                                fread(&sb,sizeof(SuperBloque),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);

                                char vacio = '0';
                                char vacio2 = '\0';
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,sb.s_bm_inode_start,SEEK_SET);
                                fwrite(&vacio,sb.s_inodes_count,1,Particion);
                                fseek(Particion,sb.s_bm_block_start,SEEK_SET);
                                fwrite(&vacio,sb.s_blocks_count,1,Particion);
                                fseek(Particion,sb.s_inode_start,SEEK_SET);
                                fwrite(&vacio2,sb.s_inodes_count * sizeof(inodoT),1,Particion);
                                fseek(Particion,sb.s_block_start,SEEK_SET);
                                fwrite(&vacio2,sb.s_blocks_count * 64,1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);
                            }

                            //JOURNALING SI ES EXT 3
                            if(sb.s_filesystem_type == 3){
                                strcpy(vitacora.Comando,"RaizYUsers.txt");
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,ebr.part_start + sizeof (ebr) + sizeof (sb),SEEK_SET);
                                fwrite(&vitacora,sizeof(vitacora),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);
                            }
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

                            cout<<"Formateo De Particion Lista :D"<<endl;
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
            cout<<"No Hay Montada Particion Con Id: "<<disco->id.toStdString().c_str()<<endl;
        }
    }else{
        cout<<"ID No Ingresada, Incorrecto"<<endl;
    }
    disco->id = "";
    disco->type = "";
    disco->fs = "";
}
