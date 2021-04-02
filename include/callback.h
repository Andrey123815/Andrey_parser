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

#endif  // INCLUDE_CALLBACK_H_
