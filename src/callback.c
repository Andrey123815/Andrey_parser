#include "parser.h"
#include <string.h>

string_t get_value(string_t *line, const char *key) {
    long int pos = strlen(key) + 1;

    if (line->str[pos] == ' ') {
        pos++;
    }

    return delete_symbols_in_begin(line, pos);
}

int get_from(string_t *line, result_t *data) {
    data->from = get_value(line, "from");

    return 0;
}

int get_to(string_t *line, result_t *data) {
    data->to = get_value(line, "to");

    return 0;
}

int get_date(string_t *line, result_t *data) {
    data->date = get_value(line, "date");

    return 0;
}

int get_boundary(string_t *content_type, result_t *data) {
    if (content_type == NULL || data == NULL) {
        return -1;
    }

    string_t key = string_from_char("multipart");

    if (str_str(content_type, &key) < 0) {
        free_string(&key);
        return 0;
    }
    free_string(&key);

    key = string_from_char("boundary=");

    long int pos = str_str(content_type, &key);
    if (pos < 0) {
        free_string(&key);
        return 0;
    }

    free_string(&data->boundary);
    data->boundary = delete_symbols_in_begin(content_type, pos + strlen("boundary="));

    if (data->boundary.str[0] == '\"') {
        delete_symbol(&data->boundary, 0);

        int i = 0;
        while (i < data->boundary.size && data->boundary.str[i] != '\"') {
            i++;
        }

        for (int j = i; j <= data->boundary.size; ++j) {
            delete_symbol(&data->boundary, j);
        }
    }

    return 0;
}

int get_parts_in_body(string_t *text, result_t *data) {
    if (data->boundary.size == 0) {
        data->part = 1;
        return 0;
    }

    if (str_str(text, &data->boundary) >= 0) {
        data->part++;
    }

    return 0;
}

/*int add_slash(string_t string) {
    if (string.size == 0) {
        return -1;
    }

    string_t new_str = create_string();
    int k = 0;

    for (int i = 0; i < string.size; ++i) {
        if (string.str[i] == '\"') {
            add_symbol(&new_str,'\\');
            k++;
        }
        add_symbol(&new_str,string.str[i]);
    }

    for (int i = 0; i < k; ++i) {
        add_symbol(&string,' ');
    }

    copy(&string,&new_str);
    free_string(&new_str);

    return 0;
}

result_t *test_results(result_t *data) {
    add_slash(data->to);
    add_slash(data->from);
    add_slash(data->date);
    return data;
}*/