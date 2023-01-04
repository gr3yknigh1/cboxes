#include <string.h>
#include <assert.h>
#include "cboxes/nodes.h"

LNode* LNode_Construct(void* value, LNode* next, size_t size) {
    assert(value != NULL);
    assert(size != 0);

    LNode* node = malloc(sizeof(LNode));
    node->value = malloc(size);
    memcpy(node->value, value, size);
    node->next = next;
    node->size = size;
    return node;
}

void LNode_Free(void *ptr, void freeValue(void* ptr)) {
    assert(ptr != NULL);
    LNode* node = (LNode*)ptr;

    freeValue(node->value);
    if (node->next != NULL) {
        LNode_Free(node->next, freeValue);
    }
    free(node);
}

void LNode_FreeD(void *ptr) {
    LNode_Free((LNode*)ptr, free);
}

bool LNode_IsEqual(const LNode* node, const LNode* other) {
    return node->value == other->value \
        && node->size == other->size   \
        && node->next == other->next;
}
