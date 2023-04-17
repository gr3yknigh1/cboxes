#include "cboxes/hash.h"

// Stoled from http://www.cse.yorku.ca/~oz/hash.html
u64 cs_LoseLoseHash(const byte *str) {
    u64 hash = 0;
    u64 ccc;

    while ((ccc = *str++)) {
        hash += ccc;
    }

    return hash;
}
