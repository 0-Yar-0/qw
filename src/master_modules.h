#ifndef MASTER_MODULES_H
#define MASTER_MODULES_H
#include <stdio.h>
#include "database.h"

Module *select_module_from_modules(FILE *db, int id);

int insert_module_to_modules(FILE *db, Module *module);

int update_module_in_modules(FILE *db, int id, Module *module);

int delete_module_from_modules(FILE *db, int id);

#endif