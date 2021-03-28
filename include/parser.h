#ifndef DZ_4_PARSER_H
#define DZ_4_PARSER_H

#include "types_and_tables.h"
#include "clever_string.h"

typedef struct {
    string_t *from;
    string_t *to;
    string_t *date;
    int part;
} final_t;

int set_from(final_t *final, string_t *str) {

    //string_cpy(final->from, str + 5);
    // PARSE
    // From: wlejfhlwe

    return 0;
}

lexem_t get_lexem_key(string_t s, char **end);

//char *parse_key(char *string); // find keys(from, date, to, content-type)
char *parser_key_value(string_t string); // find key value
char *font_parser(char* key_in_random_font); // key in one font(lower)

#endif //DZ_4_PARSER_H
