#ifndef NODES_H
#define NODES_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct LNode {
    void* value;
    size_t size;
    void* (*copyValue)(void* dest, const void* src, size_t size);
    void  (*freeValue)(void* ptr);

    struct LNode *next;
} LNode;

LNode* LNode_Construct(
    void* value,
    LNode* next,
    size_t size,
    void* (*copyValue)(void* src, const void* dest, size_t size),
    void  (*freeValue)(void* ptr)
    );
void* LNode_Copy(void *dest, const void *src, size_t size);
void LNode_Free (void *ptr, void freeValue(void *ptr));
void LNode_FreeD(void *ptr);
bool LNode_IsEqual(const LNode* node, const LNode* other);


#endif // NODES_H
