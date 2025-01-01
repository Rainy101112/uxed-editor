#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "../include/filehandle.h"

extern int fd;

int readLine(int fd, int line_number, char *buffer, size_t buffer_size) {
	char temp_buffer[32768];
	int current_line = 0;
	ssize_t bytes_read;
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
	off_t offset = 0;
	#pragma GCC diagnostic pop

	lseek(fd, 0, SEEK_SET);						// Move to head

	while ((bytes_read = read(fd, temp_buffer, sizeof(temp_buffer) - 1)) > 0) {
		temp_buffer[bytes_read] = '\0';			// The end of string is '\0'
		char *line = temp_buffer;

		while (*line) {
			if (*line == '\n' || (line == temp_buffer + bytes_read - 1 && *line != '\n')) {
				current_line++;

				if (current_line == line_number) {
					/* Find line, read */
					size_t line_length = (line == temp_buffer + bytes_read - 1 && *line != '\n') ? (line - temp_buffer + 1) : (line - temp_buffer);

					if (line_length >= buffer_size) {
						return -2;				// Len longer than buffer, leak
					}

					strncpy(buffer, temp_buffer, line_length);
					buffer[line_length] = '\0';

					return 0;					// Read successfully
				}

				line++;							// Jump over '\n' or '\0'

			} else {
				line++;							// Continue find

			}
		}

		offset += bytes_read;

		if (current_line >= line_number) {
			/* Find line, copy string to buffer */
			size_t line_length = (line == temp_buffer + bytes_read - 1 && *line != '\n') ? (line - temp_buffer + 1) : (line - temp_buffer);

			if (line_length >= buffer_size) {
				return -2;						// Len longer than buffer, leak
			}

			strncpy(buffer, temp_buffer, line_length);
			buffer[line_length] = '\0';

			return 0;							// Successed
		}

	}

	if (bytes_read == -1) {
		printf("[%s %d] Error reading file.\n", __FILE__, __LINE__);
		return -1;								// Failed

	} else if (current_line < line_number) {
		return 1;								// Leak

	}

	return 0;									// Line not found
}

long long getFilesize(){
	off_t size = lseek(fd, 0, SEEK_END);		// Get file size (offset)

	if (size == -1) {					 		// Failed
		printf("[%s %d] lseek failed.\n", __FILE__, __LINE__);
		return -1;
	} else {
		return (long long)size;					/// File size may be really really long
	}
}