#ifndef LIST_H_
#define LIST_H_

#include "cboxes/lnode.h"
#include "cboxes/types.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef enum {
    cboxes_OK,
    cboxes_ERROR,
    cboxes_INDEX_ERROR,
} cboxes_status;

typedef struct List {
    LNode *head;
    LNode *tail;

    u64 count;
    size_t size;
    void *(*copyValue)(void *src, const void *dest, size_t size);
    void (*freeValue)(void *ptr);
} List;

List *List_New(LNode *head, LNode *tail, u64 count, size_t size,
                     void *(*copyValue)(void *src, const void *dest,
                                        size_t size),
                     void (*freeValue)(void *ptr));
List *List_ConstructD(size_t size);

cboxes_status List_Get(const List *list, u64 index, void **out);
cboxes_status List_GetN(const List *list, u64 index, LNode **outNode);

List *List_Copy(const List *list);

u64 List_PushBack(List *list, void *value);
u64 List_PushFront(List *list, void *value);

cboxes_status List_Insert(List *list, u64 index, void *value);
cboxes_status List_InsertN(List *list, u64 index, LNode *node);

u64 List_ExpandBack(List *list, void *begin, const u64 length);
u64 List_ExpandFront(List *list, void *begin, const u64 length);
u64 List_ExpandInsert(List *list, u64 index, void *begin, const u64 length);

u64 List_ExpandBack2List(List *list, List *other, const u64 length);
u64 List_ExpandFront2List(List *list, List *other, const u64 length);
u64 List_ExpandInsert2List(List *list, List *other, const u64 length);

cboxes_status List_PopN(List *list, u64 index, LNode **outNode);
cboxes_status List_PopRangeN(List *list, u64 start, u64 end, LNode **outNodes);

cboxes_status List_FreeN(List *list, u64 index);
cboxes_status List_FreeRangeN(List *list, u64 start, u64 end);

void List_Clear(List *list);
void List_Free(void *ptr);

bool List_IsEmpty(const List *list);
bool List_IsFirst(const List *list, const u64 index);
bool List_IsLast(const List *list, const u64 index);
bool List_InRange(const List *list, const u64 index);

u64 _List_IncementLength(List *list);
void _List_LoopUntil(const List *list, u64 start, u64 end, u64 index,
                     LNode **outNode);

#endif // LIST_H
