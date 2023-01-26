#include <assert.h>
#include <memory.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cboxes/list.h"
#include "cboxes/lnode.h"

List *List_New(LNode *head, LNode *tail, u64 count, size_t size,
                     void *(*copyValue)(void *dest, const void *src,
                                        size_t size),
                     void (*freeValue)(void *ptr)) {

    List *list = malloc(sizeof(List));
    list->head = head;
    list->tail = tail;
    list->count = count;
    list->size = size;
    list->copyValue = copyValue;
    list->freeValue = freeValue;
    return list;
}

List *List_NewD(size_t size) {
    return List_New(NULL, NULL, 0, size, memcpy, free);
}

cboxes_status List_Get(const List *list, u64 index, void **out) {
    LNode *outNode;
    u16 statusCode = List_GetN(list, index, &outNode);

    if (statusCode == cboxes_OK) {
        *out = outNode->value;
    }

    return statusCode;
}

cboxes_status List_GetN(const List *list, u64 index, LNode **outNode) {
    if (List_IsEmpty(list) || !List_InRange(list, index)) {
        return cboxes_INDEX_ERROR;
    }

    // NOTE: Handle first and last special cases
    if (List_IsFirst(list, index)) {
        *outNode = list->head;
    } else if (List_IsLast(list, index)) {
        *outNode = list->tail;
    } else {
        // NOTE: Staring from second item because first is already handled
        _List_LoopUntil(list, 1, list->count, index, outNode);
    }

    return cboxes_OK;
}

u64 List_PushBack(List *list, void *value) {
    if (List_IsEmpty(list)) {
        list->head = LNode_Construct(value, NULL, list->size, list->copyValue,
                                     list->freeValue);
        list->tail = list->head;
    } else if (list->count == 1) {
        list->tail = LNode_Construct(value, NULL, list->size, list->copyValue,
                                     list->freeValue);
        list->head->next = list->tail;
    } else {
        list->tail->next = LNode_Construct(value, NULL, list->size,
                                           list->copyValue, list->freeValue);
        list->tail = list->tail->next;
    }

    list->count++;
    return list->count;
}

u64 List_PushFront(List *list, void *value) {
    if (List_IsEmpty(list)) {
        list->head = LNode_Construct(value, NULL, list->size, list->copyValue,
                                     list->freeValue);
        list->tail = list->head;
    } else {
        LNode *newNode = LNode_Construct(value, list->head, list->size,
                                         list->copyValue, list->freeValue);
        list->head = newNode;
    }

    list->count++;
    return list->count;
}

cboxes_status List_Insert(List *list, u64 index, void *value) {
    if (List_IsEmpty(list) || List_IsLast(list, index)) {
        List_PushBack(list, value);
        return cboxes_OK;
    } else if (List_IsFirst(list, index)) {
        List_PushFront(list, value);
        return cboxes_OK;
    } else if (!List_InRange(list, index)) {
        return cboxes_INDEX_ERROR;
    }

    LNode *before;
    _List_LoopUntil(list, 1, list->count, index - 1, &before);

    before->next = LNode_Construct(value, before->next, list->size,
                                   list->copyValue, list->freeValue);

    list->count++;
    return cboxes_OK;
}

u64 List_ExpandBack(List *list, void *begin, const u64 length);
u64 List_ExpandFront(List *list, void *begin, const u64 length);
u64 List_ExpandInsert(List *list, u64 index, void *begin, const u64 length);

cboxes_status List_PopN(List *list, u64 index, LNode **outNode) {
    if (List_IsEmpty(list)) {
        return cboxes_INDEX_ERROR;
    } else if (index >= list->count) {
        return cboxes_INDEX_ERROR;
    } else if (index < 0) {
        return cboxes_INDEX_ERROR;
    }

    if (List_IsFirst(list, index)) {
        *outNode = list->head;
        list->head = list->head->next;
    } else {
        LNode *before;
        _List_LoopUntil(list, 1, list->count, index - 1, &before);
        *outNode = before->next;
        before->next = before->next->next;
    }

    list->count--;
    return cboxes_OK;
}

cboxes_status List_PopRangeN(List *list, u64 start, u64 end, LNode **outNodes);

cboxes_status List_FreeN(List *list, u64 index) {
    if (!List_InRange(list, index)) {
        return cboxes_INDEX_ERROR;
    }

    LNode *node;
    List_PopN(list, index, &node);
    node->next = NULL;
    LNode_Free(node, list->freeValue);

    return cboxes_OK;
}

cboxes_status List_FreeRangeN(List *list, u64 start, u64 end);

void List_Clear(List *list) {
    if (list->count == 0) {
        return;
    }

    LNode_Free(list->head, list->freeValue);
    list->count = 0;
    list->head = NULL;
    list->tail = NULL;
}

void List_Free(void *ptr) {
    List *list = (List *)ptr;
    if (list->count != 0) {
        List_Clear(list);
        return;
    }
    free(list);
    list = NULL;
}

bool List_IsEmpty(const List *list) { return list->count == 0; }

bool List_IsFirst(const List *list, const u64 index) { return index == 0; }

bool List_IsLast(const List *list, const u64 index) {
    return index == list->count - 1;
}

bool List_InRange(const List *list, const u64 index) {
    return index >= 0 && index < list->count;
}

u64 _List_IncementLength(List *list) {
    list->count++;
    return list->count;
}

void _List_LoopUntil(const List *list, u64 start, u64 end, u64 index,
                     LNode **outNode) {

    u64 currentIndex = start;
    LNode *currentNode = list->head->next;
    while (currentNode != NULL) {
        if (currentIndex == index) {
            *outNode = currentNode;
            break;
        }

        currentIndex++;
        currentNode = currentNode->next;
    }
}
