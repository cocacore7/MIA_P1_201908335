#include "clmount.h"
#include <QString>
#include <iostream>
#include <QDir>
#include <fstream>
#include <mbrstruct.h>
#include <ebrstruct.h>
using namespace std;

clmount::clmount()
{

}

void clmount::mostrarDatos(clmount *disco){
    disco->path.remove(QChar('"'), Qt::CaseInsensitive);
    cout<<"-----------------------MontarParticion---------------------"<<endl;
    cout<<"El Path es: "<<disco->path.toStdString()<<endl;
    cout<<"El Name es: "<<disco->namee.toStdString()<<endl;
    if(disco->path!=""){
        if(disco->namee!=""){
            //AQUI VA TODO EL CODIGO PARA COMANDO MOUNT
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
                        archivo.close();
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
                        if(disco->namee == nombre1){
                            //GENERAR ID Y MONTAR PARTICION 1
                        }else if(disco->namee == nombre2){
                            //GENERAR ID Y MONTAR PARTICION 2
                        }else if(disco->namee == nombre3){
                            //GENERAR ID Y MONTAR PARTICION 3
                        }else if(disco->namee == nombre4){
                            //GENERAR ID Y MONTAR PARTICION 4
                        }else{
                            if(part1.part_type == 'e' || part1.part_type == 'E'){
                                Discoo=fopen(com,"rb+");
                                fseek(Discoo,part1.part_start,SEEK_SET);
                                EBR ebr;
                                fread(&ebr,sizeof(EBR),1,Discoo);
                                fseek(Discoo,0,SEEK_SET);
                                fclose(Discoo);

                                bool nombreR = false;
                                QString nombreebr(ebr.part_name);
                                if(nombreebr == disco->namee){
                                    nombreR = true;
                                }

                                int partOcupado = 0;
                                int nuevoinicio = part1.part_start;
                                int tam_Particion = part1.part_size;
                                int tam_ebr = sizeof (ebr);
                                QString nombre = "";
                                while(ebr.part_next != -1){
                                    Discoo=fopen(com,"rb+");
                                    fseek(Discoo,nuevoinicio,SEEK_SET);
                                    fread(&ebr,sizeof(EBR),1,Discoo);
                                    fseek(Discoo,0,SEEK_SET);
                                    fclose(Discoo);
                                    QString nombreChar(ebr.part_name);

                                    if(ebr.part_next != -1){
                                        if(disco->namee == nombreChar){
                                            nombreR = true;
                                            nombre = nombreChar;
                                            break;
                                        }
                                        nuevoinicio = ebr.part_next;
                                        partOcupado = partOcupado + tam_ebr + ebr.part_size;
                                    }
                                    if(partOcupado >= tam_Particion){break;}
                                }

                                if(nombreR){
                                    //GENERAR ID Y MONTAR LOGICA
                                }else{
                                    cout<<"El nombre No Existe En Ninguna Particion"<<endl;
                                }
                            }else if(part2.part_type == 'e' || part2.part_type == 'E'){
                                Discoo=fopen(com,"rb+");
                                fseek(Discoo,part2.part_start,SEEK_SET);
                                EBR ebr;
                                fread(&ebr,sizeof(EBR),1,Discoo);
                                fseek(Discoo,0,SEEK_SET);
                                fclose(Discoo);

                                bool nombreR = false;
                                QString nombreebr(ebr.part_name);
                                if(nombreebr == disco->namee){
                                    nombreR = true;
                                }


                                int partOcupado = 0;
                                int nuevoinicio = part2.part_start;
                                int tam_Particion = part2.part_size;
                                int tam_ebr = sizeof (ebr);
                                QString nombre ="";
                                while(ebr.part_next != -1){
                                    Discoo=fopen(com,"rb+");
                                    fseek(Discoo,nuevoinicio,SEEK_SET);
                                    fread(&ebr,sizeof(EBR),1,Discoo);
                                    fseek(Discoo,0,SEEK_SET);
                                    fclose(Discoo);
                                    QString nombreChar(ebr.part_name);
                                    if(ebr.part_next != -1){
                                        if(disco->namee == nombreChar){
                                            nombreR = true;
                                            nombre = nombreChar;
                                            break;
                                        }
                                        nuevoinicio = ebr.part_next;
                                        partOcupado = partOcupado + tam_ebr + ebr.part_size;
                                    }
                                    if(partOcupado >= tam_Particion){break;}
                                }

                                if(nombreR){
                                    //GENERAR ID Y MONTAR LOGICA
                                }else{
                                    cout<<"El nombre No Existe En Ninguna Particion"<<endl;
                                }
                            }else if(part3.part_type == 'e' || part3.part_type == 'E'){
                                Discoo=fopen(com,"rb+");
                                fseek(Discoo,part3.part_start,SEEK_SET);
                                EBR ebr;
                                fread(&ebr,sizeof(EBR),1,Discoo);
                                fseek(Discoo,0,SEEK_SET);
                                fclose(Discoo);

                                bool nombreR = false;
                                QString nombreebr(ebr.part_name);
                                if(nombreebr == disco->namee){
                                    nombreR = true;
                                }

                                int partOcupado = 0;
                                int nuevoinicio = part3.part_start;
                                int tam_Particion = part3.part_size;
                                int tam_ebr = sizeof (ebr);
                                QString nombre = "";
                                while(ebr.part_next != -1){
                                    Discoo=fopen(com,"rb+");
                                    fseek(Discoo,nuevoinicio,SEEK_SET);
                                    fread(&ebr,sizeof(EBR),1,Discoo);
                                    fseek(Discoo,0,SEEK_SET);
                                    fclose(Discoo);
                                    QString nombreChar(ebr.part_name);
                                    if(ebr.part_next != -1){
                                        if(disco->namee == nombreChar){
                                            nombreR = true;
                                            nombre = nombreChar;
                                            break;
                                        }
                                        nuevoinicio = ebr.part_next;
                                        partOcupado = partOcupado + tam_ebr + ebr.part_size;
                                    }
                                    if(partOcupado >= tam_Particion){break;}
                                }

                                if(nombreR){
                                    //GENERAR ID Y MONTAR LOGICA
                                }else{
                                    cout<<"El nombre No Existe En Ninguna Particion"<<endl;
                                }
                            }else if(part4.part_type == 'e' || part4.part_type == 'E'){
                                Discoo=fopen(com,"rb+");
                                fseek(Discoo,part4.part_start,SEEK_SET);
                                EBR ebr;
                                fread(&ebr,sizeof(EBR),1,Discoo);
                                fseek(Discoo,0,SEEK_SET);
                                fclose(Discoo);

                                bool nombreR = false;
                                QString nombreebr(ebr.part_name);
                                if(nombreebr == disco->namee){
                                    nombreR = true;
                                }

                                int partOcupado = 0;
                                int nuevoinicio = part4.part_start;
                                int tam_Particion = part4.part_size;
                                int tam_ebr = sizeof (ebr);
                                QString nombre ="";
                                while(ebr.part_next != -1){
                                    Discoo=fopen(com,"rb+");
                                    fseek(Discoo,nuevoinicio,SEEK_SET);
                                    fread(&ebr,sizeof(EBR),1,Discoo);
                                    fseek(Discoo,0,SEEK_SET);
                                    fclose(Discoo);
                                    QString nombreChar(ebr.part_name);
                                    if(ebr.part_next != -1){
                                        if(disco->namee == nombreChar){
                                            nombreR = true;
                                            nombre = nombreChar;
                                            break;
                                        }
                                        nuevoinicio = ebr.part_next;
                                        partOcupado = partOcupado + tam_ebr + ebr.part_size;
                                    }
                                    if(partOcupado >= tam_Particion){break;}
                                }

                                if(nombreR){
                                    //GENERAR ID Y MONTAR LOGICA
                                }else{
                                    cout<<"El nombre No Existe En Ninguna Particion"<<endl;
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
            cout<<"Nombre De Particion No Ingresada, Incorrecto"<<endl;
        }
    }else{
        cout<<"Ruta No Ingresada, Incorrecto"<<endl;
    }
    disco->path = "";
    disco->namee = "";
    cout<<"--------------------------------------------------------"<<endl;
}
