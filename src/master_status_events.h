#ifndef MASTER_MASTER_EVENTS_H
#define MASTER_MASTER_EVENTS_H
#include <stdio.h>
#include "database.h"

StatusEvent *select_event_from_status_events(FILE *db, int id);

int insert_event_to_status_events(FILE *db, StatusEvent *event);

int update_event_in_status_events(FILE *db, int id, StatusEvent *event);

int delete_event_from_status_events(FILE *db, int id);

#endif