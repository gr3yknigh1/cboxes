#include "cboxes/pair.h"
#include "cboxes/string.h"
#include "cboxes/type.h"
#include <string.h>

INIT_COMPLEX_CS_TYPE(CS_TYPE_PAIR, cs_pair_t *, cs_pair_copy, cs_pair_free);

cs_pair_t *
cs_pair_init(const char *key, void *restrict value, const cs_type_t *type) {
    cs_pair_t *pair = malloc(sizeof(cs_pair_t));
    *pair = (cs_pair_t){
        .key = key,
        .value = cs_type_store_value(type, value),
        .type = type,
    };
    return pair;
}

void *
cs_pair_copy(void *restrict dest, const void *src, size_t count) {
    (void)count;
    const cs_pair_t *src_pair = (const cs_pair_t *)src;
    cs_pair_t *copied_pair =
        cs_pair_init(src_pair->key, src_pair->value, src_pair->type);
    *((cs_pair_t *)dest) = *copied_pair;
    return copied_pair;
}

void
cs_pair_free(void *ptr) {
    cs_pair_t *pair = (cs_pair_t *)ptr;

    pair->type->free(pair->value);

    free((void *)pair->key);
    cs_type_free((void *)pair->type);
    free(ptr);
}
