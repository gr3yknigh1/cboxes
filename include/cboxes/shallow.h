#ifndef CBOXES_SHALLOW_H_
#define CBOXES_SHALLOW_H_

#include <stdlib.h>

void *cs_ShallowCopy(void *dest, const void *src, size_t count);
void cs_ShallowFree(void *ptr);

#endif // CBOXES_SHALLOW_H_
