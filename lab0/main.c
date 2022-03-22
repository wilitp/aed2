#include <stdio.h>
// tipo
struct max_min_result {
    int max_value;
    int min_value;
    unsigned int max_position;
    unsigned int min_position;
};


// Function signature
struct max_min_result compute_max_min(int array[], unsigned int length);
// Implementacion
struct max_min_result compute_max_min(int array[], unsigned int length)
{
    unsigned int i = 1;
    int min;
    int max;
    int maxi;
    int mini;
    min = array[0];
    max = array[0];
    maxi = 0;
    mini = 0;
    while(i < length) {
        if(array[i] > max){
            max = array[i];
            maxi = i;
        }
        if(array[i] < min){
            min = array[i];
            mini = i;
        }
        i += 1;
    }
    struct max_min_result r = {max,min,maxi,mini};
    return r;
}

int main(void) {
    int array[] = {0, 9, -1, 4};
    struct max_min_result result = compute_max_min(array, 4);
    printf("%d", result.max_value); // Imprime 9
    printf("%d", result.min_value); // Imprime -1
    printf("%u", result.max_position); // Imprime 1
    printf("%u", result.min_position); // Imprime 2
}

