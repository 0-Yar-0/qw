#include "database.h"
#include "master_status_events.h"
#include <stdio.h>

StatusEvent *select_event_from_status_events(FILE *db, int id) {
    return (StatusEvent *)select(db, id, sizeof(StatusEvent));
}

int insert_event_to_status_events(FILE *db, StatusEvent *event) {
    return insert(db, event, sizeof(StatusEvent));
}

int update_event_in_status_events(FILE *db, int id, StatusEvent *event) {
    return update(db, id, event, sizeof(StatusEvent));
}

int delete_event_from_status_events(FILE *db, int id) {
    return delete(db, id, sizeof(StatusEvent));
}