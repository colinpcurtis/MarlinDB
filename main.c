#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "hash_table.h"
#include "globals.h"
#include "execute.h"
#include "parser.h"

int main() {
    system("clear");
    char line[MAX_LENGTH];
    char* split_line[MAX_LENGTH];

    HashTable* hash_table = hash_table_init();

    while (1) {
        printf("> ");
        fgets(line, MAX_LENGTH, stdin);

        Data data = split_input(line, split_line);
        char* returned = execute(hash_table, &data);
        printf("%s\n", returned);
        free(returned);
    }
}
