#ifndef CBOXES_TYPE_H_
#define CBOXES_TYPE_H_

#include <stdbool.h>
#include <stdlib.h>

#include "cboxes/shallow.h"

typedef void *(*cs_copy_func_t)(void *dest, const void *src, size_t count);
typedef void (*cs_free_func_t)(void *ptr);

typedef struct cs_type {
    size_t size;
    bool is_ref;
    cs_copy_func_t copy;
    cs_free_func_t free;
} cs_type_t;

cs_type_t *cs_type_init(size_t size, bool is_ref, cs_copy_func_t copy,
                        cs_free_func_t free);
cs_type_t *cs_type_init_0(const cs_type_t *other);

void *cs_type_store_value(const cs_type_t *type, void *value);

void cs_type_free(void *ptr);

#define DEFINE_CS_TYPE(__name) extern const cs_type_t *__name

#define INIT_PRIMITIVE_CS_TYPE(__name, __type)                                 \
    const cs_type_t *__name = &(cs_type_t) {                                   \
        .size = sizeof(__type), .is_ref = false, .copy = cs_shallow_copy,      \
        .free = cs_shallow_free,                                               \
    }

#define INIT_COMPLEX_CS_TYPE(__name, __type, __copy, __free)                   \
    const cs_type_t *__name = &(cs_type_t) {                                   \
        .size = sizeof(__type), .is_ref = true, .copy = (__copy),              \
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
