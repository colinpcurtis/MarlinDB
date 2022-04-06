CC=gcc
CFLAGS=-Wall -Wextra -Werror -O2 -std=c17
DB_EXEC=marlin-cli
SERVER_EXEC=marlin-server
OBJ_DB=marlin-cli.o
OBJ_SERVER=marlin-server.o hash_table.o parser.o execute.o

.PHONY: clean install fresh

%.o: %.c %.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(DB_EXEC): $(OBJ_DB)
	$(CC) $(CFLAGS) -o $@ $(OBJ_DB) -ljson-c

$(SERVER_EXEC): $(OBJ_SERVER)
	$(CC) $(CFLAGS) -o $@ $(OBJ_SERVER) -ljson-c

install:
	./install.sh

clean:
	rm $(DB_EXEC) $(SERVER_EXEC) $(OBJ_DB) $(OBJ_SERVER)

fresh:
	rm -rf json-c json-c-build
	$(DB_EXEC) $(SERVER_EXEC) $(OBJ_DB) $(OBJ_SERVER)
