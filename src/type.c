#include "cboxes/type.h"

cs_Type *cs_Type_New(size_t size, bool isReference, cs_CopyFunc copy, cs_FreeFunc free) {
    cs_Type *type = malloc(sizeof(cs_Type));
    *type = (cs_Type) {
        .size = size,
        .isReference = isReference,
        .copy = copy,
        .free = free,
    };
    return type;
}

