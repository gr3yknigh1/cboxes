#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include <stdint.h>
#include <stdio.h>

#include "tools/common.h"

#include "cboxes/hashmap.h"
#include "cboxes/list.h"

struct {
    cs_Hashmap *map;
} data;

void init(void) { data.map = cs_Hashmap_New(CS_TYPE_I32, 20); }

void fini(void) { cs_Hashmap_Free(data.map); }

TestSuite(test_hashmap, .init = init, .fini = fini);

Test(test_hashmap, cs_Hashmap_New) {
    const uint8_t cap = 20;

    cs_Hashmap *map = cs_Hashmap_New(CS_TYPE_I32, cap);

    cr_assert_not_null(map);
    cr_assert(map->type == CS_TYPE_I32);
    cr_assert(map->capacity == cap);
    cr_assert(map->count == 0);

    cr_assert_not_null(map->slots);
    cr_assert(map->slots->type == CS_TYPE_LIST);

    for (uint64_t i = 0; i < cap; i++) {
        cs_List *slot = NULL;
        CS_LIST_GET(map->slots, i, slot);
        cr_assert_not_null(slot);
        cr_assert(cs_List_IsEmpty(slot));
    }

    cs_Hashmap_Free(map);
}

Test(test_hashmap, cs_Hashmap_Hash_Range) {
    const uint64_t hashCheckCount = 100000;
    for (uint64_t i = 0; i < hashCheckCount; i++) {
        const char *str = randStr(5, 20);
        uint64_t hash = cs_Hashmap_Hash(data.map, str);
        cr_expect(hash < data.map->capacity);
        free((void *)str);
    }
}

Test(test_hashmap, cs_Hashmap_Hash_SameValue) {
    const uint64_t hashCheckCount = 100000;
    for (uint64_t i = 0; i < hashCheckCount; i++) {
        const char *str = randStr(5, 20);
        uint64_t hashA = cs_Hashmap_Hash(data.map, str);
        uint64_t hashB = cs_Hashmap_Hash(data.map, str);
        cr_expect(hashA == hashB);
        free((void *)str);
    }
}

void printIntNode(cs_LNode *n) { printf("%d", *(int *)n->value); }

Test(test_hashmap, cs_Hashmap_Set) {
    cs_Hashmap *map = data.map;

    cstr key = randStr(10, 20);
    int value = 22;
    cr_expect(cs_Hashmap_Set(map, key, &value) == cs_OK);

    cs_List *slot = NULL;
    cr_expect(CS_LIST_GET(map->slots, cs_Hashmap_Hash(map, key), slot) ==
              cs_OK);
    cr_expect(*((int *)((cs_Pair *)slot->tail->value)->value) == value);
}

Test(test_hashmap, cs_Hashmap_Get) {
    cs_Hashmap *map = data.map;

    cstr key = "expected_key";
    int value = 22;

    cr_expect(cs_Hashmap_Set(map, key, &value) == cs_OK);

    int *stored = NULL;

    cr_expect(CS_HASHMAP_GET(map, key, stored) == cs_OK);
    cr_expect(*stored == value);

    cr_expect(CS_HASHMAP_GET(map, "unexpected_key", stored) == cs_KEY_ERROR);
}

Test(test_hashmap, cs_Hashmap_Pop) {
    cs_Hashmap *map = data.map;

    cstr key = "key_to_some_value";
    int value = 22;
    cr_expect(cs_Hashmap_Set(map, key, &value) == cs_OK);

    int *popedValue = malloc(sizeof(int));
    cr_expect(cs_Hashmap_Pop(map, key, (void **)(&popedValue)) == cs_OK);

    cr_expect(popedValue != NULL);
    cr_expect(*popedValue == value);

    cs_Status status = CS_HASHMAP_GET(map, key, popedValue);
    cr_expect(status == cs_KEY_ERROR, "Status: %u", status);
}


Test(test_hashmap, cs_Hashmap_Remove) {
    cs_Hashmap *map = data.map;

    cstr key = "key_to_some_value";
    int value = 22;
    cr_expect(cs_Hashmap_Set(map, key, &value) == cs_OK);

    cr_expect(cs_Hashmap_Remove(map, key) == cs_OK);

    int *valuePtr = malloc(sizeof(int));
    cs_Status status = CS_HASHMAP_GET(map, key, valuePtr);
    cr_expect(status == cs_KEY_ERROR, "Status: %u", status);
}
