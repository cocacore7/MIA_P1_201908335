#ifndef MBRSTRUCT_H
#define MBRSTRUCT_H
#include <time.h>

struct particion{
    char    part_status;
    char    part_type;
    char    part_fit;
    int     part_start;
    int     part_size;
    char    part_name[16];
};

struct MBR{
    int                 mbr_tam;
    time_t              mbr_fecha_creacion;
    int                 mbr_disk_signature;
    char                disk_fit;
    struct particion    mbr_partition_1;
    struct particion    mbr_partition_2;
    struct particion    mbr_partition_3;
    struct particion    mbr_partition_4;
};

#endif // MBRSTRUCT_H
