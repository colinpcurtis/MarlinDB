#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "hash_table.h"
#include "execute.h"

/* implement CRUD operations */
char* handle_set(HashTable* hash_table, char* key, char* value) {
    // TODO: return error if key exists
    int idx = hash(key) % HASH_TABLE_LENGTH;
    const int start_idx = idx;
    while (hash_table->elements[idx] != NULL) {
        idx = (idx + 1) % HASH_TABLE_LENGTH;
        if (idx == start_idx) {
            return NULL;
        }
    }

    NodeData* to_insert = malloc(sizeof(NodeData));
    strcpy(to_insert->key, key);
    strcpy(to_insert->value, value);

    hash_table->elements[idx] = to_insert;
    return value;
}

char* handle_get(HashTable* hash_table, char key[MAX_LENGTH]) {
    int idx = hash(key) % HASH_TABLE_LENGTH;
    const int start_idx = idx;
    while(hash_table->elements[idx] != NULL) {
        if (strcmp(key, hash_table->elements[idx]->key) == 0) {
            return hash_table->elements[idx]->value;
        }
        idx = (idx + 1) % HASH_TABLE_LENGTH;
        if (idx == start_idx) {
            return NULL;
        }
    }
    return NULL;
}

char* handle_update(HashTable* hash_table, char* key, char* value) {
    int idx = hash(key) % HASH_TABLE_LENGTH;
    const int start_idx = idx;
    while(hash_table->elements[idx] != NULL) {
        if (strcmp(key, hash_table->elements[idx]->key) == 0) {
            char* to_update = hash_table->elements[idx]->value;
            strcpy(to_update, value);
            return to_update;
        }
        idx = (idx + 1) % HASH_TABLE_LENGTH;
        if (idx == start_idx) {
            return NULL;
        }
    }
    return NULL;
}

char* handle_delete(HashTable* hash_table, char* key) {
    int idx = hash(key) % HASH_TABLE_LENGTH;
    const int start_idx = idx;
    while (hash_table->elements[idx] != NULL) {
        if (strcmp(key, hash_table->elements[idx]->key) == 0) {
            char* deleted_element = hash_table->elements[idx]->value;
            free(hash_table->elements[idx]);
            hash_table->elements[idx] = NULL;
            return deleted_element;
        }
        idx = (idx + 1) % HASH_TABLE_LENGTH;
        if (idx == start_idx) {
            return NULL;
        }
    }
    return NULL;
}

Data execute(HashTable* hash_table, Data* data) {
    char* updated = NULL;
    if (strcmp(data->operation, "SET") == 0) {
        updated = handle_set(hash_table, data->key, data->value);
    }
    else if (strcmp(data->operation, "GET") == 0) {
        updated = handle_get(hash_table, data->key);
    }
    else if (strcmp(data->operation, "UPDATE") == 0) {
        updated = handle_update(hash_table, data->key, data->value);
    }
    else if (strcmp(data->operation, "DELETE") == 0) {
        updated = handle_delete(hash_table, data->key);
    }

    Data return_data;
    strcpy(return_data.operation, data->operation);
    strcpy(return_data.key, data->key);

    if (updated == NULL) {
        strcpy(return_data.value, "");
    }
    else {
        strcpy(return_data.value, updated);
    }

    return return_data;
}
