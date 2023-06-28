#include "cboxes/dynamic_array.h"
#include "cboxes/memory.h"

/*
 * Returns size of whole allocated buffer in bytes
 * */
size_t
cs_darray_get_buffer_size(const cs_darray_t *darr) {
    return darr->cap * darr->type->size;
}

bool
cs_darray_is_in_range(const cs_darray_t *darr, uint64_t index) {
    return index < darr->len;
}

/*
 * Returns a pointer were valid data ending
 * */
int8_t *
cs_darray_get_data_offset(const cs_darray_t *darr) {
    return (int8_t *)darr->data + (darr->len * darr->type->size);
}

/*
 * Returns amount of bytes that left in buffer
 * */
size_t
cs_darray_get_space_left(const cs_darray_t *darr) {
    return (darr->cap - darr->len) * darr->type->size;
}

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
    if (!cs_darray_is_in_range(darr, idx)) {
        return cs_INDEX_ERROR;
    }
    *out = ((int8_t *)darr->data) + idx * darr->type->size;
    return cs_OK;
}

cs_status_t
cs_darray_get_mut(const cs_darray_t *darr, uint64_t idx, void **out) {
    if (!cs_darray_is_in_range(darr, idx)) {
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

    cs_copy_memory(cs_darray_get_data_offset(darr), data,
                   cs_darray_get_space_left(darr), darr->type->size);
    darr->len++;
}
