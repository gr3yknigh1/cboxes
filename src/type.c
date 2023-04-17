#include "cboxes/type.h"
#include "cboxes/assert.h"
#include "cboxes/numtypes.h"

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
    CS_ASSERT(type != NULL, "");

    if (value == NULL) {
        return NULL;
    }

    if (type->isReference) {
        return value;
    }

    void *stored = malloc(sizeof(type->size));
    type->copy(stored, value, type->size);
    return stored;
}

void cs_Type_Free(void *ptr) { free(ptr); }

INIT_PRIMITIVE_CS_TYPE(CS_TYPE_I8, i8);
INIT_PRIMITIVE_CS_TYPE(CS_TYPE_I16, i16);
INIT_PRIMITIVE_CS_TYPE(CS_TYPE_I32, i32);
INIT_PRIMITIVE_CS_TYPE(CS_TYPE_I64, i64);

INIT_PRIMITIVE_CS_TYPE(CS_TYPE_U8, u8);
INIT_PRIMITIVE_CS_TYPE(CS_TYPE_U16, u16);
INIT_PRIMITIVE_CS_TYPE(CS_TYPE_U32, u32);
INIT_PRIMITIVE_CS_TYPE(CS_TYPE_U64, u64);

INIT_PRIMITIVE_CS_TYPE(CS_TYPE_F32, f32);
INIT_PRIMITIVE_CS_TYPE(CS_TYPE_F64, f64);
