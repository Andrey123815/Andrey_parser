#ifndef INCLUDE_CLEVER_STRING_H_
#define INCLUDE_CLEVER_STRING_H_

#include <stdio.h>

typedef struct {
    char *str;
    size_t size;
    size_t capacity;
} string_t;

typedef struct {
    int result_status;
    unsigned int ref;
} result_t;

string_t *create_string();

int free_string(string_t *);

string_t *string_converter(char* string_in_char);

int add_symbol(string_t *, char);

string_t *delete_symbols_in_begin(string_t *key_with_value, int n);

int resize(string_t *);

int clear_string(string_t *);

int read_str(FILE *, string_t *);

result_t str_str(string_t *a, string_t *multi_a);

#endif  // INCLUDE_CLEVER_STRING_H_
