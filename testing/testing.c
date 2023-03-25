#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include "cboxes/assert.h"
#include "cboxes/list.h"

#define LOG(X, ...) printf(">>> " X __VA_OPT__(, __VA_ARGS__))

#define CS_LIST_PUSHBACK_LVALUE(__list, value)                                 \
    do {                                                                       \
        cs_List_PushBack(__list, &value);                                      \
    } while (0)

#define BENCHMARK_FUNC(__name, __func, __expr, __times, __fini)                \
    do {                                                                       \
        double totalTime = 0;                                                  \
        uint64_t times = __times;                                              \
        for (uint64_t i = 0; i < __times; i++) {                               \
            float startTime = (float)clock() / CLOCKS_PER_SEC;                 \
            __expr;                                                            \
            float endTime = (float)clock() / CLOCKS_PER_SEC;                   \
            totalTime += endTime - startTime;                                  \
            __fini                                                             \
        }                                                                      \
        LOG("%s() [%s] :: seconds: %f  times: %ld  aver: %.10lf\n", #__func,   \
            __name, totalTime, times, totalTime / times);                      \
    } while (0)

uint64_t randU64(uint64_t min, uint64_t max) {
    return min + rand() % (max - min + 1);
}

int32_t randI32(int32_t min, int32_t max) {
    return min + rand() % (max - min + 1);
}

cs_List *randListI32(uint32_t min, uint32_t max, uint64_t length) {
    cs_List *list = cs_List_New(CS_TYPE_I32);
    for (uint64_t i = 0; i < length; i++) {
        int32_t value = randI32(min, max);
        cs_List_PushBack(list, &value);
    }
    return list;
}

size_t cs_List_GetSize(const cs_List *list) {
    size_t totalSize = sizeof(cs_List);
    totalSize += sizeof(cs_Type);
    totalSize += sizeof(cs_LNode) * list->length;
    totalSize += list->type->size * list->length;
    return totalSize;
}

#define TIMES 10000

void benchmark_cs_List_New(void) {
    cs_List *list = NULL;
    BENCHMARK_FUNC("I32 EMPTY", cs_List_New, list = cs_List_New(CS_TYPE_I32),
                   TIMES, { cs_List_Free(list); });
}

void benchmark_cs_List_PushBack(void) {
    cs_List *list = cs_List_New(CS_TYPE_I32);
    int value = 10;
    BENCHMARK_FUNC("I32 FILL", cs_List_PushBack, cs_List_PushBack(list, &value),
                   TIMES, {});
    cs_List_Free(list);
}

#define CS_ASSERT_IS_OK(X) CS_ASSERT((X) == cs_OK, "")

void benchmark_cs_List_Remove(void) {
    cs_List *list = NULL;
    uint64_t index = 0;

    list = randListI32(0, TIMES, TIMES);
    index = 0;
    BENCHMARK_FUNC("I32 AT IDX 0", cs_List_Remove,
                   CS_ASSERT_IS_OK(cs_List_Remove(list, index)), TIMES, {});
    cs_List_Free(list);

    list = randListI32(0, TIMES, TIMES);
    index = list->length - 1;
    BENCHMARK_FUNC("I32 AT IDX -1", cs_List_Remove,
                   CS_ASSERT_IS_OK(cs_List_Remove(list, index)), TIMES,
                   { index = list->length - 1; });
    cs_List_Free(list);

    list = randListI32(0, TIMES, TIMES);
    index = randU64(1, list->length - 1);
    BENCHMARK_FUNC("I32 AT IDX MID", cs_List_Remove,
                   CS_ASSERT_IS_OK(cs_List_Remove(list, index)), TIMES, {
                       index =
                           list->length <= 2 ? 0 : randU64(1, list->length - 1);
                   });
    cs_List_Free(list);
}

int main(void) {
    srand(time(NULL));

    benchmark_cs_List_New();
    benchmark_cs_List_PushBack();
    benchmark_cs_List_Remove();
    return 0;
}
