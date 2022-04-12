CC=gcc
CFLAGS = -std=c99 -pedantic -Wall -Werror -Wextra -g -no-pie

all: clean reader.output

%.output: ;
	$(CC) $(CFLAGS) -c helpers.c sort.c
	$(CC) $(CFLAGS) -o mysort *.o main.c


clean:
	@rm -f *.o
	@rm -f mysort
	@rm -f *.out

