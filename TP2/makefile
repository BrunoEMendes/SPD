CC=gcc
CFLAG = -Wall -std=gnu99
CFLAGLIB = -pthread -fopenmp -lm

# https://stackoverflow.com/questions/170467/makefiles-compile-all-c-files-at-once

SRC=$(wildcard code/*.c)

test: $(SRC)
	$(CC) $(CFLAG) -o main $(SRC) $(CFLAGLIB)
