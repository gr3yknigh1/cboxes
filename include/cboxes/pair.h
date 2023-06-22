#ifndef CBOXES_PAIR_H_
#define CBOXES_PAIR_H_

#include "cboxes/string.h"
#include "cboxes/type.h"

typedef struct cs_pair {
    const char *key;
    void *value;
    const cs_type_t *type;
} cs_pair_t;

cs_pair_t *cs_pair_init(const char *key, void *value, const cs_type_t *type);

void *cs_pair_copy(void *dest, const void *src, size_t count);
void cs_pair_free(void *ptr);

DEFINE_CS_TYPE(CS_TYPE_PAIR);

#endif // CBOXES_PAIR_H_
