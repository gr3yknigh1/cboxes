#ifndef HASHMAP_H_
#define HASHMAP_H_

#include "cboxes/list.h"
#include "cboxes/numtypes.h"
#include "cboxes/status.h"
#include "cboxes/string.h"
#include "cboxes/type.h"

typedef struct cs_Hashmap {
    cs_List *buckets;
    const cs_Type *type;
    u64 count;
    u64 capacity;
} cs_Hashmap;

cs_Hashmap *cs_Hashmap_New(const cs_Type *type, u64 capacity);
cs_Hashmap *cs_Hashmap_NewD(size_t size, u64 capacity);

u64 cs_Hashmap_Hash(cs_Hashmap *hashmap, cstr key);

cs_Status cs_Hashmap_Set(cs_Hashmap *hashmap, cstr key, void *value);
cs_Status cs_Hashmap_Get(cs_Hashmap *hashmap, cstr key, void **out);
cs_Status cs_Hashmap_Pop(cs_Hashmap *hashmap, cstr key, void **out);
cs_Status cs_Hashmap_Remove(cs_Hashmap *hashmap, cstr key);

void cs_Hashmap_Free(void *ptr);

#endif // HASHMAP_H_
