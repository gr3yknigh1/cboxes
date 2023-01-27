#include <stdlib.h>

#include "cboxes/lnode.h"

cs_LNode *cs_LNode_New(cs_LNode *next, cs_LNode *prev, void *value) {
    cs_LNode *node = malloc(sizeof(cs_LNode));
    *node = (cs_LNode) {
        .next = next,
        .prev = prev,
        .value = value,
    };
    return node;
}

cs_LNode *cs_LNode_NewD(void *value) {
    return cs_LNode_New(NULL, NULL, value);
}

void cs_LNode_Chain(cs_LNode *first, cs_LNode *second) {
    first->next = second;
    second->prev = first;
}

