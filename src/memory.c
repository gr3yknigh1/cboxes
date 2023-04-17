#include "cboxes/memory.h"
#include "cboxes/assert.h"

void cs_CopyMemory(void *restrict dest, const void *src, size_t destSize,
                       size_t srcSize) {
    CS_ASSERT(destSize >= srcSize, "");

    for (size_t i = 0; i < srcSize; ++i) {
        ((char *)dest)[i] = ((char *)src)[i];
    }
}
