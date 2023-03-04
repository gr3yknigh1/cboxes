#include "cboxes/type.h"
#include <assert.h>

cs_Type *cs_Type_New(size_t size, bool isReference, cs_CopyFunc copy,
                     cs_FreeFunc free) {
    cs_Type *type = malloc(sizeof(cs_Type));
    *type = (cs_Type){
        .size = size,
        .isReference = isReference,
        .copy = copy,
        .free = free,
    };
    return type;
}

cs_Type *cs_Type_NewC(const cs_Type *other) {
    return cs_Type_New(other->size, other->isReference, other->copy,
                       other->free);
}

void *cs_Type_StoreValue(const cs_Type *type, void *value) {
    assert(type != NULL);

    if (value == NULL) {
        return NULL;
    }

    if (type->isReference) {
        return value;
    } else {
        void *stored = malloc(sizeof(type->size));
        type->copy(stored, value, type->size);
        return stored;
    }
}

INIT_PRIMITIVE_CS_TYPE(CS_INT16_TYPE, short);
INIT_PRIMITIVE_CS_TYPE(CS_INT32_TYPE, int);
INIT_PRIMITIVE_CS_TYPE(CS_INT64_TYPE, long);
INIT_PRIMITIVE_CS_TYPE(CS_UINT16_TYPE, unsigned short);
INIT_PRIMITIVE_CS_TYPE(CS_UINT32_TYPE, unsigned int);
INIT_PRIMITIVE_CS_TYPE(CS_UINT64_TYPE, unsigned long);
INIT_PRIMITIVE_CS_TYPE(CS_FLOAT32_TYPE, float);
INIT_PRIMITIVE_CS_TYPE(CS_FLOAT64_TYPE, double);

void cs_Type_Free(void *ptr) { free(ptr); }
