#ifndef DATABASE_H
#define DATABASE_H
#include <stdio.h>

void *select(FILE *db, int id, size_t entity_size);
int delete(FILE *db, int id, size_t entity_size);
int insert(FILE *db, void *entity, size_t entity_size);
int update(FILE *db, int id, void *new_data, size_t entity_size);

typedef struct {
    int id;
    char name[30];
    int level;
    int cell;
    int deleted;
} Module;

typedef struct {
    int level1;
    int cell_count;
    int protection_flag;
} Level;

typedef struct {
    int id;
    int module_id;
    int new_status;
    char date[11]; // "dd.mm.yyyy\0"
    char time[9];  // "hh:mm:ss\0"
} StatusEvent;

#endif
