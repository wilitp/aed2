CC=gcc
CFLAGS = -std=c99 -pedantic -Wall -Werror -Wextra -g -no-pie

all: clean reader.output

%.output: ;
	$(CC) $(CFLAGS) -c array_helpers.c weather.c
	$(CC) $(CFLAGS) -o weather *.o main.c


clean:
	@rm -f *.o
	@rm -f *.output
	@rm -f weather
	@rm -f *.out

