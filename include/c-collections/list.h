#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stdlib.h>
#include "types.h"


#define NODE() \
void* value;   \
size_t size    \


// Basic Node
typedef struct Node {
    NODE();
    struct CNode *parent;
    struct CNode *children;
    u64 childCount;
} Node;


// Binary Node
typedef struct BNode {
    NODE();
    struct BNode *left;
    struct BNode *right;
} BNode;

BNode* BNode_Construct(void* value, BNode* left, BNode* right, size_t size);

void BNode_Free (void *ptr, void freeValue(void *ptr));
void BNode_FreeD(void *ptr);

bool BNode_Equals(const BNode* node, const BNode* other);


// Linked Node
typedef struct LNode {
    NODE();
    struct LNode *next;
} LNode;

LNode* LNode_Construct(void* value, LNode* next, size_t size);
void LNode_Free (void *ptr, void freeValue(void *ptr));
void LNode_FreeD(void *ptr);
bool LNode_Equals(const LNode* node, const LNode* other);


#define COLLECTION()           \
u64 count;                     \
void* (*copyValue)(void* ptr); \
void  (*freeValue)(void* ptr); \


enum {
    LIST_OK,
    LIST_INDEX_ERROR,
};


typedef struct List {
    COLLECTION()

    LNode* head;
    LNode* tail;
} List;


List* List_ConstructD();

int List_Get(const List* list, u64 index, void** out);
int List_GetNode(const List* list, u64 index, LNode** outNode);

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

int List_Pop(List* list, u64 index, LNode** outNode);
int List_PopRange(List* list, u64 start, u64 end, LNode** outNodes);

int List_FreeItem(List* list, u64 index);
int List_FreeRange(List* list, u64 start, u64 end);

void List_Clear (List* list, void freeValue(void* item));
void List_ClearD(List* list);

void List_Free (List* list, void freeValue(void* item));
void List_FreeD(List* list);

bool List_IsEmpty(const List* list);
bool List_IsFirst(const List* list, const u64 index);
bool List_IsLast(const List* list, const u64 index);
bool List_InRange(const List* list, const u64 index);

u64 _List_IncementLength(List* list);
void _List_LoopUntil(
    const List* list, u64 start, u64 end, u64 index, LNode** outNode);

#endif // LIST_H
