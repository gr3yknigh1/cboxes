#include "cboxes/dynamic_array.h"
#include "cboxes/memory.h"

size_t
cs_dynamic_array_get_buffer_size(const cs_dynamic_array_t *dynamic_array) {
    return dynamic_array->capacity * dynamic_array->type->size;
}

bool
cs_dynamic_array_is_in_range(const cs_dynamic_array_t *dynamic_array,
                             uint64_t index) {
    return index < dynamic_array->length;
}

int8_t *
cs_dynamic_array_get_data_offset(const cs_dynamic_array_t *dynamic_array) {
    return (int8_t *)dynamic_array->buffer +
           (dynamic_array->length * dynamic_array->type->size);
}

size_t
cs_dynamic_array_get_space_left(const cs_dynamic_array_t *dynamic_array) {
    return (dynamic_array->capacity - dynamic_array->length) *
           dynamic_array->type->size;
}

void
cs_dynamic_array_init(cs_dynamic_array_t *out_dynamic_array,
                      const cs_type_t *type) {
    *out_dynamic_array = (cs_dynamic_array_t){
        .buffer = NULL,
        .length = 0,
        .capacity = 0,
        .type = type,
    };
}

cs_status_t
cs_dynamic_array_get_item(const cs_dynamic_array_t *dynamic_array,
                          uint64_t index, void const **out_item) {
    if (!cs_dynamic_array_is_in_range(dynamic_array, index)) {
        return cs_INDEX_ERROR;
    }
    *out_item =
        ((int8_t *)dynamic_array->buffer) + index * dynamic_array->type->size;
    return cs_OK;
}

cs_status_t
cs_dynamic_array_get_mutable_item(const cs_dynamic_array_t *dynamic_array,
                                  uint64_t index, void **out_item) {
    if (!cs_dynamic_array_is_in_range(dynamic_array, index)) {
        return cs_INDEX_ERROR;
    }
    *out_item =
        ((int8_t *)dynamic_array->buffer) + index * dynamic_array->type->size;
    return cs_OK;
}

void
cs_dynamic_array_reallocate(cs_dynamic_array_t *dynamic_array,
                            uint64_t new_capacity) {
    void *new_data = malloc(dynamic_array->type->size * new_capacity);

    if (dynamic_array->length != 0) {
        cs_copy_memory(new_data, dynamic_array->buffer, new_capacity,
                       dynamic_array->length);
    }

    if (dynamic_array->buffer != NULL) {
        free(dynamic_array->buffer);
    }

    dynamic_array->buffer = new_data;
    dynamic_array->capacity = new_capacity;
}

void
cs_dynamic_array_push_back(cs_dynamic_array_t *dynamic_array, void *item_ptr) {
    if (dynamic_array->length >
        (uint64_t)(dynamic_array->capacity * CS_DARRAY_LOAD_FACTOR)) {
        cs_dynamic_array_reallocate(dynamic_array, dynamic_array->capacity *
                                                       CS_DARRAY_LOAD_MULT);
    }

    cs_copy_memory(cs_dynamic_array_get_data_offset(dynamic_array), item_ptr,
                   cs_dynamic_array_get_space_left(dynamic_array),
                   dynamic_array->type->size);
    dynamic_array->length++;
}
