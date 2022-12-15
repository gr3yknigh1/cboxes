#include <memory.h>
#include <stdlib.h>

#include "node.h"

Node* Node_Construct(void* value, Node* next, size_t size) {
    Node* node = malloc(sizeof(Node));
    node->value = malloc(size);
    memcpy(node->value, value, size);
    node->next = next;
    node->size = size;
    return node;
}

void Node_Free(Node *node) {
    free(node->value);
    if (node->next != NULL) {
        Node_Free(node->next);
    }
    free(node);
}

