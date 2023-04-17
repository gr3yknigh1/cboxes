#ifndef CBOXES_MEMORY_H
#define CBOXES_MEMORY_H

#include <stddef.h>

void cs_CopyMemory(void *restrict dest, const void *src, size_t destSize,
                        size_t srcSize);

#endif // CBOXES_MEMORY_H
