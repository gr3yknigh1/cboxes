#ifndef CBOXES_HASH_H_
#define CBOXES_HASH_H_

#include "cboxes/numtypes.h"
#include "cboxes/string.h"

typedef u64 (*cs_HashFunc)(const byte *);

// Stoled from http://www.cse.yorku.ca/~oz/hash.html
u64 cs_LoseLoseHash(const byte *str);

#endif // CBOXES_HASH_H_
