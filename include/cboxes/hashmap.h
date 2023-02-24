#ifndef HASHMAP_H_
#define HASHMAP_H_

#include "cboxes/list.h"
#include "cboxes/type.h"
#include "cboxes/numtypes.h"

typedef struct cs_Hashmap {
    cs_List *buckets;
    cs_Type *type;

    u64 count;
    u64 capacity;
} cs_Hashmap;



#endif // HASHMAP_H_
