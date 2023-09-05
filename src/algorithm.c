#include "cboxes/algorithm.h"
#include "cboxes/assert.h"

CS_IMPL_NUMERIC_IS_GREATER(int8, int8_t)
CS_IMPL_NUMERIC_IS_GREATER(int16, int16_t)
CS_IMPL_NUMERIC_IS_GREATER(int32, int32_t)
CS_IMPL_NUMERIC_IS_GREATER(int64, int64_t)
CS_IMPL_NUMERIC_IS_GREATER(float, float)
CS_IMPL_NUMERIC_IS_GREATER(double, float)

void
cs_swap(void *restrict a, void *b, size_t size) {
    char t[size];
    cs_copy_memory(t, a, size, size);
    cs_copy_memory(a, b, size, size);
    cs_copy_memory(b, t, size, size);
}

void
cs_bubble_sort_a(void *items, uint64_t item_count, size_t item_size,
                 cs_is_greater_t is_greater) {
    for (uint64_t i = 0; i < item_count; i++) {
        for (uint64_t j = 0; j < item_count - 1; j++) {
            void *curr = (char *)items + j * item_size;
            void *next = (char *)items + (j + 1) * item_size;

            if (is_greater(curr, next)) {
                cs_swap(curr, next, item_size);
            }
        }
    }
}

void
cs_bubble_sort_b(void *items, uint64_t item_count, size_t item_size,
                 cs_is_greater_t is_greater) {
    for (uint64_t i = 0; i < item_count; i++) {
        for (uint64_t j = 0; j < item_count - 1; j++) {
            void *curr = (char *)items + j * item_size;
            void *next = (char *)items + (j + 1) * item_size;

            if (!is_greater(curr, next)) {
                cs_swap(curr, next, item_size);
            }
        }
    }
}

void
cs_quick_sort_a(void *items, uint64_t item_length, size_t item_size,
                cs_is_greater_t is_greater) {
    if (item_length < 2) {
        return;
    }

    // TODO(gr3yknigh1): Use random pivot value
    void *pivot = (char *)items + (item_length - 1) * item_size;
    void *head = items;
    void *tail = items;

    while (tail < pivot) {
        if (is_greater(pivot, tail)) {
            cs_swap(head, tail, item_size);
            head = (char *)head + item_size;
        }
        tail = (char *)tail + item_size;
    }

    cs_swap(pivot, head, item_size);

    size_t half_bytes_offset = (char *)head - (char *)items;
    uint64_t half_length = half_bytes_offset / item_size;

    cs_quick_sort_a(items, half_length, item_size, is_greater);
    cs_quick_sort_a((char *)items + half_bytes_offset + item_size,
                    item_length - (half_bytes_offset + item_size) / item_size,
                    item_size, is_greater);
}

void
cs_quick_sort_d(void *items, uint64_t item_length, size_t item_size,
                cs_is_greater_t is_greater) {
    if (item_length < 2) {
        return;
    }

    void *pivot = (char *)items + (item_length - 1) * item_size;
    void *head = items;
    void *tail = items;

    while (tail < pivot) {
        if (!is_greater(pivot, tail)) {
            cs_swap(head, tail, item_size);
            head = (char *)head + item_size;
        }
        tail = (char *)tail + item_size;
    }

    cs_swap(pivot, head, item_size);

    size_t half_bytes_offset = (char *)head - (char *)items;
    uint64_t half_length = half_bytes_offset / item_size;

    cs_quick_sort_d(items, half_length, item_size, is_greater);
    cs_quick_sort_d((char *)items + half_bytes_offset + item_size,
                    item_length - (half_bytes_offset + item_size) / item_size,
                    item_size, is_greater);
}
