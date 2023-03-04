#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include <stdint.h>

#include "cboxes/hashmap.h"
#include "cboxes/list.h"

void init() {}
void fini() {}

TestSuite(test_hashmap, .init = init, .fini = fini);

Test(test_hashmap, cs_Hashmap_New) {
    const uint8_t cap = 20;

    const cs_Hashmap *map = cs_Hashmap_New(CS_INT32_TYPE, cap);

    cr_assert_not_null(map);
    cr_assert(map->type == CS_INT32_TYPE);
    cr_assert(map->capacity == cap);
    cr_assert(map->count == 0);

    cr_assert_not_null(map->buckets);
    cr_assert(map->buckets->type == CS_LIST_TYPE);

    for (uint64_t i = 0; i < cap; i++) {
        cs_List *slot = NULL;
        CS_LIST_GET(map->buckets, i, slot);
        cr_assert_not_null(slot);
        cr_assert(cs_List_IsEmpty(slot));
    }
}
