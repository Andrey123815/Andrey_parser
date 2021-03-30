#include <stdio.h>

#include "types_and_tables.h"
#include "clever_string.h"
#include "parser.h"

#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>

int main(int argc, char **argv) {
    /*string_t *str = create_string();
    FILE * ptr = fopen(SOURCE_DIR"/1.txt", "r");
    if (ptr == NULL) {
        printf("%s", "not access");
        return 1;
    }
    read_str(ptr, str);
    printf("string: %s\n", str->str);
    fclose(ptr);
    free_string(str);

    char * str = "get_result success";
    string_t  string;
    string = string_converter(str);
    printf("%s", string.str);*/

    if (argc != 2) {
        printf("The program needs a file path to .eml document\n");
        return -1;
    }

    int fdin = 0;
    if ((fdin = fopen(argv[1], "r")) < 0) {
        printf("Usage %s invalid\n", argv[1]);
        return -1;
    }

    // gain file size
    struct stat statbuf = {};
    if (fstat(fdin, &statbuf) < 0) {
        printf("Impossible to get the %s size\n", argv[1]);
        return -1;
    }

    // using mmap
    void* file_body = NULL;
    if ((file_body = mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, fdin, 0)) == MAP_FAILED) {
        printf("mmap error\n");
        return -1;
    }
    fclose(fdin);


    FILE * file_eml = fopen(argv[1],"r");
    string_t str;
    state_t state = S_GET_KEY;

    while(state != S_EOF) {

        read_str(file_eml, &str);
        lexem_t lexem = get_lexem_key(str);
        if (lexem == L_ERR) {
            return -1;
        }

        rule_t rule = table[state][lexem];
        if (rule.state == S_ERR)
            return -1;
        if (rule.action != NULL) {
            if (rule.action(callback, data) == -1)  // как передавать экшн???
                return -1;
        }

        if (rule.state == S_EOF)
            return 0;
        state = rule.state;
    }

    return 0;
}
