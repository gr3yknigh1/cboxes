#include "cboxes/status.h"
#include <stdio.h>

#include <cboxes/algorithm.h>
#include <cboxes/assert.h>
#include <cboxes/dynamic_array.h>
#include <cboxes/type.h>

int
main(void) {

    int32_t array[] = {0, 2, 4, 19, 2, 32};

    for (uint64_t i = 0; i < CS_STATIC_ARRAY_LENGTH(array); ++i) {
        printf("%i ", array[i]);
    }

    printf("\n");

    cs_quick_sort_a(array, CS_STATIC_ARRAY_LENGTH(array),
                    CS_STATIC_ARRAY_ITEM_SIZE(array), is_greater_int32);

    for (uint64_t i = 0; i < CS_STATIC_ARRAY_LENGTH(array); ++i) {
        printf("%i ", array[i]);
    }
    printf("\n");

    return 0;
}
