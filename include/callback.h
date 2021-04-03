#ifndef INCLUDE_CALLBACK_H_
#define INCLUDE_CALLBACK_H_

#include "result.h"
#include "clever_string.h"


typedef int (*action_t)(string_t *line, result_t *data);

int get_from(string_t *line, result_t *data);
int get_to(string_t *line, result_t *data);
int get_date(string_t *line, result_t *data);
int get_boundary(string_t *content_type, result_t *data);
int get_parts_in_body(string_t *text, result_t *data);

void add_slash(string_t string);  // добавляет слеш в значение ключа если найдена ковычка
result_t *test_results(result_t *data);  // проходит по структуре проверяет на наличие ковычек и добавляет слеш

#endif  // INCLUDE_CALLBACK_H_
