#include "result.h"

result_t create_result() {
    result_t result;

    result.from = create_string();
    result.to = create_string();
    result.date = create_string();
    result.boundary = create_string();
    result.part = 0;

    return result;
}
int free_result(result_t *result) {
    free_string(&result->from);
    free_string(&result->to);
    free_string(&result->date);
    free_string(&result->boundary);

    return 0;
}
int print_result(FILE *fp, result_t *result) {
    if (fprintf(fp, "%s|%s|%s|%d", result->from.str, result->to.str, result->date.str, result->part) != 4) {
        return 1;
    }

    return 0;
}
