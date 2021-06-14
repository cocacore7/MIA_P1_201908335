#include "clreportes.h"
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
        ListaM Listaaux = lista.obtenerNodo(lista.lista,reporte->id);
        QStringList direcciones = Listaaux->ruta.split("/");
        QString ruta = "/home/oscar/archivos";
        QString StringReporte ="";
        bool NoCarpeta = false;

        MBR mbr;
        struct particion part1;
        struct particion part2;
        struct particion part3;
        struct particion part4;

        SuperBloque sb;

        FILE* Debr;
        FILE* Particion;
        EBR siguiente;
        EBR ebr;
        int iniciojour = 0;
        int tamP = 0;

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
                    QString nombre1(part1.part_name);
                    QString nombre2(part2.part_name);
                    QString nombre3(part3.part_name);
                    QString nombre4(part4.part_name);

                    if(Listaaux->nombreP == nombre1){
                        //LEER SUPER BLOQUE
                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                        fseek(Particion,part1.part_start,SEEK_SET);
                        fread(&sb,sizeof(sb),1,Particion);
                        fseek(Particion,0,SEEK_SET);
                        fclose(Particion);
                        iniciojour = part1.part_start + sizeof (SuperBloque);
                        tamP = part1.part_size;

                    }else if(Listaaux->nombreP == nombre2){
                        //LEER SUPER BLOQUE
                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                        fseek(Particion,part2.part_start,SEEK_SET);
                        fread(&sb,sizeof(sb),1,Particion);
                        fseek(Particion,0,SEEK_SET);
                        fclose(Particion);
                        iniciojour = part2.part_start + sizeof (SuperBloque);
                        tamP = part2.part_size;

                    }else if(Listaaux->nombreP == nombre3){
                        //LEER SUPER BLOQUE
                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                        fseek(Particion,part3.part_start,SEEK_SET);
                        fread(&sb,sizeof(sb),1,Particion);
                        fseek(Particion,0,SEEK_SET);
                        fclose(Particion);
                        iniciojour = part3.part_start + sizeof (SuperBloque);
                        tamP = part3.part_size;

                    }else if(Listaaux->nombreP == nombre4){
                        //LEER SUPER BLOQUE
                        Particion=fopen(ruta.toStdString().c_str(),"rb+");
                        fseek(Particion,part4.part_start,SEEK_SET);
                        fread(&sb,sizeof(sb),1,Particion);
                        fseek(Particion,0,SEEK_SET);
                        fclose(Particion);
                        iniciojour = part4.part_start + sizeof (SuperBloque);
                        tamP = part4.part_size;

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
                                QString nombreChar(ebr.part_name);
                                if(Listaaux->nombreP == nombreChar){
                                    //LEER SUPER BLOQUE
                                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                    fseek(Particion,ebr.part_start + sizeof (ebr),SEEK_SET);
                                    fread(&sb,sizeof(sb),1,Particion);
                                    fseek(Particion,0,SEEK_SET);
                                    fclose(Particion);
                                    iniciojour = ebr.part_start + sizeof (ebr) + sizeof (SuperBloque);
                                    tamP = ebr.part_size;

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
                                QString nombreChar(ebr.part_name);
                                if(Listaaux->nombreP == nombreChar){
                                    //LEER SUPER BLOQUE
                                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                    fseek(Particion,ebr.part_start + sizeof (ebr),SEEK_SET);
                                    fread(&sb,sizeof(sb),1,Particion);
                                    fseek(Particion,0,SEEK_SET);
                                    fclose(Particion);
                                    iniciojour = ebr.part_start + sizeof (ebr) + sizeof (SuperBloque);
                                    tamP = ebr.part_size;

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
                                QString nombreChar(ebr.part_name);
                                if(Listaaux->nombreP == nombreChar){
                                    //LEER SUPER BLOQUE
                                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                    fseek(Particion,ebr.part_start + sizeof (ebr),SEEK_SET);
                                    fread(&sb,sizeof(sb),1,Particion);
                                    fseek(Particion,0,SEEK_SET);
                                    fclose(Particion);
                                    iniciojour = ebr.part_start + sizeof (ebr) + sizeof (SuperBloque);
                                    tamP = ebr.part_size;

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
                                QString nombreChar(ebr.part_name);
                                if(Listaaux->nombreP == nombreChar){
                                    //LEER SUPER BLOQUE
                                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                    fseek(Particion,ebr.part_start + sizeof (ebr),SEEK_SET);
                                    fread(&sb,sizeof(sb),1,Particion);
                                    fseek(Particion,0,SEEK_SET);
                                    fclose(Particion);
                                    iniciojour = ebr.part_start + sizeof (ebr) + sizeof (SuperBloque);
                                    tamP = ebr.part_size;

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
                    cout<<"Extension de Disco incorrecta, no es .dk"<<endl;
                }
            }else{
                cout<<"Extension de Disco incorrecta, no es .dk"<<endl;
            }
        }

        if(reporte->namee.toLower() == "mbr"){
            cout<<"-----------------------ReporteMBR---------------------"<<endl;
            //Generar Particion 1 en Reporte
            StringReporte = "digraph G { bgcolor=\"yellow:purple\"\n";
            StringReporte += "node [shape=filled];\n";
            StringReporte += "a0 [label=<\n";
            StringReporte += "<TABLE border=\"10\" cellspacing=\"10\" cellpadding=\"10\" style=\"rounded\" bgcolor=\"green:red\" gradientangle=\"315\">\n";
            StringReporte += "<TR>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"blue:gray\">NOMBRE</TD>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"blue:gray\">VALOR</TD>\n";
            StringReporte += "</TR>\n";

            //DATOS DISCO
            QString tammbr = QStringLiteral("%1").arg(mbr.mbr_tam);
            StringReporte += "<TR>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"orange:white\">mbr_tamaño</TD>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"orange:white\">"+tammbr+"</TD>\n";
            StringReporte += "</TR>\n";

            struct tm *tm;
            tm=localtime(&mbr.mbr_fecha_creacion);
            QString dia = QStringLiteral("%1").arg(tm->tm_mday);
            QString mes = QStringLiteral("%1").arg(tm->tm_mon);
            QString anio = QStringLiteral("%1").arg(tm->tm_year);
            QString hora = QStringLiteral("%1").arg(tm->tm_hour);
            QString min = QStringLiteral("%1").arg(tm->tm_min);
            QString seg = QStringLiteral("%1").arg(tm->tm_sec);
            StringReporte += "<TR>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"orange:white\">mbr_fecha_creacion</TD>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"orange:white\">"+ dia + "/" + mes + "/" + anio + "/ " + hora + ":" + min + ":" + seg +"</TD>\n";
            StringReporte += "</TR>\n";

            QString sign = QStringLiteral("%1").arg(mbr.mbr_disk_signature);
            StringReporte += "<TR>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"orange:white\">mbr_disk_signature</TD>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"orange:white\">"+sign+"</TD>\n";
            StringReporte += "</TR>\n";

            QString fitmbr(mbr.disk_fit);
            StringReporte += "<TR>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"orange:white\">Disk_fit</TD>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"orange:white\">"+fitmbr+"</TD>\n";
            StringReporte += "</TR>\n";

            //Generar Particion 1 Extendida en Reporte
            QString status1(part1.part_status);
            StringReporte += "<TR>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">part_status_1</TD>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">"+status1+"</TD>\n";
            StringReporte += "</TR>\n";

            QString type1(part1.part_type);
            StringReporte += "<TR>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">part_type_1</TD>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">"+type1+"</TD>\n";
            StringReporte += "</TR>\n";

            QString fit1(part1.part_fit);
            StringReporte += "<TR>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">part_fit_1</TD>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">"+fit1+"</TD>\n";
            StringReporte += "</TR>\n";

            QString start1 = QStringLiteral("%1").arg(part1.part_start);
            StringReporte += "<TR>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">part_start_1</TD>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">"+start1+"</TD>\n";
            StringReporte += "</TR>\n";

            QString size1 = QStringLiteral("%1").arg(part1.part_size);
            StringReporte += "<TR>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">part_size_1</TD>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">"+size1+"</TD>\n";
            StringReporte += "</TR>\n";

            if(fit1 != "."){
                QString name1(part1.part_name);
                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"blue:red\">part_name_1</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"blue:red\">"+name1+"</TD>\n";
                StringReporte += "</TR>\n";
            }else{
                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"blue:red\">part_name_1</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"blue:red\">.</TD>\n";
                StringReporte += "</TR>\n";
            }

            if(part1.part_type == 'e' || part1.part_type == 'E'){
                EBR ebr;
                FILE* Debr=fopen(ruta.toStdString().c_str(),"rb+");
                fseek(Debr,part1.part_start,SEEK_SET);
                fread(&ebr,sizeof(EBR),1,Debr);
                fseek(Debr,0,SEEK_SET);
                fclose(Debr);

                int partOcupado = 0;
                int nuevoinicio = part1.part_start;
                int tam_Particion = part1.part_size;
                int tam_ebr = sizeof (ebr);
                int cantEbr = 0;
                bool primera = false;
                while(ebr.part_next != -1){
                    if(primera){
                        QString numebr = QStringLiteral("%1").arg(cantEbr);
                        StringReporte += "<TR>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"gray\">Nombre_EBR_" + numebr + "</TD>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"gray\">Valor_EBR_" + numebr + "</TD>\n";
                        StringReporte += "</TR>\n";

                        QString statusebr(ebr.part_status);
                        StringReporte += "<TR>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">part_status_1</TD>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">"+statusebr+"</TD>\n";
                        StringReporte += "</TR>\n";

                        QString fitebr(ebr.part_fit);
                        StringReporte += "<TR>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">part_fit_1</TD>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">"+fitebr+"</TD>\n";
                        StringReporte += "</TR>\n";

                        QString startebr = QStringLiteral("%1").arg(ebr.part_start);
                        StringReporte += "<TR>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">part_start_1</TD>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">"+startebr+"</TD>\n";
                        StringReporte += "</TR>\n";

                        QString sizeebr = QStringLiteral("%1").arg(ebr.part_size);
                        StringReporte += "<TR>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">part_size_1</TD>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">"+sizeebr+"</TD>\n";
                        StringReporte += "</TR>\n";

                        QString nextebr = QStringLiteral("%1").arg(ebr.part_next);
                        StringReporte += "<TR>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">part_next_1</TD>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">"+nextebr+"</TD>\n";
                        StringReporte += "</TR>\n";

                        QString nameebr(ebr.part_name);
                        if(fitebr != "."){
                            StringReporte += "<TR>\n";
                            StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">part_name_1</TD>\n";
                            StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">"+nameebr+"</TD>\n";
                            StringReporte += "</TR>\n";
                        }else{
                            StringReporte += "<TR>\n";
                            StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">part_name_1</TD>\n";
                            StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">.</TD>\n";
                            StringReporte += "</TR>\n";
                        }
                    }
                    primera = true;

                    Debr=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Debr,nuevoinicio,SEEK_SET);
                    fread(&ebr,sizeof(EBR),1,Debr);
                    fseek(Debr,0,SEEK_SET);
                    fclose(Debr);

                    if(ebr.part_next != -1){
                        nuevoinicio = ebr.part_next;
                        partOcupado = partOcupado + tam_ebr + ebr.part_size;
                        cantEbr++;
                    }
                    if(partOcupado >= tam_Particion){break;}
                }
            }

            //Generar Particion 2 Extendida en Reporte
            QString status2(part2.part_status);
            StringReporte += "<TR>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">part_status_2</TD>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">"+status2+"</TD>\n";
            StringReporte += "</TR>\n";

            QString type2(part2.part_type);
            StringReporte += "<TR>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">part_type_2</TD>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">"+type2+"</TD>\n";
            StringReporte += "</TR>\n";

            QString fit2(part2.part_fit);
            StringReporte += "<TR>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">part_fit_2</TD>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">"+fit2+"</TD>\n";
            StringReporte += "</TR>\n";

            QString start2 = QStringLiteral("%1").arg(part2.part_start);
            StringReporte += "<TR>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">part_start_2</TD>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">"+start2+"</TD>\n";
            StringReporte += "</TR>\n";

            QString size2 = QStringLiteral("%1").arg(part2.part_size);
            StringReporte += "<TR>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">part_size_2</TD>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">"+size2+"</TD>\n";
            StringReporte += "</TR>\n";

            if(fit2 != "."){
                QString name2(part2.part_name);
                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"blue:red\">part_name_2</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"blue:red\">"+name2+"</TD>\n";
                StringReporte += "</TR>\n";
            }else{
                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"blue:red\">part_name_2</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"blue:red\">.</TD>\n";
                StringReporte += "</TR>\n";
            }

            if(part2.part_type == 'e' || part2.part_type == 'E'){
                EBR ebr;
                FILE* Debr=fopen(ruta.toStdString().c_str(),"rb+");
                fseek(Debr,part2.part_start,SEEK_SET);
                fread(&ebr,sizeof(EBR),1,Debr);
                fseek(Debr,0,SEEK_SET);
                fclose(Debr);

                int partOcupado = 0;
                int nuevoinicio = part2.part_start;
                int tam_Particion = part2.part_size;
                int tam_ebr = sizeof (ebr);
                int cantEbr = 0;
                bool primera = false;
                while(ebr.part_next != -1){
                    if(primera){
                        QString numebr = QStringLiteral("%1").arg(cantEbr);
                        StringReporte += "<TR>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"gray\">Nombre_EBR_" + numebr + "</TD>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"gray\">Valor_EBR_" + numebr + "</TD>\n";
                        StringReporte += "</TR>\n";

                        QString statusebr(ebr.part_status);
                        StringReporte += "<TR>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">part_status_2</TD>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">"+statusebr+"</TD>\n";
                        StringReporte += "</TR>\n";

                        QString fitebr(ebr.part_fit);
                        StringReporte += "<TR>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">part_fit_2</TD>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">"+fitebr+"</TD>\n";
                        StringReporte += "</TR>\n";

                        QString startebr = QStringLiteral("%1").arg(ebr.part_start);
                        StringReporte += "<TR>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">part_start_2</TD>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">"+startebr+"</TD>\n";
                        StringReporte += "</TR>\n";

                        QString sizeebr = QStringLiteral("%1").arg(ebr.part_size);
                        StringReporte += "<TR>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">part_size_2</TD>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">"+sizeebr+"</TD>\n";
                        StringReporte += "</TR>\n";

                        QString nextebr = QStringLiteral("%1").arg(ebr.part_next);
                        StringReporte += "<TR>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">part_next_2</TD>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">"+nextebr+"</TD>\n";
                        StringReporte += "</TR>\n";

                        if(fitebr != "."){
                            QString nameebr(ebr.part_name);
                            StringReporte += "<TR>\n";
                            StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">part_name_2</TD>\n";
                            StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">"+nameebr+"</TD>\n";
                            StringReporte += "</TR>\n";
                        }else{
                            StringReporte += "<TR>\n";
                            StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">part_name_2</TD>\n";
                            StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">.</TD>\n";
                            StringReporte += "</TR>\n";
                        }

                    }
                    primera = true;

                    Debr=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Debr,nuevoinicio,SEEK_SET);
                    fread(&ebr,sizeof(EBR),1,Debr);
                    fseek(Debr,0,SEEK_SET);
                    fclose(Debr);

                    if(ebr.part_next != -1){
                        nuevoinicio = ebr.part_next;
                        partOcupado = partOcupado + tam_ebr + ebr.part_size;
                        cantEbr++;
                    }
                    if(partOcupado >= tam_Particion){break;}
                }
            }

            //Generar Particion 3 Extendida en Reporte
            QString status3(part3.part_status);
            StringReporte += "<TR>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">part_status_3</TD>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">"+status3+"</TD>\n";
            StringReporte += "</TR>\n";

            QString type3(part3.part_type);
            StringReporte += "<TR>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">part_type_3</TD>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">"+type3+"</TD>\n";
            StringReporte += "</TR>\n";

            QString fit3(part3.part_fit);
            StringReporte += "<TR>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">part_fit_3</TD>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">"+fit3+"</TD>\n";
            StringReporte += "</TR>\n";

            QString start3 = QStringLiteral("%1").arg(part3.part_start);
            StringReporte += "<TR>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">part_start_3</TD>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">"+start3+"</TD>\n";
            StringReporte += "</TR>\n";

            QString size3 = QStringLiteral("%1").arg(part3.part_size);
            StringReporte += "<TR>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">part_size_3</TD>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">"+size3+"</TD>\n";
            StringReporte += "</TR>\n";

            if(fit3 != "."){
                QString name3(part3.part_name);
                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"blue:red\">part_name_3</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"blue:red\">"+name3+"</TD>\n";
                StringReporte += "</TR>\n";
            }else{
                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"blue:red\">part_name_3</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"blue:red\">.</TD>\n";
                StringReporte += "</TR>\n";
            }

            if(part3.part_type == 'e' || part3.part_type == 'E'){
                EBR ebr;
                FILE* Debr=fopen(ruta.toStdString().c_str(),"rb+");
                fseek(Debr,part3.part_start,SEEK_SET);
                fread(&ebr,sizeof(EBR),1,Debr);
                fseek(Debr,0,SEEK_SET);
                fclose(Debr);

                int partOcupado = 0;
                int nuevoinicio = part3.part_start;
                int tam_Particion = part3.part_size;
                int tam_ebr = sizeof (ebr);
                int cantEbr = 0;
                bool primera = false;
                while(ebr.part_next != -1){
                    if(primera){
                        QString numebr = QStringLiteral("%1").arg(cantEbr);
                        StringReporte += "<TR>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"gray\">Nombre_EBR_" + numebr + "</TD>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"gray\">Valor_EBR_" + numebr + "</TD>\n";
                        StringReporte += "</TR>\n";

                        QString statusebr(ebr.part_status);
                        StringReporte += "<TR>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">part_status_3</TD>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">"+statusebr+"</TD>\n";
                        StringReporte += "</TR>\n";

                        QString fitebr(ebr.part_fit);
                        StringReporte += "<TR>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">part_fit_3</TD>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">"+fitebr+"</TD>\n";
                        StringReporte += "</TR>\n";

                        QString startebr = QStringLiteral("%1").arg(ebr.part_start);
                        StringReporte += "<TR>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">part_start_3</TD>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">"+startebr+"</TD>\n";
                        StringReporte += "</TR>\n";

                        QString sizeebr = QStringLiteral("%1").arg(ebr.part_size);
                        StringReporte += "<TR>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">part_size_3</TD>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">"+sizeebr+"</TD>\n";
                        StringReporte += "</TR>\n";

                        QString nextebr = QStringLiteral("%1").arg(ebr.part_next);
                        StringReporte += "<TR>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">part_next_3</TD>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">"+nextebr+"</TD>\n";
                        StringReporte += "</TR>\n";

                        if(fitebr !="."){
                            QString nameebr(ebr.part_name);
                            StringReporte += "<TR>\n";
                            StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">part_name_3</TD>\n";
                            StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">"+nameebr+"</TD>\n";
                            StringReporte += "</TR>\n";
                        }else{
                            StringReporte += "<TR>\n";
                            StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">part_name_3</TD>\n";
                            StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">.</TD>\n";
                            StringReporte += "</TR>\n";
                        }

                    }
                    primera = true;

                    Debr=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Debr,nuevoinicio,SEEK_SET);
                    fread(&ebr,sizeof(EBR),1,Debr);
                    fseek(Debr,0,SEEK_SET);
                    fclose(Debr);

                    if(ebr.part_next != -1){
                        nuevoinicio = ebr.part_next;
                        partOcupado = partOcupado + tam_ebr + ebr.part_size;
                        cantEbr++;
                    }
                    if(partOcupado >= tam_Particion){break;}
                }
            }

            //Generar Particion 4 Extendida en Reporte
            QString status4(part4.part_status);
            StringReporte += "<TR>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">part_status_4</TD>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">"+status4+"</TD>\n";
            StringReporte += "</TR>\n";

            QString type4(part4.part_type);
            StringReporte += "<TR>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">part_type_4</TD>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">"+type4+"</TD>\n";
            StringReporte += "</TR>\n";

            QString fit4(part4.part_fit);
            StringReporte += "<TR>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">part_fit_4</TD>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">"+fit4+"</TD>\n";
            StringReporte += "</TR>\n";

            QString start4 = QStringLiteral("%1").arg(part4.part_start);
            StringReporte += "<TR>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">part_start_4</TD>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">"+start4+"</TD>\n";
            StringReporte += "</TR>\n";

            QString size4 = QStringLiteral("%1").arg(part4.part_size);
            StringReporte += "<TR>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">part_size_4</TD>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">"+size4+"</TD>\n";
            StringReporte += "</TR>\n";

            if(fit4 != "."){
                QString name4(part4.part_name);
                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"blue:red\">part_name_4</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"blue:red\">"+name4+"</TD>\n";
                StringReporte += "</TR>\n";
            }else{
                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"blue:red\">part_name_4</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"blue:red\">.</TD>\n";
                StringReporte += "</TR>\n";
            }

            if(part4.part_type == 'e' || part4.part_type == 'E'){
                EBR ebr;
                FILE* Debr=fopen(ruta.toStdString().c_str(),"rb+");
                fseek(Debr,part4.part_start,SEEK_SET);
                fread(&ebr,sizeof(EBR),1,Debr);
                fseek(Debr,0,SEEK_SET);
                fclose(Debr);

                int partOcupado = 0;
                int nuevoinicio = part4.part_start;
                int tam_Particion = part4.part_size;
                int tam_ebr = sizeof (ebr);
                int cantEbr = 0;
                bool primera = false;
                while(ebr.part_next != -1){
                    if(primera){
                        QString numebr = QStringLiteral("%1").arg(cantEbr);
                        StringReporte += "<TR>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"gray\">Nombre_EBR_" + numebr + "</TD>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"gray\">Valor_EBR_" + numebr + "</TD>\n";
                        StringReporte += "</TR>\n";

                        QString statusebr(ebr.part_status);
                        StringReporte += "<TR>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">part_status_4</TD>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">"+statusebr+"</TD>\n";
                        StringReporte += "</TR>\n";

                        QString fitebr(ebr.part_fit);
                        StringReporte += "<TR>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">part_fit_4</TD>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">"+fitebr+"</TD>\n";
                        StringReporte += "</TR>\n";

                        QString startebr = QStringLiteral("%1").arg(ebr.part_start);
                        StringReporte += "<TR>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">part_start_4</TD>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">"+startebr+"</TD>\n";
                        StringReporte += "</TR>\n";

                        QString sizeebr = QStringLiteral("%1").arg(ebr.part_size);
                        StringReporte += "<TR>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">part_size_4</TD>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">"+sizeebr+"</TD>\n";
                        StringReporte += "</TR>\n";

                        QString nextebr = QStringLiteral("%1").arg(ebr.part_next);
                        StringReporte += "<TR>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">part_next_4</TD>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">"+nextebr+"</TD>\n";
                        StringReporte += "</TR>\n";

                        if(fitebr != "."){
                            QString nameebr(ebr.part_name);
                            StringReporte += "<TR>\n";
                            StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">part_name_4</TD>\n";
                            StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">"+nameebr+"</TD>\n";
                            StringReporte += "</TR>\n";
                        }else{
                            StringReporte += "<TR>\n";
                            StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">part_name_4</TD>\n";
                            StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">.</TD>\n";
                            StringReporte += "</TR>\n";
                        }

                    }
                    primera = true;

                    Debr=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Debr,nuevoinicio,SEEK_SET);
                    fread(&ebr,sizeof(EBR),1,Debr);
                    fseek(Debr,0,SEEK_SET);
                    fclose(Debr);

                    if(ebr.part_next != -1){
                        nuevoinicio = ebr.part_next;
                        partOcupado = partOcupado + tam_ebr + ebr.part_size;
                        cantEbr++;
                    }
                    if(partOcupado >= tam_Particion){break;}
                }
            }

            StringReporte += "</TABLE>>];\n";
            StringReporte += "}\n";

            QStringList direccionReporte = reporte->path.split("/");
            QString rutaR = "";
            bool primera = false;
            if(direccionReporte[1] == "home" && direccionReporte[2] == "archivos"){
                rutaR = "/home/oscar/archivos";
                for(int x=3;x<(direccionReporte.length()-1);x++){
                    if(primera){
                        QDir direc(rutaR);
                        direc.mkdir(direccionReporte[x]);
                        rutaR = rutaR + direccionReporte[x] + "/";
                    }else{
                        QDir direc(rutaR);
                        direc.mkdir(direccionReporte[x]);
                        rutaR = rutaR + "/" + direccionReporte[x] + "/";
                        primera = true;
                    }
                }
            }

            QString aux =direccionReporte[direccionReporte.length()-1];
            QStringList extensionReporte = aux.split(".");
            QString rutadot = rutaR;
            if(extensionReporte[1].toLower() == "jpg"){
                //AQUI CREAMOS ARCHIVO FISICO
                if(primera){
                    rutaR = rutaR + aux;
                }else{
                    rutaR = rutaR + "/" + aux;
                }
                //EJECUTAR COMANDO GRAPVHIZ
                rutadot = rutadot + "/" + extensionReporte[0] + ".dot";
                ofstream dot;
                dot.open(rutadot.toStdString().c_str(),ios::out);
                if(dot.fail()){
                    cout<<"No Se Creo El Archivo .dot"<<endl;
                }
                dot<<StringReporte.toStdString().c_str();
                dot.close();

                QString comando = "dot -Tjpg " + rutadot + " -o " + rutaR;
                system(comando.toStdString().c_str());
                cout<<"El Reporte MBR Se Creo Exitosamente :D"<<endl;
            }else{
                cout<<"Extension de Reporte incorrecta, no es .jpg"<<endl;
            }

        }else if(reporte->namee.toLower() == "disk"){
            cout<<"-----------------------ReporteDISK---------------------"<<endl;
            QString nodoExt = "";
            QString iniExt = "";
            int iniN = 1;
            int contN = 1;
            int nuevoinicio = 0;
            int tam_Particion = 0;
            bool final = false;
            QString n = QStringLiteral("%1").arg(contN);
            QString bytes;
            EBR ebr;
            StringReporte = "digraph G{\n";
            StringReporte += "compound=true;\n";
            StringReporte += "subgraph cluster0{\n";

            if(part1.part_type == 'e' || part1.part_type == 'E'){
                nuevoinicio = part1.part_start;
                tam_Particion = part1.part_size;
                FILE* Debr=fopen(ruta.toStdString().c_str(),"rb+");
                fseek(Debr,nuevoinicio,SEEK_SET);
                fread(&ebr,sizeof(EBR),1,Debr);
                fseek(Debr,0,SEEK_SET);
                fclose(Debr);
                if(part1.part_fit != '.'){
                    if((part1.part_start - sizeof(mbr)) == 0){
                        bytes = QStringLiteral("%1").arg(sizeof (mbr));
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"MBR | " + bytes + "\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);
                        bytes = QStringLiteral("%1").arg(part1.part_size);
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"EXTENDIDA | " + bytes + "\"];\n";
                        nodoExt = "n" + n;
                        contN++;
                        n = QStringLiteral("%1").arg(contN);

                        for(int x = iniN;x<contN;x++){
                            QString n1 = QStringLiteral("%1").arg(x);
                            QString n2 = QStringLiteral("%1").arg(x + 1);
                            StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                        }
                    }else {
                        bytes = QStringLiteral("%1").arg(sizeof (mbr));
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"MBR | " + bytes + "\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);
                        bytes = QStringLiteral("%1").arg(part1.part_start - sizeof(mbr));
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"LIBRE | " + bytes + "\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);
                        bytes = QStringLiteral("%1").arg(part1.part_size);
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"EXTENDIDA | " + bytes + "\"];\n";
                        nodoExt = "n" + n;
                        contN++;
                        n = QStringLiteral("%1").arg(contN);

                        for(int x = iniN;x<contN;x++){
                            QString n1 = QStringLiteral("%1").arg(x);
                            QString n2 = QStringLiteral("%1").arg(x + 1);
                            StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                        }
                    }
                }else{
                    bytes = QStringLiteral("%1").arg(sizeof (mbr));
                    StringReporte += "n" + n + " [shape=record,color=red,label=\"MBR | " + bytes + "\"];\n";
                    contN++;
                    n = QStringLiteral("%1").arg(contN);
                    if(part2.part_start != 0){
                        bytes = QStringLiteral("%1").arg(part2.part_start - sizeof (mbr));
                    }else if(part3.part_start != 0){
                        bytes = QStringLiteral("%1").arg(part3.part_start - sizeof (mbr));
                    }else if(part4.part_start != 0){
                        bytes = QStringLiteral("%1").arg(part4.part_start - sizeof (mbr));
                    }else{
                        bytes = QStringLiteral("%1").arg(mbr.mbr_tam - sizeof (mbr));
                        final = true;
                    }
                    StringReporte += "n" + n + " [shape=record,color=red,label=\"LIBRE | " + bytes + "\"];\n";
                    contN++;
                    n = QStringLiteral("%1").arg(contN);

                    for(int x = iniN;x<contN;x++){
                        QString n1 = QStringLiteral("%1").arg(x);
                        QString n2 = QStringLiteral("%1").arg(x + 1);
                        StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                    }
                }
            }else{
                if(part1.part_fit != '.'){
                    if((part1.part_start - sizeof(mbr)) == 0){
                        bytes = QStringLiteral("%1").arg(sizeof (mbr));
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"MBR | " + bytes + "\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);
                        bytes = QStringLiteral("%1").arg(part1.part_size);
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"PRIMARIA | " + bytes + "\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);

                        for(int x = iniN;x<contN;x++){
                            QString n1 = QStringLiteral("%1").arg(x);
                            QString n2 = QStringLiteral("%1").arg(x + 1);
                            StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                        }
                    }else {
                        bytes = QStringLiteral("%1").arg(sizeof (mbr));
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"MBR | " + bytes + "\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);
                        bytes = QStringLiteral("%1").arg(part1.part_start - sizeof(mbr));
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"LIBRE | " + bytes + "\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);
                        bytes = QStringLiteral("%1").arg(part1.part_size);
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"PRIMARIA | " + bytes + "\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);

                        for(int x = iniN;x<contN;x++){
                            QString n1 = QStringLiteral("%1").arg(x);
                            QString n2 = QStringLiteral("%1").arg(x + 1);
                            StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                        }
                    }
                }else{
                    bytes = QStringLiteral("%1").arg(sizeof (mbr));
                    StringReporte += "n" + n + " [shape=record,color=red,label=\"MBR | " + bytes + "\"];\n";
                    contN++;
                    n = QStringLiteral("%1").arg(contN);
                    if(part2.part_start != 0){
                        bytes = QStringLiteral("%1").arg(part2.part_start - sizeof (mbr));
                    }else if(part3.part_start != 0){
                        bytes = QStringLiteral("%1").arg(part3.part_start - sizeof (mbr));
                    }else if(part4.part_start != 0){
                        bytes = QStringLiteral("%1").arg(part4.part_start - sizeof (mbr));
                    }else{
                        bytes = QStringLiteral("%1").arg(mbr.mbr_tam - sizeof (mbr));
                        final = true;
                    }
                    StringReporte += "n" + n + " [shape=record,color=red,label=\"LIBRE | " + bytes + "\"];\n";
                    contN++;
                    n = QStringLiteral("%1").arg(contN);

                    for(int x = iniN;x<contN;x++){
                        QString n1 = QStringLiteral("%1").arg(x);
                        QString n2 = QStringLiteral("%1").arg(x + 1);
                        StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                    }
                }
            }

            if(part2.part_type == 'e' || part2.part_type == 'E'){
                nuevoinicio = part2.part_start;
                tam_Particion = part2.part_size;
                iniN = contN;
                FILE* Debr=fopen(ruta.toStdString().c_str(),"rb+");
                fseek(Debr,part2.part_start,SEEK_SET);
                fread(&ebr,sizeof(EBR),1,Debr);
                fseek(Debr,0,SEEK_SET);
                fclose(Debr);
                if(part2.part_fit != '.'){
                    if(part1.part_start != 0){
                        if((part2.part_start - part1.part_start - part1.part_size) == 0){
                            bytes = QStringLiteral("%1").arg(part2.part_size);
                            StringReporte += "n" + n + " [shape=record,color=red,label=\"EXTENDIDA | " + bytes + "\"];\n";
                            nodoExt = "n" + n;
                            contN++;
                            n = QStringLiteral("%1").arg(contN);

                            for(int x = iniN;x<contN;x++){
                                QString n1 = QStringLiteral("%1").arg(x);
                                QString n2 = QStringLiteral("%1").arg(x + 1);
                                StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                            }
                        }else {
                            bytes = QStringLiteral("%1").arg(part2.part_start - part1.part_start - part1.part_size);
                            StringReporte += "n" + n + " [shape=record,color=red,label=\"LIBRE | " + bytes + "\"];\n";
                            contN++;
                            n = QStringLiteral("%1").arg(contN);
                            bytes = QStringLiteral("%1").arg(part2.part_size);
                            StringReporte += "n" + n + " [shape=record,color=red,label=\"EXTENDIDA | " + bytes + "\"];\n";
                            nodoExt = "n" + n;
                            contN++;
                            n = QStringLiteral("%1").arg(contN);

                            for(int x = iniN;x<contN;x++){
                                QString n1 = QStringLiteral("%1").arg(x);
                                QString n2 = QStringLiteral("%1").arg(x + 1);
                                StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                            }
                        }
                    }else{
                        bytes = QStringLiteral("%1").arg(part2.part_size);
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"EXTENDIDA | " + bytes + "\"];\n";
                        nodoExt = "n" + n;
                        contN++;
                        n = QStringLiteral("%1").arg(contN);

                        for(int x = iniN;x<contN;x++){
                            QString n1 = QStringLiteral("%1").arg(x);
                            QString n2 = QStringLiteral("%1").arg(x + 1);
                            StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                        }
                    }
                }else{
                    if(part1.part_start != 0){
                        if(part3.part_start != 0){
                            bytes = QStringLiteral("%1").arg(part3.part_start - part1.part_start - part1.part_size);
                        }else if(part4.part_start != 0){
                            bytes = QStringLiteral("%1").arg(part4.part_start - part1.part_start - part1.part_size);
                        }else{
                            bytes = QStringLiteral("%1").arg(mbr.mbr_tam - part1.part_start - part1.part_size);
                        }
                    }else {
                        if(part3.part_start != 0){
                            bytes = QStringLiteral("%1").arg(part3.part_start - sizeof (mbr));
                        }else if(part4.part_start != 0){
                            bytes = QStringLiteral("%1").arg(part4.part_start - sizeof (mbr));
                        }else{
                            bytes = QStringLiteral("%1").arg(mbr.mbr_tam - sizeof (mbr));
                        }
                    }
                    if(!final){
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"LIBRE | " + bytes + "\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);
                        final = true;
                    }

                    for(int x = iniN;x<contN;x++){
                        QString n1 = QStringLiteral("%1").arg(x);
                        QString n2 = QStringLiteral("%1").arg(x + 1);
                        StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                    }
                }
            }else{
                iniN = contN;
                if(part2.part_fit != '.'){
                    if(part1.part_start != 0){
                        if((part2.part_start - part1.part_start - part1.part_size) == 0){
                            bytes = QStringLiteral("%1").arg(part2.part_size);
                            StringReporte += "n" + n + " [shape=record,color=red,label=\"PRIMARIA | " + bytes + "\"];\n";
                            contN++;
                            n = QStringLiteral("%1").arg(contN);

                            for(int x = iniN;x<contN;x++){
                                QString n1 = QStringLiteral("%1").arg(x);
                                QString n2 = QStringLiteral("%1").arg(x + 1);
                                StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                            }
                        }else {
                            bytes = QStringLiteral("%1").arg(part2.part_start - part1.part_start - part1.part_size);
                            StringReporte += "n" + n + " [shape=record,color=red,label=\"LIBRE | " + bytes + "\"];\n";
                            contN++;
                            n = QStringLiteral("%1").arg(contN);
                            bytes = QStringLiteral("%1").arg(part2.part_size);
                            StringReporte += "n" + n + " [shape=record,color=red,label=\"PRIMARIA | " + bytes + "\"];\n";
                            contN++;
                            n = QStringLiteral("%1").arg(contN);

                            for(int x = iniN;x<contN;x++){
                                QString n1 = QStringLiteral("%1").arg(x);
                                QString n2 = QStringLiteral("%1").arg(x + 1);
                                StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                            }
                        }
                    }else{
                        bytes = QStringLiteral("%1").arg(part2.part_size);
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"PRIMARIA | " + bytes + "\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);

                        for(int x = iniN;x<contN;x++){
                            QString n1 = QStringLiteral("%1").arg(x);
                            QString n2 = QStringLiteral("%1").arg(x + 1);
                            StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                        }
                    }
                }else{
                    if(part1.part_start != 0){
                        if(part3.part_start != 0){
                            bytes = QStringLiteral("%1").arg(part3.part_start - part1.part_start - part1.part_size);
                        }else if(part4.part_start != 0){
                            bytes = QStringLiteral("%1").arg(part4.part_start - part1.part_start - part1.part_size);
                        }else{
                            bytes = QStringLiteral("%1").arg(mbr.mbr_tam - part1.part_start - part1.part_size);
                        }
                    }else {
                        if(part3.part_start != 0){
                            bytes = QStringLiteral("%1").arg(part3.part_start - sizeof (mbr));
                        }else if(part4.part_start != 0){
                            bytes = QStringLiteral("%1").arg(part4.part_start - sizeof (mbr));
                        }else{
                            bytes = QStringLiteral("%1").arg(mbr.mbr_tam - sizeof (mbr));
                        }
                    }
                    if(!final){
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"LIBRE | " + bytes + "\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);
                        final=true;
                    }

                    for(int x = iniN;x<contN;x++){
                        QString n1 = QStringLiteral("%1").arg(x);
                        QString n2 = QStringLiteral("%1").arg(x + 1);
                        StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                    }
                }
            }

            if(part3.part_type == 'e' || part3.part_type == 'E'){
                nuevoinicio = part3.part_start;
                tam_Particion = part3.part_size;
                FILE* Debr=fopen(ruta.toStdString().c_str(),"rb+");
                fseek(Debr,part3.part_start,SEEK_SET);
                fread(&ebr,sizeof(EBR),1,Debr);
                fseek(Debr,0,SEEK_SET);
                fclose(Debr);
                iniN = contN;
                if(part3.part_fit != '.'){
                    if(part2.part_start != 0){
                        if((part3.part_start - part2.part_start - part2.part_size) == 0){
                            bytes = QStringLiteral("%1").arg(part3.part_size);
                            StringReporte += "n" + n + " [shape=record,color=red,label=\"EXTENDIDA | " + bytes + "\"];\n";
                            nodoExt = "n" + n;
                            contN++;
                            n = QStringLiteral("%1").arg(contN);

                            for(int x = iniN;x<contN;x++){
                                QString n1 = QStringLiteral("%1").arg(x);
                                QString n2 = QStringLiteral("%1").arg(x + 1);
                                StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                            }
                        }else {
                            bytes = QStringLiteral("%1").arg(part3.part_start - part2.part_start - part2.part_size);
                            StringReporte += "n" + n + " [shape=record,color=red,label=\"LIBRE | " + bytes + "\"];\n";
                            contN++;
                            n = QStringLiteral("%1").arg(contN);
                            bytes = QStringLiteral("%1").arg(part3.part_size);
                            StringReporte += "n" + n + " [shape=record,color=red,label=\"EXTENDIDA | " + bytes + "\"];\n";
                            nodoExt = "n" + n;
                            contN++;
                            n = QStringLiteral("%1").arg(contN);

                            for(int x = iniN;x<contN;x++){
                                QString n1 = QStringLiteral("%1").arg(x);
                                QString n2 = QStringLiteral("%1").arg(x + 1);
                                StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                            }
                        }
                    }else{
                        bytes = QStringLiteral("%1").arg(part3.part_size);
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"EXTENDIDA | " + bytes + "\"];\n";
                        nodoExt = "n" + n;
                        contN++;
                        n = QStringLiteral("%1").arg(contN);

                        for(int x = iniN;x<contN;x++){
                            QString n1 = QStringLiteral("%1").arg(x);
                            QString n2 = QStringLiteral("%1").arg(x + 1);
                            StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                        }
                    }
                }else{
                    if(part4.part_start != 0){
                        if(part2.part_start != 0){
                            bytes = QStringLiteral("%1").arg(part4.part_start - part2.part_start - part2.part_size);
                        }else if(part1.part_start != 0){
                            bytes = QStringLiteral("%1").arg(part4.part_start - part1.part_start - part1.part_size);
                        }else{
                            bytes = QStringLiteral("%1").arg(part4.part_start - sizeof (mbr));
                        }
                    }else{
                        if(part2.part_start != 0){
                            bytes = QStringLiteral("%1").arg(mbr.mbr_tam - part2.part_start - part2.part_size);
                        }else if(part1.part_start != 0){
                            bytes = QStringLiteral("%1").arg(mbr.mbr_tam - part1.part_start - part1.part_size);
                        }else{
                            bytes = QStringLiteral("%1").arg(mbr.mbr_tam - sizeof (mbr));
                        }
                    }
                    if(!final){
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"LIBRE | " + bytes + "\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);
                        final=true;
                    }

                    for(int x = iniN;x<contN;x++){
                        QString n1 = QStringLiteral("%1").arg(x);
                        QString n2 = QStringLiteral("%1").arg(x + 1);
                        StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                    }
                }
            }else{
                iniN = contN;
                if(part3.part_fit != '.'){
                    if(part2.part_start != 0){
                        if((part3.part_start - part2.part_start - part2.part_size) == 0){
                            bytes = QStringLiteral("%1").arg(part3.part_size);
                            StringReporte += "n" + n + " [shape=record,color=red,label=\"PRIMARIA | " + bytes + "\"];\n";
                            contN++;
                            n = QStringLiteral("%1").arg(contN);

                            for(int x = iniN;x<contN;x++){
                                QString n1 = QStringLiteral("%1").arg(x);
                                QString n2 = QStringLiteral("%1").arg(x + 1);
                                StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                            }
                        }else {
                            bytes = QStringLiteral("%1").arg(part3.part_start - part2.part_start - part2.part_size);
                            StringReporte += "n" + n + " [shape=record,color=red,label=\"LIBRE | " + bytes + "\"];\n";
                            contN++;
                            n = QStringLiteral("%1").arg(contN);
                            bytes = QStringLiteral("%1").arg(part3.part_size);
                            StringReporte += "n" + n + " [shape=record,color=red,label=\"PRIMARIA | " + bytes + "\"];\n";
                            contN++;
                            n = QStringLiteral("%1").arg(contN);

                            for(int x = iniN;x<contN;x++){
                                QString n1 = QStringLiteral("%1").arg(x);
                                QString n2 = QStringLiteral("%1").arg(x + 1);
                                StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                            }
                        }
                    }else{
                        bytes = QStringLiteral("%1").arg(part3.part_size);
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"PRIMARIA | " + bytes + "\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);

                        for(int x = iniN;x<contN;x++){
                            QString n1 = QStringLiteral("%1").arg(x);
                            QString n2 = QStringLiteral("%1").arg(x + 1);
                            StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                        }
                    }
                }else{
                    if(part4.part_start != 0){
                        if(part2.part_start != 0){
                            bytes = QStringLiteral("%1").arg(part4.part_start - part2.part_start - part2.part_size);
                        }else if(part1.part_start != 0){
                            bytes = QStringLiteral("%1").arg(part4.part_start - part1.part_start - part1.part_size);
                        }else{
                            bytes = QStringLiteral("%1").arg(part4.part_start - sizeof (mbr));
                        }
                    }else{
                        if(part2.part_start != 0){
                            bytes = QStringLiteral("%1").arg(mbr.mbr_tam - part2.part_start - part2.part_size);
                        }else if(part1.part_start != 0){
                            bytes = QStringLiteral("%1").arg(mbr.mbr_tam - part1.part_start - part1.part_size);
                        }else{
                            bytes = QStringLiteral("%1").arg(mbr.mbr_tam - sizeof (mbr));
                        }
                    }
                    if(!final){
                        final=true;
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"LIBRE | " + bytes + "\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);
                    }

                    for(int x = iniN;x<contN;x++){
                        QString n1 = QStringLiteral("%1").arg(x);
                        QString n2 = QStringLiteral("%1").arg(x + 1);
                        StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                    }
                }
            }

            if(part4.part_type == 'e' || part4.part_type == 'E'){
                nuevoinicio = part4.part_start;
                tam_Particion = part4.part_size;
                FILE* Debr=fopen(ruta.toStdString().c_str(),"rb+");
                fseek(Debr,part4.part_start,SEEK_SET);
                fread(&ebr,sizeof(EBR),1,Debr);
                fseek(Debr,0,SEEK_SET);
                fclose(Debr);
                iniN = contN;
                if(part4.part_fit != '.'){
                    if(part3.part_start != 0){
                        if((part4.part_start - part3.part_start - part3.part_size) == 0){
                            bytes = QStringLiteral("%1").arg(part4.part_size);
                            StringReporte += "n" + n + " [shape=record,color=red,label=\"EXTENDIDA | " + bytes + "\"];\n";
                            nodoExt = "n" + n;
                            contN++;
                            n = QStringLiteral("%1").arg(contN);

                            for(int x = iniN;x<contN;x++){
                                QString n1 = QStringLiteral("%1").arg(x);
                                QString n2 = QStringLiteral("%1").arg(x + 1);
                                StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                            }
                        }else {
                            bytes = QStringLiteral("%1").arg(part4.part_start - part3.part_start - part3.part_size);
                            StringReporte += "n" + n + " [shape=record,color=red,label=\"LIBRE | " + bytes + "\"];\n";
                            contN++;
                            n = QStringLiteral("%1").arg(contN);
                            bytes = QStringLiteral("%1").arg(part4.part_size);
                            StringReporte += "n" + n + " [shape=record,color=red,label=\"EXTENDIDA | " + bytes + "\"];\n";
                            nodoExt = "n" + n;
                            contN++;
                            n = QStringLiteral("%1").arg(contN);

                            for(int x = iniN;x<contN;x++){
                                QString n1 = QStringLiteral("%1").arg(x);
                                QString n2 = QStringLiteral("%1").arg(x + 1);
                                StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                            }
                        }
                    }else{
                        bytes = QStringLiteral("%1").arg(part4.part_size);
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"EXTENDIDA | " + bytes + "\"];\n";
                        nodoExt = "n" + n;
                        contN++;
                        n = QStringLiteral("%1").arg(contN);

                        for(int x = iniN;x<contN;x++){
                            QString n1 = QStringLiteral("%1").arg(x);
                            QString n2 = QStringLiteral("%1").arg(x + 1);
                            StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                        }
                    }
                }
            }else{
                iniN = contN;
                if(part4.part_fit != '.'){
                    if(part3.part_start != 0){
                        if((part4.part_start - part3.part_start - part3.part_size) == 0){
                            bytes = QStringLiteral("%1").arg(part4.part_size);
                            StringReporte += "n" + n + " [shape=record,color=red,label=\"PRIMARIA | " + bytes + "\"];\n";
                            contN++;
                            n = QStringLiteral("%1").arg(contN);

                            for(int x = iniN;x<contN;x++){
                                QString n1 = QStringLiteral("%1").arg(x);
                                QString n2 = QStringLiteral("%1").arg(x + 1);
                                StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                            }
                        }else {
                            bytes = QStringLiteral("%1").arg(part4.part_start - part3.part_start - part3.part_size);
                            StringReporte += "n" + n + " [shape=record,color=red,label=\"LIBRE | " + bytes + "\"];\n";
                            contN++;
                            n = QStringLiteral("%1").arg(contN);
                            bytes = QStringLiteral("%1").arg(part4.part_size);
                            StringReporte += "n" + n + " [shape=record,color=red,label=\"PRIMARIA | " + bytes + "\"];\n";
                            contN++;
                            n = QStringLiteral("%1").arg(contN);

                            for(int x = iniN;x<contN;x++){
                                QString n1 = QStringLiteral("%1").arg(x);
                                QString n2 = QStringLiteral("%1").arg(x + 1);
                                StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                            }
                        }
                    }else{
                        bytes = QStringLiteral("%1").arg(part4.part_size);
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"PRIMARIA | " + bytes + "\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);

                        for(int x = iniN;x<contN;x++){
                            QString n1 = QStringLiteral("%1").arg(x);
                            QString n2 = QStringLiteral("%1").arg(x + 1);
                            StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                        }
                    }
                }
            }

            if(!final){
                if((mbr.mbr_tam - part4.part_start - part4.part_size) != 0){
                    if(part4.part_start != 0){
                        bytes = QStringLiteral("%1").arg(mbr.mbr_tam - part4.part_start - part4.part_size);
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"LIBRE | " + bytes + "\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);
                    }else if(part3.part_start != 0){
                        bytes = QStringLiteral("%1").arg(mbr.mbr_tam - part3.part_start - part3.part_size);
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"LIBRE | " + bytes + "\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);
                    }else if(part2.part_start != 0){
                        bytes = QStringLiteral("%1").arg(mbr.mbr_tam - part2.part_start - part2.part_size);
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"LIBRE | " + bytes + "\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);
                    }else if(part1.part_start != 0){
                        bytes = QStringLiteral("%1").arg(mbr.mbr_tam - part1.part_start - part1.part_size);
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"LIBRE | " + bytes + "\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);
                    }else{
                        bytes = QStringLiteral("%1").arg(mbr.mbr_tam - sizeof (mbr));
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"LIBRE | " + bytes + "\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);
                    }
                }
            }

            StringReporte += "}\n";
            if(nodoExt != ""){
                EBR siguiente = ebr;
                StringReporte += "subgraph cluster1{\n";
                iniExt = "n" + n;
                int espacioUtilizado = 0;
                while(ebr.part_next != -1){
                    ebr = siguiente;
                    FILE* Debr=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Debr,siguiente.part_next,SEEK_SET);
                    fread(&siguiente,sizeof(EBR),1,Debr);
                    fseek(Debr,0,SEEK_SET);
                    fclose(Debr);

                    if(siguiente.part_next != -1){
                        if((siguiente.part_start - ebr.part_start - ebr.part_size - sizeof (ebr)) == 0){
                            iniN = contN;
                            bytes = QStringLiteral("%1").arg(sizeof (ebr));
                            StringReporte += "n" + n + " [shape=record,color=red,label=\"EBR | " + bytes + "\"];\n";
                            contN++;
                            n = QStringLiteral("%1").arg(contN);
                            bytes = QStringLiteral("%1").arg(ebr.part_size);
                            StringReporte += "n" + n + " [shape=record,color=red,label=\"ESPACIO_EBR | " + bytes + "\"];\n";
                            contN++;
                            n = QStringLiteral("%1").arg(contN);

                            espacioUtilizado = espacioUtilizado + sizeof (ebr) + ebr.part_size;

                            for(int x = iniN;x<contN;x++){
                                QString n1 = QStringLiteral("%1").arg(x);
                                QString n2 = QStringLiteral("%1").arg(x + 1);
                                StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                            }
                        }else{
                            iniN = contN;
                            bytes = QStringLiteral("%1").arg(sizeof (ebr));
                            StringReporte += "n" + n + " [shape=record,color=red,label=\"EBR | " + bytes + "\"];\n";
                            contN++;
                            n = QStringLiteral("%1").arg(contN);
                            bytes = QStringLiteral("%1").arg(ebr.part_size);
                            StringReporte += "n" + n + " [shape=record,color=red,label=\"ESPACIO_EBR | " + bytes + "\"];\n";
                            contN++;
                            n = QStringLiteral("%1").arg(contN);
                            bytes = QStringLiteral("%1").arg(siguiente.part_start - ebr.part_start - ebr.part_size - sizeof (ebr));
                            StringReporte += "n" + n + " [shape=record,color=red,label=\"ESPACIO_LIBRE | " + bytes + "\"];\n";
                            contN++;
                            n = QStringLiteral("%1").arg(contN);

                            espacioUtilizado = espacioUtilizado + sizeof (ebr) + ebr.part_size + (siguiente.part_start - ebr.part_start - ebr.part_size - sizeof (ebr));

                            for(int x = iniN;x<contN;x++){
                                QString n1 = QStringLiteral("%1").arg(x);
                                QString n2 = QStringLiteral("%1").arg(x + 1);
                                StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                            }
                        }
                    }else{
                        iniN = contN;
                        bytes = QStringLiteral("%1").arg(sizeof (ebr));
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"EBR | " + bytes + "\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);
                        bytes = QStringLiteral("%1").arg(ebr.part_size);
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"ESPACIO_EBR | " + bytes + "\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);

                        espacioUtilizado = espacioUtilizado + sizeof (ebr) + ebr.part_size;

                        for(int x = iniN;x<contN;x++){
                            QString n1 = QStringLiteral("%1").arg(x);
                            QString n2 = QStringLiteral("%1").arg(x + 1);
                            StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                        }
                        if((tam_Particion - espacioUtilizado)>0){
                            bytes = QStringLiteral("%1").arg(tam_Particion - espacioUtilizado);
                            StringReporte += "n" + n + " [shape=record,color=red,label=\"LIBRE | " + bytes + "\"];\n";
                        }
                        break;
                    }
                }
                StringReporte += "}\n";
                StringReporte += nodoExt + " ->" + iniExt + " \n";

            }
            StringReporte += "}\n";

            //INGRESAMOS AL REPORTE LAS EBR DE LA EXTENDIDA

            QStringList direccionReporte = reporte->path.split("/");
            QString rutaR = "";
            bool primera = false;
            if(direccionReporte[1] == "home" && direccionReporte[2] == "archivos"){
                rutaR = "/home/oscar/archivos";
                for(int x=3;x<(direccionReporte.length()-1);x++){
                    if(primera){
                        QDir direc(rutaR);
                        direc.mkdir(direccionReporte[x]);
                        rutaR = rutaR + direccionReporte[x] + "/";
                    }else{
                        QDir direc(rutaR);
                        direc.mkdir(direccionReporte[x]);
                        rutaR = rutaR + "/" + direccionReporte[x] + "/";
                        primera = true;
                    }
                }
            }

            QString aux =direccionReporte[direccionReporte.length()-1];
            QStringList extensionReporte = aux.split(".");
            QString rutadot = rutaR;
            if(extensionReporte[1].toLower() == "jpg"){
                //AQUI CREAMOS ARCHIVO FISICO
                if(primera){
                    rutaR = rutaR + aux;
                }else{
                    rutaR = rutaR + "/" + aux;
                }
                //EJECUTAR COMANDO GRAPVHIZ
                rutadot = rutadot + "/" + extensionReporte[0] + ".dot";
                ofstream dot;
                dot.open(rutadot.toStdString().c_str(),ios::out);
                if(dot.fail()){
                    cout<<"No Se Creo El Archivo .dot"<<endl;
                }
                dot<<StringReporte.toStdString().c_str();
                dot.close();

                QString comando = "dot -Tjpg " + rutadot + " -o " + rutaR;
                system(comando.toStdString().c_str());
                cout<<"El Reporte DISK Se Creo Exitosamente :D"<<endl;
            }else{
                cout<<"Extension de Reporte incorrecta, no es .jpg"<<endl;
            }

        }else if(reporte->namee.toLower() == "journaling"){
            cout<<"-----------------------ReporteJOURNALING---------------------"<<endl;
            StringReporte = "digraph G { bgcolor=\"yellow:purple\"\n";
            StringReporte += "node [shape=filled];\n";
            StringReporte += "a0 [label=<\n";
            StringReporte += "<TABLE border=\"10\" cellspacing=\"10\" cellpadding=\"10\" style=\"rounded\" bgcolor=\"green:red\" gradientangle=\"315\">\n";
            StringReporte += "<TR>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"gray\">NOMBRE</TD>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"gray\">VALOR</TD>\n";
            StringReporte += "</TR>\n";

            if(sb.s_filesystem_type == 3){
                int inicio = iniciojour;
                FILE *Particion;
                Journaling vitacora;
                while (iniciojour <= (sb.s_bm_inode_start - inicio)) {
                    Particion=fopen(ruta.toStdString().c_str(),"rb+");
                    fseek(Particion,iniciojour,SEEK_SET);
                    fread(&vitacora,sizeof(Journaling),1,Particion);
                    fseek(Particion,0,SEEK_SET);
                    fclose(Particion);
                    iniciojour += sizeof (Journaling);
                    QString linea(vitacora.Comando);
                    StringReporte += "<TR>\n";
                    StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">Comando</TD>\n";
                    StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">"+linea+"</TD>\n";
                    StringReporte += "</TR>\n";
                }
            }else{
                cout<<"La Particion No Tiene Formato EXT3"<<endl;
            }

            StringReporte += "</TABLE>>];\n";
            StringReporte += "}\n";

            QStringList direccionReporte = reporte->path.split("/");
            QString rutaR = "";
            bool primera = false;
            if(direccionReporte[1] == "home" && direccionReporte[2] == "archivos"){
                rutaR = "/home/oscar/archivos";
                for(int x=3;x<(direccionReporte.length()-1);x++){
                    if(primera){
                        QDir direc(rutaR);
                        direc.mkdir(direccionReporte[x]);
                        rutaR = rutaR + direccionReporte[x] + "/";
                    }else{
                        QDir direc(rutaR);
                        direc.mkdir(direccionReporte[x]);
                        rutaR = rutaR + "/" + direccionReporte[x] + "/";
                        primera = true;
                    }
                }
            }

            QString aux =direccionReporte[direccionReporte.length()-1];
            QStringList extensionReporte = aux.split(".");
            QString rutadot = rutaR;
            if(extensionReporte[1].toLower() == "jpg"){
                //AQUI CREAMOS ARCHIVO FISICO
                if(primera){
                    rutaR = rutaR + aux;
                }else{
                    rutaR = rutaR + "/" + aux;
                }
                //EJECUTAR COMANDO GRAPVHIZ
                rutadot = rutadot + "/" + extensionReporte[0] + ".dot";
                ofstream dot;
                dot.open(rutadot.toStdString().c_str(),ios::out);
                if(dot.fail()){
                    cout<<"No Se Creo El Archivo .dot"<<endl;
                }
                dot<<StringReporte.toStdString().c_str();
                dot.close();

                QString comando = "dot -Tjpg " + rutadot + " -o " + rutaR;
                system(comando.toStdString().c_str());
                cout<<"El Reporte Journaling Se Creo Exitosamente :D"<<endl;
            }else{
                cout<<"Extension de Reporte incorrecta, no es .jpg"<<endl;
            }

        }else if(reporte->namee.toLower() == "inode"){
            cout<<"-----------------------ReporteINODE---------------------"<<endl;
            StringReporte = "digraph G { bgcolor=\"yellow:purple\"\n";

            QStringList posNodos;
            char bit = 'a';
            int inicio = sb.s_bm_inode_start;
            int contador = 0;
            while (inicio < (sb.s_bm_inode_start + sb.s_inodes_count)) {
                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                fseek(Particion,inicio,SEEK_SET);
                fread(&bit,sizeof(bit),1,Particion);
                fseek(Particion,0,SEEK_SET);
                fclose(Particion);
                if(bit == '1'){
                    QString num = QStringLiteral("%1").arg(contador);
                    posNodos.append(num);
                }
                contador++;
                inicio+=sizeof(bit);
            }

            TablaInodos inodoT;
            inicio = sb.s_inode_start;
            FILE *Particion;
            QStringList nodos;
            int cantnodos = 0;
            while (inicio < sb.s_block_start) {
                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                fseek(Particion,inicio,SEEK_SET);
                fread(&inodoT,sizeof(inodoT),1,Particion);
                fseek(Particion,0,SEEK_SET);
                fclose(Particion);
                inicio+=sizeof(inodoT);
                if(inodoT.i_type == '\0'){break;}

                QString numnodo = QStringLiteral("%1").arg(cantnodos);
                StringReporte += "n" + numnodo + " [shape=record,label=\"{ Inodo " + posNodos[cantnodos] + " |";

                QString uid = QStringLiteral("%1").arg(inodoT.i_uid);
                StringReporte += "{i_uid | " + uid + "}|";
                QString gid = QStringLiteral("%1").arg(inodoT.i_gid);
                StringReporte += "{i_gid | " + gid + "}|";
                QString zise = QStringLiteral("%1").arg(inodoT.i_size);
                StringReporte += "{i_zise | " + zise + "}|";
                struct tm *tm;
                tm=localtime(&inodoT.i_atime);
                QString dia = QStringLiteral("%1").arg(tm->tm_mday);
                QString mes = QStringLiteral("%1").arg(tm->tm_mon);
                QString anio = QStringLiteral("%1").arg(tm->tm_year);
                QString hora = QStringLiteral("%1").arg(tm->tm_hour);
                QString min = QStringLiteral("%1").arg(tm->tm_min);
                QString seg = QStringLiteral("%1").arg(tm->tm_sec);
                StringReporte += "{i_atime | "+ dia + "/" + mes + "/" + anio + "/ " + hora + ":" + min + ":" + seg +" }|";
                tm=localtime(&inodoT.i_ctime);
                dia = QStringLiteral("%1").arg(tm->tm_mday);
                mes = QStringLiteral("%1").arg(tm->tm_mon);
                anio = QStringLiteral("%1").arg(tm->tm_year);
                hora = QStringLiteral("%1").arg(tm->tm_hour);
                min = QStringLiteral("%1").arg(tm->tm_min);
                seg = QStringLiteral("%1").arg(tm->tm_sec);
                StringReporte += "{i_ctime | "+ dia + "/" + mes + "/" + anio + "/ " + hora + ":" + min + ":" + seg +" }|";
                tm=localtime(&inodoT.i_mtime);
                dia = QStringLiteral("%1").arg(tm->tm_mday);
                mes = QStringLiteral("%1").arg(tm->tm_mon);
                anio = QStringLiteral("%1").arg(tm->tm_year);
                hora = QStringLiteral("%1").arg(tm->tm_hour);
                min = QStringLiteral("%1").arg(tm->tm_min);
                seg = QStringLiteral("%1").arg(tm->tm_sec);
                StringReporte += "{i_mtime | "+ dia + "/" + mes + "/" + anio + "/ " + hora + ":" + min + ":" + seg +" }|";
                for(int x=0;x<15;x++){
                    QString numblock = QStringLiteral("%1").arg(x);
                    QString puntblock = QStringLiteral("%1").arg(inodoT.i_block[x]);
                    StringReporte += "{i_block " + numblock + " | " + puntblock + "}|";
                }
                QString tipo(inodoT.i_type);
                StringReporte += "{i_type | " + tipo + "}|";
                QString perm = QStringLiteral("%1").arg(inodoT.i_perm);
                StringReporte += "{i_perm | " + perm + "}|";

                StringReporte += " }\"];\n";
                nodos.append("n"+numnodo);
                cantnodos++;
            }

            for(int x = 1;x<cantnodos;x++){
                QString numnodo = QStringLiteral("%1").arg(x);
                QString numnodo2 = QStringLiteral("%1").arg(x-1);
                StringReporte += "n" + numnodo2 + " -> n" + numnodo + " \n";
            }

            StringReporte += "}\n";

            QStringList direccionReporte = reporte->path.split("/");
            QString rutaR = "";
            bool primera = false;
            if(direccionReporte[1] == "home" && direccionReporte[2] == "archivos"){
                rutaR = "/home/oscar/archivos";
                for(int x=3;x<(direccionReporte.length()-1);x++){
                    if(primera){
                        QDir direc(rutaR);
                        direc.mkdir(direccionReporte[x]);
                        rutaR = rutaR + direccionReporte[x] + "/";
                    }else{
                        QDir direc(rutaR);
                        direc.mkdir(direccionReporte[x]);
                        rutaR = rutaR + "/" + direccionReporte[x] + "/";
                        primera = true;
                    }
                }
            }

            QString aux =direccionReporte[direccionReporte.length()-1];
            QStringList extensionReporte = aux.split(".");
            QString rutadot = rutaR;
            if(extensionReporte[1].toLower() == "jpg"){
                //AQUI CREAMOS ARCHIVO FISICO
                if(primera){
                    rutaR = rutaR + aux;
                }else{
                    rutaR = rutaR + "/" + aux;
                }
                //EJECUTAR COMANDO GRAPVHIZ
                rutadot = rutadot + "/" + extensionReporte[0] + ".dot";
                ofstream dot;
                dot.open(rutadot.toStdString().c_str(),ios::out);
                if(dot.fail()){
                    cout<<"No Se Creo El Archivo .dot"<<endl;
                }
                dot<<StringReporte.toStdString().c_str();
                dot.close();

                QString comando = "dot -Tjpg " + rutadot + " -o " + rutaR;
                system(comando.toStdString().c_str());
                cout<<"El Reporte Inode Se Creo Exitosamente :D"<<endl;
            }else{
                cout<<"Extension de Reporte incorrecta, no es .jpg"<<endl;
            }
        }else if(reporte->namee.toLower() == "block"){
            cout<<"-----------------------ReporteBLOCK---------------------"<<endl;
            StringReporte = "digraph G { bgcolor=\"yellow:purple\"\n";


            QStringList posNodos;
            char bit = 'a';
            int inicio = sb.s_bm_block_start;
            int contador = 0;
            while (inicio <= (sb.s_bm_block_start + sb.s_blocks_count)) {
                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                fseek(Particion,inicio,SEEK_SET);
                fread(&bit,sizeof(bit),1,Particion);
                fseek(Particion,0,SEEK_SET);
                fclose(Particion);
                if(bit == '1'){
                    QString num = QStringLiteral("%1").arg(contador);
                    posNodos.append(num);
                }
                contador++;
                inicio+=sizeof(bit);
            }

            TablaInodos inodoT;
            inicio = sb.s_inode_start;
            FILE *Particion;
            int cantnodos = 0;
            BloquesApuntadores apuntador;
            BloquesArchivos archivo;
            BloquesCarpetas carpeta;
            QStringList nodos;
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

                            QString numnodo = QStringLiteral("%1").arg(cantnodos);
                            StringReporte += "n" + numnodo + " [shape=record,label=\"{ Bloque Puntero " + posNodos[cantnodos] + " |";
                            for(int x=0;x<16;x++){
                                QString numP = QStringLiteral("%1").arg(x);
                                QString Puntero = QStringLiteral("%1").arg(apuntador.b_pointers[x]);
                                StringReporte += "{Puntero" + numP + " | " + Puntero + "}|";
                            }
                            StringReporte += " }\"];\n";
                            nodos.append("n"+numnodo);
                            cantnodos++;
                        }else if(x==13){
                            //Apuntador doble
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_block_start + (inodoT.i_block[x]*64),SEEK_SET);
                            fread(&apuntador,sizeof(apuntador),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            QString numnodo = QStringLiteral("%1").arg(cantnodos);
                            StringReporte += "n" + numnodo + " [shape=record,label=\"{ Bloque Puntero " + posNodos[cantnodos] + " |";
                            for(int x=0;x<16;x++){
                                QString numP = QStringLiteral("%1").arg(x);
                                QString Puntero = QStringLiteral("%1").arg(apuntador.b_pointers[x]);
                                StringReporte += "{Puntero" + numP + " | " + Puntero + "}|";
                            }
                            StringReporte += " }\"];\n";
                            nodos.append("n"+numnodo);
                            cantnodos++;
                        }else if(x==12){
                            //Apuntador simple
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_block_start + (inodoT.i_block[x]*64),SEEK_SET);
                            fread(&apuntador,sizeof(apuntador),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            QString numnodo = QStringLiteral("%1").arg(cantnodos);
                            StringReporte += "n" + numnodo + " [shape=record,label=\"{ Bloque Puntero " + posNodos[cantnodos] + " |";
                            for(int x=0;x<16;x++){
                                QString numP = QStringLiteral("%1").arg(x);
                                QString Puntero = QStringLiteral("%1").arg(apuntador.b_pointers[x]);
                                StringReporte += "{Puntero" + numP + " | " + Puntero + "}|";
                            }
                            StringReporte += " }\"];\n";
                            nodos.append("n"+numnodo);
                            cantnodos++;
                        }else{
                            if(inodoT.i_type == '0'){
                                //Carpeta
                                //donde empiezan bloques + (intapuntador * 64)
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,sb.s_block_start + (inodoT.i_block[x]*64),SEEK_SET);
                                fread(&carpeta,sizeof(carpeta),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);

                                QString numnodo = QStringLiteral("%1").arg(cantnodos);
                                StringReporte += "n" + numnodo + " [shape=record,label=\"{ Bloque Carpeta " + posNodos[cantnodos] + " |";
                                for(int x=0;x<4;x++){
                                    QString nombreC_A(carpeta.b_content[x].b_name);
                                    QString Puntero = QStringLiteral("%1").arg(carpeta.b_content[x].b_inodo);
                                    StringReporte += "{ " + nombreC_A + " | " + Puntero + "}|";
                                }
                                StringReporte += " }\"];\n";
                                nodos.append("n"+numnodo);
                                cantnodos++;
                            }else{
                                //Archivo
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,sb.s_block_start + (inodoT.i_block[x]*64),SEEK_SET);
                                fread(&archivo,sizeof(archivo),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);

                                QString numnodo = QStringLiteral("%1").arg(cantnodos);
                                QString contenido(archivo.b_content);
                                StringReporte += "n" + numnodo + " [shape=record,label=\"{Bloque Archivo " + posNodos[cantnodos] + " |" + contenido + " }\"];\n";
                                nodos.append("n"+numnodo);
                                cantnodos++;
                            }
                        }
                    }
                }
            }

            for(int x = 1;x<cantnodos;x++){
                QString numnodo = QStringLiteral("%1").arg(x);
                QString numnodo2 = QStringLiteral("%1").arg(x-1);
                StringReporte += "n" + numnodo2 + " -> n" + numnodo + " \n";
            }

            StringReporte += "}\n";

            QStringList direccionReporte = reporte->path.split("/");
            QString rutaR = "";
            bool primera = false;
            if(direccionReporte[1] == "home" && direccionReporte[2] == "archivos"){
                rutaR = "/home/oscar/archivos";
                for(int x=3;x<(direccionReporte.length()-1);x++){
                    if(primera){
                        QDir direc(rutaR);
                        direc.mkdir(direccionReporte[x]);
                        rutaR = rutaR + direccionReporte[x] + "/";
                    }else{
                        QDir direc(rutaR);
                        direc.mkdir(direccionReporte[x]);
                        rutaR = rutaR + "/" + direccionReporte[x] + "/";
                        primera = true;
                    }
                }
            }

            QString aux =direccionReporte[direccionReporte.length()-1];
            QStringList extensionReporte = aux.split(".");
            QString rutadot = rutaR;
            if(extensionReporte[1].toLower() == "jpg"){
                //AQUI CREAMOS ARCHIVO FISICO
                if(primera){
                    rutaR = rutaR + aux;
                }else{
                    rutaR = rutaR + "/" + aux;
                }
                //EJECUTAR COMANDO GRAPVHIZ
                rutadot = rutadot + "/" + extensionReporte[0] + ".dot";
                ofstream dot;
                dot.open(rutadot.toStdString().c_str(),ios::out);
                if(dot.fail()){
                    cout<<"No Se Creo El Archivo .dot"<<endl;
                }
                dot<<StringReporte.toStdString().c_str();
                dot.close();

                QString comando = "dot -Tjpg " + rutadot + " -o " + rutaR;
                system(comando.toStdString().c_str());
                cout<<"El Reporte Block Se Creo Exitosamente :D"<<endl;
            }else{
                cout<<"Extension de Reporte incorrecta, no es .jpg"<<endl;
            }

        }else if(reporte->namee.toLower() == "bm_inode"){
            cout<<"-----------------------ReporteBM_INODE---------------------"<<endl;
            char bit = 'a';
            int inicio = sb.s_bm_inode_start;
            int contador = 0;
            FILE *Particion;
            while (inicio <= (sb.s_bm_inode_start + sb.s_inodes_count)) {
                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                fseek(Particion,inicio,SEEK_SET);
                fread(&bit,sizeof(bit),1,Particion);
                fseek(Particion,0,SEEK_SET);
                fclose(Particion);
                if(bit=='1'){StringReporte += "[";
                    StringReporte += bit;
                    StringReporte += "]";
                }else{
                    StringReporte += "[0]";
                }
                contador++;
                if(contador == 20){StringReporte += '\n'; contador = 0;}
                inicio+=sizeof(bit);
            }

            QStringList direccionReporte = reporte->path.split("/");
            QString rutaR = "";
            bool primera = false;
            if(direccionReporte[1] == "home" && direccionReporte[2] == "archivos"){
                rutaR = "/home/oscar/archivos";
                for(int x=3;x<(direccionReporte.length()-1);x++){
                    if(primera){
                        QDir direc(rutaR);
                        direc.mkdir(direccionReporte[x]);
                        rutaR = rutaR + direccionReporte[x] + "/";
                    }else{
                        QDir direc(rutaR);
                        direc.mkdir(direccionReporte[x]);
                        rutaR = rutaR + "/" + direccionReporte[x] + "/";
                        primera = true;
                    }
                }
            }

            QString aux =direccionReporte[direccionReporte.length()-1];
            QStringList extensionReporte = aux.split(".");
            QString rutadot = rutaR;
            if(extensionReporte[1].toLower() == "txt"){
                //AQUI CREAMOS ARCHIVO FISICO
                if(primera){
                    rutaR = rutaR + aux;
                }else{
                    rutaR = rutaR + "/" + aux;
                }
                //EJECUTAR COMANDO GRAPVHIZ
                rutadot = rutadot + "/" + extensionReporte[0] + ".txt";
                ofstream dot;
                dot.open(rutadot.toStdString().c_str(),ios::out);
                if(dot.fail()){
                    cout<<"No Se Creo El Archivo .dot"<<endl;
                }
                dot<<StringReporte.toStdString().c_str();
                dot.close();
                cout<<"El Reporte Bm_Inode Se Creo Exitosamente :D"<<endl;
            }else{
                cout<<"Extension de Reporte incorrecta, no es .txt"<<endl;
            }

        }else if(reporte->namee.toLower() == "bm_block"){
            cout<<"-----------------------ReporteBM_BLOCK---------------------"<<endl;
            char bit = 'a';
            int inicio = sb.s_bm_block_start;
            int contador = 0;
            FILE *Particion;
            while (inicio <= (sb.s_bm_block_start + sb.s_blocks_count)) {
                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                fseek(Particion,inicio,SEEK_SET);
                fread(&bit,sizeof(bit),1,Particion);
                fseek(Particion,0,SEEK_SET);
                fclose(Particion);
                if(bit=='1'){StringReporte += "[";
                    StringReporte += bit;
                    StringReporte += "]";
                }else{
                    StringReporte += "[0]";
                }
                contador++;
                if(contador == 20){StringReporte += '\n'; contador = 0;}
                inicio+=sizeof(bit);
            }

            //AQUI CREAMOS ARCHIVO TXT
            QStringList direccionReporte = reporte->path.split("/");
            QString rutaR = "";
            bool primera = false;
            if(direccionReporte[1] == "home" && direccionReporte[2] == "archivos"){
                rutaR = "/home/oscar/archivos";
                for(int x=3;x<(direccionReporte.length()-1);x++){
                    if(primera){
                        QDir direc(rutaR);
                        direc.mkdir(direccionReporte[x]);
                        rutaR = rutaR + direccionReporte[x] + "/";
                    }else{
                        QDir direc(rutaR);
                        direc.mkdir(direccionReporte[x]);
                        rutaR = rutaR + "/" + direccionReporte[x] + "/";
                        primera = true;
                    }
                }
            }

            QString aux =direccionReporte[direccionReporte.length()-1];
            QStringList extensionReporte = aux.split(".");
            QString rutadot = rutaR;
            if(extensionReporte[1].toLower() == "txt"){
                //AQUI CREAMOS ARCHIVO FISICO
                if(primera){
                    rutaR = rutaR + aux;
                }else{
                    rutaR = rutaR + "/" + aux;
                }
                //EJECUTAR COMANDO GRAPVHIZ
                rutadot = rutadot + "/" + extensionReporte[0] + ".txt";
                ofstream dot;
                dot.open(rutadot.toStdString().c_str(),ios::out);
                if(dot.fail()){
                    cout<<"No Se Creo El Archivo .dot"<<endl;
                }
                dot<<StringReporte.toStdString().c_str();
                dot.close();
                cout<<"El Reporte Bm_Block Se Creo Exitosamente :D"<<endl;
            }else{
                cout<<"Extension de Reporte incorrecta, no es .txt"<<endl;
            }

        }else if(reporte->namee.toLower() == "tree"){
            cout<<"-----------------------ReporteTREE---------------------"<<endl;
            StringReporte = "digraph G { bgcolor=\"yellow:purple\"\n";

            QStringList posINodos;
            char bit = 'a';
            int inicio = sb.s_bm_inode_start;
            int contador = 0;
            while (inicio < (sb.s_bm_inode_start + sb.s_inodes_count)) {
                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                fseek(Particion,inicio,SEEK_SET);
                fread(&bit,sizeof(bit),1,Particion);
                fseek(Particion,0,SEEK_SET);
                fclose(Particion);
                if(bit == '1'){
                    QString num = QStringLiteral("%1").arg(contador);
                    posINodos.append(num);
                }
                contador++;
                inicio+=sizeof(bit);
            }

            QStringList posBloques;
            bit = 'a';
            inicio = sb.s_bm_block_start;
            contador = 0;
            while (inicio <= (sb.s_bm_block_start + sb.s_blocks_count)) {
                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                fseek(Particion,inicio,SEEK_SET);
                fread(&bit,sizeof(bit),1,Particion);
                fseek(Particion,0,SEEK_SET);
                fclose(Particion);
                if(bit == '1'){
                    QString num = QStringLiteral("%1").arg(contador);
                    posBloques.append(num);
                }
                contador++;
                inicio+=sizeof(bit);
            }

            TablaInodos inodoT;
            inicio = sb.s_inode_start;
            FILE *Particion;
            int cantInodos = 0;
            int cantBloques = 0;
            BloquesApuntadores apuntador;
            BloquesArchivos archivo;
            BloquesCarpetas carpeta;
            QStringList nodos;
            while (inicio < sb.s_block_start) {
                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                fseek(Particion,inicio,SEEK_SET);
                fread(&inodoT,sizeof(inodoT),1,Particion);
                fseek(Particion,0,SEEK_SET);
                fclose(Particion);
                inicio+=sizeof(inodoT);
                if(inodoT.i_type == '\0'){break;}

                //CREAMOS BLOQUE INODO
                StringReporte += "i" + posINodos[cantInodos] + " [shape=record,label=\"{ Inodo " + posINodos[cantInodos] + " |";

                QString uid = QStringLiteral("%1").arg(inodoT.i_uid);
                StringReporte += "{i_uid | " + uid + "}|";
                QString gid = QStringLiteral("%1").arg(inodoT.i_gid);
                StringReporte += "{i_gid | " + gid + "}|";
                QString zise = QStringLiteral("%1").arg(inodoT.i_size);
                StringReporte += "{i_zise | " + zise + "}|";
                struct tm *tm;
                tm=localtime(&inodoT.i_atime);
                QString dia = QStringLiteral("%1").arg(tm->tm_mday);
                QString mes = QStringLiteral("%1").arg(tm->tm_mon);
                QString anio = QStringLiteral("%1").arg(tm->tm_year);
                QString hora = QStringLiteral("%1").arg(tm->tm_hour);
                QString min = QStringLiteral("%1").arg(tm->tm_min);
                QString seg = QStringLiteral("%1").arg(tm->tm_sec);
                StringReporte += "{i_atime | "+ dia + "/" + mes + "/" + anio + "/ " + hora + ":" + min + ":" + seg +" }|";
                tm=localtime(&inodoT.i_ctime);
                dia = QStringLiteral("%1").arg(tm->tm_mday);
                mes = QStringLiteral("%1").arg(tm->tm_mon);
                anio = QStringLiteral("%1").arg(tm->tm_year);
                hora = QStringLiteral("%1").arg(tm->tm_hour);
                min = QStringLiteral("%1").arg(tm->tm_min);
                seg = QStringLiteral("%1").arg(tm->tm_sec);
                StringReporte += "{i_ctime | "+ dia + "/" + mes + "/" + anio + "/ " + hora + ":" + min + ":" + seg +" }|";
                tm=localtime(&inodoT.i_mtime);
                dia = QStringLiteral("%1").arg(tm->tm_mday);
                mes = QStringLiteral("%1").arg(tm->tm_mon);
                anio = QStringLiteral("%1").arg(tm->tm_year);
                hora = QStringLiteral("%1").arg(tm->tm_hour);
                min = QStringLiteral("%1").arg(tm->tm_min);
                seg = QStringLiteral("%1").arg(tm->tm_sec);
                StringReporte += "{i_mtime | "+ dia + "/" + mes + "/" + anio + "/ " + hora + ":" + min + ":" + seg +" }|";
                for(int x=0;x<15;x++){
                    QString numblock = QStringLiteral("%1").arg(x);
                    QString puntblock = QStringLiteral("%1").arg(inodoT.i_block[x]);
                    StringReporte += "{i_block " + numblock + " | " + puntblock + "}|";
                }
                QString tipo(inodoT.i_type);
                StringReporte += "{i_type | " + tipo + "}|";
                QString perm = QStringLiteral("%1").arg(inodoT.i_perm);
                StringReporte += "{i_perm | " + perm + "}|";

                StringReporte += " }\"];\n";
                nodos.append("i"+posINodos[cantInodos]);
                cantInodos++;

                //CREAMOS LOS BLOQUES CONECTADOS AL INODO
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

                            nodos.append("b"+posBloques[cantBloques]);
                            StringReporte += "b" + posBloques[cantBloques] + " [shape=record,label=\"{ Bloque Puntero " + posBloques[cantBloques] + " |";
                            for(int x=0;x<16;x++){
                                QString numP = QStringLiteral("%1").arg(x);
                                QString Puntero = QStringLiteral("%1").arg(apuntador.b_pointers[x]);
                                StringReporte += "{Puntero" + numP + " | " + Puntero + "}|";
                                if(apuntador.b_pointers[x] != -1){
                                    nodos.append("b"+posBloques[cantBloques]+"b"+apuntador.b_pointers[x]);
                                }
                            }
                            StringReporte += " }\"];\n";
                            cantBloques++;
                        }else if(x==13){
                            //Apuntador doble
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_block_start + (inodoT.i_block[x]*64),SEEK_SET);
                            fread(&apuntador,sizeof(apuntador),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            nodos.append("b"+posBloques[cantBloques]);
                            StringReporte += "b" + posBloques[cantBloques] + " [shape=record,label=\"{ Bloque Puntero " + posBloques[cantBloques] + " |";
                            for(int x=0;x<16;x++){
                                QString numP = QStringLiteral("%1").arg(x);
                                QString Puntero = QStringLiteral("%1").arg(apuntador.b_pointers[x]);
                                StringReporte += "{Puntero" + numP + " | " + Puntero + "}|";if(apuntador.b_pointers[x] != -1){
                                    nodos.append("b"+posBloques[cantBloques]+"b"+apuntador.b_pointers[x]);
                                }
                            }
                            StringReporte += " }\"];\n";
                            cantBloques++;
                        }else if(x==12){
                            //Apuntador simple
                            Particion=fopen(ruta.toStdString().c_str(),"rb+");
                            fseek(Particion,sb.s_block_start + (inodoT.i_block[x]*64),SEEK_SET);
                            fread(&apuntador,sizeof(apuntador),1,Particion);
                            fseek(Particion,0,SEEK_SET);
                            fclose(Particion);

                            nodos.append("b"+posBloques[cantBloques]);
                            StringReporte += "b" + posBloques[cantBloques] + " [shape=record,label=\"{ Bloque Puntero " + posBloques[cantBloques] + " |";
                            for(int x=0;x<16;x++){
                                QString numP = QStringLiteral("%1").arg(x);
                                QString Puntero = QStringLiteral("%1").arg(apuntador.b_pointers[x]);
                                StringReporte += "{Puntero" + numP + " | " + Puntero + "}|";
                                if(apuntador.b_pointers[x] != -1){
                                    nodos.append("b"+posBloques[cantBloques]+"b"+apuntador.b_pointers[x]);
                                }
                            }
                            StringReporte += " }\"];\n";
                            cantBloques++;
                        }else{
                            if(inodoT.i_type == '0'){
                                //Carpeta
                                //donde empiezan bloques + (intapuntador * 64)
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,sb.s_block_start + (inodoT.i_block[x]*64),SEEK_SET);
                                fread(&carpeta,sizeof(carpeta),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);

                                StringReporte += "b" + posBloques[cantBloques] + " [shape=record,label=\"{ Bloque Carpeta " + posBloques[cantBloques] + " |";
                                nodos.append("b"+posBloques[cantBloques]);
                                for(int x=0;x<4;x++){
                                    QString nombreC_A(carpeta.b_content[x].b_name);
                                    QString Puntero = QStringLiteral("%1").arg(carpeta.b_content[x].b_inodo);
                                    StringReporte += "{ " + nombreC_A + " | " + Puntero + "}|";
                                    if(carpeta.b_content[x].b_inodo != -1){
                                        nodos.append("b"+posBloques[cantBloques]+"i"+posINodos[cantInodos]);
                                    }
                                }
                                StringReporte += " }\"];\n";

                                cantBloques++;
                            }else{
                                //Archivo
                                Particion=fopen(ruta.toStdString().c_str(),"rb+");
                                fseek(Particion,sb.s_block_start + (inodoT.i_block[x]*64),SEEK_SET);
                                fread(&archivo,sizeof(archivo),1,Particion);
                                fseek(Particion,0,SEEK_SET);
                                fclose(Particion);

                                QString contenido(archivo.b_content);
                                StringReporte += "b" + posBloques[cantBloques] + " [shape=record,label=\"{Bloque Archivo " + posBloques[cantBloques] + " |" + contenido + " }\"];\n";
                                nodos.append("b"+posBloques[cantBloques]);
                                cantBloques++;
                            }
                        }
                    }
                }
            }

            QString pivote = "";
            for(int x = 1;x<nodos.length();x++){
                QString numnodo = nodos[x];
                QString numnodo2 = nodos[x-1];
                if(numnodo.length() == 4){
                    QChar letra = numnodo[0];
                    QChar letra2 = numnodo[1];
                    QString bloquelet(letra);
                    QString bloquenum(letra2);
                    QString bloque = bloquelet+bloquenum;

                    QChar letr3 = numnodo[2];
                    QChar letra4 = numnodo[3];
                    QString inodolet(letr3);
                    QString inodonum(letra4);
                    QString inodo = inodolet+inodonum;
                    StringReporte += bloque + " -> " + inodo + " \n";
                }else {
                    if(numnodo2.length() == 2){
                        if(numnodo2[0] == 'i'){
                            pivote = numnodo2;
                        }
                        StringReporte += pivote + " -> " + numnodo + " \n";
                    }
                }
            }

            StringReporte += "}\n";

            QStringList direccionReporte = reporte->path.split("/");
            QString rutaR = "";
            bool primera = false;
            if(direccionReporte[1] == "home" && direccionReporte[2] == "archivos"){
                rutaR = "/home/oscar/archivos";
                for(int x=3;x<(direccionReporte.length()-1);x++){
                    if(primera){
                        QDir direc(rutaR);
                        direc.mkdir(direccionReporte[x]);
                        rutaR = rutaR + direccionReporte[x] + "/";
                    }else{
                        QDir direc(rutaR);
                        direc.mkdir(direccionReporte[x]);
                        rutaR = rutaR + "/" + direccionReporte[x] + "/";
                        primera = true;
                    }
                }
            }

            QString aux =direccionReporte[direccionReporte.length()-1];
            QStringList extensionReporte = aux.split(".");
            QString rutadot = rutaR;
            if(extensionReporte[1].toLower() == "jpg"){
                //AQUI CREAMOS ARCHIVO FISICO
                if(primera){
                    rutaR = rutaR + aux;
                }else{
                    rutaR = rutaR + "/" + aux;
                }
                //EJECUTAR COMANDO GRAPVHIZ
                rutadot = rutadot + "/" + extensionReporte[0] + ".dot";
                ofstream dot;
                dot.open(rutadot.toStdString().c_str(),ios::out);
                if(dot.fail()){
                    cout<<"No Se Creo El Archivo .dot"<<endl;
                }
                dot<<StringReporte.toStdString().c_str();
                dot.close();

                QString comando = "dot -Tjpg " + rutadot + " -o " + rutaR;
                system(comando.toStdString().c_str());
                cout<<"El Reporte Block Se Creo Exitosamente :D"<<endl;
            }else{
                cout<<"Extension de Reporte incorrecta, no es .jpg"<<endl;
            }

        }else if(reporte->namee.toLower() == "sb"){
            cout<<"-----------------------ReporteSB---------------------"<<endl;
            StringReporte = "digraph G { bgcolor=\"yellow:purple\"\n";
            StringReporte += "node [shape=filled];\n";
            StringReporte += "a0 [label=<\n";
            StringReporte += "<TABLE border=\"10\" cellspacing=\"10\" cellpadding=\"10\" style=\"rounded\" bgcolor=\"green:red\" gradientangle=\"315\">\n";
            StringReporte += "<TR>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"gray\">NOMBRE</TD>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"gray\">VALOR</TD>\n";
            StringReporte += "</TR>\n";



            if(sb.s_filesystem_type == 2 || sb.s_filesystem_type == 3){
                QString filesystem = QStringLiteral("%1").arg(sb.s_filesystem_type);
                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">s_filesystem_type</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">"+filesystem+"</TD>\n";
                StringReporte += "</TR>\n";

                QString inodescount = QStringLiteral("%1").arg(sb.s_inodes_count);
                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">s_inodes_count</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">"+inodescount+"</TD>\n";
                StringReporte += "</TR>\n";

                QString blockcount = QStringLiteral("%1").arg(sb.s_blocks_count);
                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">s_blocks_count</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">"+blockcount+"</TD>\n";
                StringReporte += "</TR>\n";

                QString finodecount = QStringLiteral("%1").arg(sb.s_free_inodes_count);
                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">s_free_inodes_count</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">"+finodecount+"</TD>\n";
                StringReporte += "</TR>\n";

                QString fblockcount = QStringLiteral("%1").arg(sb.s_free_blocks_count);
                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">s_free_blocks_count</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">"+fblockcount+"</TD>\n";
                StringReporte += "</TR>\n";

                struct tm *tm;
                tm=localtime(&sb.s_mtime);
                QString dia = QStringLiteral("%1").arg(tm->tm_mday);
                QString mes = QStringLiteral("%1").arg(tm->tm_mon);
                QString anio = QStringLiteral("%1").arg(tm->tm_year);
                QString hora = QStringLiteral("%1").arg(tm->tm_hour);
                QString min = QStringLiteral("%1").arg(tm->tm_min);
                QString seg = QStringLiteral("%1").arg(tm->tm_sec);
                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">s_mtime</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">"+ dia + "/" + mes + "/" + anio + "/ " + hora + ":" + min + ":" + seg +"</TD>\n";
                StringReporte += "</TR>\n";

                tm=localtime(&sb.s_umtime);
                dia = QStringLiteral("%1").arg(tm->tm_mday);
                mes = QStringLiteral("%1").arg(tm->tm_mon);
                anio = QStringLiteral("%1").arg(tm->tm_year);
                hora = QStringLiteral("%1").arg(tm->tm_hour);
                min = QStringLiteral("%1").arg(tm->tm_min);
                seg = QStringLiteral("%1").arg(tm->tm_sec);
                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">s_umtime</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">"+ dia + "/" + mes + "/" + anio + "/ " + hora + ":" + min + ":" + seg +"</TD>\n";
                StringReporte += "</TR>\n";

                QString mntcount = QStringLiteral("%1").arg(sb.s_mnt_count);
                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">s_mnt_count</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">"+mntcount+"</TD>\n";
                StringReporte += "</TR>\n";

                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">s_magic</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">0xEF53</TD>\n";
                StringReporte += "</TR>\n";

                QString inodesize = QStringLiteral("%1").arg(sb.s_inode_size);
                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">s_inode_size</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">"+inodesize+"</TD>\n";
                StringReporte += "</TR>\n";

                QString blocksize = QStringLiteral("%1").arg(sb.s_block_size);
                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">s_block_size</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">"+blocksize+"</TD>\n";
                StringReporte += "</TR>\n";

                QString firstino = QStringLiteral("%1").arg(sb.s_first_ino);
                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">s_first_ino</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">"+firstino+"</TD>\n";
                StringReporte += "</TR>\n";

                QString fistblock = QStringLiteral("%1").arg(sb.s_first_blo);
                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">s_first_blo</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">"+fistblock+"</TD>\n";
                StringReporte += "</TR>\n";

                QString mbinodestart = QStringLiteral("%1").arg(sb.s_bm_inode_start);
                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">s_bm_inode_start</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">"+mbinodestart+"</TD>\n";
                StringReporte += "</TR>\n";

                QString bmblockstart = QStringLiteral("%1").arg(sb.s_bm_block_start);
                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">s_bm_block_start</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">"+bmblockstart+"</TD>\n";
                StringReporte += "</TR>\n";

                QString inodestart = QStringLiteral("%1").arg(sb.s_inode_start);
                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">s_inode_start</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">"+inodestart+"</TD>\n";
                StringReporte += "</TR>\n";

                QString blockstart = QStringLiteral("%1").arg(sb.s_block_start);
                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">s_block_start</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">"+blockstart+"</TD>\n";
                StringReporte += "</TR>\n";
            }else{
                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">s_filesystem_type</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">.</TD>\n";
                StringReporte += "</TR>\n";

                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">s_inodes_count</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">.</TD>\n";
                StringReporte += "</TR>\n";

                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">s_blocks_count</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">.</TD>\n";
                StringReporte += "</TR>\n";

                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">s_free_inodes_count</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">.</TD>\n";
                StringReporte += "</TR>\n";

                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">s_free_blocks_count</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">.</TD>\n";
                StringReporte += "</TR>\n";

                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">s_mtime</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">.</TD>\n";
                StringReporte += "</TR>\n";

                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">s_umtime</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">.</TD>\n";
                StringReporte += "</TR>\n";

                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">s_mnt_count</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">.</TD>\n";
                StringReporte += "</TR>\n";

                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">s_magic</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">.</TD>\n";
                StringReporte += "</TR>\n";

                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">s_inode_size</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">.</TD>\n";
                StringReporte += "</TR>\n";

                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">s_block_size</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">.</TD>\n";
                StringReporte += "</TR>\n";

                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">s_first_ino</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">.</TD>\n";
                StringReporte += "</TR>\n";

                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">s_first_blo</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">.</TD>\n";
                StringReporte += "</TR>\n";

                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">s_bm_inode_start</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">.</TD>\n";
                StringReporte += "</TR>\n";

                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">s_bm_block_start</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">.</TD>\n";
                StringReporte += "</TR>\n";

                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">s_inode_start</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">.</TD>\n";
                StringReporte += "</TR>\n";

                StringReporte += "<TR>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">s_block_start</TD>\n";
                StringReporte += "<TD border=\"3\"  bgcolor=\"red:yellow\">.</TD>\n";
                StringReporte += "</TR>\n";
            }

            StringReporte += "</TABLE>>];\n";
            StringReporte += "}\n";

            QStringList direccionReporte = reporte->path.split("/");
            QString rutaR = "";
            bool primera = false;
            if(direccionReporte[1] == "home" && direccionReporte[2] == "archivos"){
                rutaR = "/home/oscar/archivos";
                for(int x=3;x<(direccionReporte.length()-1);x++){
                    if(primera){
                        QDir direc(rutaR);
                        direc.mkdir(direccionReporte[x]);
                        rutaR = rutaR + direccionReporte[x] + "/";
                    }else{
                        QDir direc(rutaR);
                        direc.mkdir(direccionReporte[x]);
                        rutaR = rutaR + "/" + direccionReporte[x] + "/";
                        primera = true;
                    }
                }
            }

            QString aux =direccionReporte[direccionReporte.length()-1];
            QStringList extensionReporte = aux.split(".");
            QString rutadot = rutaR;
            if(extensionReporte[1].toLower() == "jpg"){
                //AQUI CREAMOS ARCHIVO FISICO
                if(primera){
                    rutaR = rutaR + aux;
                }else{
                    rutaR = rutaR + "/" + aux;
                }
                //EJECUTAR COMANDO GRAPVHIZ
                rutadot = rutadot + "/" + extensionReporte[0] + ".dot";
                ofstream dot;
                dot.open(rutadot.toStdString().c_str(),ios::out);
                if(dot.fail()){
                    cout<<"No Se Creo El Archivo .dot"<<endl;
                }
                dot<<StringReporte.toStdString().c_str();
                dot.close();

                QString comando = "dot -Tjpg " + rutadot + " -o " + rutaR;
                system(comando.toStdString().c_str());
                cout<<"El Reporte SupberBloque Se Creo Exitosamente :D"<<endl;
            }else{
                cout<<"Extension de Reporte incorrecta, no es .jpg"<<endl;
            }

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
