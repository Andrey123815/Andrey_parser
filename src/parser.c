#include "clever_string.h"
#include "parser.h"
#include "types_and_tables.h"
#include <string.h>

lexem_t get_lexem(string_t *s) {
    if (s->str[0] == EOF) {
        return L_EOF;
    }

    if (s->size == 0) {
        return L_ENTER;
    }

    string_t key_t = str_tok(s, ':');

    font_lower(&key_t);

    if (strcmp(key_t.str, "from") == 0) {
        free_string(&key_t);
        return L_FROM;
    }

    if (strcmp(key_t.str, "to") == 0) {
        free_string(&key_t);
        return L_TO;
    }

    if (strcmp(key_t.str, "date") == 0) {
        free_string(&key_t);
        return L_DATE;
    }

    if (strcmp(key_t.str, "content-type") == 0) {
        free_string(&key_t);
        return L_CONTENT_TYPE;
    }

    free_string(&key_t);

    if (s->size > 0) {
        return L_TEXT;
    }

    return L_ERR;
}

int parse(FILE *file_eml, result_t *result) {
    if (file_eml == NULL || result == NULL) {
        return -1;
    }

    string_t current_line = create_string();

    state_t state = S_BEGIN;

    while (state != S_END) {
        if (read_str(file_eml, &current_line)) {
            free_string(&current_line);
            return -1;
        }

        lexem_t lexem = get_lexem(&current_line);

        if (lexem == L_ERR) {
            free_string(&current_line);
            return -1;
        }

        rule_t rule = table[state][lexem];

        if (rule.state == S_ERR) {
            free_string(&current_line);
            return -1;
        }

        if (rule.action != NULL) {
            if (rule.action(&current_line, result)) {
                free_string(&current_line);
                return -1;
            }
        }

        state = rule.state;
    }
    test_results(result);
    free_string(&current_line);

    return 0;
}
