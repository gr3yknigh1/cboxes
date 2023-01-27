#ifndef LIST_H_
#define LIST_H_

#include <stdbool.h>
#include <stddef.h>

#include "cboxes/types.h"

#define CS_LIST_GET(list, index, out) cs_List_Get(list, index, ((void**)out))
#define CS_LIST_FOREACHN(list, i, n, body) \
    do {                                   \
        cs_LNode *n = list->head;          \
        u64 i = 0;                         \
        while (n != NULL) {                \
            body;                          \
            n = n->next;                   \
            i++;                           \
        }                                  \
    } while (0)                            \

#define CS_LIST_FOREACH(list, type, v, body) \
    do {                                     \
        cs_LNode *__n = list->head;          \
        while (__n != NULL) {                \
            type *v = NULL;                  \
            v = (type *)(__n->value);        \
            body;                            \
            __n = __n->next;                 \
        }                                    \
    } while(0)                               \

#define CS_LIST_FOREACHO(list, type, v, i, s, e, body) \
    do {                                     \
        cs_LNode *__n = list->head;          \
        u64 i = 0;                           \
        while (__n != NULL) {                \
            if (i > e) break; \
            if (i >= s || i <= e) { \
            type *v = NULL;                  \
            v = (type *)(__n->value);        \
            body;                            \
            } \
            __n = __n->next;                 \
            i++;                             \
        }                                    \
    } while(0)                               \


typedef enum cs_Status {
    cs_OK,
    cs_INDEX_ERROR,
    cs_OUT_OF_RANGE,
    cs_COLLECTION_IS_EMPTY,
} cs_Status;

typedef struct cs_LNode {
    struct cs_LNode *next;
    struct cs_LNode *prev;
    void *value;
} cs_LNode;

cs_LNode *cs_LNode_New(cs_LNode *next, cs_LNode *prev, void *value);
cs_LNode *cs_LNode_NewD(void *value);
void cs_LNode_Chain(cs_LNode *first, cs_LNode *second);

typedef void (*cs_CopyFunc)(void *dest, const void *src, size_t count);
typedef void (*cs_FreeFunc)(void *ptr);

typedef struct cs_Type {
    size_t size;
    bool isReference;
    cs_CopyFunc copy;
    cs_FreeFunc free;
} cs_Type;

void cs_ShallowCopy(void *dest, const void *src, size_t count);
void cs_ShallowFree(void *ptr);

typedef struct cs_List {
    cs_LNode *head;
    cs_LNode *tail;

    u64 length;
    cs_Type type;
} cs_List;

cs_List *cs_List_New(cs_Type type);
cs_List *cs_List_NewD(size_t size);

void cs_List_PushBack(cs_List *list, void *value);
void cs_List_PushFront(cs_List *list, void *value);

cs_Status cs_List_Get(cs_List *list, u64 index, void **out);
cs_Status cs_List_Insert(cs_List *list, u64 index, void *value);
cs_Status cs_List_Pop(cs_List *list);
cs_Status cs_List_Remove(cs_List *list);

// TODO: Add is empty function (?)
bool cs_List_IsInRange(cs_List *list, u64 index);

void cs_List_Print(const cs_List* list, void (*printNode)(cs_LNode*));

#endif // LIST_H
