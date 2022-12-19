#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stdlib.h>
#include "types.h"

typedef struct Node {
    void* value;
    size_t size;
    struct Node* next;
} Node;

Node* Node_Construct(void* value, Node* next, size_t size);
void Node_Free(Node* node);

bool Node_Equals(const Node* node, const Node* other);

enum {
    LIST_OK,
    LIST_INDEX_ERROR,
};

typedef struct List {
    Node* head;
    Node* tail;
    u64 length;
} List;


List* List_Construct();

int List_Get(const List* list, u64 index, Node** outNode);

List* List_Copy(const List* list);

u64 List_PushBack(List* list, void* value, size_t size);
u64 List_PushFront(List* list, void* value, size_t size);

int List_Insert(List* list, u64 index, void* value, size_t size);

u64 List_ExpandBack(List* list, void* begin, const u64 length);
u64 List_ExpandFront(List* list, void* begin, const u64 length);
u64 List_ExpandInsert(
    List* list, u64 index, void* begin, const u64 length);


u64 List_ExpandBack2List(List* list, List* other, const u64 length);
u64 List_ExpandFront2List(List* list, List* other, const u64 length);
u64 List_ExpandInsert2List(List* list, List* other, const u64 length);

int List_Pop(List* list, u64 index, Node** outNode);
int List_PopRange(List* list, u64 start, u64 end, Node** outNodes);

int List_FreeItem(List* list, u64 index);
int List_FreeRange(List* list, u64 start, u64 end);

void List_Clear(List* list);
void List_Free(List* list);

bool List_IsEmpty(const List* list);
bool List_IsFirst(const List* list, const u64 index);
bool List_IsLast(const List* list, const u64 index);
bool List_InRange(const List* list, const u64 index);

u64 _List_IncementLength(List* list);
void _List_LoopUntil(
    const List* list, u64 start, u64 end, u64 index, Node** outNode);

#endif // LIST_H
