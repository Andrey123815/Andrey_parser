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

string_t *str_tok(string_t *string, char sep_symbol);

int copy(string_t *a, string_t *b);

string_t *font_lower(string_t *key_in_random_font);  // понижает регистр до строчного

int free_string(string_t *);

int add_symbol(string_t *, char);

string_t *delete_symbols_in_begin(string_t *key_with_value, int n);

int resize(string_t *);

int clear_string(string_t *);

int read_str(FILE *, string_t *);

result_t str_str(string_t *a, string_t *multi_a);

#endif  // INCLUDE_CLEVER_STRING_H_
