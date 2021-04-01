#include <stdio.h>

#include "clever_string.h"
#include "parser.h"


int main(int argc, char **argv) {
    if (argc != 2) {
        printf("The program needs a file path to .eml document\n");
        return -1;
    }

    FILE *file_eml = fopen(argv[1],"r");
    if (file_eml == NULL) {
        printf("Usage %s invalid\n", argv[1]);
        return -1;
    }
    string_t *current_str = create_string();

    state_t state = S_KEY;
    callback_t  callback;
    req_date_t data;

    while(state != S_EOF) {
        if (read_str(file_eml, current_str)) {
            // ебана, продумай как тут быть
            return 1;
        }

        lexem_t lexem = get_lexem(current_str);

        if (lexem == L_ERR) {
            return -1;
        }

        rule_t rule = table[state][lexem];

        if (rule.state == S_ERR)
            return -1;

        if (rule.action != NULL) {
            if (rule.action(callback, &data) == -1)
                return -1;
        }

        if (rule.state == S_EOF) {
            printf("%s|%s|%s|%d", data.to->str, data.from->str, data.date->str, data.part);
            return 0;
        }
        state = rule.state;
    }

    fclose(file_eml);
    free_string(current_str);

    return 0;
}
