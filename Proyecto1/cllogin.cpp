#include "cllogin.h"
#include <QString>
#include <iostream>
#include <QDir>
#include <fstream>
#include <mbrstruct.h>
#include <ebrstruct.h>
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

cllogin::cllogin()
{

}

void cllogin::logear(cllogin *solicitud){
    cout<<"----------------------IniciarSesion--------------------------"<<endl;
    cout<<"-El Id Es: "<<solicitud->id.toStdString().c_str()<<endl;
    cout<<"-El PWD Es: "<<solicitud->pwd.toStdString().c_str()<<endl;
    cout<<"-El USR Es: "<<solicitud->usr.toStdString().c_str()<<endl;
    if(sesion.usuario == ""){
        if(lista.comprobarId(lista.lista,solicitud->id)){
            ListaM listaAux = lista.obtenerNodo(lista.lista,solicitud->id);
            QStringList direcciones = listaAux->ruta.split("/");
            QString ruta = "";
            bool NoCarpeta = false;
            if(direcciones[1] == "home" && direcciones[2] == "oscar"&& direcciones[3] == "archivos"){
                ruta = "/home/oscar/archivos";
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
                        MBR mbr;
                        fread(&mbr,sizeof(MBR),1,Discoo);
                        fseek(Discoo,0,SEEK_SET);
                        fclose(Discoo);

                        //COMPROBAR TIPO DE PARTICION A CREAR
                        struct particion part1;
                        struct particion part2;
                        struct particion part3;
                        struct particion part4;
                        part1 = mbr.mbr_partition_1;
                        part2 = mbr.mbr_partition_2;
                        part3 = mbr.mbr_partition_3;
                        part4 = mbr.mbr_partition_4;
                        QString nombre1(part1.part_name);
                        QString nombre2(part2.part_name);
                        QString nombre3(part3.part_name);
                        QString nombre4(part4.part_name);

                        SuperBloque sb;
                        FILE *Particion;
                        TablaInodos inodoT;
                        BloquesArchivos archivo;
                        EBR ebr;
                        EBR siguiente;
                        FILE* Debr;

                        if(listaAux->nombreP == nombre1){
                            //LEER SUPER BLOQUE
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,part1.part_start,SEEK_SET);
                            fread(&sb,sizeof(sb),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);
                            //LEER USERS.TXT
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_inode_start + sizeof (inodoT),SEEK_SET);
                            fread(&inodoT,sizeof(inodoT),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            QString contenido = "";
                            bool encontrado = false;

                            for(int x = 0; x<15;x++){
                                if(inodoT.i_block[x] == -1){break;}else{
                                    if(x == 12){

                                    }else if(x == 13){

                                    }else if(x == 14){

                                    }else{
                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_block_start + (64 * inodoT.i_block[x]),SEEK_SET);
                                        fread(&archivo,sizeof(archivo),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);

                                        QString contenidotmp(archivo.b_content);
                                        contenido += contenidotmp;
                                    }
                                }
                            }

                            QStringList lineas = contenido.split("\n");
                            for(int y =0;y<lineas.length();y++){
                                QStringList usr_grp = lineas[y].split(",");
                                if(usr_grp.length() == 5){
                                    if(usr_grp[3] == solicitud->usr && usr_grp[4] == solicitud->pwd){
                                        sesion.usuario = usr_grp[3]; sesion.activaP = listaAux; encontrado = true;
                                        cout<<"Sesion Iniciada Con Exito"<<endl;
                                    }
                                }
                                if(encontrado){break;}
                            }

                            if(!encontrado){
                                cout<<"No Se Encontro Al Usuario Con Los Datos Proporcionados"<<endl;
                            }
                        }else if(listaAux->nombreP == nombre2){
                            //LEER SUPER BLOQUE
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,part2.part_start,SEEK_SET);
                            fread(&sb,sizeof(sb),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);
                            //LEER USERS.TXT
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_inode_start + sizeof (inodoT),SEEK_SET);
                            fread(&inodoT,sizeof(inodoT),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            QString contenido = "";
                            bool encontrado = false;

                            for(int x = 0; x<15;x++){
                                if(inodoT.i_block[x] == -1){break;}else{
                                    if(x == 12){

                                    }else if(x == 13){

                                    }else if(x == 14){

                                    }else{
                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_block_start + (sizeof (BloquesArchivos) * (inodoT.i_block[x] + 1)),SEEK_SET);
                                        fread(&archivo,sizeof(BloquesArchivos),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);

                                        QString contenidotmp(archivo.b_content);
                                        contenido += contenidotmp;
                                    }
                                }
                            }

                            QStringList lineas = contenido.split("\n");
                            for(int y =0;y<lineas.length();y++){
                                QStringList usr_grp = lineas[y].split(",");
                                if(usr_grp.length() == 5){
                                    if(usr_grp[3] == solicitud->usr && usr_grp[4] == solicitud->pwd){
                                        sesion.usuario = usr_grp[3]; sesion.activaP = listaAux; encontrado = true;
                                        cout<<"Sesion Iniciada Con Exito"<<endl;
                                    }
                                }
                                if(encontrado){break;}
                            }

                            if(!encontrado){
                                cout<<"No Se Encontro Al Usuario Con Los Datos Proporcionados"<<endl;
                            }

                        }else if(listaAux->nombreP == nombre3){
                            //LEER SUPER BLOQUE
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,part3.part_start,SEEK_SET);
                            fread(&sb,sizeof(sb),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);
                            //LEER USERS.TXT
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_inode_start + sizeof (inodoT),SEEK_SET);
                            fread(&inodoT,sizeof(inodoT),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            QString contenido = "";
                            bool encontrado = false;

                            for(int x = 0; x<15;x++){
                                if(inodoT.i_block[x] == -1){break;}else{
                                    if(x == 12){

                                    }else if(x == 13){

                                    }else if(x == 14){

                                    }else{
                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_block_start + (sizeof (BloquesArchivos) * (inodoT.i_block[x] + 1)),SEEK_SET);
                                        fread(&archivo,sizeof(BloquesArchivos),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);

                                        QString contenidotmp(archivo.b_content);
                                        contenido += contenidotmp;
                                    }
                                }
                            }

                            QStringList lineas = contenido.split("\n");
                            for(int y =0;y<lineas.length();y++){
                                QStringList usr_grp = lineas[y].split(",");
                                if(usr_grp.length() == 5){
                                    if(usr_grp[3] == solicitud->usr && usr_grp[4] == solicitud->pwd){
                                        sesion.usuario = usr_grp[3]; sesion.activaP = listaAux; encontrado = true;
                                        cout<<"Sesion Iniciada Con Exito"<<endl;
                                    }
                                }
                                if(encontrado){break;}
                            }

                            if(!encontrado){
                                cout<<"No Se Encontro Al Usuario Con Los Datos Proporcionados"<<endl;
                            }
                        }else if(listaAux->nombreP == nombre4){
                            //LEER SUPER BLOQUE
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,part4.part_start,SEEK_SET);
                            fread(&sb,sizeof(sb),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);
                            //LEER USERS.TXT
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_inode_start + sizeof (inodoT),SEEK_SET);
                            fread(&inodoT,sizeof(inodoT),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            QString contenido = "";
                            bool encontrado = false;

                            for(int x = 0; x<15;x++){
                                if(inodoT.i_block[x] == -1){break;}else{
                                    if(x == 12){

                                    }else if(x == 13){

                                    }else if(x == 14){

                                    }else{
                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_block_start + (sizeof (BloquesArchivos) * (inodoT.i_block[x] + 1)),SEEK_SET);
                                        fread(&archivo,sizeof(BloquesArchivos),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);

                                        QString contenidotmp(archivo.b_content);
                                        contenido += contenidotmp;
                                    }
                                }
                            }

                            QStringList lineas = contenido.split("\n");
                            for(int y =0;y<lineas.length();y++){
                                QStringList usr_grp = lineas[y].split(",");
                                if(usr_grp.length() == 5){
                                    if(usr_grp[3] == solicitud->usr && usr_grp[4] == solicitud->pwd){
                                        sesion.usuario = usr_grp[3]; sesion.activaP = listaAux; encontrado = true;
                                        cout<<"Sesion Iniciada Con Exito"<<endl;
                                    }
                                }
                                if(encontrado){break;}
                            }

                            if(!encontrado){
                                cout<<"No Se Encontro Al Usuario Con Los Datos Proporcionados"<<endl;
                            }
                        }else{
                            if(part1.part_type == 'e' || part1.part_type == 'E'){
                                Discoo=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Discoo,part1.part_start,SEEK_SET);
                                fread(&ebr,sizeof(EBR),1,Discoo);
                                fseek(Discoo,0,SEEK_SET);
                                fclose(Discoo);

                                siguiente = ebr;
                                while(siguiente.part_next != -1){
                                    ebr = siguiente;
                                    Debr=fopen(ruta.toStdString().c_str(),"rb+");
                                    fseek(Debr,siguiente.part_next,SEEK_SET);
                                    fread(&siguiente,sizeof(EBR),1,Debr);
                                    fseek(Debr,0,SEEK_SET);
                                    fclose(Debr);
                                    QString nombreChar(siguiente.part_name);
                                    if(listaAux->nombreP == nombreChar){
                                        //LEER SUPER BLOQUE
                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,ebr.part_start + sizeof (ebr),SEEK_SET);
                                        fread(&sb,sizeof(sb),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);
                                        //LEER USERS.TXT
                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_inode_start + sizeof (inodoT),SEEK_SET);
                                        fread(&inodoT,sizeof(inodoT),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);

                                        QString contenido = "";
                                        bool encontrado = false;

                                        for(int x = 0; x<15;x++){
                                            if(inodoT.i_block[x] == -1){break;}else{
                                                if(x == 12){

                                                }else if(x == 13){

                                                }else if(x == 14){

                                                }else{
                                                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                                    fseek(Particion,sb.s_block_start + (sizeof (BloquesArchivos) * (inodoT.i_block[x] + 1)),SEEK_SET);
                                                    fread(&archivo,sizeof(BloquesArchivos),1,Particion);
                                                    fseek(Particion,0,SEEK_SET);
                                                    fclose(Particion);

                                                    QString contenidotmp(archivo.b_content);
                                                    contenido += contenidotmp;
                                                }
                                            }
                                        }

                                        QStringList lineas = contenido.split("\n");
                                        for(int y =0;y<lineas.length();y++){
                                            QStringList usr_grp = lineas[y].split(",");
                                            if(usr_grp.length() == 5){
                                                if(usr_grp[3] == solicitud->usr && usr_grp[4] == solicitud->pwd){
                                                    sesion.usuario = usr_grp[3]; sesion.activaP = listaAux; encontrado = true;
                                                    cout<<"Sesion Iniciada Con Exito"<<endl;
                                                }
                                            }
                                            if(encontrado){break;}
                                        }

                                        if(!encontrado){
                                            cout<<"No Se Encontro Al Usuario Con Los Datos Proporcionados"<<endl;
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
                            }else if(part2.part_type == 'e' || part2.part_type == 'E'){
                                Discoo=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Discoo,part2.part_start,SEEK_SET);
                                fread(&ebr,sizeof(EBR),1,Discoo);
                                fseek(Discoo,0,SEEK_SET);
                                fclose(Discoo);

                                siguiente = ebr;
                                while(siguiente.part_next != -1){
                                    ebr = siguiente;
                                    Debr=fopen(ruta.toStdString().c_str(),"rb+");
                                    fseek(Debr,siguiente.part_next,SEEK_SET);
                                    fread(&siguiente,sizeof(EBR),1,Debr);
                                    fseek(Debr,0,SEEK_SET);
                                    fclose(Debr);
                                    QString nombreChar(siguiente.part_name);
                                    if(listaAux->nombreP == nombreChar){
                                        //LEER SUPER BLOQUE
                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,ebr.part_start + sizeof (ebr),SEEK_SET);
                                        fread(&sb,sizeof(sb),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);
                                        //LEER USERS.TXT
                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_inode_start + sizeof (inodoT),SEEK_SET);
                                        fread(&inodoT,sizeof(inodoT),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);

                                        QString contenido = "";
                                        bool encontrado = false;

                                        for(int x = 0; x<15;x++){
                                            if(inodoT.i_block[x] == -1){break;}else{
                                                if(x == 12){

                                                }else if(x == 13){

                                                }else if(x == 14){

                                                }else{
                                                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                                    fseek(Particion,sb.s_block_start + (sizeof (BloquesArchivos) * (inodoT.i_block[x] + 1)),SEEK_SET);
                                                    fread(&archivo,sizeof(BloquesArchivos),1,Particion);
                                                    fseek(Particion,0,SEEK_SET);
                                                    fclose(Particion);

                                                    QString contenidotmp(archivo.b_content);
                                                    contenido += contenidotmp;
                                                }
                                            }
                                        }

                                        QStringList lineas = contenido.split("\n");
                                        for(int y =0;y<lineas.length();y++){
                                            QStringList usr_grp = lineas[y].split(",");
                                            if(usr_grp.length() == 5){
                                                if(usr_grp[3] == solicitud->usr && usr_grp[4] == solicitud->pwd){
                                                    sesion.usuario = usr_grp[3]; sesion.activaP = listaAux; encontrado = true;
                                                    cout<<"Sesion Iniciada Con Exito"<<endl;
                                                }
                                            }
                                            if(encontrado){break;}
                                        }

                                        if(!encontrado){
                                            cout<<"No Se Encontro Al Usuario Con Los Datos Proporcionados"<<endl;
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
                            }else if(part3.part_type == 'e' || part3.part_type == 'E'){
                                Discoo=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Discoo,part3.part_start,SEEK_SET);
                                fread(&ebr,sizeof(EBR),1,Discoo);
                                fseek(Discoo,0,SEEK_SET);
                                fclose(Discoo);

                                siguiente = ebr;
                                while(siguiente.part_next != -1){
                                    ebr = siguiente;
                                    Debr=fopen(ruta.toStdString().c_str(),"rb+");
                                    fseek(Debr,siguiente.part_next,SEEK_SET);
                                    fread(&siguiente,sizeof(EBR),1,Debr);
                                    fseek(Debr,0,SEEK_SET);
                                    fclose(Debr);
                                    QString nombreChar(siguiente.part_name);
                                    if(listaAux->nombreP == nombreChar){
                                        //LEER SUPER BLOQUE
                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,ebr.part_start + sizeof (ebr),SEEK_SET);
                                        fread(&sb,sizeof(sb),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);
                                        //LEER USERS.TXT
                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_inode_start + sizeof (inodoT),SEEK_SET);
                                        fread(&inodoT,sizeof(inodoT),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);

                                        QString contenido = "";
                                        bool encontrado = false;

                                        for(int x = 0; x<15;x++){
                                            if(inodoT.i_block[x] == -1){break;}else{
                                                if(x == 12){

                                                }else if(x == 13){

                                                }else if(x == 14){

                                                }else{
                                                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                                    fseek(Particion,sb.s_block_start + (sizeof (BloquesArchivos) * (inodoT.i_block[x] + 1)),SEEK_SET);
                                                    fread(&archivo,sizeof(BloquesArchivos),1,Particion);
                                                    fseek(Particion,0,SEEK_SET);
                                                    fclose(Particion);

                                                    QString contenidotmp(archivo.b_content);
                                                    contenido += contenidotmp;
                                                }
                                            }
                                        }

                                        QStringList lineas = contenido.split("\n");
                                        for(int y =0;y<lineas.length();y++){
                                            QStringList usr_grp = lineas[y].split(",");
                                            if(usr_grp.length() == 5){
                                                if(usr_grp[3] == solicitud->usr && usr_grp[4] == solicitud->pwd){
                                                    sesion.usuario = usr_grp[3]; sesion.activaP = listaAux; encontrado = true;
                                                    cout<<"Sesion Iniciada Con Exito"<<endl;
                                                }
                                            }
                                            if(encontrado){break;}
                                        }

                                        if(!encontrado){
                                            cout<<"No Se Encontro Al Usuario Con Los Datos Proporcionados"<<endl;
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
                            }else if(part4.part_type == 'e' || part4.part_type == 'E'){
                                Discoo=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Discoo,part4.part_start,SEEK_SET);
                                fread(&ebr,sizeof(EBR),1,Discoo);
                                fseek(Discoo,0,SEEK_SET);
                                fclose(Discoo);

                                siguiente = ebr;
                                while(siguiente.part_next != -1){
                                    ebr = siguiente;
                                    Debr=fopen(ruta.toStdString().c_str(),"rb+");
                                    fseek(Debr,siguiente.part_next,SEEK_SET);
                                    fread(&siguiente,sizeof(EBR),1,Debr);
                                    fseek(Debr,0,SEEK_SET);
                                    fclose(Debr);
                                    QString nombreChar(siguiente.part_name);
                                    if(listaAux->nombreP == nombreChar){
                                        //LEER SUPER BLOQUE
                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,ebr.part_start + sizeof (ebr),SEEK_SET);
                                        fread(&sb,sizeof(sb),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);
                                        //LEER USERS.TXT
                                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                        fseek(Particion,sb.s_inode_start + sizeof (inodoT),SEEK_SET);
                                        fread(&inodoT,sizeof(inodoT),1,Particion);
                                        fseek(Particion,0,SEEK_SET);
                                        fclose(Particion);

                                        QString contenido = "";
                                        bool encontrado = false;

                                        for(int x = 0; x<15;x++){
                                            if(inodoT.i_block[x] == -1){break;}else{
                                                if(x == 12){

                                                }else if(x == 13){

                                                }else if(x == 14){

                                                }else{
                                                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                                    fseek(Particion,sb.s_block_start + (sizeof (BloquesArchivos) * (inodoT.i_block[x] + 1)),SEEK_SET);
                                                    fread(&archivo,sizeof(BloquesArchivos),1,Particion);
                                                    fseek(Particion,0,SEEK_SET);
                                                    fclose(Particion);

                                                    QString contenidotmp(archivo.b_content);
                                                    contenido += contenidotmp;
                                                }
                                            }
                                        }

                                        QStringList lineas = contenido.split("\n");
                                        for(int y =0;y<lineas.length();y++){
                                            QStringList usr_grp = lineas[y].split(",");
                                            if(usr_grp.length() == 5){
                                                if(usr_grp[3] == solicitud->usr && usr_grp[4] == solicitud->pwd){
                                                    sesion.usuario = usr_grp[3]; sesion.activaP = listaAux; encontrado = true;
                                                    cout<<"Sesion Iniciada Con Exito"<<endl;
                                                }
                                            }
                                            if(encontrado){break;}
                                        }

                                        if(!encontrado){
                                            cout<<"No Se Encontro Al Usuario Con Los Datos Proporcionados"<<endl;
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
                            }else{
                                cout<<"La particion Que Desea Montar No Existe"<<endl;
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
            cout<<"La Particion Solicitada No Se Encuentra Montada"<<endl;
        }
    }else{
        cout<<"Ya hay una Sesion Iniciada"<<endl;
    }

    solicitud->id = "";
    solicitud->pwd = "";
    solicitud->usr = "";
    cout<<"--------------------------------------------------------"<<endl;
}

void cllogin::salir(){
    cout<<"----------------------CerrarSesion--------------------------"<<endl;
    if(sesion.usuario != ""){
        sesion.logout(sesion.activaP,sesion.usuario);
        cout<<"Sesion Finalizada"<<endl;
    }else{
        cout<<"No Hay Una Sesion Iniciada"<<endl;
    }

    cout<<"--------------------------------------------------------"<<endl;
}
