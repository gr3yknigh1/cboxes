#ifndef DARRAY_H_
#define DARRAY_H_

#include <stdlib.h>

#include "cboxes/type.h"
#include "cboxes/types.h"

typedef struct cs_DArray {
    void *begin;

    u64 space;
    u64 count;

    cs_Type type;
} cs_DArray;

cs_DArray *cs_DArray_New(cs_Type type);
cs_DArray *cs_DArray_NewD(size_t size);

void *cs_DArray_Reallocate(cs_DArray *arr, u64 count);

#endif // DARRAY_H_
