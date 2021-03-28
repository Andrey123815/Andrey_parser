#include "clever_string.h"
#include <stdlib.h>
#include <string.h>


string_t *create_string() {
    string_t *str = malloc(sizeof(string_t));
    if (str == NULL) {
        return NULL;
    }

    str->str = malloc(sizeof(char));
    if (str->str == NULL) {
        free(str);
        return NULL;
    }

    str->str[0] = '\0';
    str->size = 0;
    str->capacity = 1;

    return str;
}
int free_string(string_t *str) {
    if (str == NULL) {
        return 1;
    }

    free(str->str);
    free(str);

    return 0;
}
int add_symbol(string_t *str, char symbol) {
    if (str == NULL) {
        return 1;
    }

    if (str->capacity <= str->size + 1) {
        if (resize(str) != 0) {
            return 1;
        }
    }

    str->str[str->size++] = symbol;
    str->str[str->size] = '\0';

    return 0;
}
int resize(string_t *str) {
    if (str == NULL) {
        return 1;
    }

    char *tmp = realloc(str->str, str->capacity * 2);
    if (tmp == NULL) {
        return 1;
    }

    str->str = tmp;
    str->capacity *= 2;

    return 0;
}
int clear_string(string_t *str) {
    if (str == NULL) {
        return 1;
    }

    str->size = 0;
    str->str[0] = '\0';

    return 0;
}
int read_str(FILE *fp, string_t *str) {
    if (fp == NULL || str == NULL) {
        return 1;
    }

    clear_string(str);

    int symbol;

    while ((symbol = fgetc(fp)) != EOF) {
        if (symbol == '\n' || symbol == '\r') {
            if ((symbol = fgetc(fp)) != EOF && symbol != '\t' && symbol != ' ') {
                // вернуть указатель
                break;
            }
        }

        if (add_symbol(str, (char)symbol) != 0) {
            return 1;
        }
    }

    return 0;
}
