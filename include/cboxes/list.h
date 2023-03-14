#ifndef LIST_H_
#define LIST_H_

#include <stdbool.h>
#include <stddef.h>

#include "cboxes/lnode.h"
#include "cboxes/numtypes.h"
#include "cboxes/status.h"
#include "cboxes/type.h"

#define CS_LIST_GET(list, index, out)                                          \
    cs_List_Get(list, index, ((void **)(&out)))

#define CS_LIST_INSERT(list, index, in, status)                                \
    do {                                                                       \
        void *ptr = &in;                                                       \
        status = cs_List_Insert(list, index, ptr);                             \
    } while (0)

#define CS_LIST_FOREACHN(list, i, n, body)                                     \
    do {                                                                       \
        cs_LNode *n = list->head;                                              \
        u64 i = 0;                                                             \
        while (n != NULL) {                                                    \
            body;                                                              \
            n = n->next;                                                       \
            i++;                                                               \
        }                                                                      \
    } while (0)

#define CS_LIST_FOREACHV(__list, __t, __v, __code)                             \
    do {                                                                       \
        cs_LNode *__n = __list->head;                                          \
        __t *__v = NULL;                                                       \
        while (__n != NULL) {                                                  \
            __v = __n->value;                                                  \
            __code;                                                            \
            __n = __n->next;                                                   \
        }                                                                      \
    } while (0)

#define CS_LIST_FOREACH(list, type, i, v, body)                                \
    do {                                                                       \
        cs_LNode *__n = list->head;                                            \
        u64 i = 0;                                                             \
        while (__n != NULL) {                                                  \
            type *v = NULL;                                                    \
            v = (type *)(__n->value);                                          \
            body;                                                              \
            __n = __n->next;                                                   \
            i++;                                                               \
        }                                                                      \
    } while (0)

// TODO: Add out-of-range handling
#define CS_LIST_FOREACHO(list, type, v, i, s, e, body)                         \
    do {                                                                       \
        cs_LNode *__n = list->head;                                            \
        u64 i = 0;                                                             \
        while (__n != NULL) {                                                  \
            if (i > e)                                                         \
                break;                                                         \
            if (i >= s && i <= e) {                                            \
                type *v = NULL;                                                \
                v = (type *)(__n->value);                                      \
                body;                                                          \
            }                                                                  \
            __n = __n->next;                                                   \
            i++;                                                               \
        }                                                                      \
    } while (0)

typedef struct cs_List {
    cs_LNode *head;
    cs_LNode *tail;

    u64 length;
    const cs_Type *type;
} cs_List;

cs_List *cs_List_New(const cs_Type *type);

void *cs_List_Copy(void *dest, const void *src, size_t count);

void cs_List_PushBack(cs_List *list, void *value);
void cs_List_PushFront(cs_List *list, void *value);

cs_Status cs_List_Get(cs_List *list, u64 index, void **out);
cs_Status cs_List_Insert(cs_List *list, u64 index, void *value);
cs_Status cs_List_Pop(cs_List *list, u64 index, void **out);
cs_Status cs_List_Remove(cs_List *list, u64 index);

void cs_List_Clear(cs_List *list);
void cs_List_Free(void *ptr);

#define cs_List_IsInRange(__list, __index)                                     \
    (__index >= 0 && __index < __list->length)
#define cs_List_IsEmpty(__list) (__list->length == 0)

void cs_List_Print(const cs_List *list, void (*printNode)(cs_LNode *));

DEFINE_CS_TYPE(CS_TYPE_LIST);

#endif // LIST_H_
