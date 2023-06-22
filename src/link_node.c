#include <stdlib.h>

#include "cboxes/link_node.h"

cs_link_node_t *
cs_link_node_init(cs_link_node_t *next, cs_link_node_t *prev, void *value) {
    cs_link_node_t *node = malloc(sizeof(cs_link_node_t));
    *node = (cs_link_node_t){
        .next = next,
        .prev = prev,
        .value = value,
    };
    return node;
}

cs_link_node_t *
cs_link_node_NewD(void *value) {
    return cs_link_node_init(NULL, NULL, value);
}

void
cs_link_node_chain(cs_link_node_t *n0, cs_link_node_t *n1) {
    n0->next = n1;
    n1->prev = n0;
}
