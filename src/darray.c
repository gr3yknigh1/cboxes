#include "cboxes/darray.h"
#include "cboxes/memory.h"

void
cs_darray_init(cs_darray_t *out, const cs_type_t *type) {
    *out = (cs_darray_t){
        .data = NULL,
        .len = 0,
        .cap = 0,
        .type = type,
    };
}

cs_status_t
cs_darray_get(const cs_darray_t *darr, uint64_t idx, void const **out) {
    if (!CS_DARRAY_IN_RANGE(darr, idx)) {
        return cs_INDEX_ERROR;
    }
    *out = ((int8_t *)darr->data) + idx * darr->type->size;
    return cs_OK;
}

cs_status_t
cs_darray_get_mut(const cs_darray_t *darr, uint64_t idx, void **out) {
    if (!CS_DARRAY_IN_RANGE(darr, idx)) {
        return cs_INDEX_ERROR;
    }
    *out = ((int8_t *)darr->data) + idx * darr->type->size;
    return cs_OK;
}

void
cs_darray_reallocate(cs_darray_t *darr, uint64_t new_cap) {
    void *new_data = malloc(darr->type->size * new_cap);

    if (darr->len != 0) {
        cs_copy_memory(new_data, darr->data, new_cap, darr->len);
    }

    if (darr->data != NULL) {
        free(darr->data);
    }

    darr->data = new_data;
    darr->cap = new_cap;
}

void
cs_darray_push_back(cs_darray_t *darr, void *data) {
    if (darr->len > (uint64_t)(darr->cap * CS_DARRAY_LOAD_FACTOR)) {
        cs_darray_reallocate(darr, darr->cap * CS_DARRAY_LOAD_MULT);
    }

    cs_copy_memory(CS_DARRAY_OFFSET(darr), data, CS_DARRAY_SPACE_LEFT(darr),
                   darr->type->size);
    darr->len++;
}
