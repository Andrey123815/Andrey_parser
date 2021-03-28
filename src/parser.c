#include "parser.h"

#include <string.h>


lexem_t get_lexem_key(char *s, char *current_state) {
    if (strcmp(s,EOF) == 0) {
        return L_EOF;
    }
    char * key = strtok(s,":");
    key = font_parser(key);
    if (strcmp(key,"content-type" == 0)) {
        return L_CONTENT_TYPE;
    }
    if (strcmp(key,"from") == 0 || strcmp(key,"from") == 0 || strcmp(key,"from") == 0) {
        return L_OTHER_KEYS;
    }

}



