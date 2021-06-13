#ifndef BLOQUESCASTRUCT_H
#define BLOQUESCASTRUCT_H

typedef struct{
    char                b_name[12];
    int                 b_inodo;
} Content;

typedef struct{
    Content             b_content[4];
} BloquesCarpetas;

#endif // BLOQUESCASTRUCT_H
