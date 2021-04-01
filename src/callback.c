#define NOT_SUCCESS   0
#define SUCCESS       1

#include "parser.h"
#include <stddef.h>


int get_to(string_t *line, result_t *data) {
    data->to = delete_symbols_in_begin(line, 3);  // с учетом двоеточия после ключа

}

int get_from(string_t *line, result_t *data) {
    data->from = delete_symbols_in_begin(line, 5);  // с учетом двоеточия после ключа
}

int get_date(string_t *line, result_t *data) {
    data->date = delete_symbols_in_begin(line, 5);  // с учетом двоеточия после ключа
}

/*string_t* get_boundary(string_t *content_type, result_t *data) {
    string_t *bound_1 = create_string(), *bound_2 = create_string();
    bound_1->str = "multipart";
    long int k;

    if (str_str(bound_1, content_type) < 0) {
        bound_1->str = "";
        return bound_1;
    } else {
        bound_1->str = "boundary=";  // как обозначить кавычки?
        bound_2->str = "boundary=\"";

        if (k = str_str(bound_1, content_type)) {
            return delete_symbols_in_begin(content_type, k.ref);  // check without quotes
        }

        if ((k = str_str(bound_2, content_type)).result_status == SUCCESS) {
            return delete_symbols_in_begin(content_type, k.ref);  // with quotes
        }
    }

    return NULL;
}

int get_parts_in_body(string_t *text, string_t *boundary, result_t *data) {
    if (str_str(boundary, text) >= 0) {
        data->part++;
    }
    return 0;
}*/
