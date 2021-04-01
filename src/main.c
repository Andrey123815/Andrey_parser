#include <stdio.h>

#include "parser.h"

int parse(FILE *file_eml, result_t *result) {
    if (file_eml == NULL || result == NULL) {
        return -1;
    }

    string_t *current_line = create_string();

    state_t state = S_BEGIN;
//    callback_t  callback;

    while (state != S_END) {
        if (read_str(file_eml, current_line)) {
            free_string(current_line);
            return -1;
        }

        lexem_t lexem = get_lexem(current_line);

        if (lexem == L_ERR) {
            free_string(current_line);
            return -1;
        }

        rule_t rule = table[state][lexem];

        if (rule.state == S_ERR) {
            free_string(current_line);
            return -1;
        }

        if (rule.action != NULL) {
            if (rule.action(current_line, result))
                free_string(current_line);
                return -1;
        }

        state = rule.state;
    }

    free_string(current_line);

    return 0;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("The program needs a file path to .eml document\n");
        return 1;
    }

    FILE *file_eml = fopen(argv[1], "r");
    if (file_eml == NULL) {
        printf("Usage %s invalid\n", argv[1]);
        return 1;
    }

    result_t result;
    if (parse(file_eml, &result)) {
        return -1;
    }

    print_result(stdout, &result);

    fclose(file_eml);

    return 0;
}
