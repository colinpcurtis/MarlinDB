CC=gcc
CFLAGS=-Wall -Wextra -std=c17
DB_EXEC=marlin-cli
SERVER_EXEC=server
OBJ_DB=marlin-cli.o hash_table.o parser.o execute.o
OBJ_SERVER=server.o hash_table.o parser.o execute.o

.PHONY: clean

%.o: %.c %.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(DB_EXEC): $(OBJ_DB)
	$(CC) $(CFLAGS) -o $@ $(OBJ_DB) -ljson-c

$(SERVER_EXEC): $(OBJ_SERVER)
	$(CC) $(CFLAGS) -o $@ $(OBJ_SERVER) -ljson-c

clean:
	rm $(DB_EXEC) $(SERVER_EXEC) $(OBJ_DB) $(OBJ_SERVER)
