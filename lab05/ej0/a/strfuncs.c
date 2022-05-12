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
    char aux[unfiltered_length];
    size_t j = 0;
    for(unsigned int i=0; i<=unfiltered_length; i++) {
        if(str[i]!=c) {
            aux[j] = str[i];
            j++;
        }
    }
    char *filtered = malloc(j+1);

    for(unsigned int i=0; i<=unfiltered_length; i++) {
        filtered[i] = aux[i];
    }
    return filtered;
}