#ifndef INCLUDE_FILEHANDLE_H_

#ifdef _clang_
#pragma once
#endif

#ifdef __GNUC__
#define INCLUDE_FILEHANDLE_H_
#endif

#include <stdio.h>

int readLine(int fd, int line_number, char *buffer, size_t buffer_size);
long long getFilesize();

#endif // INCLUDE_FILEHANDLE_H_