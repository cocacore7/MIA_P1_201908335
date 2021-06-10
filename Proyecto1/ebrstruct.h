#ifndef EBRSTRUCT_H
#define EBRSTRUCT_H


typedef struct{
    char                part_status;
    char                part_fit;
    int                 part_start;
    int                 part_size;
    int                 part_next;
    char                part_name[16];
} EBR;

#endif // EBRSTRUCT_H
