#include <assert.h>

#include "cboxes/assert.h"
#include "cboxes/hash.h"
#include "cboxes/hashmap.h"
#include "cboxes/list.h"
#include "cboxes/pair.h"
#include "cboxes/shallow.h"
#include "cboxes/status.h"
#include "cboxes/type.h"

static void cs_Hashmap_PushBackPair(cs_List *bucket, cstr key, void *data,
                                    const cs_Type *type) {
    cs_List_PushBack(bucket, cs_Pair_New(key, data, type));
}

static void cs_Hashmap_ReplacePairValue(cs_Pair *pair, void *data) {
    pair->type->free(pair->value);
    pair->value = cs_Type_StoreValue(pair->type, data);
}

static cs_Pair *cs_Hashmap_FindPair(const cs_List *bucket, cstr key,
                                    u64 *pairIndexOut) {
    cs_Pair *pair = NULL;
    CS_LIST_FOREACHN(bucket, index, node, {
        pair = (cs_Pair *)(node->value);
        if (pair->key == key) {
            if (pairIndexOut != NULL) {
                *pairIndexOut = index;
            }
            break;
        }
    });
    return pair;
}

static cs_List *cs_Hashmap_GetBucket(cs_List *bucketList, u64 capacity,
                                     cstr key) {
    u64 index = cs_Hashmap_Hash(capacity, key);
    cs_List *bucket = NULL;
    cs_Status status = CS_LIST_GET(bucketList, index, bucket);
    CS_ASSERT(
        status == cs_OK,
        "HASHMAP: missmatch with hash's index and bucket array length. Index = "
        "'%lu', array length = '%lu'. cs_List_Get status code = %d\n",
        index, bucketList->length, status);
    CS_ASSERT(bucket != NULL, "HASHMAP: founded bucket is NULL\n");

    return bucket;
}

cs_Hashmap *cs_Hashmap_New(const cs_Type *type, u64 capacity) {
    cs_Hashmap *map = malloc(sizeof(cs_Hashmap));

    *map = (cs_Hashmap){
        .bucketList = cs_List_New(CS_TYPE_LIST),
        .type = type,
        .capacity = capacity,
        .pairCount = 0,
    };

    for (u64 i = 0; i < capacity; i++) {
        cs_List_PushBack(map->bucketList, cs_List_New(CS_TYPE_PAIR));
    }
    return map;
}

u64 cs_Hashmap_Hash(u64 capacity, cstr key) {
    return cs_LoseLoseHash((const unsigned char *)key) % capacity;
}

cs_Status cs_Hashmap_Set(cs_Hashmap *map, cstr key, void *data) {
    cs_List *bucket = cs_Hashmap_GetBucket(map->bucketList, map->capacity, key);

    if (cs_List_IsEmpty(bucket)) {
        cs_Hashmap_PushBackPair(bucket, key, data, map->type);
        return cs_OK;
    }

    cs_Pair *targetPair = cs_Hashmap_FindPair(bucket, key, NULL);

    if (targetPair == NULL) {
        cs_Hashmap_PushBackPair(bucket, key, data, map->type);
        return cs_OK;
    }

    cs_Hashmap_ReplacePairValue(targetPair, data);

    return cs_OK;
}

cs_Status cs_Hashmap_Get(const cs_Hashmap *map, cstr key, void **outWritePtr) {
    cs_List *bucket = cs_Hashmap_GetBucket(map->bucketList, map->capacity, key);

    cs_Pair *pair = cs_Hashmap_FindPair(bucket, key, NULL);
    if (pair == NULL) {
        return cs_KEY_ERROR;
    }

    *outWritePtr = pair->value;

    return cs_OK;
}

cs_Status cs_Hashmap_Pop(cs_Hashmap *map, cstr key, void **outWritePtr) {
    cs_List *bucket = cs_Hashmap_GetBucket(map->bucketList, map->capacity, key);

    u64 index;
    cs_Pair *pair = cs_Hashmap_FindPair(bucket, key, &index);

    if (pair == NULL) {
        return cs_KEY_ERROR;
    }

    // TODO: Add difference when using references
    pair->type->copy(*outWritePtr, pair->value, pair->type->size);

    CS_ASSERT(cs_List_Remove(bucket, index) == cs_OK,
              "HASHMAP: can't remove pair from bucket list on index = '%lu'",
              index);

    return cs_OK;
}

cs_Status cs_Hashmap_Remove(cs_Hashmap *map, cstr key) {
    cs_List *bucket = cs_Hashmap_GetBucket(map->bucketList, map->capacity, key);

    u64 index = 0;
    cs_Pair *pair = cs_Hashmap_FindPair(bucket, key, &index);

    if (pair == NULL) {
        return cs_KEY_ERROR;
    }

    CS_ASSERT(cs_List_Remove(bucket, index) == cs_OK,
              "HASHMAP: can't remove pair from bucket list on index = '%lu'",
              index);

    return cs_OK;
}

void cs_Hashmap_Free(void *ptr) {
    cs_Hashmap *map = (cs_Hashmap *)ptr;

    for (u64 i = 0; i < map->capacity; i++) {
        cs_List *bucket = NULL;
        CS_LIST_GET(map->bucketList, i, bucket);
        cs_List_Free(bucket);
    }
    cs_List_Free(map->bucketList);

    free(ptr);
}
