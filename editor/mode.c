#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/mode.h"
#include "../include/pool.h"
#include "../include/input.h"
#include "../include/filehandle.h"

extern poolNode* pool;

int modea(){
	char command[32768];						// Max len(I know it is too small)

	while (1){
		getstr(command);

		if ((!strcmp(command, ".")) != 1){
			poolPushBack(&pool, command);		// Push current command into string pool(to the back)
			poolPushBack(&pool, "\n");			// Push in new line
			continue;
		} else {
			break;
		}
	}

	return 0;
}

int modei(){
	return 0;
}