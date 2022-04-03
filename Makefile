CC=gcc
CFLAGS=-Wall -Wextra -std=c17
EXEC=db
OBJ=main.o hash_table.o parser.o execute.o

.PHONY: clean

%.o: %.c %.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

clean:
	rm $(EXEC) $(OBJ)