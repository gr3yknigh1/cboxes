#ifndef CBOXES_HASHMAP_H_
#define CBOXES_HASHMAP_H_

#include "cboxes/linked_list.h"
#include "cboxes/pair.h"
#include "cboxes/status.h"
#include "cboxes/string.h"
#include "cboxes/type.h"

#define CS_HASHMAP_GET(__MAP, __KEY, __OUT_PTR)                                \
    cs_hashmap_get((__MAP), (__KEY), (void **)(&(__OUT_PTR)))

typedef struct cs_hashmap {
    cs_list_t *bucket_list;
    const cs_type_t *type;
    uint64_t pair_count;
    uint64_t capacity;
} cs_hashmap_t;

cs_hashmap_t *cs_hashmap_init(const cs_type_t *type, uint64_t capacity);

uint64_t cs_hashmap_hash(uint64_t capacity, const char *key);

cs_status_t cs_hashmap_set(cs_hashmap_t *map, const char *key, void *data);
cs_status_t cs_hashmap_get(const cs_hashmap_t *map, const char *key,
                           void **out_ptr);
cs_status_t cs_hashmap_pop(cs_hashmap_t *map, const char *key, void **out_ptr);
cs_status_t cs_hashmap_remove(cs_hashmap_t *map, const char *key);

void cs_hashmap_free(void *ptr);

#endif // CBOXES_HASHMAP_H_
