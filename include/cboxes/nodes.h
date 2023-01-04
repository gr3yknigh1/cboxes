#ifndef NODES_H
#define NODES_H

#include <stdlib.h>
#include <stdbool.h>
#include "cboxes/types.h"


#define NODE()                                                \
void* value;                                                  \
size_t size;                                                  \
void* (*copyValue)(void* dest, const void* src, size_t size); \
void  (*freeValue)(void* ptr)                                 \

// Basic Node
typedef struct Node {
    NODE();

    struct Node *parent;
    struct Node *children;
    u64 childCount;
} Node;

Node* Node_Construct(
    void* value,
    Node* left,
    Node* right,
    size_t size,
    void* (*copyValue)(void* src, const void* dest, size_t size),
    void  (*freeValue)(void* ptr)
    );
void Node_Free(void *ptr);
bool Node_IsEqual(const Node* node, const Node* other);


// Binary Node
typedef struct BNode {
    NODE();
    struct BNode *left;
    struct BNode *right;
} BNode;

BNode* BNode_Construct(void* value, BNode* left, BNode* right, size_t size);
void BNode_Free (void *ptr, void freeValue(void *ptr));
void BNode_FreeD(void *ptr);
bool BNode_IsEqual(const BNode* node, const BNode* other);


// Linked Node
typedef struct LNode {
    NODE();

    struct LNode *next;
} LNode;

LNode* LNode_Construct(
    void* value,
    LNode* next,
    size_t size,
    void* (*copyValue)(void* src, const void* dest, size_t size),
    void  (*freeValue)(void* ptr)
    );
void* LNode_Copy(void *dest, const void *src, size_t size);
void LNode_Free (void *ptr, void freeValue(void *ptr));
void LNode_FreeD(void *ptr);
bool LNode_IsEqual(const LNode* node, const LNode* other);


#endif // NODES_H
