#ifndef PAIR_H_
#define PAIR_H_

#include "cboxes/string.h"

typedef struct cs_Pair {
    cstr key;
    void *value;
} cs_Pair;

#endif // PAIR_H_
