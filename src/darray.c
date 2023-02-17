#include "cboxes/darray.h"
#include "cboxes/shallow.h"
#include <stdlib.h>

cs_DArray *cs_DArray_New(cs_Type type) {
    cs_DArray *arr = malloc(sizeof(cs_DArray));
    *arr = (cs_DArray){
        .begin = NULL,
        .space = 0,
        .count = 0,
        .type = type,
    };
    return arr;
}

cs_DArray *cs_DArray_NewD(size_t size) {
    return cs_DArray_New((cs_Type){
        .size = size,
        .isReference = false,
        .copy = cs_ShallowCopy,
        .free = cs_ShallowFree,
    });
}

void *cs_DArray_Reallocate(cs_DArray *arr, u64 count) {
    void *newBegin = malloc((arr->count + count) * arr->type.size);

    return newBegin;
}
