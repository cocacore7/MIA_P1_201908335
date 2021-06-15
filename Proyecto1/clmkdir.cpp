#include "clmkdir.h"
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
#include <clsesion.h>
//-------------------------------------------

using namespace std;

clmkdir::clmkdir()
{

}

void clmkdir::mostrarDatos(clmkdir *carpeta){
    cout<<"----------------------CrearCarpeta--------------------------"<<endl;
    cout<<"-El Path Es: "<<carpeta->path.toStdString().c_str()<<endl;
    cout<<"-El P Es: "<<carpeta->P.toStdString().c_str()<<endl;
    if(carpeta->path != ""){
        if(sesion.usuario != ""){
            ListaM aux = sesion.activaP;
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

            QStringList caminoC = carpeta->path.split("/");
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

                //BUSCAR SI YA EXISTE INGRESADA

                TablaInodos inodoT;
                int inicio = sb.s_inode_start;
                BloquesApuntadores apuntador;
                BloquesArchivos archivo;
                BloquesCarpetas carpeta;
                bool encontrado = false;
                for(int z = 1;z<caminoC.length();z++){
                    inicio = sb.s_inode_start;
                    encontrado = false;
                    while (inicio < sb.s_block_start) {
                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                        fseek(Particion,inicio,SEEK_SET);
                        fread(&inodoT,sizeof(inodoT),1,Particion);
                        fseek(Particion,0,SEEK_SET);
                        fclose(Particion);
                        inicio+=sizeof(inodoT);
                        if(inodoT.i_type == '\0'){break;}

                        for(int x = 0;x<15;x++){
                            if(inodoT.i_block[x] != -1){
                                for(int x=0;x<4;x++){
                                    carpeta.b_content[x].b_inodo = -1;
                                    memset(carpeta.b_content[x].b_name,0,12);
                                }
                                memset(archivo.b_content,0,64);
                                for(int x=0;x<16;x++){
                                    apuntador.b_pointers[x] = -1;
                                }
                                if(x == 14){
                                    //Apuntador triple
                                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                    fseek(Particion,sb.s_block_start + (inodoT.i_block[x]*64),SEEK_SET);
                                    fread(&apuntador,sizeof(apuntador),1,Particion);
                                    fseek(Particion,0,SEEK_SET);
                                    fclose(Particion);

                                }else if(x==13){
                                    //Apuntador doble
                                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                    fseek(Particion,sb.s_block_start + (inodoT.i_block[x]*64),SEEK_SET);
                                    fread(&apuntador,sizeof(apuntador),1,Particion);
                                    fseek(Particion,0,SEEK_SET);
                                    fclose(Particion);

                                }else if(x==12){
                                    //Apuntador simple
                                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                    fseek(Particion,sb.s_block_start + (inodoT.i_block[x]*64),SEEK_SET);
                                    fread(&apuntador,sizeof(apuntador),1,Particion);
                                    fseek(Particion,0,SEEK_SET);
                                    fclose(Particion);

                                }else{
                                    if(inodoT.i_type == '0'){
                                        //Carpeta
                                        //donde empiezan bloques + (intapuntador * 64)
                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_block_start + (inodoT.i_block[x]*64),SEEK_SET);
                                        fread(&carpeta,sizeof(carpeta),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);

                                        for(int y=0;y<4;y++){
                                            if(carpeta.b_content[y].b_inodo != -1){
                                                if((caminoC.length()-1) == z){
                                                    QString nombre(carpeta.b_content[y].b_name);
                                                    if(caminoC[z] == nombre){
                                                        encontrado = true;
                                                    }else{
                                                        if(encontrado){
                                                            encontrado=false;
                                                        }
                                                    }
                                                }else{
                                                    QString nombre(carpeta.b_content[y].b_name);
                                                    if(caminoC[z] == nombre){
                                                        encontrado = true;
                                                    }else{encontrado = false;}
                                                }

                                            }
                                            if(encontrado){break;}
                                        }
                                    }
                                }
                            }
                            if(encontrado){break;}
                        }
                        if(encontrado){break;}
                    }
                }

                bool ingresado = false;
                if(!encontrado){
                    //IngresarCarpetaNueva
                    inicio = sb.s_inode_start;
                    while (inicio < sb.s_block_start) {
                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                        fseek(Particion,inicio,SEEK_SET);
                        fread(&inodoT,sizeof(inodoT),1,Particion);
                        fseek(Particion,0,SEEK_SET);
                        fclose(Particion);
                        inicio+=sizeof(inodoT);
                        if(inodoT.i_type == '\0'){break;}

                        for(int x = 0;x<15;x++){
                            if(inodoT.i_block[x] != -1){
                                for(int x=0;x<4;x++){
                                    carpeta.b_content[x].b_inodo = -1;
                                    memset(carpeta.b_content[x].b_name,0,12);
                                }
                                memset(archivo.b_content,0,64);
                                for(int x=0;x<16;x++){
                                    apuntador.b_pointers[x] = -1;
                                }
                                if(x == 14){
                                    //Apuntador triple
                                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                    fseek(Particion,sb.s_block_start + (inodoT.i_block[x]*64),SEEK_SET);
                                    fread(&apuntador,sizeof(apuntador),1,Particion);
                                    fseek(Particion,0,SEEK_SET);
                                    fclose(Particion);

                                }else if(x==13){
                                    //Apuntador doble
                                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                    fseek(Particion,sb.s_block_start + (inodoT.i_block[x]*64),SEEK_SET);
                                    fread(&apuntador,sizeof(apuntador),1,Particion);
                                    fseek(Particion,0,SEEK_SET);
                                    fclose(Particion);

                                }else if(x==12){
                                    //Apuntador simple
                                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                    fseek(Particion,sb.s_block_start + (inodoT.i_block[x]*64),SEEK_SET);
                                    fread(&apuntador,sizeof(apuntador),1,Particion);
                                    fseek(Particion,0,SEEK_SET);
                                    fclose(Particion);

                                }else{
                                    if(inodoT.i_type == '0'){
                                        //Carpeta
                                        //donde empiezan bloques + (intapuntador * 64)
                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_block_start + (inodoT.i_block[x]*64),SEEK_SET);
                                        fread(&carpeta,sizeof(carpeta),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);

                                        for(int y=0;y<4;y++){
                                            if(carpeta.b_content[y].b_inodo == -1){
                                                TablaInodos nuevoI;
                                                nuevoI.i_uid = sesion.uid;
                                                nuevoI.i_gid = sesion.gid;
                                                nuevoI.i_size = sizeof (TablaInodos);
                                                nuevoI.i_atime = time(NULL);
                                                nuevoI.i_ctime = time(NULL);
                                                nuevoI.i_mtime = time(NULL);
                                                for(int a = 0;a<15;a++){
                                                    nuevoI.i_block[a] = -1;
                                                }
                                                nuevoI.i_type = '0';
                                                nuevoI.i_perm = sesion.perm;
                                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                                fseek(Particion,sb.s_first_ino,SEEK_SET);
                                                fwrite(&nuevoI,sizeof(nuevoI),1,Particion);
                                                fseek(Particion,0,SEEK_SET);
                                                fclose(Particion);

                                                BloquesCarpetas nuevaC;
                                                for(int a=0;a<4;a++){
                                                    nuevaC.b_content[a].b_inodo = -1;
                                                    memset(nuevaC.b_content[a].b_name,0,12);
                                                }
                                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                                fseek(Particion,sb.s_first_blo,SEEK_SET);
                                                fwrite(&nuevaC,sizeof(nuevaC),1,Particion);
                                                fseek(Particion,0,SEEK_SET);
                                                fclose(Particion);

                                                char bit = 'a';
                                                int inicio2 = sb.s_bm_inode_start;
                                                while (inicio2 <= (sb.s_bm_inode_start + sb.s_inodes_count)) {
                                                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                                    fseek(Particion,inicio2,SEEK_SET);
                                                    fread(&bit,sizeof(bit),1,Particion);
                                                    fseek(Particion,0,SEEK_SET);
                                                    fclose(Particion);
                                                    if(bit!='1'){
                                                        bit = '1';
                                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                                        fseek(Particion,inicio2,SEEK_SET);
                                                        fwrite(&bit,sizeof(bit),1,Particion);
                                                        fseek(Particion,0,SEEK_SET);
                                                        fclose(Particion);
                                                        break;
                                                    }
                                                    inicio2+=sizeof(bit);
                                                }

                                                bit = 'a';
                                                inicio2 = sb.s_bm_block_start;
                                                while (inicio2 <= (sb.s_bm_block_start + sb.s_blocks_count)) {
                                                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                                    fseek(Particion,inicio2,SEEK_SET);
                                                    fread(&bit,sizeof(bit),1,Particion);
                                                    fseek(Particion,0,SEEK_SET);
                                                    fclose(Particion);
                                                    if(bit!='1'){
                                                        bit = '1';
                                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                                        fseek(Particion,inicio2,SEEK_SET);
                                                        fwrite(&bit,sizeof(bit),1,Particion);
                                                        fseek(Particion,0,SEEK_SET);
                                                        fclose(Particion);
                                                        break;
                                                    }
                                                    inicio2+=sizeof(bit);
                                                }

                                                sb.s_first_blo += 64;
                                                sb.s_first_ino += sizeof (TablaInodos);
                                                sb.s_free_blocks_count -=1;
                                                sb.s_free_inodes_count -=1;
                                                strcpy(carpeta.b_content[y].b_name,caminoC[caminoC.length() - 1].toStdString().c_str());
                                                cout<<"Carpeta Ingresada Con Exito :D"<<endl;
                                                ingresado = true;
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                            if(ingresado){break;}
                        }
                        if(ingresado){break;}
                    }
                }else{
                    cout<<"La Carpeta Solicitada Ya Existe"<<endl;
                }
            }else if(nombre2 == nombreP){
                SuperBloque sb;
                FILE *Particion;
                //OBTENER SUPER BLOQUE
                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                fseek(Particion,part2.part_start,SEEK_SET);
                fread(&sb,sizeof(sb),1,Particion);
                fseek(Particion,0,SEEK_SET);
                fclose(Particion);

                //BUSCAR SI YA EXISTE INGRESADA

                //INGRESAR EN DADO NO EXISTE EN ESPACIO VACIO
                cout<<"Carpeta Ingresada Con Exito :D"<<endl;
            }else if(nombre3 == nombreP){
                SuperBloque sb;
                FILE *Particion;
                //OBTENER SUPER BLOQUE
                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                fseek(Particion,part3.part_start,SEEK_SET);
                fread(&sb,sizeof(sb),1,Particion);
                fseek(Particion,0,SEEK_SET);
                fclose(Particion);

                //BUSCAR SI YA EXISTE INGRESADA

                //INGRESAR EN DADO NO EXISTE EN ESPACIO VACIO
                cout<<"Carpeta Ingresada Con Exito :D"<<endl;
            }else if(nombre4 == nombreP){
                SuperBloque sb;
                FILE *Particion;
                //OBTENER SUPER BLOQUE
                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                fseek(Particion,part4.part_start,SEEK_SET);
                fread(&sb,sizeof(sb),1,Particion);
                fseek(Particion,0,SEEK_SET);
                fclose(Particion);

                //BUSCAR SI YA EXISTE INGRESADA

                //INGRESAR EN DADO NO EXISTE EN ESPACIO VACIO
                cout<<"Carpeta Ingresada Con Exito :D"<<endl;
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

                            //BUSCAR SI YA EXISTE INGRESADA

                            //INGRESAR EN DADO NO EXISTE EN ESPACIO VACIO
                            cout<<"Carpeta Ingresada Con Exito :D"<<endl;
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

                            //BUSCAR SI YA EXISTE INGRESADA

                            //INGRESAR EN DADO NO EXISTE EN ESPACIO VACIO
                            cout<<"Carpeta Ingresada Con Exito :D"<<endl;
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

                            //BUSCAR SI YA EXISTE INGRESADA

                            //INGRESAR EN DADO NO EXISTE EN ESPACIO VACIO
                            cout<<"Carpeta Ingresada Con Exito :D"<<endl;
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

                            //BUSCAR SI YA EXISTE INGRESADA

                            //INGRESAR EN DADO NO EXISTE EN ESPACIO VACIO
                            cout<<"Carpeta Ingresada Con Exito :D"<<endl;
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
            cout<<"No Hay Una Sesion Iniciada"<<endl;
        }
        if(carpeta->P.toLower() != "-p"){

        }else{

        }
    }else{
        cout<<"No Se Ingreso Una Ruta"<<endl;
    }

    carpeta->path = "";
    carpeta->P = "";
    cout<<"--------------------------------------------------------"<<endl;
}
