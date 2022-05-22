#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Esto ya andaria:
/* char *string_clone(const char *str) { */
/*     char *clone=NULL; */
/*     clone = malloc(strlen(str)+1); */
/*     strcpy(clone, str); */
/*     return clone; */
/* } */

// Pero asi copias un string sin necesidad de usar string.h
char *string_clone(const char *str) {
    char *clone=NULL;
    if(str != NULL) {
        size_t cap = 1;
        clone = malloc(cap);
        size_t index = 0;
        while(str[index] != '\0') {
            if(cap < index+1) {
                cap = 2*cap;
                clone = realloc(clone, cap);
            }
            clone[index] = str[index];
            index++;
        }
        if(cap < index+1) {
            cap = 2*cap;
            clone = realloc(clone, cap);
        }
        clone[index] = '\0';
        clone = realloc(clone, sizeof(char)*(index+1));

    }
    return clone;
}


int main(void) {
    char *original="\n"
         "A long time ago in a galaxy far, far away...\n\n\n"
         "         _______..___________.     ___      .______             \n"
         "        /       ||           |    /   \\     |   _  \\          \n"
         "       |   (----``---|  |----`   /  ^  \\    |  |_)  |          \n"
         "        \\   \\        |  |       /  /_\\  \\   |      /        \n"
         "    .----)   |       |  |      /  _____  \\  |  |\\  \\----.    \n"
         "    |_______/        |__|     /__/     \\__\\ | _| `._____|     \n"
         "                                                                \n"
         "____    __    ____      ___      .______           _______.     \n"
         "\\   \\  /  \\  /   /     /   \\     |   _  \\         /       |\n"
         " \\   \\/    \\/   /     /  ^  \\    |  |_)  |       |   (----` \n"
         "  \\            /     /  /_\\  \\   |      /         \\   \\    \n"
         "   \\    /\\    /     /  _____  \\  |  |\\  \\----..----)   |   \n"
         "    \\__/  \\__/     /__/     \\__\\ | _| `._____||_______/     \n"
         "\n\n\n"
         "                     Episode IV \n\n"
         "                     A NEW HOPE \n\n"
         "                     It is a period of civil war. Rebel\n"
         "spaceships, striking from a hidden base, have won their\n"
         "first victory against the evil Galactic Empire. During the\n"
         "battle, Rebel spies managed to steal secret plans to the\n"
         "Empire’s ultimate weapon, the DEATH STAR, an armored space\n"
         "station with enough power to destroy an entire planet.\n"
         "Pursued by the Empire’s sinister agents, Princess Leia\n"
         "races home aboard her starship, custodian of the stolen\n"
         "plans that can save her people and restore freedom to the\n"
         "galaxy...\n";
    char *copy=NULL;

    copy = string_clone(original);
    printf("Original: %s\n", original);
    printf("Copia   : %s\n", copy);
    free(copy);


    return EXIT_SUCCESS;
}

