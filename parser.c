#include <string.h>
#include "parser.h"

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
