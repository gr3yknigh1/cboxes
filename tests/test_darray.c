#include "ccheck.h"

#include <cboxes/dynamic_array.h>

TEST_PACK(darray);

TEST(get_data_size) {
    const uint64_t array_length = 4;
    const uint64_t array_capacity = 10;
    const cs_dynamic_array_t array = {
        .data = NULL,
        .item_count = array_length,
        .item_capacity = array_capacity,
        .type = CS_TYPE_I32,
    };

    ASSERT(cs_dynamic_array_get_buffer_size(&array) ==
           array_capacity * array.type->size);
}

TEST(is_in_range) {
    const uint64_t array_length = 4;
    const uint64_t array_capacity = 10;
    const cs_dynamic_array_t array = {
        .data = NULL,
        .item_count = array_length,
        .item_capacity = array_capacity,
        .type = CS_TYPE_I32,
    };

    ASSERT(cs_dynamic_array_is_in_range(&array, 0));
    ASSERT(cs_dynamic_array_is_in_range(&array, array_length));
    ASSERT(!cs_dynamic_array_is_in_range(&array, array_length + 2));
    ASSERT(!cs_dynamic_array_is_in_range(&array, array_capacity));
    ASSERT(!cs_dynamic_array_is_in_range(&array, array_capacity + 2));
}

TEST(get_space_left) {
    uint64_t buf_int_cap = 10;
    size_t buf_cap = sizeof(int) * buf_int_cap;
    void *buf = malloc(buf_cap);

    cs_dynamic_array_t array = (cs_dynamic_array_t){
        .data = buf,
        .item_count = 0,
        .item_capacity = buf_int_cap,
        .type = CS_TYPE_I32,
    };

    ASSERT(cs_dynamic_array_get_space_left(&array) == array.item_capacity);

    // NOTE Adding half
    array.item_count = buf_int_cap / 2;

    ASSERT(cs_dynamic_array_get_space_left(&array) ==
           array.item_capacity * array.type->size / 2);

    free(buf);
}
