#include <stdint.h>

#include "cboxes/assert.h"
#include "cboxes/type.h"

cs_type_t *
cs_type_init(size_t size, bool is_ref, cs_copy_func_t copy,
             cs_free_func_t free) {
    cs_type_t *type = malloc(sizeof(cs_type_t));
    *type = (cs_type_t){
        .size = size,
        .is_ref = is_ref,
        .copy = copy,
        .free = free,
    };
    return type;
}

cs_type_t *
cs_type_init_0(const cs_type_t *other) {
    return cs_type_init(other->size, other->is_ref, other->copy, other->free);
}

void *
cs_type_store_value(const cs_type_t *type, void *value) {
    CS_ASSERT(type != NULL, "");

    if (value == NULL) {
        return NULL;
    }

    if (type->is_ref) {
        return value;
    }

    void *stored = malloc(sizeof(type->size));
    type->copy(stored, value, type->size);
    return stored;
}

void
cs_Type_Free(void *ptr) {
    free(ptr);
}

INIT_PRIMITIVE_CS_TYPE(CS_TYPE_I8, int8_t);
INIT_PRIMITIVE_CS_TYPE(CS_TYPE_I16, int16_t);
INIT_PRIMITIVE_CS_TYPE(CS_TYPE_I32, int32_t);
INIT_PRIMITIVE_CS_TYPE(CS_TYPE_I64, int64_t);

INIT_PRIMITIVE_CS_TYPE(CS_TYPE_U8, uint8_t);
INIT_PRIMITIVE_CS_TYPE(CS_TYPE_U16, uint16_t);
INIT_PRIMITIVE_CS_TYPE(CS_TYPE_U32, uint32_t);
INIT_PRIMITIVE_CS_TYPE(CS_TYPE_U64, uint64_t);

INIT_PRIMITIVE_CS_TYPE(CS_TYPE_F32, float);
INIT_PRIMITIVE_CS_TYPE(CS_TYPE_F64, double);
