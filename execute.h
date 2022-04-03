#pragma once

#include "hash_table.h"
#include "globals.h"
#include "parser.h"

int handle_set(HashTable* hash_table, char* key, char* value);

char* handle_get(HashTable* hash_table, char key[MAX_LENGTH]);

int handle_update(HashTable* hash_table, char* key, char* value);

int handle_delete(HashTable* hash_table, char* key);

void handle_exit(HashTable* hash_table);

void execute(HashTable* hash_table, Data* data);

