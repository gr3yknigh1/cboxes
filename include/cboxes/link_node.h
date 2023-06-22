#ifndef CBOXES_LNODE_H
#define CBOXES_LNODE_H

typedef struct cs_link_node {
    struct cs_link_node *next;
    struct cs_link_node *prev;
    void *value;
} cs_link_node_t;

#define CS_LNODE_GET(__lnode, __type) *((__type *)(__lnode)->value)

cs_link_node_t *cs_link_node_init(cs_link_node_t *next, cs_link_node_t *prev,
                                  void *value);
cs_link_node_t *cs_link_node_init_0(void *value);
void cs_link_node_chain(cs_link_node_t *first, cs_link_node_t *second);

#endif // CBOXES_LNODE_H
