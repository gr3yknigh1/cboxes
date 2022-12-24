#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "darray.h"

DArray* DArray_Construct() {
    DArray* darray = malloc(sizeof(DArray));
    darray->items = NULL;
    darray->itemSize = 0;
    darray->length = 0;
    return darray;
}

DArray* DArray_ConstructC(const void* items, size_t itemSize, u64 length) {
    assert(items != NULL);
    assert(itemSize > 0);
    assert(length > 0);

    DArray* darray = malloc(sizeof(DArray));

    darray->items = malloc(itemSize * length);
    memcpy(darray->items, items, itemSize * length);

    darray->itemSize = itemSize;
    darray->length = length;
    return darray;
}

DArray* DArray_ConstructA(void* items, size_t itemSize, u64 length) {
    assert(items != NULL);
    assert(itemSize > 0);
    assert(length > 0);

    DArray* darray = malloc(sizeof(DArray));
    darray->items = items;

    darray->itemSize = itemSize;
    darray->length = length;
    return darray;
}
