CC=gcc
CFLAGS = -std=c99 -pedantic -Wall -Werror -Wextra -g

all: clean reader.output

%.output: ;
	$(CC) $(CFLAGS) -c main.c
	$(CC) $(CFLAGS) main.o -o reader.output

clean:
	@rm -f *.o
	@rm -f *.output

