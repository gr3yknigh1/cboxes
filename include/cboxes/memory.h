#ifndef CBOXES_MEMORY_H_
#define CBOXES_MEMORY_H_

#include <stddef.h>

void cs_CopyMemory(void *restrict dest, const void *src, size_t destSize,
                        size_t srcSize);

#endif // CBOXES_MEMORY_H_
