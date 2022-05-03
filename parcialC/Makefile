FLAGS = -Wextra -Wall -Werror -g -pedantic -std=c99
all: clean
	gcc $(FLAGS) -o delivery ./main.c ./flight.c ./array_helpers.c

clean:
	@rm -f delivery
	@rm -f *.o
