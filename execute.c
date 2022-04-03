#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "hash_table.h"
#include "execute.h"

/* implement CRUD operations */
int handle_set(HashTable* hash_table, char* key, char* value) {
    int idx = hash(key) % HASH_TABLE_LENGTH;
    printf("idx %d\n", idx);
    const int start_idx = idx;
    while (hash_table->elements[idx] != NULL) {
        idx = (idx + 1) % HASH_TABLE_LENGTH;
        if (idx == start_idx) {
            return 1;
        }
    }

    NodeData* to_insert = malloc(sizeof(NodeData));
    strcpy(to_insert->key, key);
    strcpy(to_insert->value, value);

    hash_table->elements[idx] = to_insert;
    return 0;
}

char* handle_get(HashTable* hash_table, char key[MAX_LENGTH]) {
    int idx = hash(key) % HASH_TABLE_LENGTH;
    printf("idx %d\n", idx);
    while(hash_table->elements[idx] != NULL) {
        if (strcmp(key, hash_table->elements[idx]->key) == 0) {
            printf("retrieved %s\n", hash_table->elements[idx]->value);
            return hash_table->elements[idx]->value;
        }
        idx = (idx + 1) % HASH_TABLE_LENGTH;
    }
    printf("element not found\n");
    return NULL;
}

int handle_update(HashTable* hash_table, char* key, char* value) {
    int idx = hash(key) % HASH_TABLE_LENGTH;
    printf("idx %d\n", idx);
    const int start_idx = idx;
    while(hash_table->elements[idx] != NULL) {
        if (strcmp(key, hash_table->elements[idx]->key) == 0) {
            strcpy(hash_table->elements[idx]->value, value);
            printf("updated %s\n", hash_table->elements[idx]->value);
            return 0;
        }
        idx = (idx + 1) % HASH_TABLE_LENGTH;
        if (idx == start_idx) {
            return 1;
        }
    }
    return 1;
}

int handle_delete(HashTable* hash_table, char* key) {
    int idx = hash(key) % HASH_TABLE_LENGTH;
    const int start_idx = idx;
    printf("idx %d\n", idx);
    while (hash_table->elements[idx] != NULL) {
        if (strcmp(key, hash_table->elements[idx]->key) == 0) {

            free(hash_table->elements[idx]);
            hash_table->elements[idx] = NULL;
            printf("deleted\n");
            return 0;
        }
        idx = (idx + 1) % HASH_TABLE_LENGTH;
        if (idx == start_idx) {
            return 1;
        }
    }
    return 1;
}

void handle_exit(HashTable* hash_table) {
    hash_table_destroy(hash_table);
    printf("exited gracefully\n");
    exit(0);
}

void execute(HashTable* hash_table, Data* data) {
    int error_code;
    if (strcmp(data->operation, "exit") == 0) {
        handle_exit(hash_table);
    }
    if (strcmp(data->operation, "SET") == 0) {
        error_code = handle_set(hash_table, data->key, data->value);
    }
    else if (strcmp(data->operation, "GET") == 0) {
        handle_get(hash_table, data->key);
    }
    else if (strcmp(data->operation, "UPDATE") == 0) {
        handle_update(hash_table, data->key, data->value);
    }
    else if (strcmp(data->operation, "DELETE") == 0) {
        handle_delete(hash_table, data->key);
    }
}