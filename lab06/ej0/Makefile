sources := /main.c /queue.c /queue_helpers.c
targets := ./a/readqueue ./b/readqueue
cc      := gcc
flags   := -g -Wextra -Wall -Werror -std=c99 -pedantic 

all: $(targets)

./%/readqueue: 
	$(cc) $(flags) $(addprefix ./$*,$(sources)) -o $@

clean:
	rm -rf $(targets)

.PHONY: clean

