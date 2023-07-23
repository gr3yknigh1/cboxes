#include "cboxes/algorithm.h"
#include "cboxes/assert.h"

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
cs_quick_sort_a(int *items, uint64_t item_length, size_t item_size,
                cs_is_greater_t is_greater) {
    if (item_length < 2) {
        return;
    }

    int *pivot = items + item_length - 1;
    int *head = items;
    int *tail = items;

    while (tail < pivot) {
        if (*tail < *pivot) {
            cs_swap(head, tail, item_size);
            head++;
        }
        tail++;
    }

    cs_swap(pivot, head, item_size);

    cs_quick_sort_a(items, head - items, item_size, is_greater);
    cs_quick_sort_a(items + (head - items) + 1,
                    item_length - (head - items + 1), item_size, is_greater);
}

// void
// QuickSort_D_i32(int *data, uint64_t length) {
//     if (length < 2) {
//         return;
//     }
//
//     int *pivot = data + length / 2;
//     int *head = data;
//     int *tail = data;
//
//     while (tail < pivot) {
//         ++compCount;
//         if (*tail > *pivot) {
//             Swap_i32(head, tail);
//             head++;
//         }
//         tail++;
//     }
//     Swap_i32(pivot, head);
//
//     QuickSort_D_i32(data, head - data);
//     QuickSort_D_i32(data + (head - data) + 1, length - (head - data + 1));
// }
