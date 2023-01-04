#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <assert.h>

#include "cboxes/list.h"
#include "cboxes/error.h"
#include "cboxes/nodes.h"


List* List_Construct(
    LNode* head,
    LNode* tail,
    u64 count,
    size_t size,
    void* (*copyValue)(void* dest, const void* src, size_t size),
    void  (*freeValue)(void* ptr)
    ) {

    List* list = malloc(sizeof(List));
    list->head = head;
    list->tail = tail;
    list->count = count;
    list->size  = size;
    list->copyValue = copyValue;
    list->freeValue = freeValue;
    return list;
}

List* List_ConstructD(size_t size) {
    return List_Construct(NULL, NULL, 0, size, memcpy, free);
}


int List_Get(const List *list, u64 index, void **out) {
    LNode* outNode;
    u16 exitCode = List_GetNode(list, index, &outNode);

    if (exitCode == cboxes_Ok) {
        *out = outNode->value;
    }

    return exitCode;
}

int List_GetNode(const List* list, u64 index, LNode** outNode) {
    if (List_IsEmpty(list)) {
        printf("Error: No items in list\n");
        return cboxes_IndexError;
    } else if (!List_InRange(list, index)) {
        printf("IndexError: List[%lu] Index(%lu)\n", list->count, index);
        return cboxes_IndexError;
    }

    // NOTE: Handle first and last special cases
    if (List_IsFirst(list, index)) {
        *outNode = list->head;
        return cboxes_Ok;
    } else if (List_IsLast(list, index)) {
        *outNode = list->tail;
        return cboxes_Ok;
    } else {
        // NOTE: Staring from second item because first is already handled
        _List_LoopUntil(list, 1, list->count, index, outNode);
    }

    return cboxes_Ok;
}

u64 List_PushBack(List *list, void *value) {
    if (List_IsEmpty(list)) {
        list->head = LNode_Construct(value, NULL, list->size, list->copyValue, list->freeValue);
        list->tail = list->head;
    } else if (list->count == 1) {
        list->tail = LNode_Construct(value, NULL, list->size, list->copyValue, list->freeValue);
        list->head->next = list->tail;
    } else {
        list->tail->next = LNode_Construct(value, NULL, list->size, list->copyValue, list->freeValue);
        list->tail = list->tail->next;
    }

    list->count++;
    return list->count;
}

u64 List_PushFront(List *list, void *value) {
    if (List_IsEmpty(list)) {
        list->head = LNode_Construct(value, NULL, list->size, list->copyValue, list->freeValue);
        list->tail = list->head;
    } else {
        LNode* newNode = LNode_Construct(value, list->head, list->size, list->copyValue, list->freeValue);
        list->head = newNode;
    }

    list->count++;
    return list->count;
}

int List_Insert(List *list, u64 index, void *value) {
    if (List_IsEmpty(list) || List_IsLast(list, index)) {
        List_PushBack(list, value);
        return cboxes_Ok;
    } else if (List_IsFirst(list, index)) {
        List_PushFront(list, value);
        return cboxes_Ok;
    } else if (!List_InRange(list, index)) {
        printf("IndexError: List[%lu] Index(%lu)\n", list->count, index);
        return cboxes_IndexError;
    }

    LNode *before;
    _List_LoopUntil(list, 1, list->count, index - 1, &before);

    before->next = LNode_Construct(value, before->next, list->size, list->copyValue, list->freeValue);

    list->count++;
    return cboxes_Ok;
}

u64 List_ExpandBack(List* list, void* begin, const u64 length);
u64 List_ExpandFront(List* list, void* begin, const u64 length);
u64 List_ExpandInsert(
    List* list, u64 index, void* begin, const u64 length);

int List_PopNode(List *list, u64 index, LNode** outNode) {
    if (List_IsEmpty(list)) {
        printf("Error: No items in list\n");
        return cboxes_IndexError;
    } else if (index >= list->count) {
        printf("Error: Index greater or equal to length: %lu\n", index);
        return cboxes_IndexError;
    } else if (index < 0) {
        printf("Error: Index less than 0: %lu\n", index);
        return cboxes_IndexError;
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
    return cboxes_Ok;
}

int List_PopNodeRange(List* list, u64 start, u64 end, LNode** outNodes);

int List_FreeNode(List* list, u64 index) {
    if (!List_InRange(list, index)) {
        printf("IndexError: List[%lu] Index(%lu)\n", list->count, index);
        return cboxes_IndexError;
    }

    LNode* node;
    List_PopNode(list, index, &node);
    node->next = NULL;
    LNode_Free(node, list->freeValue);

    return cboxes_Ok;
}


int List_FreeNodeRange(List* list, u64 start, u64 end);

void List_Clear(List* list) {
    if (list->count == 0) {
        return;
    }

    LNode_Free(list->head, list->freeValue);
    list->count = 0;
    list->head = NULL;
    list->tail = NULL;
}

void List_Free(void* ptr) {
    List* list = (List*)ptr;
    if (list->count != 0) {
        List_Clear(list);
        return;
    }
    free(list);
    list = NULL;
}

bool List_IsEmpty(const List* list) {
    return list->count == 0;
}

bool List_IsFirst(const List* list, const u64 index) {
    return index == 0;
}

bool List_IsLast(const List* list, const u64 index) {
    return index == list->count - 1;
}

bool List_InRange(const List* list, const u64 index) {
    return index >= 0 && index < list->count;
}

u64 _List_IncementLength(List* list) {
    list->count++;
    return list->count;
}

void _List_LoopUntil(
    const List* list,
    u64 start,
    u64 end,
    u64 index,
    LNode** outNode
) {

    u64 currentIndex = start;
    LNode* currentNode = list->head->next;
    while(currentNode != NULL) {
        if (currentIndex == index) {
            *outNode = currentNode;
            break;
        }

        currentIndex++;
        currentNode = currentNode->next;
    }
}

