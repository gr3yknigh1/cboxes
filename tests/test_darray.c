#include "ccheck.h"

#include <cboxes/darray.h>

CC_TEST_SUITE(darray);

CC_TEST_CASE(data_size) {
    cs_darray_t arr = {
        .data = NULL,
        .len = 0,
        .cap = 10,
        .type = CS_TYPE_I32,
    };

    size_t testing_size = CS_DARRAY_DATA_SIZE(&arr);
    size_t expected_size = 10 * arr.type->size;

    ASSERT(testing_size == expected_size);
}
