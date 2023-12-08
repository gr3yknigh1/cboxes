#ifndef CBOXES_ALGORITHM_H_
#define CBOXES_ALGORITHM_H_

#include <stdbool.h>
#include <stdint.h>

#include "cboxes/memory.h"

#define CS_STATIC_ARRAY_ITEM_SIZE(ARRAY) (sizeof((ARRAY)[0]))
#define CS_STATIC_ARRAY_LENGTH(ARRAY)                                          \
    (sizeof((ARRAY)) / CS_STATIC_ARRAY_ITEM_SIZE(ARRAY))

typedef bool (*cs_is_greater_t)(const void *, const void *);

void cs_swap(void *restrict a, void *b, size_t size);

void cs_bubble_sort_a(void *items, uint64_t item_count, size_t item_size,
                      cs_is_greater_t is_greater);

void cs_bubble_sort_b(void *items, uint64_t item_count, size_t item_size,
                      cs_is_greater_t is_greater);

void cs_quick_sort_a(void *items, uint64_t item_length, size_t item_size,
                     cs_is_greater_t is_greater);

void cs_quick_sort_d(void *items, uint64_t item_length, size_t item_size,
                     cs_is_greater_t is_greater);

#endif // CBOXES_ALGORITHM_H_
