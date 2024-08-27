#include "database.h"
#include "master_modules.h"
#include <stdio.h>

Module *select_module_from_modules(FILE *db, int id) {
    return (Module *)select(db, id, sizeof(Module));
}

int insert_module_to_modules(FILE *db, Module *module) {
    return insert(db, module, sizeof(Module));
}

int update_module_in_modules(FILE *db, int id, Module *module) {
    return update(db, id, module, sizeof(Module));
}

int delete_module_from_modules(FILE *db, int id) {
    return delete(db, id, sizeof(Module));
}

