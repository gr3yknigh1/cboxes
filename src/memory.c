#include "cboxes/memory.h"
#include "cboxes/assert.h"

void
cs_copy_memory(void *restrict dest, const void *src, size_t dest_size,
               size_t src_size) {
    CS_ASSERT(dest_size >= src_size, "Destanation is less than source");

    for (size_t i = 0; i < dest_size; ++i) {
        ((char *)dest)[i] = ((char *)src)[i];
    }
}
