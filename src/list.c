#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "cboxes/list.h"
#include "cboxes/numtypes.h"
#include "cboxes/shallow.h"
#include "cboxes/status.h"
#include "cboxes/type.h"

INIT_COMPLEX_CS_TYPE(CS_LIST_TYPE, cs_List *, cs_List_Copy, cs_List_Free);

cs_List *cs_List_New(const cs_Type *type) {
    assert(type->size > 0);

    cs_List *list = malloc(sizeof(cs_List));
    *list = (cs_List){
        .head = NULL,
        .tail = NULL,
        .length = 0,
        .type = type,
    };
    return list;
}

cs_List *cs_List_NewD(size_t size) {
    return cs_List_New(
        cs_Type_New(size, false, cs_ShallowCopy, cs_ShallowFree));
}

void *cs_List_Copy(void *dest, const void *src, size_t count) { return NULL; }

void cs_List_PushBack(cs_List *list, void *value) {
    cs_LNode *node = cs_LNode_NewD(cs_Type_StoreValue(list->type, value));

    if (cs_List_IsEmpty(list)) {
        list->head = node;
    } else {
        cs_LNode_Chain(list->tail, node);
    }

    list->tail = node;
    list->length++;
}

void cs_List_PushFront(cs_List *list, void *value) {
    cs_LNode *node = cs_LNode_NewD(cs_Type_StoreValue(list->type, value));

    if (cs_List_IsEmpty(list)) {
        list->tail = node;
    } else {
        cs_LNode_Chain(node, list->head);
    }

    list->head = node;
    list->length++;
}

static cs_Status cs_List_GetNode(cs_List *list, u64 index, cs_LNode **outNode) {
    if (cs_List_IsEmpty(list)) {
        return cs_COLLECTION_IS_EMPTY;
    }

    if (index == 0) {
        *outNode = list->head;
        return cs_OK;
    } else if (index == list->length - 1) {
        *outNode = list->tail;
        return cs_OK;
    }

    if (!cs_List_IsInRange(list, index)) {
        return cs_INDEX_ERROR;
    }

    CS_LIST_FOREACHN(list, i, n, {
        if (i == index) {
            *outNode = n;
            return cs_OK;
        }
    });

    return cs_OUT_OF_RANGE;
}

cs_Status cs_List_Get(cs_List *list, u64 index, void **out) {
    cs_LNode *node = NULL;
    cs_Status status = cs_List_GetNode(list, index, &node);
    if (status == cs_OK) {
        *out = node->value;
    }
    return status;
}

cs_Status cs_List_Insert(cs_List *list, u64 index, void *value) {
    if (!cs_List_IsInRange(list, index)) {
        return cs_INDEX_ERROR;
    }

    if (cs_List_IsEmpty(list) || index == list->length - 1) {
        cs_List_PushBack(list, value);
    } else if (index == 0) {
        cs_List_PushFront(list, value);
    } else {
        cs_LNode *targetNode = NULL;
        cs_Status status = cs_List_GetNode(list, index, &targetNode);
        if (status != cs_OK) {
            return status;
        }

        cs_LNode *prevNode = targetNode->prev;
        cs_LNode *node = cs_LNode_NewD(cs_Type_StoreValue(list->type, value));

        cs_LNode_Chain(prevNode, node);
        cs_LNode_Chain(node, targetNode);
    }

    return cs_OK;
}

static cs_Status cs_List_PopNode(cs_List *list, u64 index, cs_LNode **out) {
    if (list == NULL)
        return cs_NULL_REFERENCE_ERROR;
    if (cs_List_IsEmpty(list))
        return cs_OK;
    if (!cs_List_IsInRange(list, index))
        return cs_INDEX_ERROR;

    if (index == 0) {
        *out = list->head;
        list->head = (*out)->next;
        list->head->prev = NULL;
    } else if (index == list->length - 1) {
        *out = list->tail;
        list->tail = (*out)->prev;
        list->tail->next = NULL;
    } else {
        CS_LIST_FOREACHN(list, i, n, {
            if (i == index) {
                *out = n;
                break;
            }
        });

        if (*out == NULL)
            return cs_OUT_OF_RANGE;

        cs_LNode_Chain((*out)->prev, (*out)->next);
    }

    (*out)->next = NULL;
    (*out)->prev = NULL;

    list->length--;
    return cs_OK;
}

cs_Status cs_List_Pop(cs_List *list, u64 index, void **out) {
    cs_LNode *outNode = NULL;
    cs_Status status = cs_List_PopNode(list, index, &outNode);
    if (status == cs_OK) {
        *out = outNode->value;
    }
    return status;
}

cs_Status cs_List_Remove(cs_List *list, u64 index) {
    cs_LNode *node = NULL;
    cs_Status status = cs_List_PopNode(list, index, &node);
    if (status == cs_OK && node != NULL) {
        if (!list->type->isReference) {
            list->type->free(node->value);
        }
        free(node);
    }
    return status;
}

void cs_List_Clear(cs_List *list) {
    if (cs_List_IsEmpty(list))
        return;

    const cs_Type *type = list->type;
    cs_LNode *cur = list->head;
    cs_LNode *nxt;
    while (cur != NULL) {
        nxt = cur->next;

        if (!type->isReference)
            type->free(cur->value);

        free(cur);
        cur = nxt;
    }

    list->length = 0;
    list->head = NULL;
    list->tail = NULL;
}

void cs_List_Free(void *ptr) {
    cs_List *list = ptr;
    cs_List_Clear(list);
    free(list);
}

bool cs_List_IsInRange(cs_List *list, u64 index) {
    return index >= 0 && index < list->length;
}

bool cs_List_IsEmpty(cs_List *list) { return list->length == 0; }

void cs_List_Print(const cs_List *list, void (*printValue)(cs_LNode *)) {
    CS_LIST_FOREACHN(list, i, n, {
        printf("<LNode [%lu]>\n", i);

        printf("prev: ");
        if (n->prev != NULL) {
            printf("[%lu]\n", i - 1);
        } else {
            printf("NULL\n");
        }

        printf("next: ");
        if (n->next != NULL) {
            printf("[%lu]\n", i + 1);
        } else {
            printf("NULL\n");
        }

        printf("Value: ");
        printValue(n);
        printf("\n\n");
    });
}
