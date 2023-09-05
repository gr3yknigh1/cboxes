#ifndef CCHECK_CCHECK_H_
#define CCHECK_CCHECK_H_

/*
 * TODO:
 *   - [ ] Add quite mode
 *   - [ ] .init and .fini for suite
 *   - [ ] .init and .fini for case
 * */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef void (*cc_proc_t)(void);

typedef enum {
    CC_NONE,
    CC_ERROR,
    CC_PASS,
} cc_test_case_status_t;

typedef struct {
    const char *expr;
    const char *file_path;
    unsigned long line_number;
} cc_assert_expr_info_t;

typedef struct {
    cc_proc_t init;
    cc_proc_t fini;

    const char *_name;
    cc_proc_t _run;
    cc_test_case_status_t _status;
    cc_assert_expr_info_t _last_expr_info;
} cc_test_case_t;

typedef struct {
    cc_proc_t init;
    cc_proc_t fini;

    const char *_name;
    cc_test_case_t *_cur_case;
} cc_test_suite_t;

static cc_test_suite_t CC_TEST_SUITE;

#define _SUITE CC_TEST_SUITE
#define _CUR_CASE CC_TEST_SUITE._cur_case
#define _CUR_EXPR_INFO CC_TEST_SUITE._cur_case->_last_expr_info
#define _CUR_STATUS CC_TEST_SUITE._cur_case->_status

#define _CALL_PROC_IF_NOT_NULL(PROC)                                           \
    if (PROC != NULL) {                                                        \
        PROC();                                                                \
    }

#define CC_TEST_CASE_MAX_COUNT 128
static cc_test_case_t *CC_TEST_CASES[CC_TEST_CASE_MAX_COUNT];
static unsigned long CC_TEST_CASE_COUNT = 0;

#define CC_PRE_MAIN_PROC(NAME)                                                 \
    void NAME(void) __attribute__((constructor));                              \
    void NAME(void)

#define _TEST_RUN_NAME(__TEST_NAME) _##__TEST_NAME##_run
#define _TEST_STRUCT_NAME(__TEST_NAME) _##__TEST_NAME

#define _TEST_STRUCT(__TEST_NAME)                                              \
    static cc_test_case_t _TEST_STRUCT_NAME(__TEST_NAME) =
#define _TEST_STRUCT_INIT(__TEST_NAME)                                         \
    CC_PRE_MAIN_PROC(__TEST_NAME) {                                            \
        CC_TEST_CASES[CC_TEST_CASE_COUNT] = &_TEST_STRUCT_NAME(__TEST_NAME);   \
        CC_TEST_CASE_COUNT++;                                                  \
    }

#define TEST(TEST_NAME)                                                        \
    void _TEST_RUN_NAME(TEST_NAME)(void);                                      \
    _TEST_STRUCT(TEST_NAME){                                                   \
        .init = NULL,                                                          \
        .fini = NULL,                                                          \
        ._name = #TEST_NAME,                                                   \
        ._run = _TEST_RUN_NAME(TEST_NAME),                                     \
        ._status = CC_NONE,                                                    \
    };                                                                         \
    _TEST_STRUCT_INIT(TEST_NAME)                                               \
    void _TEST_RUN_NAME(TEST_NAME)(void)

#define TEST_PACK(PACK_NAME)                                                   \
    int main(void) {                                                           \
        int return_code = EXIT_SUCCESS;                                        \
        for (unsigned long i = 0; i < CC_TEST_CASE_COUNT; ++i) {               \
            _CUR_CASE = CC_TEST_CASES[i];                                      \
            _CALL_PROC_IF_NOT_NULL(_CUR_CASE->init);                           \
            _CUR_CASE->_run();                                                 \
            if (_CUR_CASE->_status == CC_ERROR) {                              \
                printf("[%s::%s]: FAILED: '%s' in %s:%lu\n", #PACK_NAME,       \
                       _CUR_CASE->_name, _CUR_EXPR_INFO.expr,                  \
                       _CUR_EXPR_INFO.file_path, _CUR_EXPR_INFO.line_number);  \
                return_code = EXIT_FAILURE;                                    \
            }                                                                  \
            if (_CUR_STATUS == CC_PASS) {                                      \
                printf("[%s::%s]: PASS\n", #PACK_NAME, _CUR_CASE->_name);      \
            }                                                                  \
            if (_CUR_STATUS == CC_NONE) {                                      \
                printf("[%s::%s]: NONE\n", #PACK_NAME, _CUR_CASE->_name);      \
            }                                                                  \
            _CALL_PROC_IF_NOT_NULL(_CUR_CASE->fini);                           \
        }                                                                      \
        return return_code;                                                    \
    }                                                                          \
    static cc_test_suite_t _SUITE = {._name = #PACK_NAME}

#define _SET_EXPR_INFO(__OUT_PTR, __EXPR)                                      \
    *(__OUT_PTR) = (cc_assert_expr_info_t) {                                   \
        .expr = #__EXPR, .file_path = __FILE__, .line_number = __LINE__,       \
    }

#define _VALIDATE_EXPR(__OUT_STATUS, __EXPR)                                   \
    if ((__EXPR) != true) {                                                    \
        *(__OUT_STATUS) = CC_ERROR;                                            \
    } else {                                                                   \
        *(__OUT_STATUS) = CC_PASS;                                             \
    }

#define ASSERT(__EXPR)                                                         \
    do {                                                                       \
        _SET_EXPR_INFO(&_CUR_EXPR_INFO, __EXPR);                               \
        _VALIDATE_EXPR(&_CUR_STATUS, __EXPR);                                  \
    } while (0)

#endif // CCHECK_CCHECK_H_
