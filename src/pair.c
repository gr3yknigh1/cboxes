#include "cboxes/pair.h"
#include "cboxes/string.h"
#include "cboxes/type.h"
#include <string.h>

INIT_COMPLEX_CS_TYPE(CS_TYPE_PAIR, cs_Pair *, cs_Pair_Copy, cs_Pair_Free);

cs_Pair *cs_Pair_New(cstr key, void *value, const cs_Type *type) {
    cs_Pair *pair = malloc(sizeof(cs_Pair));
    *pair = (cs_Pair){
        .key = key,
        .value = cs_Type_StoreValue(type, value),
        .type = type,
    };
    return pair;
}

void *cs_Pair_Copy(void *dest, const void *src, size_t count) {
    const cs_Pair *sourcePair = (const cs_Pair *)src;
    cs_Pair *copiedPair =
        cs_Pair_New(sourcePair->key, sourcePair->value, sourcePair->type);
    *((cs_Pair *)dest) = *copiedPair;
    return copiedPair;
}

void cs_Pair_Free(void *ptr) {
    cs_Pair *pair = (cs_Pair *)ptr;

    pair->type->free(pair->value);

    free((void *)pair->key);
    cs_Type_Free((void *)pair->type);
    free(ptr);
}
