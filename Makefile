CC = gcc
RM = rm
MEMTEST = valgrind

C_OBJ_FLAGS = -c -Wall -Ofast -o 
C_FLAGS = -Wall -Ofast -o 

all: build

build:
	@printf "\033[32m[BUILD]\033[0m Start building...\n"

	@$(CC) editor/mode.c $(C_OBJ_FLAGS) editor/mode.o
	@$(CC) editor/pool.c $(C_OBJ_FLAGS) editor/pool.o
	@$(CC) editor/input.c $(C_OBJ_FLAGS) editor/input.o
	@$(CC) file/filehandle.c $(C_OBJ_FLAGS) file/filehandle.o

	@$(CC) ed.c $(C_FLAGS) ed					\
	editor/mode.o editor/input.o editor/pool.o	\
	file/filehandle.o

	@printf "\033[32m[BUILD]\033[0m Build done.\n"

.PHONY: clean
clean:
	$(RM) editor/*.o
	$(RM) file/*.o
	$(RM) ed

.PHONY: memtest
memtest:
	$(MEMTEST) -s --leak-check=full ./ed
