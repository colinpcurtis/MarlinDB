#pragma once
#include "globals.h"

typedef struct Data {
    char operation[MAX_LENGTH];
    char key[MAX_LENGTH];
    char value[MAX_LENGTH];
} Data;

Data split_input(char* line, char** split_line);
