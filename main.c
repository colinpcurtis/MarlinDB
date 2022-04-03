#include <stdlib.h>
#include <string.h>
#include <stdio.h>

const int MAX_LENGTH = 100;
const int HASH_TABLE_LENGTH = 10000;

typedef struct Data {
    char operation[MAX_LENGTH];
    char key[MAX_LENGTH];
    char value[MAX_LENGTH];
} Data;

Data split_input(char* line, char** split_line) {
    char* token = strtok(line, " ");
    int splits = 0;
    while (token != NULL) {
        token[strcspn(token, "\n")] = 0;
        split_line[splits] = token;
        token = strtok(NULL, " ");
        splits++;
    }
    split_line[splits] = NULL;
    Data data;

    if (splits >= 1) {
        strcpy(data.operation, split_line[0]);
    }
    if (splits >= 2) {
        strcpy(data.key, split_line[1]);
    }
    if (splits >= 3) {
        strcpy(data.value, split_line[2]);
    }

    return data;
}

unsigned long hash(char *str) {
    unsigned long hash = 5381;
    int idx = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        hash = ((hash << 5) + hash) + str[i]; /* hash * 33 + c */
    }
    return hash;
}

typedef struct NodeData {
    char key[MAX_LENGTH];
    char value[MAX_LENGTH];
} NodeData;

typedef struct HashTable {
    NodeData* elements[HASH_TABLE_LENGTH];
} HashTable;

HashTable* hash_table_init() {
    HashTable* hash_table = malloc(sizeof(hash_table));
    for (int i = 0; i < HASH_TABLE_LENGTH; i++) {
        hash_table->elements[i] = NULL;
    }
    printf("initialized hash table\n");
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

/* handle CRUD operations */
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

int main() {
    system("clear");
    char line[MAX_LENGTH];
    char* split_line[MAX_LENGTH];

    HashTable* hash_table = hash_table_init();

    while (1) {
        printf("> ");
        size_t bufsize = 100;
        fgets(line, MAX_LENGTH, stdin);

        Data data = split_input(line, split_line);
        execute(hash_table, &data);
    }
}
