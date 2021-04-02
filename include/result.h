#ifndef DZ_4_RESULT_H
#define DZ_4_RESULT_H

#include "clever_string.h"

typedef struct {
    string_t from;
    string_t to;
    string_t date;
    int part;
} result_t;

result_t create_result();
int free_result(result_t *result);
int print_result(FILE *fp, result_t *result);

#endif //DZ_4_RESULT_H
