#include "cboxes/bst.h"
#include <memory.h>
#include <string.h>
#include <assert.h>

SPair SPair_Construct();

void SPair_Free(SPair* pair);


BNode* BNode_Construct(void* value, size_t size, BNode* left, BNode* right) {
    assert(value != NULL);
    assert(size != 0);

    BNode* node = malloc(sizeof(BNode));
    node->value = malloc(size);
    memcpy(node->value, value, size);
    node->left = left;
    node->right = right;
    return node;
}

BNode* BNode_ConstructD(void* value, size_t size) {
    return BNode_Construct(value, size, NULL, NULL);
}

u64 BNode_CountChildren(BNode* node) {
    u64 count = 0;
    if (node->left != NULL) {
        count += BNode_CountChildren(node->left);
    }
    if (node->right != NULL) {
        count += BNode_CountChildren(node->right);
    }
    return count;
}

void BNode_Free(BNode* node) {
    if (node->left != NULL) {
        BNode_Free(node->left);
    }
    if (node->right != NULL) {
        BNode_Free(node->right);
    }
    free(node->value);
    free(node);
}


BST* BST_Construct(BNode* root) {
    BST* bst = malloc(sizeof(BST));
    bst->root = root;
    if (root != NULL) {
        bst->count = BNode_CountChildren(root) + 1;
    } else {
        bst->count = 0;
    }
    return bst;
}

BST* BST_ConstructD() {
    return BST_Construct(NULL);
}

void BST_Free(BST* bst) {
    if (bst->root != NULL) {
        BNode_Free(bst->root);
    }
    free(bst);
}
