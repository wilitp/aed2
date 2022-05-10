#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ARRAY_SIZE 7

static void
print_array(int a[], size_t length) {
    assert(length > 0);
    printf("[ %d", a[0]);
    for (size_t i=1; i<length; i++) {
        printf(", %d", a[i]);
    }
    printf("]\n");
}

int main(void) {
    int array[ARRAY_SIZE] = {7, 4, 1, 3, 9, 3, 5};
    int *p=NULL;
    printf("before: ");
    print_array(array, ARRAY_SIZE);
    /* --------------------- Modificar ---------------------- */
    for (p=array; p < array+ARRAY_SIZE; p++) {
        p[0] = 0;
    }
    /* ------------------------------------------------------ */
    printf("after : ");
    print_array(array, ARRAY_SIZE);

    return EXIT_SUCCESS;
}

