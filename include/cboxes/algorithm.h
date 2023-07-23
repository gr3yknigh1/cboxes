#ifndef CBOXES_ALGORITHM_H_
#define CBOXES_ALGORITHM_H_

#include <stdbool.h>

#include "cboxes/memory.h"

typedef bool (*cs_is_greater_t)(void *, void *);

void cs_swap(void *restrict a, void *b, size_t size);

#endif // CBOXES_ALGORITHM_H_
