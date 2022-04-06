#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <json-c/json.h>

#include "globals.h"

int main(int argc, char** argv) {
    system("clear");

    if (argc != 3) {
        printf("Must provide server IP address and port");
        exit(1);
    }

    char* server_ip = argv[1];
    int port = atoi(argv[2]);

    while (1) {
        int socket_desc;
        struct sockaddr_in server_addr;
        char server_message[2000], client_message[2000];

        // Clean buffers:
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));

        char operation[MAX_LENGTH], key[MAX_LENGTH], value[MAX_LENGTH];

        printf("enter operation> ");
        fgets(operation, MAX_LENGTH, stdin);

        printf("enter key> ");
        fgets(key, MAX_LENGTH, stdin);

        printf("enter value> ");
        fgets(value, MAX_LENGTH, stdin);

        operation[strcspn(operation, "\n")] = 0;
        key[strcspn(key, "\n")] = 0;
        value[strcspn(value, "\n")] = 0;

        struct json_object* json_obj = json_object_new_object();
        json_object_object_add(json_obj, "operation", json_object_new_string(operation));
        json_object_object_add(json_obj, "key", json_object_new_string(key));
        json_object_object_add(json_obj, "value", json_object_new_string(value));

        strcpy(client_message, json_object_to_json_string(json_obj));

        // Create socket:
        socket_desc = socket(AF_INET, SOCK_STREAM, 0);

        if(socket_desc < 0){
            printf("Unable to create socket\n");
            return -1;
        }

        // Set port and IP the same as server-side:
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        server_addr.sin_addr.s_addr = inet_addr(server_ip);

        // Send connection request to server:
        if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
            printf("Unable to connect\n");
            return -1;
        }

        // Send the message to server:
        if(send(socket_desc, client_message, strlen(client_message), 0) < 0){
            printf("Unable to send message\n");
            return -1;
        }

        // Receive the server's response:
        if(recv(socket_desc, server_message, sizeof(server_message), 0) < 0){
            printf("Error while receiving server's msg\n");
            return -1;
        }
        printf("%s\n",server_message);
        close(socket_desc);
    }
}
