#ifndef CBOXES_ALGORITHM_H_
#define CBOXES_ALGORITHM_H_

#include <stdbool.h>
#include <stdint.h>

#include "cboxes/memory.h"

#define CS_STATIC_ARRAY_ITEM_SIZE(ARRAY) (sizeof((ARRAY)[0]))
#define CS_STATIC_ARRAY_LENGTH(ARRAY)                                          \
    (sizeof((ARRAY)) / CS_STATIC_ARRAY_ITEM_SIZE(ARRAY))

typedef bool (*cs_is_greater_t)(void *, void *);

#define CS_DEFINE_NUMERIC_IS_GREATER(POSTFIX, TYPE)                            \
    bool is_greater_##POSTFIX(void *a, void *b)

#define CS_IMPL_NUMERIC_IS_GREATER(POSTFIX, TYPE)                              \
    bool is_greater_##POSTFIX(void *a, void *b) {                              \
        return (*(TYPE *)a) > (*(TYPE *)b);                                    \
    }

CS_DEFINE_NUMERIC_IS_GREATER(int8, int8_t);
CS_DEFINE_NUMERIC_IS_GREATER(int16, int16_t);
CS_DEFINE_NUMERIC_IS_GREATER(int32, int32_t);
CS_DEFINE_NUMERIC_IS_GREATER(int64, int64_t);
CS_DEFINE_NUMERIC_IS_GREATER(float, float);
CS_DEFINE_NUMERIC_IS_GREATER(double, float);

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
