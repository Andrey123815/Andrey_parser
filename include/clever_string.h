#ifndef INCLUDE_CLEVER_STRING_H_
#define INCLUDE_CLEVER_STRING_H_

#include <stdio.h>

typedef struct {
    char *str;
    size_t size;
    size_t capacity;
} string_t;

string_t create_string();
int free_string(string_t *string);

int clear_string(string_t *string);
int resize(string_t *string);
int add_symbol(string_t *string, char symbol);
int read_str(FILE *fp, string_t *string);

int font_lower(string_t *string);
string_t str_tok(string_t *string, char sep_symbol);
int copy(string_t *destination, const string_t *source);
string_t delete_symbols_in_begin(const string_t *source, int num);
long int str_str(const string_t *string1, const string_t *string2);

#endif  // INCLUDE_CLEVER_STRING_H_
