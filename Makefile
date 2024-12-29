CC = gcc
RM = rm
MEMTEST = valgrind

C_FLAGS = -Wall -Ofast -o 

all: build

build:
	$(CC) ed.c $(C_FLAGS) ed

.PHONY: clean
clean:
	$(RM) ed

.PHONY: memtest
memtest:
	$(MEMTEST) -s --leak-check=full ./ed
