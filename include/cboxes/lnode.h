#ifndef LNODE_H_
#define LNODE_H_

typedef struct cs_LNode {
    struct cs_LNode *next;
    struct cs_LNode *prev;
    void *value;
} cs_LNode;

#define CS_LNODE_GET(__lnode, __type) *((__type *)__lnode->value)

cs_LNode *cs_LNode_New(cs_LNode *next, cs_LNode *prev, void *value);
cs_LNode *cs_LNode_NewD(void *value);
void cs_LNode_Chain(cs_LNode *first, cs_LNode *second);

#endif // LNODE_H_
