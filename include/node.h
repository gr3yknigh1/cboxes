#ifndef NODE_H
#define NODE_H 

#include <stdlib.h>

typedef struct Node {
    void* value;
    size_t size;
    struct Node* next;
} Node;

Node* Node_Construct(void* value, Node* next, size_t size);
void Node_Free(Node* node);

#endif // NODE_H
