#include <criterion/criterion.h>
#include <stdlib.h>
#include <time.h>

#include "cboxes/list.h"
#include "cboxes/shallow.h"

void setup(void) { srand(time(NULL)); }

void teardown(void) {}

TestSuite(test_list, .init = setup, .fini = teardown);

int randInt(int min, int max) { return min + rand() % (max + 1 - min); }

int *generateArray(size_t length, int min, int max) {
    int *array = malloc(sizeof(int) * length);
    for (size_t i = 0; i < length; i++) {
        array[i] = randInt(min, max);
    }
    return array;
}

cs_List *generateList(size_t length, int min, int max) {
    cs_List *list = cs_List_NewD(sizeof(int));

    for (size_t i = 0; i < length; i++) {
        int randNum = randInt(min, max);
        cs_List_PushBack(list, &randNum);
    }

    return list;
}

Test(test_list, List_Creation_Full) {
    cs_Type type = {
        .isReference = false,
        .size = sizeof(int),
        .copy = cs_ShallowCopy,
        .free = cs_ShallowFree,
    };
    cs_List *list = cs_List_New(type);

    cr_assert(list != NULL);
    cr_assert(list->head == NULL);
    cr_assert(list->tail == NULL);
    cr_assert(list->length == 0);
    cr_assert(sizeof(*list) == 56);

    cs_List_Free(list);
}

Test(test_list, List_Creation_Default) {
    cs_List *list = cs_List_NewD(sizeof(int));

    cr_assert(list != NULL);
    cr_assert(list->head == NULL);
    cr_assert(list->tail == NULL);
    cr_assert(list->length == 0);
    cr_assert(sizeof(*list) == 56);

    cs_List_Free(list);
}

Test(test_list, List_Operations_PushBack) {
    cs_List *list = cs_List_NewD(sizeof(int));

    size_t sourceArrayLength = 10;
    int *sourceArray = generateArray(sourceArrayLength, 0, 20);

    for (size_t i = 0; i < sourceArrayLength; i++) {
        cs_List_PushBack(list, sourceArray + i);
    }

    cr_assert(list->length == sourceArrayLength);

    CS_LIST_FOREACH(list, int, i, storedValue, {
        int *sourceValue = sourceArray + i;
        cr_assert(sourceValue != storedValue);
        cr_assert(*sourceValue == *storedValue);
    });

    cr_assert(list->head->prev == NULL);
    cr_assert(list->tail->next == NULL);
}

Test(test_list, List_Operations_PushFront) {
    cs_List *list = cs_List_NewD(sizeof(int));

    size_t sourceArrayLength = 10;
    int *sourceArray = generateArray(sourceArrayLength, 0, 20);

    for (size_t i = 0; i < sourceArrayLength; i++) {
        cs_List_PushFront(list, sourceArray + i);
    }

    cr_assert(list->length == sourceArrayLength);

    CS_LIST_FOREACH(list, int, i, storedValue, {
        int *sourceValue = sourceArray - i + sourceArrayLength - 1;
        cr_assert(sourceValue != storedValue);
        cr_assert(*sourceValue == *storedValue);
    });

    cr_assert(list->head->prev == NULL);
    cr_assert(list->tail->next == NULL);
}

Test(test_list, List_Free) {
    cs_List *list = cs_List_NewD(sizeof(int));

    cs_List_Free(list);
}
