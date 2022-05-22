#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "stack.h"
#include "reverse/array_helpers.h"

static const unsigned int MAX_SIZE = 100u;
void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n"
           "Loads an array given in a file in disk and prints it on the screen."
           "\n\n"
           "The input file must have the following format:\n"
           " * The first line must contain only a positive integer,"
           " which is the length of the array.\n"
           " * The second line must contain the members of the array"
           " separated by one or more spaces. Each member must be an integer."
           "\n\n"
           "In other words, the file format is:\n"
           "<amount of array elements>\n"
           "<array elem 1> <array elem 2> ... <array elem N>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;
    // Program takes exactly two arguments
    // (the program's name itself and the input-filepath)
    bool valid_args_count = (argc == 2);

    if (!valid_args_count) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return result;
}

int main(int argc, char *argv[]) {
    char *filepath = parse_filepath(argc, argv);
    stack_elem arr[MAX_SIZE];
    unsigned int length = array_from_file(arr, MAX_SIZE, filepath);
    stack s = stack_empty();
    for(int i=length-1; 0<=i;--i) {
        s = stack_push(s, arr[i]);
    }
    stack_elem *revarr = stack_to_array(s);

    printf("Original");
    array_dump(arr, length);
    printf("Reversed");
    array_dump(revarr, length);
    stack_destroy(s);
    free(revarr);
}
