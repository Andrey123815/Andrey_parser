#include <stdio.h>

#include "types_and_tables.h"
#include "clever_string.h"
#include "parser.h"

#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>

int main(int argc, char **argv) {

   //FILE * ptr = fopen(SOURCE_DIR"/1.txt", "r");

    if (argc != 2) {
        printf("The program needs a file path to .eml document\n");
        return -1;
    }

    FILE *fdin = fopen(argv[1], "r");
    if (fdin == NULL) {
        printf("Usage %s invalid\n", argv[1]);
        return -1;
    }

    // gain file size
    struct stat statbuf = {};
    if (fstat(fdin, &statbuf) < 0) {
        printf("Impossible to get the %s size\n", argv[1]);
        return -1;
    }

    fclose(fdin);


    FILE * file_eml = fopen(argv[1],"r");
    string_t *str = create_string();
    state_t state = S_KEY;
    callback_t  callback;
    req_date_t data;

    while(state != S_EOF) {

        read_str(file_eml, str);
        lexem_t lexem = get_lexem_key(str);

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
    return 0;
}
