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


string_t *str_tok(string_t *input_str, char sep_symbol) {
    if (input_str == NULL) {
        return NULL;
    }

    string_t *new_str = create_string();
    unsigned int i = 0;

    for (i = 0; i < input_str->size && input_str->str[i] != sep_symbol; ++i) {
        if (input_str->str[i] == ' ') {
            free_string(new_str);
            return NULL;
        }
        add_symbol(new_str,input_str->str[i]);
    }

    return new_str;
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


string_t *delete_symbols_in_begin(string_t *key_with_value, int n) {
    string_t *value = create_string();

    if (n >= key_with_value->size) {
        printf("n >= size");
        return value;
    }

    for (unsigned  int i = n; i < key_with_value->size; ++i) {
        add_symbol(value, key_with_value->str[i]);
    }
    return value;
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
    int flag_str = 0;
    while ((symbol = fgetc(fp)) != EOF) {
        if (symbol == '\n' || symbol == '\r') {
            if ((symbol = fgetc(fp)) != EOF && symbol != '\t' && symbol != ' ') {
                fseek(fp, -1, SEEK_CUR);
                break;
            }

            if (symbol == '\t' || symbol == ' ') {
                add_symbol(str, ' ');
                symbol = fgetc(fp);

                while ((symbol == '\t') || (symbol == ' ')) {
                    symbol = fgetc(fp);
                }

                while (symbol != '\r' && symbol != EOF && symbol != '\n') {
                    add_symbol(str, (char) symbol);
                    symbol = fgetc(fp);;
                }

                if (symbol == '\n' || symbol == '\r') {
                    fseek(fp, -1, SEEK_CUR);
                    flag_str = 1;
                }
            }
        }

        if (flag_str < 1) {
            if (add_symbol(str, (char) symbol) != 0) {
                return 1;
            }
        }
    }

    return 0;
}


result_t str_str(string_t *a, string_t *multi_a) {
    result_t res;
    for (unsigned int i = 0; i < multi_a->size - a->size; ++i) {
        for (unsigned int j = 0; j < a->size; ++j) {
            if (a->str[j] != multi_a->str[i]) {
                break;
            }

            if (a->str[j] == multi_a->str[i]) {
                ++i;
            }

            if (j == a->size - 1) {
                res.result_status = 1;
                res.ref = i - a->size;
                return res;
            }
        }
    }
    return res;
}
