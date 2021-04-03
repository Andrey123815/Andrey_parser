#include "clever_string.h"
#include <stdlib.h>
#include <string.h>


static inline int is_null(const string_t *string) {
    if (string == NULL || string->str == NULL || string->capacity == 0) {
        return 1;
    }
    return 0;
}

string_t create_string() {
    string_t str = {.str = NULL, .size = 0, .capacity = 0};

    str.str = malloc(sizeof(char));
    if (str.str == NULL) {
        return str;
    }

    str.str[0] = '\0';
    str.capacity = 1;

    return str;
}

string_t string_from_char(const char *string) {
    string_t string_new = create_string();

    for (unsigned int i = 0; i < strlen(string); ++i) {
        add_symbol(&string_new, string[i]);
    }

    return string_new;
}

int free_string(string_t *string) {
    if (is_null(string)) {
        return 1;
    }

    free(string->str);

    string->str = NULL;
    string->size = 0;
    string->capacity = 0;

    return 0;
}

int clear_string(string_t *string) {
    if (is_null(string)) {
        return 1;
    }

    string->size = 0;
    string->str[0] = '\0';

    return 0;
}
int resize(string_t *string) {
    if (is_null(string)) {
        return 1;
    }

    char *tmp = realloc(string->str, string->capacity * 2);
    if (tmp == NULL) {
        return 1;
    }

    string->str = tmp;
    string->capacity *= 2;

    return 0;
}
int add_symbol(string_t *string, char symbol) {
    if (is_null(string)) {
        return 1;
    }

    if (string->capacity <= string->size + 1) {
        if (resize(string) != 0) {
            return 1;
        }
    }

    string->str[string->size++] = symbol;
    string->str[string->size] = '\0';

    return 0;
}

int delete_symbol(string_t *string, int i) {
    if (is_null(string)) {
        return 1;
    }

    for (int j = i; j < string->size - 1; ++j) {
        string->str[i] = string->str[i+1];
    }
    string->size--;

    return 0;
}

int read_str(FILE *fp, string_t *string) {
    if (fp == NULL || is_null(string)) {
        return 1;
    }

    clear_string(string);

    int symbol;
    int flag_str = 0;
    while ((symbol = fgetc(fp)) != EOF) {
        if (symbol == '\n' || symbol == '\r') {
            if ((symbol = fgetc(fp)) != EOF && symbol != '\t' && symbol != ' ') {
                fseek(fp, -1, SEEK_CUR);
                break;
            }

            if (symbol == '\t' || symbol == ' ') {
                add_symbol(string, ' ');
                symbol = fgetc(fp);

                while ((symbol == '\t') || (symbol == ' ')) {
                    symbol = fgetc(fp);
                }

                while (symbol != '\r' && symbol != EOF && symbol != '\n') {
                    add_symbol(string, (char) symbol);
                    symbol = fgetc(fp);;
                }

                if (symbol == '\n' || symbol == '\r') {
                    fseek(fp, -1, SEEK_CUR);
                    flag_str = 1;
                }
            }
        }

        if (flag_str < 1) {
            if (add_symbol(string, (char) symbol) != 0) {
                return 1;
            }
        }
    }

    if (symbol == EOF) {
        clear_string(string);
        add_symbol(string, EOF);
    }

    return 0;
}

int font_lower(string_t *string) {
    if (is_null(string)) {
        return 1;
    }

    for (size_t i = 0; i < string->size; ++i) {
        if (string->str[i] >= 'A' && string->str[i] <= 'Z') {
            string->str[i] += ('a' - 'A');
        }
    }

    return 0;
}
string_t str_tok(string_t *input_str, char sep_symbol) {
    if (is_null(input_str)) {
        return create_string();
    }

    string_t new_str = create_string();

    for (size_t i = 0; i < input_str->size && input_str->str[i] != sep_symbol; ++i) {
        if (input_str->str[i] == ' ') {
            return new_str;
        }
        add_symbol(&new_str, input_str->str[i]);
    }

    return new_str;
}
int copy(string_t *destination, const string_t *source) {
    if (destination == NULL || is_null(source)) {
        return 1;
    }

    free_string(destination);
    *destination = create_string();

    for (unsigned int i = 0; i < source->size; ++i) {
        add_symbol(destination, source->str[i]);
    }

    return 0;
}
string_t delete_symbols_in_begin(const string_t *source, long int num) {
    if (is_null(source)) {
        return create_string();
    }

    string_t value = create_string();

    if (num >= source->size) {
        printf("num >= size");
        return value;
    }

    for (unsigned int i = num; i < source->size; ++i) {
        add_symbol(&value, source->str[i]);
    }

    return value;
}
long int str_str(const string_t *string1, const string_t *string2) {
    if (is_null(string1) || is_null(string2)) {
        return -1;
    }

    char *pch = strstr(string1->str, string2->str);
    if (pch == NULL) {
        return -1;
    }

    return pch - string1->str;
}
