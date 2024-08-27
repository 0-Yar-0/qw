#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "master_modules.h"
#include "master_levels.h"
#include "master_status_events.h"

void display_modules(FILE *db) {
    int id = 0;
    Module *module;

    printf("All modules:\n");
    while ((module = select_module_from_modules(db, id++)) != NULL) {
        printf("%d %s %d %d %d\n", module->id, module->name, module->level, module->cell, module->deleted);
        free(module);
    }
}

void display_levels(FILE *db) {
    int id = 0;
    Level *level;

    printf("All levels:\n");
    while ((level = select_level_from_levels(db, id++)) != NULL) {
        printf("%d %d %d\n", level->level1, level->cell_count, level->protection_flag);
        free(level);
    }
}

void display_status_events(FILE *db) {
    int id = 0;
    StatusEvent *event;

    printf("All status events:\n");
    while ((event = select_event_from_status_events(db, id++)) != NULL) {
        printf("%d %d %d %s %s\n", event->id, event->module_id, event->new_status, event->date, event->time);
        free(event);
    }
}

void insert_module(FILE *db) {
    Module module;
    printf("Enter module details (id name level cell deleted):\n");
    scanf("%d %s %3d %d %d", &module.id, module.name, &module.level, &module.cell, &module.deleted);

    if (insert_module_to_modules(db, &module)) {
        printf("Module inserted successfully.\n");
    } else {
        printf("Failed to insert module.\n");
    }
}

void update_module_data(FILE *db) {
    int id;
    Module module;
    printf("Enter module id to update:\n");
    scanf("%d", &id);

    printf("Enter new module details (name level cell deleted):\n");
    scanf("%s %d %d %d", module.name, &module.level, &module.cell, &module.deleted);

    if (update_module_in_modules(db, id, &module)) {
        printf("Module updated successfully.\n");
    } else {
        printf("Failed to update module.\n");
    }
}

void delete_module(FILE *db) {
    int id;
    printf("Enter module id to delete:\n");
    scanf("%d", &id);

    if (delete_module_from_modules(db, id)) {
        printf("Module deleted successfully.\n");
    } else {
        printf("Failed to delete module.\n");
    }
}

void get_all_active_additional_modules(FILE *db) {
    int id = 0;
    StatusEvent *event;

    printf("All active additional modules:\n");
    while ((event = select_event_from_status_events(db, id++)) != NULL) {
        if (event->new_status == 1) {
            printf("Module ID: %d is active\n", event->module_id);
        }
        free(event);
    }
}

void delete_modules_by_ids(FILE *db) {
    int id;
    printf("Enter module ids to delete (space-separated, end with -1):\n");
    while (scanf("%d", &id) && id != -1) {
        delete_module_from_modules(db, id);
    }
    printf("Modules marked as deleted.\n");
}

void set_protected_mode_for_module(FILE *db) {
    int id;
    printf("Enter module id to set protected mode:\n");
    scanf("%d", &id);

    StatusEvent event;
    event.module_id = id;
    event.new_status = 0;
    strcpy(event.date, "01.01.2021");
    strcpy(event.time, "00:00:00");
    insert_event_to_status_events(db, &event);

    event.new_status = 1;
    strcpy(event.date, "01.01.2021");
    strcpy(event.time, "00:01:00");
    insert_event_to_status_events(db, &event);

    event.new_status = 20;
    strcpy(event.date, "01.01.2021");
    strcpy(event.time, "00:02:00");
    insert_event_to_status_events(db, &event);

    printf("Module set to protected mode.\n");
}

void move_module(FILE *modules_db) {
    int id, new_level, new_cell;
    printf("Enter module id to move:\n");
    scanf("%d", &id);

    Module *module = select_module_from_modules(modules_db, id);
    if (module == NULL) {
        printf("Module not found.\n");
        return;
    }

    printf("Enter new level and cell number:\n");
    scanf("%d %d", &new_level, &new_cell);

    module->level = new_level;
    module->cell = new_cell;

    update_module_in_modules(modules_db, id, module);
    free(module);

    printf("Module moved successfully.\n");
}

void set_protection_flag_for_memory_level(FILE *db) {
    int l;
    printf("Enter memory level to set protection flag:\n");
    scanf("%d", &l);

    Level *level = select_level_from_levels(db, l);
    if (level == NULL) {
        printf("Memory level not found.\n");
        return;
    }

    level->protection_flag = 1;
    update_level_in_levels(db, l, level);
    free(level);

    printf("Memory level protection flag set.\n");
}

int main() {
    FILE *modules_db = fopen("materials/master_modules.db", "r+");
    FILE *levels_db = fopen("materials/master_levels.db", "r+");
    FILE *status_events_db = fopen("materials/master_status_events.db", "r+");

    if (!modules_db || !levels_db || !status_events_db) {
        printf("Failed to open databases.\n");
        return 1;
    }

    int choice;
    while (1) {
        printf("Please choose one operation:\n");
        printf("1. SELECT\n");
        printf("2. INSERT\n");
        printf("3. UPDATE\n");
        printf("4. DELETE\n");
        printf("5. Get all active additional modules (last module status is 1)\n");
        printf("6. Delete modules by ids\n");
        printf("7. Set protected mode for module by id\n");
        printf("8. Move module by id to specified memory level and cell\n");
        printf("9. Set protection flag of the specified memory level\n");
        printf("0. Exit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Please choose a table:\n1. Modules\n2. Levels\n3. Status events\n");
                scanf("%d", &choice);
                if (choice == 1) display_modules(modules_db);
                else if (choice == 2) display_levels(levels_db);
                else if (choice == 3) display_status_events(status_events_db);
                break;
            case 2:
                insert_module(modules_db);
                break;
            case 3:
                update_module_data(modules_db);
                break;
            case 4:
                delete_module(modules_db);
                break;
            case 5:
                get_all_active_additional_modules(status_events_db);
                break;
            case 6:
                delete_modules_by_ids(modules_db);
                break;
            case 7:
                set_protected_mode_for_module(status_events_db);
                break;
            case 8:
                move_module(modules_db);
                break;
            case 9:
                set_protection_flag_for_memory_level(levels_db);
                break;
            case 0:
                fclose(modules_db);
                fclose(levels_db);
                fclose(status_events_db);
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}
