#ifndef SHALLOW_H_
#define SHALLOW_H_

#include <stdlib.h>

void cs_ShallowCopy(void *dest, const void *src, size_t count);
void cs_ShallowFree(void *ptr);

#endif // SHALLOW_H_
