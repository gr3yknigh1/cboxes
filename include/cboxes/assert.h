#ifndef ASSERT_H_
#define ASSERT_H_

#include <stdio.h>

#define CS_ASSERT(__X, ...)                                                    \
    do {                                                                       \
        if (!(__X)) {                                                          \
            fprintf(stderr, "AssertionError: " __VA_OPT__(__VA_ARGS__));       \
            exit(1);                                                           \
        }                                                                      \
    } while (0)

#endif // ASSERT_H_