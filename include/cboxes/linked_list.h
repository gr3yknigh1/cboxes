#ifndef CBOXES_LIST_H_
#define CBOXES_LIST_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "cboxes/link_node.h"
#include "cboxes/status.h"
#include "cboxes/type.h"

#define CS_LIST_GET(__list, __index, __outPtr)                                 \
    cs_list_get((__list), (__index), ((void **)(&(__outPtr))))

#define CS_LIST_INSERT(__list, __index, __in, __statusPtr)                     \
    do {                                                                       \
        void *ptr = &(__in);                                                   \
        *(__statusPtr) = cs_list_insert((__list), (__index), ptr);             \
    } while (0)

#define CS_LIST_FOREACHN(__list, __index, __node, __body)                      \
    do {                                                                       \
        cs_link_node_t *(__node) = (__list)->head;                             \
        uint64_t __index = 0;                                                  \
        while ((__node) != NULL) {                                             \
            __body;                                                            \
            (__node) = (__node)->next;                                         \
            (__index)++;                                                       \
        }                                                                      \
    } while (0)

#define CS_LIST_FOREACHV(__list, __type, __value, __body)                      \
    do {                                                                       \
        cs_link_node_t *node = (__list)->head;                                 \
        (__type) * (__value) = NULL;                                           \
        while (node != NULL) {                                                 \
            (__value) = node->value;                                           \
            __body;                                                            \
            node = node->next;                                                 \
        }                                                                      \
    } while (0)

#define CS_LIST_FOREACH(__list, __type, __index, __value, __body)              \
    do {                                                                       \
        cs_link_node_t *node = (__list)->head;                                 \
        uint64_t(__index) = 0;                                                 \
        while (node != NULL) {                                                 \
            (__type) * (__value) = NULL;                                       \
            (__value) = ((__type) *)(node->value);                             \
            __body;                                                            \
            node = node->next;                                                 \
            (__index)++;                                                       \
        }                                                                      \
    } while (0)

// TODO: Ranged macro

typedef struct cs_list {
    cs_link_node_t *head;
    cs_link_node_t *tail;

    uint64_t length;
    const cs_type_t *type;
} cs_list_t;

void cs_list_init(cs_list_t *out_list, const cs_type_t *type);

void cs_list_push_back(cs_list_t *list, void *value);
void cs_list_push_front(cs_list_t *list, void *value);

void *cs_list_copy(void *dest, const void *src, size_t count);

cs_status_t cs_list_get(const cs_list_t *list, uint64_t index, void **out);
cs_status_t cs_list_insert(cs_list_t *list, uint64_t index, void *value);
cs_status_t cs_list_pop(cs_list_t *list, uint64_t index, void **out);
cs_status_t cs_list_remove(cs_list_t *list, uint64_t index);

void cs_list_clear(cs_list_t *list);
void cs_list_free(void *ptr);

#define CS_LIST_INRANGE(__list, __index) ((__index) < (__list)->length)
#define CS_LIST_ISEMPTY(__list) ((__list)->length == 0)

// TODO: Replace with Interator
void cs_list_print(const cs_list_t *list, void (*print_node)(cs_link_node_t *));

DEFINE_CS_TYPE(CS_TYPE_LIST);

#endif // CBOXES_LIST_H_
