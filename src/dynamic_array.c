#include "cboxes/dynamic_array.h"
#include "cboxes/assert.h"
#include "cboxes/memory.h"

size_t
cs_dynamic_array_get_buffer_size(const cs_dynamic_array_t *dynamic_array) {
    return dynamic_array->item_capacity * dynamic_array->type->size;
}

bool
cs_dynamic_array_is_in_range(const cs_dynamic_array_t *dynamic_array,
                             uint64_t index) {
    return index < dynamic_array->item_count;
}

int8_t *
cs_dynamic_array_get_end(const cs_dynamic_array_t *dynamic_array) {
    return (int8_t *)dynamic_array->data +
           (dynamic_array->item_count * dynamic_array->type->size);
}

size_t
cs_dynamic_array_get_space_left(const cs_dynamic_array_t *dynamic_array) {
    return (dynamic_array->item_capacity - dynamic_array->item_count) *
           dynamic_array->type->size;
}

void
cs_dynamic_array_init(cs_dynamic_array_t *out_dynamic_array,
                      const cs_type_t *type) {
    *out_dynamic_array = (cs_dynamic_array_t){
        .data = NULL,
        .item_count = 0,
        .item_capacity = 0,
        .type = type,
    };
}

#define CS_DYNAMIC_ARRAY_PTR_FROM_INDEX(ARRAY_PTR, INDEX)                      \
    (((int8_t *)(ARRAY_PTR)->data) + (INDEX) * (ARRAY_PTR)->type->size)

cs_status_t
cs_dynamic_array_get_item_ptr(const cs_dynamic_array_t *dynamic_array,
                              uint64_t index, void const **out_item) {
    if (!cs_dynamic_array_is_in_range(dynamic_array, index)) {
        return cs_INDEX_ERROR;
    }

    *out_item = CS_DYNAMIC_ARRAY_PTR_FROM_INDEX(dynamic_array, index);
    return cs_OK;
}

cs_status_t
cs_dynamic_array_get_mutable_item_ptr(const cs_dynamic_array_t *dynamic_array,
                                      uint64_t index, void **out_item) {
    if (!cs_dynamic_array_is_in_range(dynamic_array, index)) {
        return cs_INDEX_ERROR;
    }

    *out_item =
        ((int8_t *)dynamic_array->data) + index * dynamic_array->type->size;
    return cs_OK;
}

void
cs_dynamic_array_reallocate(cs_dynamic_array_t *dynamic_array,
                            uint64_t new_item_capacity) {
    size_t new_data_size = dynamic_array->type->size * new_item_capacity;
    void *new_data = malloc(new_data_size);

    if (dynamic_array->item_count != 0) {
        cs_copy_memory(new_data, dynamic_array->data, new_item_capacity,
                       cs_dynamic_array_get_buffer_size(dynamic_array));
    }

    if (dynamic_array->data != NULL) {
        free(dynamic_array->data);
    }

    dynamic_array->data = new_data;
    dynamic_array->item_capacity = new_item_capacity;

    CS_ASSERT(new_data != NULL);
}

void
cs_dynamic_array_push_back(cs_dynamic_array_t *dynamic_array, void *item_ptr) {
    if (dynamic_array->item_count >
        (uint64_t)(dynamic_array->item_capacity * CS_DARRAY_LOAD_FACTOR)) {
        cs_dynamic_array_reallocate(
            dynamic_array, dynamic_array->item_capacity * CS_DARRAY_LOAD_MULT);
    }

    cs_copy_memory(cs_dynamic_array_get_end(dynamic_array), item_ptr,
                   cs_dynamic_array_get_space_left(dynamic_array),
                   dynamic_array->type->size);
    dynamic_array->item_count++;
}

void
cs_dynamic_array_clear(cs_dynamic_array_t *dynamic_array) {
    dynamic_array->item_count = 0;
}

void
cs_dynamic_array_free(cs_dynamic_array_t *dynamic_array) {
    if (dynamic_array->type->is_ref) {
        // TODO: Replace with FOREACH macro
        for (uint64_t i = 0; i < dynamic_array->item_count; ++i) {
            void *item_ptr = CS_DYNAMIC_ARRAY_PTR_FROM_INDEX(dynamic_array, i);
            dynamic_array->type->free(item_ptr);
        }
    } else {
        free(dynamic_array->data);
        dynamic_array->data = NULL;
    }
    dynamic_array->item_capacity = 0;
    dynamic_array->item_count = 0;
}
