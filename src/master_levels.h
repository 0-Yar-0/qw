#ifndef MASTER_LEVELS_H
#define MASTER_LEVELS_H
#include <stdio.h>
#include "database.h"

Level *select_level_from_levels(FILE *db, int id);

int insert_level_to_levels(FILE *db, Level *level);

int update_level_in_levels(FILE *db, int id, Level *level);

int delete_level_from_levels(FILE *db, int id);

#endif