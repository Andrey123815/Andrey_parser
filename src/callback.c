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
    if (content_type == NULL || data == NULL) {
        return create_string();
    }

    string_t key = string_from_char("multipart");

    if (str_str(content_type, &key) < 0) {
        free_string(&key);
        return create_string();
    }
    free_string(&key);

    key = string_from_char("boundary=");

    long int pos = str_str(content_type, &key);
    if (pos < 0) {
        free_string(&key);
        return create_string();
    }

    return delete_symbols_in_begin(content_type, pos);
}

int get_parts_in_body(string_t *text, string_t *boundary, result_t *data) {
    if (str_str(text, boundary) >= 0) {
        data->part++;
    }
    return 0;
}
