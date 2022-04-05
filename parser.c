#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <json-c/json.h>

#include "parser.h"
#include "globals.h"

Data split_input(char* line) {
    struct json_object *parsed_json;
    struct json_object *operation;
	struct json_object *key;
	struct json_object *value;

    parsed_json = json_tokener_parse(line);

	json_object_object_get_ex(parsed_json, "operation", &operation);
	json_object_object_get_ex(parsed_json, "key", &key);
	json_object_object_get_ex(parsed_json, "value", &value);

    // printf("Operation: %s\n", json_object_get_string(operation));
	// printf("Key: %s\n", json_object_get_string(key));
	// printf("Value: %s\n", json_object_get_string(value));

    Data data;

    strcpy(data.operation, json_object_get_string(operation));
    strcpy(data.key, json_object_get_string(key));
    if (json_object_get_string(value) != NULL) {
        strcpy(data.value, json_object_get_string(value));
    }

    return data;
}
