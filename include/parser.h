#ifndef DZ_4_PARSER_H
#define DZ_4_PARSER_H

#include "types_and_tables.h"
#include "clever_string.h"

typedef struct {
    string_t *from;
    string_t *to;
    string_t *date;
    int part;
} req_date_t;

lexem_t get_lexem_key(string_t s);  // возвращает лексему для перехода в следующий стейт

string_t font_parser(string_t key_in_random_font); // понижает регистр до строчного

string_t get_multi_bound(string_t content_type);  // возвращает или пустую структуру string_t или string_t со значением boundary

int get_number_parts(string_t text, string_t boundary, int part);  // итерационно подсчитывает количество партов

string_t get_key_value(string_t string, int status_key);  // считывает значение ключа

#endif //DZ_4_PARSER_H
