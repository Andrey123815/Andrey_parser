#include "parser.h"

#include <string.h>


lexem_t get_lexem_key(string_t s, char **end) {
    if (strcmp(s.str, EOF) == 0) {
        return L_EOF;
    }
    char * key = strtok(s.str, ":");
    font_parser(key);
    if (strcmp(key, "content-type") == 0) {
        end = *s.str +  13;  // с учетом двоеточия
        return L_CONTENT_TYPE;
    }
    if (strcmp(key, "date") == 0 || strcmp(key, "from") == 0) {
        end = *s.str + 5;  // с учетом двоеточия
        return L_OTHER_KEYS;
    }
    if ( strcmp(key, "to") == 0) {
        end = *s.str + 3;  // с учетом двоеточия
        return L_OTHER_KEYS;
    }
    if (s.size == 0) {
        return L_ENTER;
    }
    if (s.size != 0) {
        return L_NO_ENTER;
    }
}

char *font_parser(char* key_in_random_font) {
    if (key_in_random_font == NULL) {
        return NULL;
    }
    for (size_t i = 0; key_in_random_font[i] != '\0'; i++) {
        if (key_in_random_font[i] >= 'A' && key_in_random_font[i] <= 'Z')
            key_in_random_font[i] += ('a'-'A');
    }
    return key_in_random_font;
}

char *parser_key_value(string_t string) {

}
