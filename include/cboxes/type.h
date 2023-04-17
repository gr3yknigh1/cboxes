#ifndef CBOXES_TYPE_H_
#define CBOXES_TYPE_H_

#include <stdbool.h>
#include <stdlib.h>

#include "cboxes/numtypes.h"
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

#define DEFINE_CS_TYPE(__name) extern const cs_Type *__name

#define INIT_PRIMITIVE_CS_TYPE(__name, __type)                                 \
    const cs_Type *__name = &(cs_Type) {                                       \
        .size = sizeof(__type), .isReference = false, .copy = cs_ShallowCopy,  \
        .free = cs_ShallowFree,                                                \
    }

#define INIT_COMPLEX_CS_TYPE(__name, __type, __copy, __free)                   \
    const cs_Type *__name = &(cs_Type) {                                       \
        .size = sizeof(__type), .isReference = true, .copy = (__copy),         \
        .free = (__free),                                                      \
    }

DEFINE_CS_TYPE(CS_TYPE_I8);
DEFINE_CS_TYPE(CS_TYPE_I16);
DEFINE_CS_TYPE(CS_TYPE_I32);
DEFINE_CS_TYPE(CS_TYPE_I64);

DEFINE_CS_TYPE(CS_TYPE_U8);
DEFINE_CS_TYPE(CS_TYPE_U16);
DEFINE_CS_TYPE(CS_TYPE_U32);
DEFINE_CS_TYPE(CS_TYPE_U64);

DEFINE_CS_TYPE(CS_TYPE_F32);
DEFINE_CS_TYPE(CS_TYPE_F64);

#endif // CBOXES_TYPE_H_
