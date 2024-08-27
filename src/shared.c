#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

void *select(FILE *db, int id, size_t entity_size) {
    void *entity = malloc(entity_size);
    while (fread(entity, entity_size, 1, db)) {
        if (((Module *)entity)->id == id) {
            return entity;
        }
    }
    free(entity);
    return NULL;
}

int insert(FILE *db, void *entity, size_t entity_size) {
    fseek(db, 0, SEEK_END);
    return fwrite(entity, entity_size, 1, db) == 1;
}

int update(FILE *db, int id, void *new_data, size_t entity_size) {
    void *entity = malloc(entity_size);
    while (fread(entity, entity_size, 1, db)) {
        if (((Module *)entity)->id == id) {
            fseek(db, -entity_size, SEEK_CUR);
            int result = fwrite(new_data, entity_size, 1, db);
            free(entity);
            return result == 1;
        }
    }
    free(entity);
    return 0;
}

int delete(FILE *db, int id, size_t entity_size) {
    Module *entity = malloc(entity_size);
    while (fread(entity, entity_size, 1, db)) {
        if (entity->id == id) {
            entity->deleted = 1;
            fseek(db, -entity_size, SEEK_CUR);
            int result = fwrite(entity, entity_size, 1, db);
            free(entity);
            return result == 1;
        }
    }
    free(entity);
    return 0;
}
