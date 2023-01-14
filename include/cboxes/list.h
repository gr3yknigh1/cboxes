#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "cboxes/nodes.h"
#include "cboxes/types.h"
#include "cboxes/error.h"


typedef struct List {
    LNode* head;
    LNode* tail;

    u64 count;
    size_t size;
    void* (*copyValue)(void* src, const void* dest, size_t size);
    void  (*freeValue)(void* ptr);
} List;

List* List_Construct(
    LNode* head,
    LNode* tail,
    u64 count,
    size_t size,
    void* (*copyValue)(void* src, const void* dest, size_t size),
    void  (*freeValue)(void* ptr)
    );
List* List_ConstructD(size_t size);

int List_Get(const List* list, u64 index, void** out);
int List_GetNode(const List* list, u64 index, LNode** outNode);

List* List_Copy(const List* list);

u64 List_PushBack(List* list, void* value);
u64 List_PushFront(List* list, void* value);

int List_Insert(List* list, u64 index, void* value);
int List_InsertNode(List* list, u64 index, LNode* node);

u64 List_ExpandBack(List* list, void* begin, const u64 length);
u64 List_ExpandFront(List* list, void* begin, const u64 length);
u64 List_ExpandInsert(
    List* list, u64 index, void* begin, const u64 length);


u64 List_ExpandBack2List(List* list, List* other, const u64 length);
u64 List_ExpandFront2List(List* list, List* other, const u64 length);
u64 List_ExpandInsert2List(List* list, List* other, const u64 length);

int List_PopNode(List* list, u64 index, LNode** outNode);
int List_PopNodeRange(List* list, u64 start, u64 end, LNode** outNodes);

int List_FreeNode(List* list, u64 index);
int List_FreeNodeRange(List* list, u64 start, u64 end);

void List_Clear(List* list);
void List_Free(void* ptr);

bool List_IsEmpty(const List* list);
bool List_IsFirst(const List* list, const u64 index);
bool List_IsLast(const List* list, const u64 index);
bool List_InRange(const List* list, const u64 index);

u64 _List_IncementLength(List* list);
void _List_LoopUntil(
    const List* list, u64 start, u64 end, u64 index, LNode** outNode);

#endif // LIST_H
