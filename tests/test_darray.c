#include "ccheck.h"

#include <cboxes/dynamic_array.h>

TEST_PACK(darray);

TEST(data_size) {
    const uint64_t arr_len = 4;
    const uint64_t arr_cap = 10;
    cs_darray_t arr = {
        .data = NULL,
        .len = arr_len,
        .cap = arr_cap,
        .type = CS_TYPE_I32,
    };

    size_t calc_size = cs_darray_get_buffer_size(&arr);
    size_t expected_size = arr_cap * arr.type->size;

    ASSERT(calc_size == expected_size);
}

TEST(in_range) {
    const uint64_t arr_len = 4;
    const uint64_t arr_cap = 10;
    cs_darray_t arr = {
        .data = NULL,
        .len = arr_len,
        .cap = arr_cap,
        .type = CS_TYPE_I32,
    };

    ASSERT(cs_darray_is_in_range(&arr, 0));
    ASSERT(cs_darray_is_in_range(&arr, arr_len));
    ASSERT(!cs_darray_is_in_range(&arr, arr_len + 2));
    ASSERT(!cs_darray_is_in_range(&arr, arr_cap));
    ASSERT(!cs_darray_is_in_range(&arr, arr_cap + 2));
}
