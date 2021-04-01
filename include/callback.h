#ifndef INCLUDE_CALLBACK_H_
#define INCLUDE_CALLBACK_H_

#include "parser.h"  // модуль со структурой ответа
#include "string.h"

typedef int (*action_t)(string_t *line, req_date_t *data);

int get_to(string_t *line, req_date_t *data);
int get_from(string_t *line, req_date_t *data);
int get_date(string_t *line, req_date_t *data);
string_t * get_boundary(string_t *line, req_date_t *data);
int get_parts_in_body(string_t *text, string_t *boundary, req_date_t *data);

#endif  // INCLUDE_CALLBACK_H_
