#include "cboxes/shallow.h"
#include "cboxes/types.h"

void cs_ShallowCopy(void *dest, const void *src, size_t count) {
    for (size_t i = 0; i < count; i++) {
        ((byte*)dest)[i] = ((byte*)src)[i];
    }
}

void cs_ShallowFree(void *ptr) { free(ptr); }

