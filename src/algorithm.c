#include <stdbool.h>
#include <stdint.h>

#include "cboxes/algorithm.h"

void
cs_swap(void *restrict a, void *b, size_t size) {
    char t[size];
    cs_copy_memory(t, a, size, size);
    cs_copy_memory(a, b, size, size);
    cs_copy_memory(b, t, size, size);
}

void
cs_bubble_sort_a(void **items, uint64_t item_count, size_t item_size,
                 cs_is_greater_t is_greater) {

    for (size_t i = 0; i < item_count; i++) {
        for (size_t j = 0; j < item_count - 1; j++) {
            void *curr = *(char **)items + j * item_size;
            void *next = *(char **)items + (j + 1) * item_size;

            if (is_greater(curr, next)) {
                cs_swap(curr, next, item_size);
            }
        }
    }
}

void
cs_bubble_sort_b(void **items, uint64_t item_count, size_t item_size,
                 cs_is_greater_t is_greater) {

    for (size_t i = 0; i < item_count; i++) {
        for (size_t j = 0; j < item_count - 1; j++) {
            void *curr = *(char **)items + j * item_size;
            void *next = *(char **)items + (j + 1) * item_size;

            if (!is_greater(curr, next)) {
                cs_swap(curr, next, item_size);
            }
        }
    }
}
