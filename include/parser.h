#ifndef DZ_4_PARSER_H
#define DZ_4_PARSER_H

#include "types_and_tables.h"
#include "clever_string.h"

typedef enum {
    L_CONTENT_TYPE,
    L_OTHER_KEYS,
    L_ENTER,
    L_EOF,
    L_TEXT,
    L_BOUND,
} lexem_t;

lexem_t get_lexem_key(char* s,char *state);

//char *parse_key(char *string); // find keys(from, date, to, content-type)
char *parse_key_value(char * string); // find key value
char *parse_enter(char *s); // miss enter? get number enters to get number parts
char *font_parser(char* key_in_random_font); // key in one font(lower)

#endif //DZ_4_PARSER_H
