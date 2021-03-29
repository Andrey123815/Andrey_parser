#define TO           11
#define FROM         22
#define DATE         33
#define CONTENT_TYPE 44
#include "parser.h"

#include <string.h>


lexem_t get_lexem_key(string_t s) {

    if (strcmp(s.str, EOF) == 0) {
        return L_EOF;
    }

    string_t key_t = string_converter(strtok(s.str, ":"));
    font_parser(key_t);

    if (strcmp(key_t.str, "content-type") == 0) {
        return L_CONTENT_TYPE;
    }

    if (strcmp(key_t.str, "date") == 0 || strcmp(key_t.str, "from") == 0 || strcmp(key_t.str, "to") == 0) {
        return L_OTHER_KEYS;
    }

    if (s.size == 0) {
        return L_ENTER;
    } else {
        return L_NO_ENTER;
    }

    return L_ERR;
}


string_t font_parser(string_t key_in_random_font) {
    for (size_t i = 0; key_in_random_font.str[i] != '\0'; i++) {
        if (key_in_random_font.str[i] >= 'A' && key_in_random_font.str[i] <= 'Z')
            key_in_random_font.str[i] += ('a'-'A');
    }
    return key_in_random_font;
}


string_t get_multi_bound(string_t content_type) {
    string_t bound_1, bound_2;
    bound_1.str = "multipart";
    result_t k;

    if (str_str(bound_1, content_type).result_status == 0) {
        bound_1.str = "";
        return bound_1;
    }

    if (str_str(bound_1, content_type).result_status == 1) {
        bound_1.str = "boundary="""; // как обозначить кавычки?
        bound_2.str = "boundary=";

        if ((k = str_str(bound_1, content_type)).result_status == 1) {
            return delete_symbols_in_begin(content_type,k.ref);
        }

        if ((k = str_str(bound_2, content_type)).result_status == 1) {
            return delete_symbols_in_begin(content_type,k.ref);
        }
    }
    bound_1.str = "";
    return bound_1;
}


int get_number_parts(string_t text, string_t boundary, int part) {
    if (text.size > 0 && str_str(boundary,text).result_status != 0) {
        part++;
    }
    return part;
}


string_t get_key_value(string_t key_with_value, int status_key) {

    string_t str;
    if (status_key == TO)  {
        str = delete_symbols_in_begin(key_with_value,3);  // с учетом двоеточия после ключа
        if ((char)str.str[0] == " ") {
            return delete_symbols_in_begin(key_with_value,1);
        }
        return str;
    }

    if (status_key == FROM || status_key == DATE) {
        str = delete_symbols_in_begin(key_with_value,5);
        if ((char)str.str[0] == " ") {
            return delete_symbols_in_begin(key_with_value,1);
        }
        return str;
    }

    if (status_key == CONTENT_TYPE) {
        return get_multi_bound(key_with_value);
    }
    return str;
}
