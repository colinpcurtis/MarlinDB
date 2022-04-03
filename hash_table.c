#include <stdlib.h>

#include "hash_table.h"
#include "globals.h"

unsigned long hash(char *str) {
    unsigned long hash = 5381;
    for (int i = 0; str[i] != '\0'; i++) {
        hash = ((hash << 5) + hash) + str[i]; /* hash * 33 + c */
    }
    return hash;
}

HashTable* hash_table_init() {
    HashTable* hash_table = malloc(sizeof(hash_table));
    for (int i = 0; i < HASH_TABLE_LENGTH; i++) {
        hash_table->elements[i] = NULL;
    }
    return hash_table;
}

void hash_table_destroy(HashTable* table) {
    for (int i = 0; i < HASH_TABLE_LENGTH; i++) {
        if (table->elements[i] != NULL) {
            free(table->elements[i]);
        }
    }
    free(table);
}