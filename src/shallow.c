#include "cboxes/shallow.h"
#include "cboxes/numtypes.h"

void *cs_ShallowCopy(void *dest, const void *src, size_t count) {
    for (size_t i = 0; i < count; i++) {
        ((byte *)dest)[i] = ((byte *)src)[i];
    }
    return dest;
}

void cs_ShallowFree(void *ptr) { free(ptr); }
