#pragma once

#include "util.h"
#include <string.h>
#include <stdlib.h>

char* io_read_file(const char* path);

int io_write_file(void *buffer, size_t size, const char *path);

void pe_free_mem(void *ptr);