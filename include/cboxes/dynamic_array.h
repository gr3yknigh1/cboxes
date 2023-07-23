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
    uint64_t item_count;
    uint64_t item_capacity;

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
 *
 * Example:
 *
 * `item_count` = 3
 * `item_size` = 2
 * `item_capacity` = 5
 *
 * 0A 3B FA __ __
 *          ^ - return pointer
 * */
int8_t *cs_dynamic_array_get_end(const cs_dynamic_array_t *dynamic_array);

/*
 * Returns amount of bytes that left in buffer
 * */
size_t cs_dynamic_array_get_space_left(const cs_dynamic_array_t *dynamic_array);

void cs_dynamic_array_init(cs_dynamic_array_t *out_dynamic_array,
                           const cs_type_t *type);

cs_status_t
cs_dynamic_array_get_item_ptr(const cs_dynamic_array_t *dynamic_array,
                              uint64_t index, void const **out_item);
cs_status_t
cs_dynamic_array_get_mutable_item_ptr(const cs_dynamic_array_t *dynamic_array,
                                      uint64_t index, void **out_item);

void cs_dynamic_array_reallocate(cs_dynamic_array_t *dynamic_array,
                                 uint64_t new_capacity);

void cs_dynamic_array_push_back(cs_dynamic_array_t *dynamic_array,
                                void *item_ptr);

void cs_dynamic_array_clear(cs_dynamic_array_t *dynamic_array);
void cs_dynamic_array_free(cs_dynamic_array_t *dynamic_array);

#endif // CBOXES_DYNAMIC_ARRAY_H_
