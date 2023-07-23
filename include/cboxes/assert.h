#ifndef CBOXES_ASSERT_H_
#define CBOXES_ASSERT_H_

#include <stdio.h>
#include <stdlib.h>

#include "cboxes/def.h"


// TODO(gr3yknigh1): Move to separete header
#define CS_PRINT_IMPL(FD, ...) fprintf((FD)__VA_OPT__(, __VA_ARGS__))
#define CS_PRINT_ERROR(...) CS_PRINT_IMPL(stderr __VA_OPT__(, __VA_ARGS__))

#define CS_ASSERT_IMPL(EXPR, MESSAGE, ...)                                     \
    do {                                                                       \
        if (!(EXPR)) {                                                         \
            CS_PRINT_ERROR("AssertionError: '" CS_STRINGIFY(                   \
                EXPR) "'%s " CS_EXPAND_MACRO(MESSAGE)                          \
                               __VA_OPT__(, __VA_ARGS__));                     \
            exit(EXIT_FAILURE);                                                \
        }                                                                      \
    } while (0)

#define CS_ASSERT_WITHOUT_MESSAGE(EXPR) CS_ASSERT_IMPL(EXPR, "", "")
#define CS_ASSERT_WITH_MESSAGE(EXPR, MESSAGE)                                  \
    CS_ASSERT_IMPL(EXPR, MESSAGE, ": ")
#define CS_ASSERT_WITH_FMT_MESSAGE(EXPR, MESSAGE, ...)                         \
    CS_ASSERT_IMPL(EXPR, MESSAGE, ":", __VA_ARGS__)

#define CS_GET_ASSERT_MACRO_NAME(                                              \
    ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, ARG8, ARG9, ARG10, ARG11, ARG12, \
    ARG13, ARG14, ARG15, ARG16, ARG17, ARG18, ARG19, ARG20, ARG21, ARG22,      \
    ARG23, ARG24, ARG25, ARG26, ARG27, ARG28, ARG29, ARG30, ARG31, ARG32,      \
    ARG33, ARG34, ARG35, ARG36, ARG37, ARG38, ARG39, ARG40, ARG41, ARG42,      \
    ARG43, ARG44, ARG45, ARG46, ARG47, ARG48, ARG49, ARG50, ARG51, ARG52,      \
    ARG53, ARG54, ARG55, ARG56, ARG57, ARG58, ARG59, ARG60, ARG61, ARG62,      \
    ARG63, MACRO, ...)                                                         \
    MACRO

// TODO(gr3yknigh1): Replace it with more convinient way of expanding multiple
// arguments. Try reuse macros `__VA_NARG__`
#define CS_GET_ASSERT_MACRO(...)                                               \
    CS_EXPAND_MACRO(CS_GET_ASSERT_MACRO_NAME(                                  \
        __VA_ARGS__, CS_ASSERT_WITH_FMT_MESSAGE, CS_ASSERT_WITH_FMT_MESSAGE,   \
        CS_ASSERT_WITH_FMT_MESSAGE, CS_ASSERT_WITH_FMT_MESSAGE,                \
        CS_ASSERT_WITH_FMT_MESSAGE, CS_ASSERT_WITH_FMT_MESSAGE,                \
        CS_ASSERT_WITH_FMT_MESSAGE, CS_ASSERT_WITH_FMT_MESSAGE,                \
        CS_ASSERT_WITH_FMT_MESSAGE, CS_ASSERT_WITH_FMT_MESSAGE,                \
        CS_ASSERT_WITH_FMT_MESSAGE, CS_ASSERT_WITH_FMT_MESSAGE,                \
        CS_ASSERT_WITH_FMT_MESSAGE, CS_ASSERT_WITH_FMT_MESSAGE,                \
        CS_ASSERT_WITH_FMT_MESSAGE, CS_ASSERT_WITH_FMT_MESSAGE,                \
        CS_ASSERT_WITH_FMT_MESSAGE, CS_ASSERT_WITH_FMT_MESSAGE,                \
        CS_ASSERT_WITH_FMT_MESSAGE, CS_ASSERT_WITH_FMT_MESSAGE,                \
        CS_ASSERT_WITH_FMT_MESSAGE, CS_ASSERT_WITH_FMT_MESSAGE,                \
        CS_ASSERT_WITH_FMT_MESSAGE, CS_ASSERT_WITH_FMT_MESSAGE,                \
        CS_ASSERT_WITH_FMT_MESSAGE, CS_ASSERT_WITH_FMT_MESSAGE,                \
        CS_ASSERT_WITH_FMT_MESSAGE, CS_ASSERT_WITH_FMT_MESSAGE,                \
        CS_ASSERT_WITH_FMT_MESSAGE, CS_ASSERT_WITH_FMT_MESSAGE,                \
        CS_ASSERT_WITH_FMT_MESSAGE, CS_ASSERT_WITH_FMT_MESSAGE,                \
        CS_ASSERT_WITH_FMT_MESSAGE, CS_ASSERT_WITH_FMT_MESSAGE,                \
        CS_ASSERT_WITH_FMT_MESSAGE, CS_ASSERT_WITH_FMT_MESSAGE,                \
        CS_ASSERT_WITH_FMT_MESSAGE, CS_ASSERT_WITH_FMT_MESSAGE,                \
        CS_ASSERT_WITH_FMT_MESSAGE, CS_ASSERT_WITH_FMT_MESSAGE,                \
        CS_ASSERT_WITH_FMT_MESSAGE, CS_ASSERT_WITH_FMT_MESSAGE,                \
        CS_ASSERT_WITH_FMT_MESSAGE, CS_ASSERT_WITH_FMT_MESSAGE,                \
        CS_ASSERT_WITH_FMT_MESSAGE, CS_ASSERT_WITH_FMT_MESSAGE,                \
        CS_ASSERT_WITH_FMT_MESSAGE, CS_ASSERT_WITH_FMT_MESSAGE,                \
        CS_ASSERT_WITH_FMT_MESSAGE, CS_ASSERT_WITH_FMT_MESSAGE,                \
        CS_ASSERT_WITH_FMT_MESSAGE, CS_ASSERT_WITH_FMT_MESSAGE,                \
        CS_ASSERT_WITH_FMT_MESSAGE, CS_ASSERT_WITH_FMT_MESSAGE,                \
        CS_ASSERT_WITH_FMT_MESSAGE, CS_ASSERT_WITH_FMT_MESSAGE,                \
        CS_ASSERT_WITH_FMT_MESSAGE, CS_ASSERT_WITH_FMT_MESSAGE,                \
        CS_ASSERT_WITH_FMT_MESSAGE, CS_ASSERT_WITH_FMT_MESSAGE,                \
        CS_ASSERT_WITH_FMT_MESSAGE, CS_ASSERT_WITH_MESSAGE,                    \
        CS_ASSERT_WITHOUT_MESSAGE, , void))

#define CS_ASSERT(...)                                                         \
    CS_EXPAND_MACRO(CS_GET_ASSERT_MACRO(__VA_ARGS__))(__VA_ARGS__)

#endif // CBOXES_ASSERT_H_
