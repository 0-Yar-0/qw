#include "database.h"
#include "master_levels.h"
#include <stdio.h>

Level *select_level_from_levels(FILE *db, int id) {
    return (Level *)select(db, id, sizeof(Level));
}

int insert_level_to_levels(FILE *db, Level *level) {
    return insert(db, level, sizeof(Level));
}

int update_level_in_levels(FILE *db, int id, Level *level) {
    return update(db, id, level, sizeof(Level));
}

int delete_level_from_levels(FILE *db, int id) {
    return delete(db, id, sizeof(Level));
}