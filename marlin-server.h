#pragma once

#include "hash_table.h"

typedef struct PoolData {
    HashTable* hash_table;
    char* client_message;
    int client_sock;
} PoolData;

const char* handle_message(HashTable* hash_table, char* client_message);

void pool_worker(PoolData* data);

int accept_client_connection(int server_sock);

int init_server();
