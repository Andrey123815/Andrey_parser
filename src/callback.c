#include "parser.h"


int get_from(string_t *line, result_t *data) {
    data->from = delete_symbols_in_begin(line, 5);  // с учетом двоеточия после ключа

    return 0;
}

int get_to(string_t *line, result_t *data) {
    data->to = delete_symbols_in_begin(line, 3);  // с учетом двоеточия после ключа

    return 0;
}

int get_date(string_t *line, result_t *data) {
    data->date = delete_symbols_in_begin(line, 5);  // с учетом двоеточия после ключа

    return 0;
}

string_t get_boundary(string_t *content_type, result_t *data) {
    string_t bound_1 = create_string();
    string_t bound_2 = create_string();
    bound_1.str = "multipart";
    long int k;

    if (str_str(content_type, &bound_1) < 0) {
        bound_1.str = "";
        return bound_1;
    } else {
        bound_1.str = "boundary=";  // как обозначить кавычки?

        if (str_str(&bound_1, content_type) {
            return delete_symbols_in_begin(content_type, k.ref);  // check without quotes
        }

        if (str_str(&bound_2, content_type)) {
            return delete_symbols_in_begin(content_type, k.ref);  // with quotes
        }
    }

    return delete_symbols_in_begin(bou);
}

int get_parts_in_body(string_t *text, string_t *boundary, result_t *data) {
    if (str_str(text, boundary) >= 0) {
        data->part++;
    }
    return 0;
}
