#ifndef HASH_H_
#define HASH_H_

#include "cboxes/numtypes.h"
#include "cboxes/string.h"

typedef u64 (*cs_HashFunc)(const byte *);

// Stoled from http://www.cse.yorku.ca/~oz/hash.html
u64 cs_lose_lose_hash(const byte *str);

#endif // HASH_H_
