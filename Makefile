EJS = $(wildcard lab*/**/*.c)
OUTPUT = $(patsubst %.c, %.output, $(EJS))
CC=gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -g -no-pie

all: clean $(OUTPUT)
	@echo $(EJS)
	@echo $(OUTPUT)

%.output: ;
	$(CC) $(CFLAGS) -o $@ $(subst .output,.c,$@)

clean:
	@rm -f lab*/**/*.output

