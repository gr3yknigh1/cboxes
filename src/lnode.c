#include "cboxes/lnode.h"
#include <assert.h>
#include <string.h>

LNode *LNode_Construct(void *value, LNode *next, size_t size,
                       void *(*copyValue)(void *src, const void *dest,
                                          size_t size),
                       void (*freeValue)(void *ptr)) {
    assert(value != NULL);
    assert(size != 0);
LNode *node = malloc(sizeof(LNode));
    node->next = next;
    node->size = size;
    node->copyValue = copyValue;
    node->freeValue = freeValue;
    node->value = malloc(size);
    node->copyValue(node->value, value, size);
    return node;
}

void *LNode_Copy(void *dest, const void *src, size_t size) {
    const LNode *srcNode = src;
    LNode *destNode = dest;
    *destNode = *LNode_Construct(srcNode->value, srcNode->next, srcNode->size,
                                 srcNode->copyValue, srcNode->freeValue);
    if (destNode->next != NULL) {
        LNode_Copy(destNode->next, srcNode->next, size);
    }
    return dest;
}

void LNode_Free(void *ptr, void freeValue(void *ptr)) {
    assert(ptr != NULL);
    LNode *node = (LNode *)ptr;

    freeValue(node->value);
    if (node->next != NULL) {
        LNode_Free(node->next, freeValue);
    }
    free(node);
}

void LNode_FreeD(void *ptr) { LNode_Free((LNode *)ptr, free); }

bool LNode_IsEqual(const LNode *node, const LNode *other) {
    return node->value == other->value && node->size == other->size &&
           node->next == other->next;
}
