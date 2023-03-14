#ifndef HASHMAP_H_
#define HASHMAP_H_

#include "cboxes/list.h"
#include "cboxes/numtypes.h"
#include "cboxes/pair.h"
#include "cboxes/status.h"
#include "cboxes/string.h"
#include "cboxes/type.h"

#define CS_HASHMAP_GET(__map, __key, __outWritePtr)                            \
    cs_Hashmap_Get(__map, __key, (void **)(&__outWritePtr))

typedef struct cs_Hashmap {
    cs_List *bucketList;
    const cs_Type *type;
    u64 pairCount;
    u64 capacity;
} cs_Hashmap;

cs_Hashmap *cs_Hashmap_New(const cs_Type *type, u64 capacity);

u64 cs_Hashmap_Hash(u64 capacity, cstr key);

cs_Status cs_Hashmap_Set(cs_Hashmap *map, cstr key, void *data);
cs_Status cs_Hashmap_Get(const cs_Hashmap *map, cstr key, void **outWritePtr);
cs_Status cs_Hashmap_Pop(cs_Hashmap *map, cstr key, void **outWritePtr);
cs_Status cs_Hashmap_Remove(cs_Hashmap *map, cstr key);

void cs_Hashmap_Free(void *ptr);

#endif // HASHMAP_H_
