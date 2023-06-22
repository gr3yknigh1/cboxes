#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "cboxes/assert.h"
#include "cboxes/linked_list.h"
#include "cboxes/shallow.h"
#include "cboxes/status.h"
#include "cboxes/type.h"

INIT_COMPLEX_CS_TYPE(CS_TYPE_LIST, cs_list_t *, cs_list_copy, cs_list_free);

cs_list_t *
cs_list_init(const cs_type_t *type) {
    cs_list_t *list = malloc(sizeof(cs_list_t));
    *list = (cs_list_t){
        .head = NULL,
        .tail = NULL,
        .length = 0,
        .type = type,
    };
    return list;
}

void *
cs_list_copy(void *restrict dest, const void *src, size_t count) {
    (void)count;

    const cs_list_t *orig = (const cs_list_t *)src;
    cs_list_t *copy = cs_list_init(orig->type);

    CS_LIST_FOREACHN(orig, index, node, {
        (void)index;
        cs_list_push_back(copy, node->value);
    });

    *(cs_list_t *)dest = *copy;
    return copy;
}

void
cs_list_push_back(cs_list_t *list, void *value) {
    cs_link_node_t *node =
        cs_link_node_init_0(cs_type_store_value(list->type, value));

    if (CS_LIST_ISEMPTY(list)) {
        list->head = node;
    } else {
        cs_link_node_chain(list->tail, node);
    }

    list->tail = node;
    list->length++;
}

void
cs_list_push_front(cs_list_t *list, void *value) {
    cs_link_node_t *node =
        cs_link_node_init_0(cs_type_store_value(list->type, value));

    if (CS_LIST_ISEMPTY(list)) {
        list->tail = node;
    } else {
        cs_link_node_chain(node, list->head);
    }

    list->head = node;
    list->length++;
}

static cs_status_t
cs_list_get_node(const cs_list_t *list, uint64_t idx,
                 cs_link_node_t **out_ptr) {
    if (CS_LIST_ISEMPTY(list)) {
        return cs_INDEX_ERROR;
    }

    if (idx == 0) {
        *out_ptr = list->head;
        return cs_OK;
    }

    if (idx == list->length - 1) {
        *out_ptr = list->tail;
        return cs_OK;
    }

    if (!CS_LIST_INRANGE(list, idx)) {
        return cs_INDEX_ERROR;
    }

    CS_LIST_FOREACHN(list, iter_idx, node, {
        if (iter_idx == idx) {
            *out_ptr = node;
            return cs_OK;
        }
    });

    return cs_OUT_OF_RANGE;
}

cs_status_t
cs_list_get(const cs_list_t *list, uint64_t idx, void **out_ptr) {
    cs_link_node_t *node = NULL;
    cs_status_t status = cs_list_get_node(list, idx, &node);
    if (status == cs_OK) {
        *out_ptr = node->value;
    }
    return status;
}

cs_status_t
cs_list_insert(cs_list_t *list, uint64_t idx, void *value) {
    if (!CS_LIST_INRANGE(list, idx)) {
        return cs_INDEX_ERROR;
    }

    if (CS_LIST_ISEMPTY(list) || idx == list->length - 1) {
        cs_list_push_back(list, value);
    } else if (idx == 0) {
        cs_list_push_front(list, value);
    } else {
        cs_link_node_t *target_node = NULL;
        cs_status_t status = cs_list_get_node(list, idx, &target_node);
        if (status != cs_OK) {
            return status;
        }

        cs_link_node_t *prevNode = target_node->prev;
        cs_link_node_t *node =
            cs_link_node_init_0(cs_type_store_value(list->type, value));

        cs_link_node_chain(prevNode, node);
        cs_link_node_chain(node, target_node);
    }

    return cs_OK;
}

static cs_status_t
cs_list_pop_node(cs_list_t *list, uint64_t index, cs_link_node_t **out_ptr) {
    CS_ASSERT(list != NULL, "<List [addr: %p]>", (void *)list);

    if (list == NULL) {
        return cs_NULL_REFERENCE_ERROR;
    }

    if (!CS_LIST_INRANGE(list, index) || CS_LIST_ISEMPTY(list)) {
        return cs_INDEX_ERROR;
    }

    if (list->length == 1) {
        *out_ptr = list->head;
        list->head = NULL;
        list->tail = NULL;
    } else if (index == 0) {
        *out_ptr = list->head;
        list->head = (*out_ptr)->next;
        list->head->prev = NULL;
    } else if (index == list->length - 1) {
        *out_ptr = list->tail;
        list->tail = (*out_ptr)->prev;
        list->tail->next = NULL;
    } else {
        CS_LIST_FOREACHN(list, iter_idx, iter_node, {
            if (iter_idx == index) {
                *out_ptr = iter_node;
                break;
            }
        });

        if (*out_ptr == NULL) {
            return cs_OUT_OF_RANGE;
        }

        cs_link_node_chain((*out_ptr)->prev, (*out_ptr)->next);
    }

    (*out_ptr)->next = NULL;
    (*out_ptr)->prev = NULL;

    list->length--;
    return cs_OK;
}

cs_status_t
cs_list_pop(cs_list_t *list, uint64_t idx, void **out_ptr) {
    cs_link_node_t *out_node = NULL;
    cs_status_t status = cs_list_pop_node(list, idx, &out_node);
    if (status == cs_OK) {
        *out_ptr = out_node->value;
    }
    return status;
}

cs_status_t
cs_list_remove(cs_list_t *list, uint64_t index) {
    cs_link_node_t *node = NULL;
    cs_status_t status = cs_list_pop_node(list, index, &node);

    if (status == cs_OK && node != NULL) {
        if (!list->type->is_ref) {
            list->type->free(node->value);
        }
        free(node);
    }
    return status;
}

void
cs_list_clear(cs_list_t *list) {
    if (CS_LIST_ISEMPTY(list)) {
        return;
    }

    const cs_type_t *type = list->type;
    cs_link_node_t *cur = list->head;
    cs_link_node_t *nxt;

    while (cur != NULL) {
        nxt = cur->next;

        if (!type->is_ref) {
            type->free(cur->value);
        }

        free(cur);
        cur = nxt;
    }

    list->length = 0;
    list->head = NULL;
    list->tail = NULL;
}

void
cs_list_free(void *ptr) {
    cs_list_t *list = ptr;
    cs_list_clear(list);
    free(list);
}

void
cs_list_print(const cs_list_t *list, void (*print_node)(cs_link_node_t *)) {
    printf("<List length:%ld>\n", list->length);
    CS_LIST_FOREACHN(list, idx, node, {
        printf("<LNode [%lu]>\n", idx);

        printf("prev: ");
        if (node->prev != NULL) {
            printf("[%lu]\n", idx - 1);
        } else {
            printf("NULL\n");
        }

        printf("next: ");
        if (node->next != NULL) {
            printf("[%lu]\n", idx + 1);
        } else {
            printf("NULL\n");
        }

        printf("Value: ");
        print_node(node);
        printf("\n\n");
    });
}
