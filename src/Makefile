CC = gcc
CFLAGS = -Wall -Werror -Wextra 

all: build_db

build_db: shared.o master_modules.o master_levels.o master_status_events.o modules_db.o
	$(CC) $(CFLAGS) -o build_db shared.o master_modules.o master_levels.o master_status_events.o modules_db.o

shared.o: shared.c
	$(CC) $(CFLAGS) -c shared.c

master_modules.o: master_modules.c
	$(CC) $(CFLAGS) -c master_modules.c

master_levels.o: master_levels.c
	$(CC) $(CFLAGS) -c master_levels.c

master_status_events.o: master_status_events.c
	$(CC) $(CFLAGS) -c master_status_events.c

modules_db.o: modules_db.c
	$(CC) $(CFLAGS) -c modules_db.c

clean:
	rm -f *.o build_db
