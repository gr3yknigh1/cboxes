#ifndef CBOXES_ASSERT_H_
#define CBOXES_ASSERT_H_

#include <stdio.h>
#include <stdlib.h>

// NOTE: Credits to them:
// <https://groups.google.com/forum/#!msg/comp.std.c/d-6Mj5Lko_s/5R6bMWTEbzQJ>
// NOTE: It only can handle from 0 to 62 arguments
#define __VA_NARG__(...)                                                       \
    (__VA_NARG_(_0 __VA_OPT__(, __VA_ARGS__), __RSEQ_N()) - 1)
#define __VA_NARG_(...) __VA_ARG_N(__VA_ARGS__)
#define __VA_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13,     \
                   _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, \
                   _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, \
                   _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, \
                   _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, \
                   _62, _63, N, ...)                                           \
    N

#define __RSEQ_N()                                                             \
    63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46,    \
        45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29,    \
        28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12,    \
        11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0

#define CS_EXPAND_MACRO(X) X
#define CS_STRINGIFY(X) #X

// NOTE Credits:
// <https://github.com/gpakosz/PPK_ASSERT/blob/833b8b7ea49aea540a49f07ad08bf0bae1faac32/src/ppk_assert.h#L88C1-L109C30>
#define CS_CUR_FILE __FILE__
#define CS_CUR_LINE __LINE__
#if defined(__GNUC__) || defined(__clang__)
#define CS_CUR_FUNCTION __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
#define CS_CUR_FUNCTION __FUNCSIG__
#elif defined(__SUNPRO_CC)
#define CS_CUR_FUNCTION __func__
#else
#define CS_CUR_FUNCTION __FUNCTION__
#endif

#if defined(_MSC_VER)
#define CS_FORCE_INLINE __forceinline
#elif defined(__GNUC__) || defined(__clang__)
#define CS_FORCE_INLINE inline __attribute__((always_inline))
#else
#define CS_FORCE_INLINE inline
#endif

#define CS_NO_MACRO

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
