#ifndef INCLUDE_PARSER_H_
#define INCLUDE_PARSER_H_

#include "types_and_tables.h"
#include "clever_string.h"

#include "result.h"


lexem_t get_lexem(string_t *s);  // возвращает лексему для перехода в следующий стейт

string_t *get_multi_bound(string_t *content_type);  // возвращает или пустую структуру string_t или string_t со значением boundary  // NOLINT

int get_number_parts(string_t *text, string_t *boundary, int part);  // итерационно подсчитывает количество партов

string_t *get_key_value(string_t *string, int lexem);  // считывает значение ключа

#endif  // INCLUDE_PARSER_H_
