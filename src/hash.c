#include "cboxes/hash.h"

// Stoled from http://www.cse.yorku.ca/~oz/hash.html
u64 cs_lose_lose_hash(const byte *str) {
    u64 hash = 0;
    i32 c;

    while ((c = *str++)) {
        hash += c;
    }

    return hash;
}
