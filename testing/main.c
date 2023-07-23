#include "cboxes/status.h"
#include <stdio.h>

#include <cboxes/algorithm.h>
#include <cboxes/assert.h>
#include <cboxes/dynamic_array.h>
#include <cboxes/type.h>

bool
int32_is_greater(void *a, void *b) {
    return (*(int32_t *)a) > (*(int32_t *)b);
}

int
main(void) {

    int array[] = {0, 2, 4, 19, 2, 32};

    for (uint64_t i = 0; i < CS_STATIC_ARRAY_LENGTH(array); ++i) {
        printf("%i ", array[i]);
    }
    printf("\n");

    cs_bubble_sort_a((void *)array, CS_STATIC_ARRAY_LENGTH(array),
                     CS_STATIC_ARRAY_ITEM_SIZE(array), int32_is_greater);

    for (uint64_t i = 0; i < CS_STATIC_ARRAY_LENGTH(array); ++i) {
        printf("%i ", array[i]);
    }
    printf("\n");


    cs_bubble_sort_b((void *)array, CS_STATIC_ARRAY_LENGTH(array),
                     CS_STATIC_ARRAY_ITEM_SIZE(array), int32_is_greater);

    for (uint64_t i = 0; i < CS_STATIC_ARRAY_LENGTH(array); ++i) {
        printf("%i ", array[i]);
    }
    printf("\n");

    return 0;
}
