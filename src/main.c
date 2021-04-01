#include <stdio.h>

#include "parser.h"


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

    result_t result = create_result();
    if (parse(file_eml, &result)) {
        return 1;
    }
    print_result(stdout, &result);
    free_result(&result);

    fclose(file_eml);

    return 0;
}
