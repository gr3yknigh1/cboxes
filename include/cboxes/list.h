#ifndef CBOXES_LIST_H_
#define CBOXES_LIST_H_

#include <stdbool.h>
#include <stddef.h>

#include "cboxes/lnode.h"
#include "cboxes/numtypes.h"
#include "cboxes/status.h"
#include "cboxes/type.h"

#define CS_LIST_GET(__list, __index, __outPtr)                                 \
    cs_List_Get((__list), (__index), ((void **)(&(__outPtr))))

#define CS_LIST_INSERT(__list, __index, __in, __statusPtr)                     \
    do {                                                                       \
        void *ptr = &(__in);                                                   \
        *(__statusPtr) = cs_List_Insert((__list), (__index), ptr);             \
    } while (0)

#define CS_LIST_FOREACHN(__list, __index, __node, __body)                      \
    do {                                                                       \
        cs_LNode *(__node) = (__list)->head;                                   \
        u64 __index = 0;                                                       \
        while ((__node) != NULL) {                                             \
            __body;                                                            \
            (__node) = (__node)->next;                                         \
            (__index)++;                                                       \
        }                                                                      \
    } while (0)

#define CS_LIST_FOREACHV(__list, __type, __value, __body)                      \
    do {                                                                       \
        cs_LNode *node = (__list)->head;                                       \
        (__type) * (__value) = NULL;                                           \
        while (node != NULL) {                                                 \
            (__value) = node->value;                                           \
            __body;                                                            \
            node = node->next;                                                 \
        }                                                                      \
    } while (0)

#define CS_LIST_FOREACH(__list, __type, __index, __value, __body)              \
    do {                                                                       \
        cs_LNode *node = (__list)->head;                                       \
        u64(__index) = 0;                                                      \
        while (node != NULL) {                                                 \
            (__type) * (__value) = NULL;                                       \
            (__value) = ((__type) *)(node->value);                             \
            __body;                                                            \
            node = node->next;                                                 \
            (__index)++;                                                       \
        }                                                                      \
    } while (0)

// TODO: Ranged macro

typedef struct cs_List {
    cs_LNode *head;
    cs_LNode *tail;

    u64 length;
    const cs_Type *type;
} cs_List;

cs_List *cs_List_New(const cs_Type *type);

void cs_List_PushBack(cs_List *list, void *value);
void cs_List_PushFront(cs_List *list, void *value);

void *cs_List_Copy(void *dest, const void *src, size_t count);

cs_Status cs_List_Get(cs_List *list, u64 index, void **out);
cs_Status cs_List_Insert(cs_List *list, u64 index, void *value);
cs_Status cs_List_Pop(cs_List *list, u64 index, void **out);
cs_Status cs_List_Remove(cs_List *list, u64 index);

void cs_List_Clear(cs_List *list);
void cs_List_Free(void *ptr);

#define cs_List_IsInRange(__list, __index)                                     \
    ((__index) >= 0 && (__index) < (__list)->length)
#define cs_List_IsEmpty(__list) ((__list)->length == 0)

void cs_List_Print(const cs_List *list, void (*printNode)(cs_LNode *));

DEFINE_CS_TYPE(CS_TYPE_LIST);

#endif // CBOXES_LIST_H_
