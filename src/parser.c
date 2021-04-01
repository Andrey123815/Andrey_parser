#define NOT_SUCCESS   0
#define SUCCESS       1
#define TO           11
#define FROM         22
#define DATE         33
#define CONTENT_TYPE 44

#include "parser.h"

#include <string.h>


lexem_t get_lexem_key(string_t *s) {
    if (strcmp(s->str, (const char *) EOF) == 0) {
        return L_EOF;
    }

    string_t *key_t = str_tok(s,':');
    font_parser(key_t->str);

    if (strcmp(key_t->str, "content-type") == 0) {
        free_string(key_t);
        return L_CONTENT_TYPE;
    }

    if (strcmp(key_t->str, "date") == 0) {
        free_string(key_t);
        return L_DATE;
    }

    if (strcmp(key_t->str, "from") == 0) {
        free_string(key_t);
        return L_FROM;
    }

    if (strcmp(key_t->str, "to") == 0) {
        free_string(key_t);
        return L_TO;
    }

    if (s->size == 0) {
        free_string(key_t);
        return L_ENTER;
    } else {
        free_string(key_t);
        return L_NO_ENTER;
    }
    free_string(key_t);
    return L_ERR;
}


string_t *font_parser(string_t *key_in_random_font) {
    for (size_t i = 0; key_in_random_font->str[i] != '\0'; ++i) {
        if (key_in_random_font->str[i] >= 'A' && key_in_random_font->str[i] <= 'Z') {
            key_in_random_font->str[i] += ('a'-'A');
        }
    }
    return key_in_random_font;
}

string_t *get_multi_bound(string_t *content_type) {
    string_t *bound_1 = create_string(), *bound_2 = create_string();
    bound_1->str = "multipart";
    result_t k;

    if (str_str(bound_1, content_type).result_status == NOT_SUCCESS) {
        bound_1->str = "";
        return bound_1;
    } else {
        bound_1->str = "boundary=";  // как обозначить кавычки?
        bound_2->str = "boundary=\"";

        if ((k = str_str(bound_1, content_type)).result_status == SUCCESS) {
            return delete_symbols_in_begin(content_type, k.ref);
        }

        if ((k = str_str(bound_2, content_type)).result_status == SUCCESS) {
            return delete_symbols_in_begin(content_type, k.ref);
        }
    }

    bound_1->str = "";

    return bound_1;
}


int get_number_parts(string_t *text, string_t *boundary, int part) {
    if (text->size > 0 && str_str(boundary, text).result_status == SUCCESS) {
        part++;
    }
    return part;
}


string_t *get_key_value(string_t *key_with_value, int lexem) {
    string_t *str = create_string();

    if (lexem == TO)  {
        str = delete_symbols_in_begin(key_with_value, 3);  // с учетом двоеточия после ключа
    }

    if (lexem == FROM || lexem == DATE) {
        str = delete_symbols_in_begin(key_with_value, 5);
    }

    if (lexem == CONTENT_TYPE) {
        return get_multi_bound(key_with_value);
    }

    if ((char)str->str[0] == ' ') {
        return delete_symbols_in_begin(key_with_value, 1);
    }

    return str;
}
