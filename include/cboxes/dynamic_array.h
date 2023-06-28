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
    uint64_t len;
    uint64_t cap;

    const cs_type_t *type;
} cs_darray_t;

size_t cs_darray_get_buffer_size(const cs_darray_t *darr);

bool cs_darray_is_in_range(const cs_darray_t *darr, uint64_t index);

int8_t *cs_darray_get_data_offset(const cs_darray_t *darr);

size_t cs_darray_get_space_left(const cs_darray_t *darr);

void cs_darray_init(cs_darray_t *out, const cs_type_t *type);

cs_status_t cs_darray_get(const cs_darray_t *darr, uint64_t idx,
                          void const **out);
cs_status_t cs_darray_get_mut(const cs_darray_t *darr, uint64_t idx,
                              void **out);

void cs_darray_reallocate(cs_darray_t *darr, uint64_t new_cap);

void cs_darray_push_back(cs_darray_t *darr, void *data);

#endif // CBOXES_DYNAMIC_ARRAY_H_
