#ifndef CBOXES_DYNAMIC_ARRAY_H_
#define CBOXES_DYNAMIC_ARRAY_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "cboxes/status.h"
#include "cboxes/type.h"

#define CS_DARRAY_LOAD_FACTOR 0.5
#define CS_DARRAY_LOAD_MULT 2

typedef struct {
    void *data;
    uint64_t length;
    uint64_t capacity;

    const cs_type_t *type;
} cs_dynamic_array_t;

/*
 * Returns size of whole allocated buffer in bytes
 * */
size_t
cs_dynamic_array_get_buffer_size(const cs_dynamic_array_t *dynamic_array);

bool cs_dynamic_array_is_in_range(const cs_dynamic_array_t *dynamic_array,
                                  uint64_t index);

/*
 * Returns a pointer were valid data ending
 * */
int8_t *
cs_dynamic_array_get_data_offset(const cs_dynamic_array_t *dynamic_array);

/*
 * Returns amount of bytes that left in buffer
 * */
size_t cs_dynamic_array_get_space_left(const cs_dynamic_array_t *dynamic_array);

void cs_dynamic_array_init(cs_dynamic_array_t *out_dynamic_array,
                           const cs_type_t *type);

cs_status_t cs_dynamic_array_get_item(const cs_dynamic_array_t *dynamic_array,
                                      uint64_t index, void const **out_item);
cs_status_t
cs_dynamic_array_get_mutable_item(const cs_dynamic_array_t *dynamic_array,
                                  uint64_t index, void **out_item);

void cs_dynamic_array_reallocate(cs_dynamic_array_t *dynamic_array,
                                 uint64_t new_capacity);

void cs_dynamic_array_push_back(cs_dynamic_array_t *dynamic_array, void *item_ptr);

#endif // CBOXES_DYNAMIC_ARRAY_H_
