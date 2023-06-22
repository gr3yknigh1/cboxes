#ifndef CBOXES_MEMORY_H_
#define CBOXES_MEMORY_H_

#include <stddef.h>

void cs_copy_memory(void *restrict dest, const void *src, size_t dest_size,
                    size_t src_size);

#endif // CBOXES_MEMORY_H_
