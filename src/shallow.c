#include "cboxes/shallow.h"
#include "cboxes/string.h"

void *
cs_shallow_copy(void *restrict dest, const void *src, size_t count) {
    for (size_t i = 0; i < count; i++) {
        ((uint8_t *)dest)[i] = ((uint8_t *)src)[i];
    }
    return dest;
}

void
cs_shallow_free(void *ptr) {
    free(ptr);
}
