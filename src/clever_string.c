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


string_t string_converter(char* string_in_char) {
    string_t *ptr = create_string();
    for (unsigned int i = 0; i < strlen(string_in_char); ++i) {
        add_symbol(ptr,string_in_char[i]);
    }
    return *ptr;
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


string_t delete_symbols_in_begin(string_t key_with_value, int n) {
    string_t *value = NULL;
    if (n >= key_with_value.size) {
        printf("n >= size");
        return *value;
    }
    resize((string_t *) value->size);  // как увеличиваем сайз, нужен ли криэйт стринг?
    for (unsigned  int i = n; i < key_with_value.size; ++i) {
        add_symbol(value, key_with_value.str[i]);
    }
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
    int i;
    while ((symbol = fgetc(fp)) != EOF) {
        if (symbol == '\n' || symbol == '\r') {
            if ((symbol = fgetc(fp)) != EOF && symbol != '\t' && symbol != ' ') {
                fseek(fp,-1,SEEK_CUR);
                //printf("%s", "success");
                break;
            } else {
                while ((symbol = fgetc(fp) == '\t') || (symbol = fgetc(fp) == ' ')) {}
                //symbol = fgetc(fp);
                //printf("%d", (char)symbol);
                add_symbol(str, ' ');
                while ((symbol = fgetc(fp) == '\r') || (symbol = fgetc(fp) == '\n')) {
                    add_symbol(str, (char) symbol);
                }
            }
        }

        if (add_symbol(str, (char)symbol) != 0) {
            return 1;
        }
    }

    return 0;
}


result_t str_str(string_t a, string_t multi_a) {
    result_t res;
    for (unsigned int i = 0; i < multi_a.size - a.size; ++i) {
        for (unsigned int j = 0; j < a.size; ++j) {
            if (a.str[j] != multi_a.str[i]) {
                break;
            }

            if (a.str[j] == multi_a.str[i]) {
                ++i;
            }

            if (j == a.size - 1) {
                res.result_status = 1;
                res.ref = i - a.size;
                return res;
            }
        }
    }
    return res;
}
