#ifndef CCHECK_CCHECK_H_
#define CCHECK_CCHECK_H_

#include <stdbool.h>
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
    cc_proc_t _case;
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

#define CC_CALL_PROC_IF_NOT_NULL(PROC)                                         \
    if (PROC != NULL) {                                                        \
        PROC();                                                                \
    }

#define CC_TEST_CASE_MAX_COUNT 128
static cc_test_case_t *CC_TEST_CASES[CC_TEST_CASE_MAX_COUNT];
static unsigned long CC_TEST_CASE_COUNT = 0;

#define CC_PRE_MAIN_PROC(NAME)                                                 \
    void NAME(void) __attribute__((constructor));                              \
    void NAME(void)

#define CC_TEST_CASE(TEST_NAME)                                                \
    void TEST_CASE_##TEST_NAME##_RUN(void);                                    \
    static cc_test_case_t TEST_CASE_##TEST_NAME = (cc_test_case_t){            \
        .init = NULL,                                                          \
        .fini = NULL,                                                          \
        ._name = #TEST_NAME,                                                   \
        ._case = TEST_CASE_##TEST_NAME##_RUN,                                  \
        ._status = CC_NONE,                                                    \
    };                                                                         \
    CC_PRE_MAIN_PROC(TEST_NAME) {                                              \
        CC_TEST_CASES[CC_TEST_CASE_COUNT] = &TEST_CASE_##TEST_NAME;            \
        CC_TEST_CASE_COUNT++;                                                  \
    }                                                                          \
    void TEST_CASE_##TEST_NAME##_RUN(void)

#define CC_TEST_SUITE(SUITE_NAME)                                              \
    int main(void) {                                                           \
        int return_code = EXIT_SUCCESS;                                        \
        for (unsigned long i = 0; i < CC_TEST_CASE_COUNT; ++i) {               \
            CC_TEST_SUITE._cur_case = CC_TEST_CASES[i];                        \
            cc_test_case_t *cur_case = CC_TEST_SUITE._cur_case;                \
            CC_CALL_PROC_IF_NOT_NULL(cur_case->init);                          \
            cur_case->_case();                                                 \
            if (cur_case->_status == CC_ERROR) {                               \
                printf("[%s::%s]: FAILED: '%s' in %s:%lu\n", #SUITE_NAME,      \
                       cur_case->_name, cur_case->_last_expr_info.expr,        \
                       cur_case->_last_expr_info.file_path,                    \
                       cur_case->_last_expr_info.line_number);                 \
                return_code = EXIT_FAILURE;                                    \
            }                                                                  \
            if (cur_case->_status == CC_PASS) {                                \
                printf("[%s::%s]: PASS\n", #SUITE_NAME, cur_case->_name);      \
            }                                                                  \
            if (cur_case->_status == CC_NONE) {                                \
                printf("[%s::%s]: NONE\n", #SUITE_NAME, cur_case->_name);      \
            }                                                                  \
            CC_CALL_PROC_IF_NOT_NULL(cur_case->fini);                          \
        }                                                                      \
        return return_code;                                                    \
    }                                                                          \
    static cc_test_suite_t CC_TEST_SUITE = (cc_test_suite_t) {                 \
        ._name = #SUITE_NAME                                                   \
    }

#define ASSERT(EXPR)                                                           \
    do {                                                                       \
        CC_TEST_SUITE._cur_case->_last_expr_info = (cc_assert_expr_info_t){    \
            .expr = #EXPR,                                                     \
            .file_path = __FILE__,                                             \
            .line_number = __LINE__,                                           \
        };                                                                     \
        if ((EXPR) != true) {                                                  \
            CC_TEST_SUITE._cur_case->_status = CC_ERROR;                       \
        } else {                                                               \
            CC_TEST_SUITE._cur_case->_status = CC_PASS;                        \
        }                                                                      \
    } while (0)

#endif // CCHECK_CCHECK_H_
