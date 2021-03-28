#include <stdio.h>
#include "clever_string.h"

int main() {
    printf("Hello, World!\n");
    string_t *str = create_string();
    FILE * ptr = fopen(SOURCE_DIR"/1.txt", "r");
    if (ptr == NULL) {
        printf("%s", "not access");
        return 1;
    }
    read_str(ptr, str);
    printf("string: %s\n", str->str);
    //printf("path: %s\n", SOURCE_DIR);
    //printf("%d", (int)(str->str[0]));
    fclose(ptr);
    free_string(str);
    return 0;
}
