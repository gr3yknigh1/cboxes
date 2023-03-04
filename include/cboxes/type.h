#ifndef TYPE_H_
#define TYPE_H_

#include <stdbool.h>
#include <stdlib.h>

#include "cboxes/shallow.h"

typedef void *(*cs_CopyFunc)(void *dest, const void *src, size_t count);
typedef void (*cs_FreeFunc)(void *ptr);

typedef struct cs_Type {
    size_t size;
    bool isReference;
    cs_CopyFunc copy;
    cs_FreeFunc free;
} cs_Type;

cs_Type *cs_Type_New(size_t size, bool isReference, cs_CopyFunc copy,
                     cs_FreeFunc free);
cs_Type *cs_Type_NewC(const cs_Type *other);
void *cs_Type_StoreValue(const cs_Type *type, void *value);

void cs_Type_Free(void *ptr);

#define DEFINE_CS_TYPE(name) extern const cs_Type *name

#define INIT_PRIMITIVE_CS_TYPE(name, type)                                     \
    const cs_Type *name = &(cs_Type) {                                         \
        .size = sizeof(type), .isReference = false, .copy = cs_ShallowCopy,    \
        .free = cs_ShallowFree,                                                \
    }

#define INIT_COMPLEX_CS_TYPE(name, type, _copy, _free)                         \
    const cs_Type *name = &(cs_Type) {                                         \
        .size = sizeof(type), .isReference = true, .copy = _copy,              \
        .free = _free,                                                         \
    }

DEFINE_CS_TYPE(CS_INT16_TYPE);
DEFINE_CS_TYPE(CS_INT32_TYPE);
DEFINE_CS_TYPE(CS_INT64_TYPE);
DEFINE_CS_TYPE(CS_UINT16_TYPE);
DEFINE_CS_TYPE(CS_UINT32_TYPE);
DEFINE_CS_TYPE(CS_UINT64_TYPE);
DEFINE_CS_TYPE(CS_FLOAT32_TYPE);
DEFINE_CS_TYPE(CS_FLOAT64_TYPE);

#endif // TYPE_H_
