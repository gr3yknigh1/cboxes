#include "ccheck.h"

#include <cboxes/dynamic_array.h>

TEST_PACK(darray);

TEST(data_size) {
    const uint64_t array_length = 4;
    const uint64_t array_capacity = 10;
    const cs_dynamic_array_t array = {
        .buffer = NULL,
        .length = array_length,
        .capacity = array_capacity,
        .type = CS_TYPE_I32,
    };

    ASSERT(cs_dynamic_array_get_buffer_size(&array) ==
           array_capacity * array.type->size);
}

TEST(in_range) {
    const uint64_t array_length = 4;
    const uint64_t array_capacity = 10;
    const cs_dynamic_array_t arr = {
        .buffer = NULL,
        .length = array_length,
        .capacity = array_capacity,
        .type = CS_TYPE_I32,
    };

    ASSERT(cs_dynamic_array_is_in_range(&arr, 0));
    ASSERT(cs_dynamic_array_is_in_range(&arr, array_length));
    ASSERT(!cs_dynamic_array_is_in_range(&arr, array_length + 2));
    ASSERT(!cs_dynamic_array_is_in_range(&arr, array_capacity));
    ASSERT(!cs_dynamic_array_is_in_range(&arr, array_capacity + 2));
}
