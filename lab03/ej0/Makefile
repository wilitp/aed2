CC=gcc
CFLAGS = -std=c99 -pedantic -Wall -Werror -Wextra -g -no-pie

all: clean reader.output

%.output: ;
	$(CC) $(CFLAGS) -o phrasereader main.c


clean:
	@rm -f *.o
	@rm -f phrasereader

