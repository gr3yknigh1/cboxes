#ifndef CBOXES_DARRAY_H_
#define CBOXES_DARRAY_H_

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

#define CS_DARRAY_DATA_SIZE(__DARR_PTR)                                        \
    ((__DARR_PTR)->cap * (__DARR_PTR)->type->size)

#define CS_DARRAY_IN_RANGE(__DARR_PTR, __IDX) ((__IDX) <= (__DARR_PTR)->len)

#define CS_DARRAY_OFFSET(__DARR_PTR)                                           \
    ((int8_t *)(__DARR_PTR)->data +                                            \
     ((__DARR_PTR)->len * (__DARR_PTR)->type->size))

#define CS_DARRAY_SPACE_LEFT(__DARR_PTR)                                       \
    (((__DARR_PTR)->cap - (__DARR_PTR)->len) * (__DARR_PTR)->type->size)

void cs_darray_init(cs_darray_t *out, const cs_type_t *type);

cs_status_t cs_darray_get(const cs_darray_t *darr, uint64_t idx,
                          void const **out);
cs_status_t cs_darray_get_mut(const cs_darray_t *darr, uint64_t idx,
                              void **out);

void cs_darray_reallocate(cs_darray_t *darr, uint64_t new_cap);

void cs_darray_push_back(cs_darray_t *darr, void *data);

#endif // CBOXES_DARRAY_H_
