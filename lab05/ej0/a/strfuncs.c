#include <stdlib.h>
#include <stdbool.h>

size_t string_length(const char *str) {
    size_t c = 0;
    if(str != NULL) {
        while(true) {
            if(str[c] == '\0') {
                break;
            } else {
                c++;
            }
        }

    }
    return c;
}

char *string_filter(const char *str, char c) {
    size_t unfiltered_length = string_length(str);
    char *filtered = malloc(unfiltered_length+1);
    size_t j = 0;

    for(unsigned int i=0; i<=unfiltered_length; i++) {
        if(str[i]!=c) {
            filtered[j] = str[i];
            j++;
        }
    }

    filtered = realloc(filtered, sizeof(char)*j);

    return filtered;
}
