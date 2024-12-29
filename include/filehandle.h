#ifndef INCLUDE_FILEHANDLE_H_
#define INCLUDE_FILEHANLDE_H_

#include <stdio.h>

int readLine(int fd, int line_number, char *buffer, size_t buffer_size);
long long getFilesize();

#endif // INCLUDE_FILEHANDLE_H_