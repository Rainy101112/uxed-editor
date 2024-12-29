#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "include/pool.h"
#include "include/mode.h"
#include "include/filehandle.h"
#include "include/input.h"

extern poolNode* pool;

int fd = 0;					// File discription
int showpmt = 0;			// Show prompt
char *filepath;				// Current file path

int looping();				// Command main loop

int looping(){
	char command[32768];						// Max len

	while (1){									// Main loop
		if (showpmt == 1){						// Show prompt by this
			printf("*");
		}
		getstr(command);

		if ((!strcmp(command, "f")) == 1){		// Command "f"
			printf("%s\n", filepath);

		} else 
		if ((!strcmp(command, "a")) == 1){		// Command "a"
			modea();

		} else 
		if ((!strcmp(command, "w")) == 1){		// Command "w"
			poolNode* pcur = pool;

			if (pcur != NULL){					// User had wrote something into pool
				while (pcur) {
					ssize_t written = write(fd, pcur->data, strlen(pcur->data));
					if (written == -1) {		// If write failed
						printf("Write failed");
						break;
					}
					pcur = pcur->next;			// Jump to next
				}

				long long size = getFilesize();	// Get file size

				if (size != -1) {				// If lseek successfully
					printf("%lld\n", size); // Show current file size(bytes).
				}
			} else {							// String pool is empty
				printf("?\n");					// I can't understand what is user doing
			}

		} else 
		if ((!strcmp(command, "P")) == 1){		// Show prompt
			showpmt = 1;

		} else 
		if ((!strcmp(command, "q")) == 1){		// Quit
			poolListDesTroy(&pool);
			return 0;
		}
		else {
			printf("?\n");						// What are you doing?
		}
	}

	return 0;
}

int main(int argc, char **argv){
	if (argc > 1){								// Has more than 1 args
		if (argv[1][0] == '-' || (argv[1][0] == '-' && argv[1][1] == '-')) {		// Is option
			if ((!strcmp(argv[1], "-h")) == 1 || (!strcmp(argv[1], "--help")) == 1){	// Help
				printf("Uinxed ed is a line-oriented text editor. It is used to create, display,\n"
						"modify and otherwise manipulate text files, both interactively and via\n"
						"shell scripts. A restricted version of ed, red, can only edit files in\n"
						"the current directory and cannot execute shell commands. Ed is the	\n"
						"'standard' text editor in the sense that it is the original editor for\n"
						"Unix, and thus widely available. For most purposes, however, it is	\n"
						"superseded by full-screen editors such as GNU Emacs or GNU Moe.\n"
						"\n"
						"Usage: ed [options] [file]\n"
						"\n"
						"Options:\n"
						"  -h, --help                 display this help and exit\n"
						"  -V, --version              output version information and exit\n"
						"  -E, --extended-regexp      use extended regular expressions\n"
						"  -G, --traditional          run in compatibility mode\n"
						"  -l, --loose-exit-status    exit with 0 status even if a command fails\n"
						"  -p, --prompt=STRING        use STRING as an interactive prompt\n"
						"  -q, --quiet, --silent      suppress diagnostics written to stderr\n"
						"  -r, --restricted           run in restricted mode\n"
						"  -s, --script               suppress byte counts and '!' prompt\n"
						"  -v, --verbose              be verbose; equivalent to the 'H' command\n"
						"      --strip-trailing-cr    strip carriage returns at end of text lines\n"
						"\n"
						"Start edit by reading in 'file' if given.\n"
						"If 'file' begins with a '!', read output of shell command.\n"
						"\n"
						"Exit status: 0 for a normal exit, 1 for environmental problems\n"
						"(file not found, invalid command line options, I/O errors, etc), 2 to\n"
						"indicate a corrupt or invalid input file, 3 for an internal consistency\n"
						"error (e.g., bug) which caused ed to panic.\n"
						);
			} else 
			if ((!strcmp(argv[1], "-v")) == 1 || (!strcmp(argv[1], "--version")) == 1){		// Show version
				printf(
					"Uinxed ed 0.1\n"
					"Copyright (C) 2024 Rainy101112.\n"
					"License MIT. <https://opensource.org/license/MIT> <https://mit-license.org/>\n"
					"This is free software: you are free to change and redistribute it.\n"
				);
			} 
			else {
				printf("ed: Wrong options or options is unavailable.\n");			// My bad or your bad
			}
		} else {
			pool = NULL;						// Now pool is empty(Initialization)
			filepath = strdup(argv[1]); 		// strdup copy string

			fd = open(filepath, O_RDWR);		// Open, mode read&write

			if (fd == -1){						// Oh no, it failed
				printf("ed: Could not open file: %s\n", filepath);
				free(filepath);					// Free filepath
				return -1;
			}
			
			long long size = getFilesize();		// Get file size

			if (size != -1) {					// If successfully
				printf("%lld\n", size);			// Show current file size(bytes).
			}

			looping();							// Start main loop
			close(fd);							// Loop out, close file discription
			free(filepath);						// Free file path
			}
	} else {
		printf("Usage: ed [Options] [file]\n");
	}

	return 0;
}