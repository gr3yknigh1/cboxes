#ifndef PAIR_H_
#define PAIR_H_

#include "cboxes/string.h"
#include "cboxes/type.h"

typedef struct cs_Pair {
    cstr key;
    void *value;
    const cs_Type *type;
} cs_Pair;

cs_Pair *cs_Pair_New(cstr key, void *value, const cs_Type *type);

void *cs_Pair_Copy(void *dest, const void *src, size_t count);
void cs_Pair_Free(void *ptr);

#endif // PAIR_H_
