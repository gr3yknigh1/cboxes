#include <assert.h>

#include "cboxes/hash.h"
#include "cboxes/hashmap.h"
#include "cboxes/list.h"
#include "cboxes/pair.h"
#include "cboxes/shallow.h"
#include "cboxes/type.h"

cs_Hashmap *cs_Hashmap_New(cs_Type *type, u64 capacity) {
    cs_Hashmap *hashmap = malloc(sizeof(cs_Hashmap));

    *hashmap = (cs_Hashmap){
        .buckets = cs_List_New(
            cs_Type_New(sizeof(cs_List), true, cs_List_Copy, cs_List_Free)),
        .bucket_type =
            cs_Type_New(sizeof(cs_Type), true, cs_Pair_Copy, cs_Pair_Free),
        .type = type,
        .capacity = capacity,
        .count = 0,
    };

    return hashmap;
}

cs_Hashmap *cs_Hashmap_NewD(size_t size, u64 capacity) {
    return cs_Hashmap_New(
        cs_Type_New(size, false, cs_ShallowCopy, cs_ShallowFree), capacity);
}

u64 cs_Hashmap_Hash(cs_Hashmap *hashmap, cstr key) {
    return cs_lose_lose_hash((const unsigned char *)key) % hashmap->capacity;
}

cs_Status cs_Hashmap_Set(cs_Hashmap *hashmap, cstr key, void *value) {
    u64 hash = cs_Hashmap_Hash(hashmap, key);

    cs_List *bucket = NULL;
    cs_Status g_status = CS_LIST_GET(hashmap->buckets, hash, &bucket);
    assert(g_status == cs_OK);

    if (cs_List_IsEmpty(bucket)) {
        cs_List_PushBack(bucket, cs_Pair_New(key, value, hashmap->type));
    } else {
        CS_LIST_FOREACH(bucket, cs_Pair, i, v, {
            (void)i;
            if (v->key->data == key) {
                hashmap->type->free(v->value);
                v->value = cs_Type_StoreValue(hashmap->type, value);
                break;
            }
        });
    }

    return cs_OK;
}
