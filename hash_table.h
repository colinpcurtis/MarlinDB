#pragma once

#include "globals.h"

typedef struct NodeData {
    char key[MAX_LENGTH];
    char value[MAX_LENGTH];
} NodeData;

typedef struct HashTable {
    NodeData* elements[HASH_TABLE_LENGTH];
} HashTable;

unsigned long hash(char *str);

struct HashTable* hash_table_init();

void hash_table_destroy(HashTable* table);
