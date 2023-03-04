#ifndef TYPE_H_
#define TYPE_H_

#include <stdbool.h>
#include <stdlib.h>

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

#endif // TYPE_H_
