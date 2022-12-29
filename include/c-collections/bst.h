#ifndef BST_H
#define BST_H

#include <stdlib.h>
#include "c-collections/types.h"

/*
 * String pair
 * */
typedef struct SPair {
    const char* key;

    void* value;
    size_t size;
} SPair;

SPair SPair_Construct();

void SPair_Free(SPair* pair);

/*
 * Binary tree node
 * */
typedef struct BNode {
    void* value;
    size_t size;

    struct BNode* left;
    struct BNode* right;
} BNode;

BNode* BNode_Construct(void* value, size_t size, BNode* left, BNode* right);
BNode* BNode_ConstructD(void* value, size_t size);

u64 BNode_CountChildren(BNode* node);

void BNode_Free(BNode* node);

/*
 * Binary Search tree
 * */
typedef struct BST {
    BNode* root;
    u64 count;
} BST;


BST* BST_Construct(BNode* root);
BST* BST_ConstructD();

int BST_Add();
int BST_Insert();
int BST_Remove();
int BST_Search();

BNode* BST_GetMax();
BNode* BST_GetMin();

void BST_InorderTreeWalk(void visitNode(BNode* node));

void BST_Free(BST* bst);

#endif // BST_H
