flags := -Wextra -Wall -Werror -std=c99 -pedantic -g 
all:
	gcc $(flags) -c ./dict.c ./dict_helpers.c ./helpers.c ../ej2/string.c ./main.c
	gcc $(flags) -o dictionary *.o

clean:
	rm -rf dictionary *.o
