#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <json-c/json.h>

#include "hash_table.h"
#include "globals.h"
#include "execute.h"
#include "parser.h"
#include "marlin-server.h"

const char* handle_message(HashTable* hash_table, char* client_message) {
    Data input_data = split_input(client_message);
    Data return_data = execute(hash_table, &input_data);

    struct json_object* json_obj = json_object_new_object();
    if (strcmp(return_data.value, "") == 0) {
        json_object_object_add(json_obj, "status", json_object_new_string("NOT_FOUND"));       
    }
    else {
        json_object_object_add(json_obj, "status", json_object_new_string("OK"));
    }
    json_object_object_add(json_obj, "data", json_object_new_string(return_data.value));
    printf("%s\n", json_object_to_json_string(json_obj));

    return json_object_to_json_string(json_obj);
}

int main() {
    int socket_desc, client_sock;
    socklen_t client_size;
    struct sockaddr_in server_addr, client_addr;
    char server_message[2000], client_message[2000];

    // Clean buffers:
    memset(server_message, '\0', sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message));

    // Create socket:
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if(socket_desc < 0){
        printf("Error while creating socket\n");
        return -1;
    }
    printf("Socket created successfully\n");

    // Set port and IP:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(7000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Bind to the set port and IP:
    if(bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr))<0){
        printf("Couldn't bind to the port\n");
        return -1;
    }
    printf("Done with binding\n");

    // Listen for clients:
    if(listen(socket_desc, 1) < 0){
        printf("Error while listening\n");
        return -1;
    }
    printf("Listening for incoming connections.....\n");
    
    HashTable* hash_table = hash_table_init();

    while (1) {
        // Clean buffers:
        memset(server_message, '\0', sizeof(server_message));
        memset(client_message, '\0', sizeof(client_message));
        // Accept an incoming connection:
        client_size = sizeof(client_addr);
        client_sock = accept(socket_desc, (struct sockaddr*)&client_addr, &client_size);
        
        if (client_sock < 0){
            printf("Can't accept\n");
            return -1;
        }

        // Receive client's message:
        if (recv(client_sock, client_message, sizeof(client_message), 0) < 0){
            printf("Couldn't receive\n");
            return -1;
        }
        printf("Msg from client: %s\n", client_message);

        const char* response = handle_message(hash_table, client_message);

        // Respond to client:
        strcpy(server_message, response);
        
        if (send(client_sock, server_message, strlen(server_message), 0) < 0){
            printf("Can't send\n");
            return -1;
        }
    }

    // Closing the socket:
    close(client_sock);
    close(socket_desc);
    hash_table_destroy(hash_table);

    return 0;
}
