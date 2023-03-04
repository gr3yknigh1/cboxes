#include "cboxes/pair.h"
#include "cboxes/string.h"
#include "cboxes/type.h"

cs_Pair *cs_Pair_New(cstr key, void *value, const cs_Type *type) {
    cs_Pair *pair = malloc(sizeof(cs_Pair));
    *pair = (cs_Pair){
        .key = cs_String_New(key),
        .value = cs_Type_StoreValue(type, value),
        .type = cs_Type_NewC(type),
    };
    return pair;
}

void *cs_Pair_Copy(void *dest, const void *src, size_t count) {
    for (size_t i = 0; i < count; i++) {
        ((byte *)dest)[i] = ((byte *)src)[i];
    }
    return dest;
}

void cs_Pair_Free(void *ptr) {
    cs_Pair *pair = (cs_Pair *)ptr;

    pair->type->free(pair->value);

    cs_String_Free(pair->key);
    cs_Type_Free((void *)pair->type);
    free(ptr);
}
