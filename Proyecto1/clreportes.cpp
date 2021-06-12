#include "clreportes.h"
#include <QString>
#include <iostream>
#include <QStringList>
#include <QDir>
#include <mbrstruct.h>
#include <ebrstruct.h>
#include <time.h>
#include <fstream>
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
        ListaM aux = lista.obtenerNodo(lista.lista,reporte->id);
        QStringList direcciones = aux->ruta.split("/");
        QString ruta = "/home/oscar/archivos";
        QString StringReporte ="";
        bool NoCarpeta = false;

        MBR mbr;
        struct particion part1;
        struct particion part2;
        struct particion part3;
        struct particion part4;

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

            QString name1(part1.part_name);
            StringReporte += "<TR>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"blue:red\">part_name_1</TD>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"blue:red\">"+name1+"</TD>\n";
            StringReporte += "</TR>\n";
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
                        StringReporte += "<TR>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">part_name_1</TD>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">"+nameebr+"</TD>\n";
                        StringReporte += "</TR>\n";
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

            QString name2(part2.part_name);
            StringReporte += "<TR>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"blue:red\">part_name_2</TD>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"blue:red\">"+name2+"</TD>\n";
            StringReporte += "</TR>\n";
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

                        QString nameebr(ebr.part_name);
                        StringReporte += "<TR>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">part_name_2</TD>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">"+nameebr+"</TD>\n";
                        StringReporte += "</TR>\n";
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

            QString name3(part3.part_name);
            StringReporte += "<TR>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"blue:red\">part_name_3</TD>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"blue:red\">"+name3+"</TD>\n";
            StringReporte += "</TR>\n";
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

                        QString nameebr(ebr.part_name);
                        StringReporte += "<TR>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">part_name_3</TD>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">"+nameebr+"</TD>\n";
                        StringReporte += "</TR>\n";
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

            QString name4(part4.part_name);
            StringReporte += "<TR>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"blue:red\">part_name_4</TD>\n";
            StringReporte += "<TD border=\"3\"  bgcolor=\"blue:red\">"+name4+"</TD>\n";
            StringReporte += "</TR>\n";
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

                        QString nameebr(ebr.part_name);
                        StringReporte += "<TR>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">part_name_4</TD>\n";
                        StringReporte += "<TD border=\"3\"  bgcolor=\"red:gray\">"+nameebr+"</TD>\n";
                        StringReporte += "</TR>\n";
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
            int iniN = 1;
            int contN = 1;
            QString n = QStringLiteral("%1").arg(contN);
            EBR ebr;
            StringReporte = "digraph G{\n";
            StringReporte += "compound=true;\n";
            StringReporte += "subgraph cluster0{\n";

            if(part1.part_type == 'e' || part1.part_type == 'E'){
                FILE* Debr=fopen(ruta.toStdString().c_str(),"rb+");
                fseek(Debr,part1.part_start,SEEK_SET);
                fread(&ebr,sizeof(EBR),1,Debr);
                fseek(Debr,0,SEEK_SET);
                fclose(Debr);
                if(part1.part_fit != '.'){
                    if((part1.part_start - sizeof(mbr)) == 0){
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"MBR\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"EXTENDIDA\"];\n";
                        nodoExt = "n" + n;
                        contN++;
                        n = QStringLiteral("%1").arg(contN);

                        for(int x = iniN;x<contN;x++){
                            QString n1 = QStringLiteral("%1").arg(x);
                            QString n2 = QStringLiteral("%1").arg(x + 1);
                            StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                        }
                    }else {
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"MBR\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"LIBRE\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"EXTENDIDA\"];\n";
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
                    StringReporte += "n" + n + " [shape=record,color=red,label=\"MBR\"];\n";
                    contN++;
                    n = QStringLiteral("%1").arg(contN);
                    StringReporte += "n" + n + " [shape=record,color=red,label=\"LIBRE\"];\n";
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
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"MBR\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"PRIMARIA\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);

                        for(int x = iniN;x<contN;x++){
                            QString n1 = QStringLiteral("%1").arg(x);
                            QString n2 = QStringLiteral("%1").arg(x + 1);
                            StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                        }
                    }else {
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"MBR\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"LIBRE\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"PRIMARIA\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);

                        for(int x = iniN;x<contN;x++){
                            QString n1 = QStringLiteral("%1").arg(x);
                            QString n2 = QStringLiteral("%1").arg(x + 1);
                            StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                        }
                    }
                }else{
                    StringReporte += "n" + n + " [shape=record,color=red,label=\"MBR\"];\n";
                    contN++;
                    n = QStringLiteral("%1").arg(contN);
                    StringReporte += "n" + n + " [shape=record,color=red,label=\"LIBRE\"];\n";
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
                iniN = contN;
                FILE* Debr=fopen(ruta.toStdString().c_str(),"rb+");
                fseek(Debr,part2.part_start,SEEK_SET);
                fread(&ebr,sizeof(EBR),1,Debr);
                fseek(Debr,0,SEEK_SET);
                fclose(Debr);
                if(part2.part_fit != '.'){
                    if((part2.part_start - part1.part_start - part1.part_size) == 0){
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"EXTENDIDA\"];\n";
                        nodoExt = "n" + n;
                        contN++;
                        n = QStringLiteral("%1").arg(contN);

                        for(int x = iniN;x<contN;x++){
                            QString n1 = QStringLiteral("%1").arg(x);
                            QString n2 = QStringLiteral("%1").arg(x + 1);
                            StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                        }
                    }else {
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"LIBRE\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"EXTENDIDA\"];\n";
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
                    StringReporte += "n" + n + " [shape=record,color=red,label=\"LIBRE\"];\n";
                    contN++;
                    n = QStringLiteral("%1").arg(contN);

                    for(int x = iniN;x<contN;x++){
                        QString n1 = QStringLiteral("%1").arg(x);
                        QString n2 = QStringLiteral("%1").arg(x + 1);
                        StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                    }
                }
            }else{
                iniN = contN;
                if(part2.part_fit != '.'){
                    if((part2.part_start - - part1.part_start - part1.part_size) == 0){
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"PRIMARIA\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);

                        for(int x = iniN;x<contN;x++){
                            QString n1 = QStringLiteral("%1").arg(x);
                            QString n2 = QStringLiteral("%1").arg(x + 1);
                            StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                        }
                    }else {
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"LIBRE\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"PRIMARIA\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);

                        for(int x = iniN;x<contN;x++){
                            QString n1 = QStringLiteral("%1").arg(x);
                            QString n2 = QStringLiteral("%1").arg(x + 1);
                            StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                        }
                    }
                }else{
                    StringReporte += "n" + n + " [shape=record,color=red,label=\"LIBRE\"];\n";
                    contN++;
                    n = QStringLiteral("%1").arg(contN);

                    for(int x = iniN;x<contN;x++){
                        QString n1 = QStringLiteral("%1").arg(x);
                        QString n2 = QStringLiteral("%1").arg(x + 1);
                        StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                    }
                }
            }

            if(part3.part_type == 'e' || part3.part_type == 'E'){
                FILE* Debr=fopen(ruta.toStdString().c_str(),"rb+");
                fseek(Debr,part3.part_start,SEEK_SET);
                fread(&ebr,sizeof(EBR),1,Debr);
                fseek(Debr,0,SEEK_SET);
                fclose(Debr);
                iniN = contN;
                if(part3.part_fit != '.'){
                    if((part3.part_start - part2.part_start - part2.part_size) == 0){
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"EXTENDIDA\"];\n";
                        nodoExt = "n" + n;
                        contN++;
                        n = QStringLiteral("%1").arg(contN);

                        for(int x = iniN;x<contN;x++){
                            QString n1 = QStringLiteral("%1").arg(x);
                            QString n2 = QStringLiteral("%1").arg(x + 1);
                            StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                        }
                    }else {
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"LIBRE\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"EXTENDIDA\"];\n";
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
                    StringReporte += "n" + n + " [shape=record,color=red,label=\"LIBRE\"];\n";
                    contN++;
                    n = QStringLiteral("%1").arg(contN);

                    for(int x = iniN;x<contN;x++){
                        QString n1 = QStringLiteral("%1").arg(x);
                        QString n2 = QStringLiteral("%1").arg(x + 1);
                        StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                    }
                }
            }else{
                iniN = contN;
                if(part3.part_fit != '.'){
                    if((part3.part_start - part2.part_start - part2.part_size) == 0){
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"PRIMARIA\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);

                        for(int x = iniN;x<contN;x++){
                            QString n1 = QStringLiteral("%1").arg(x);
                            QString n2 = QStringLiteral("%1").arg(x + 1);
                            StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                        }
                    }else {
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"LIBRE\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"PRIMARIA\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);

                        for(int x = iniN;x<contN;x++){
                            QString n1 = QStringLiteral("%1").arg(x);
                            QString n2 = QStringLiteral("%1").arg(x + 1);
                            StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                        }
                    }
                }else{
                    StringReporte += "n" + n + " [shape=record,color=red,label=\"LIBRE\"];\n";
                    contN++;
                    n = QStringLiteral("%1").arg(contN);

                    for(int x = iniN;x<contN;x++){
                        QString n1 = QStringLiteral("%1").arg(x);
                        QString n2 = QStringLiteral("%1").arg(x + 1);
                        StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                    }
                }
            }

            if(part4.part_type == 'e' || part4.part_type == 'E'){
                FILE* Debr=fopen(ruta.toStdString().c_str(),"rb+");
                fseek(Debr,part4.part_start,SEEK_SET);
                fread(&ebr,sizeof(EBR),1,Debr);
                fseek(Debr,0,SEEK_SET);
                fclose(Debr);
                iniN = contN;
                if(part4.part_fit != '.'){
                    if((part4.part_start - part3.part_start - part3.part_size) == 0){
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"EXTENDIDA\"];\n";
                        nodoExt = "n" + n;
                        contN++;
                        n = QStringLiteral("%1").arg(contN);

                        for(int x = iniN;x<contN;x++){
                            QString n1 = QStringLiteral("%1").arg(x);
                            QString n2 = QStringLiteral("%1").arg(x + 1);
                            StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                        }
                    }else {
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"LIBRE\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"EXTENDIDA\"];\n";
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
                    StringReporte += "n" + n + " [shape=record,color=red,label=\"LIBRE\"];\n";
                    contN++;
                    n = QStringLiteral("%1").arg(contN);

                    for(int x = iniN;x<contN;x++){
                        QString n1 = QStringLiteral("%1").arg(x);
                        QString n2 = QStringLiteral("%1").arg(x + 1);
                        StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                    }
                }
            }else{
                iniN = contN;
                if(part4.part_fit != '.'){
                    if((part4.part_start - part3.part_start - part3.part_size) == 0){
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"PRIMARIA\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);

                        for(int x = iniN;x<contN;x++){
                            QString n1 = QStringLiteral("%1").arg(x);
                            QString n2 = QStringLiteral("%1").arg(x + 1);
                            StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                        }
                    }else {
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"LIBRE\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);
                        StringReporte += "n" + n + " [shape=record,color=red,label=\"PRIMARIA\"];\n";
                        contN++;
                        n = QStringLiteral("%1").arg(contN);

                        for(int x = iniN;x<contN;x++){
                            QString n1 = QStringLiteral("%1").arg(x);
                            QString n2 = QStringLiteral("%1").arg(x + 1);
                            StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                        }
                    }
                }else{
                    StringReporte += "n" + n + " [shape=record,color=red,label=\"LIBRE\"];\n";
                    contN++;
                    n = QStringLiteral("%1").arg(contN);

                    for(int x = iniN;x<contN;x++){
                        QString n1 = QStringLiteral("%1").arg(x);
                        QString n2 = QStringLiteral("%1").arg(x + 1);
                        StringReporte += "n" + n1 + " -> n" + n2 + ";\n";
                    }
                }
            }

            if((mbr.mbr_tam - part4.part_start - part4.part_size) != 0){
                StringReporte += "n" + n + " [shape=record,color=red,label=\"LIBRE\"];\n";
                contN++;
                n = QStringLiteral("%1").arg(contN);
            }

            StringReporte += "}\n";
            StringReporte += "subgraph cluster1{\n";

            StringReporte += "}}\n";

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

        }else if(reporte->namee.toLower() == "inode"){
            cout<<"-----------------------ReporteINODE---------------------"<<endl;

        }else if(reporte->namee.toLower() == "journaling"){
            cout<<"-----------------------ReporteJOURNALING---------------------"<<endl;

        }else if(reporte->namee.toLower() == "block"){
            cout<<"-----------------------ReporteBLOCK---------------------"<<endl;

        }else if(reporte->namee.toLower() == "bm_inode"){
            cout<<"-----------------------ReporteBM_INODE---------------------"<<endl;

        }else if(reporte->namee.toLower() == "bm_block"){
            cout<<"-----------------------ReporteBM_BLOCK---------------------"<<endl;

        }else if(reporte->namee.toLower() == "tree"){
            cout<<"-----------------------ReporteTREE---------------------"<<endl;

        }else if(reporte->namee.toLower() == "sb"){
            cout<<"-----------------------ReporteSB---------------------"<<endl;

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
