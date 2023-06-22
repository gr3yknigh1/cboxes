#ifndef CBOXES_SHALLOW_H_
#define CBOXES_SHALLOW_H_

#include <stdlib.h>

void *cs_shallow_copy(void *dest, const void *src, size_t count);
void cs_shallow_free(void *ptr);

#endif // CBOXES_SHALLOW_H_
