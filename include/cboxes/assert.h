#ifndef CBOXES_ASSERT_H_
#define CBOXES_ASSERT_H_

#include <stdio.h>
#include <stdlib.h>

#define CS_ASSERT(EXPR, ...)                                                   \
    do {                                                                       \
        if (!(EXPR)) {                                                         \
            fprintf(stderr,                                                    \
                    "AssertionError: %s:%i '" #EXPR                           \
                    "' expresion failed: "__VA_OPT__(__VA_ARGS__),             \
                    __FILE__, __LINE__);                                       \
            exit(1);                                                           \
        }                                                                      \
    } while (0)

#endif // CBOXES_ASSERT_H_
