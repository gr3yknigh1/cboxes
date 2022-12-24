#ifndef ARRAY_H
#define ARRAY_H

#include <stdbool.h>
#include <stdlib.h>

#include "types.h"

/*
 * Dynamic array
 * Coping values by default
 * */
typedef struct DArray {
    void* items;
    size_t itemSize;
    u64 length;
} DArray;

enum {
    DArray_OK,
    DArray_INDEX_ERR,
};

DArray* DArray_Construct();
DArray* DArray_ConstructC(const void* items, size_t itemSize, u64 length);
DArray* DArray_ConstructA(void* items, size_t itemSize, u64 length);

int DArray_Get(const DArray* array, u64 index, void** out);
int DArray_Set(DArray* array, u64 index, void* value);

void DArray_Reserve(DArray* array, u64 amount);
void DArray_FreeEmpty(DArray* array);

void DArray_EmplaceBack(DArray* array);
void DArray_PushBack(DArray* array, void* item);

void DArray_Clear(DArray* array);
void DArray_Free(DArray* array);

bool DArray_IsInRange(const DArray* array, u64 index);

#endif // ARRAY_H
