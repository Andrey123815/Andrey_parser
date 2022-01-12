#include <stdio.h>
#include "clever_string.h"

int main() {
    string_t *str = create_string();
    
    FILE * ptr = fopen(SOURCE_DIR"/1.txt", "r");
    
    if (ptr == NULL) {
        printf("%s", "not access");
        return 1;
    }
    
    read_str(ptr, str);
    printf("string: %s\n", str->str);
    
    fclose(ptr);
    free_string(str);
    
    return 0;
}

