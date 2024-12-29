#include <stdio.h>
#include <stdlib.h>

#include "../include/input.h"

void getstr(char *buf){
	char temp = 0;
	int i = 0;

	while (1){
		temp = (char)(getchar());

		if (temp != '\n'){
			buf[i] = temp;
			i++;
			continue;
		} else {
			buf[i] = '\0';
			break;
		}
	}

	return;
}