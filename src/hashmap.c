#include <assert.h>

#include "cboxes/assert.h"
#include "cboxes/hash.h"
#include "cboxes/hashmap.h"
#include "cboxes/linked_list.h"
#include "cboxes/pair.h"
#include "cboxes/shallow.h"
#include "cboxes/status.h"
#include "cboxes/type.h"

static void
_cs_hashmap_push_back_pair(cs_list_t *bucket, const char *key, void *data,
                           const cs_type_t *type) {
    cs_list_push_back(bucket, cs_pair_init(key, data, type));
}

static void
_cs_hashmap_replace_pair_value(cs_pair_t *pair, void *data) {
    pair->type->free(pair->value);
    pair->value = cs_type_store_value(pair->type, data);
}

static cs_pair_t *
_cs_hashmap_find_pair(const cs_list_t *bucket, const char *key,
                      uint64_t *out_pair) {
    cs_pair_t *pair = NULL;
    CS_LIST_FOREACHN(bucket, index, node, {
        pair = (cs_pair_t *)(node->value);
        if (pair->key == key) {
            if (out_pair != NULL) {
                *out_pair = index;
            }
            break;
        }
    });
    return pair;
}

static cs_list_t *
_cs_hashmap_get_bucket(const cs_list_t *bucket_list, uint64_t capacity,
                       const char *key) {
    uint64_t index = cs_hashmap_hash(capacity, key);
    cs_list_t *bucket = NULL;
    cs_status_t status = CS_LIST_GET(bucket_list, index, bucket);
    CS_ASSERT(
        status == cs_OK,
        "HASHMAP: missmatch with hash's index and bucket array length. Index = "
        "'%lu', array length = '%lu'. cs_List_Get status code = %d\n",
        index, bucket_list->length, status);
    CS_ASSERT(bucket != NULL, "HASHMAP: founded bucket is NULL\n");

    return bucket;
}

cs_hashmap_t *
cs_hashmap_init(const cs_type_t *type, uint64_t capacity) {
    cs_hashmap_t *map = malloc(sizeof(cs_hashmap_t));

    *map = (cs_hashmap_t){
        .bucket_list = cs_list_init(CS_TYPE_LIST),
        .type = type,
        .capacity = capacity,
        .pair_count = 0,
    };

    // TODO: Add func for capacity change
    for (uint64_t i = 0; i < capacity; i++) {
        cs_list_push_back(map->bucket_list, cs_list_init(CS_TYPE_PAIR));
    }
    return map;
}

uint64_t
cs_hashmap_hash(uint64_t capacity, const char *key) {
    return cs_hash_lose_lose((const unsigned char *)key) % capacity;
}

cs_status_t
cs_hashmap_set(cs_hashmap_t *map, const char *key, void *data) {
    cs_list_t *bucket =
        _cs_hashmap_get_bucket(map->bucket_list, map->capacity, key);

    if (CS_LIST_ISEMPTY(bucket)) {
        _cs_hashmap_push_back_pair(bucket, key, data, map->type);
        return cs_OK;
    }

    cs_pair_t *target_pair = _cs_hashmap_find_pair(bucket, key, NULL);

    if (target_pair == NULL) {
        _cs_hashmap_push_back_pair(bucket, key, data, map->type);
        return cs_OK;
    }

    _cs_hashmap_replace_pair_value(target_pair, data);

    return cs_OK;
}

cs_status_t
cs_hashmap_get(const cs_hashmap_t *map, const char *key, void **out_ptr) {
    cs_list_t *bucket =
        _cs_hashmap_get_bucket(map->bucket_list, map->capacity, key);

    cs_pair_t *pair = _cs_hashmap_find_pair(bucket, key, NULL);
    if (pair == NULL) {
        return cs_KEY_ERROR;
    }

    *out_ptr = pair->value;

    return cs_OK;
}

cs_status_t
cs_hashmap_pop(cs_hashmap_t *map, const char *key, void **out_ptr) {
    cs_list_t *bucket =
        _cs_hashmap_get_bucket(map->bucket_list, map->capacity, key);

    uint64_t index = 0;
    cs_pair_t *pair = _cs_hashmap_find_pair(bucket, key, &index);

    if (pair == NULL) {
        return cs_KEY_ERROR;
    }

    // TODO: Add difference when using references
    pair->type->copy(*out_ptr, pair->value, pair->type->size);

    CS_ASSERT(cs_list_remove(bucket, index) == cs_OK,
              "HASHMAP: can't remove pair from bucket list on index = '%lu'",
              index);

    return cs_OK;
}

cs_status_t
cs_hashmap_remove(cs_hashmap_t *map, const char *key) {
    cs_list_t *bucket =
        _cs_hashmap_get_bucket(map->bucket_list, map->capacity, key);

    uint64_t index = 0;
    cs_pair_t *pair = _cs_hashmap_find_pair(bucket, key, &index);

    if (pair == NULL) {
        return cs_KEY_ERROR;
    }

    CS_ASSERT(cs_list_remove(bucket, index) == cs_OK,
              "HASHMAP: can't remove pair from bucket list on index = '%lu'",
              index);

    return cs_OK;
}

void
cs_hashmap_free(void *ptr) {
    cs_hashmap_t *map = (cs_hashmap_t *)ptr;

    for (uint64_t i = 0; i < map->capacity; i++) {
        cs_list_t *bucket = NULL;
        CS_LIST_GET(map->bucket_list, i, bucket);
        cs_list_free(bucket);
    }
    cs_list_free(map->bucket_list);

    free(ptr);
}
