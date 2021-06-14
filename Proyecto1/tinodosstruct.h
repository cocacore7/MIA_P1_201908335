#ifndef TINODOSSTRUCT_H
#define TINODOSSTRUCT_H
#include <time.h>

typedef struct{
    int                 i_uid;
    int                 i_gid;
    int                 i_size;
    time_t              i_atime;
    time_t              i_ctime;
    time_t              i_mtime;
    int                 i_block[15];
    char                i_type;
    int                 i_perm;
} TablaInodos;

#endif // TINODOSSTRUCT_H
