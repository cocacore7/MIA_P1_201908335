#ifndef USUARIOSTRUCT_H
#define USUARIOSTRUCT_H


typedef struct{
    char                UID;
    char                Tipo;
    char                Grupo[10];
    char                Usuario[10];
    char                Contra[10];
} Usuario;

typedef struct{
    char                GID;
    char                Tipo;
    char                Grupo[10];
} Grupo;

#endif // USUARIOSTRUCT_H
