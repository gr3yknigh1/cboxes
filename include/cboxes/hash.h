#ifndef CBOXES_HASH_H_
#define CBOXES_HASH_H_

#include <stdint.h>

#include "cboxes/string.h"

typedef uint64_t (*cs_hash_func_t)(const uint8_t *);

// Stoled from http://www.cse.yorku.ca/~oz/hash.html
uint64_t cs_hash_lose_lose(const uint8_t *str);

#endif // CBOXES_HASH_H_
