#include "cboxes/hash.h"

// Stoled from http://www.cse.yorku.ca/~oz/hash.html
uint64_t
cs_hash_lose_lose(const uint8_t *str) {
    uint64_t hash = 0;
    uint64_t ccc;

    while ((ccc = *str++)) {
        hash += ccc;
    }

    return hash;
}
