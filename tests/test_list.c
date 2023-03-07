#include <criterion/criterion.h>
#include <stdlib.h>
#include <time.h>

#include "cboxes/list.h"
#include "cboxes/shallow.h"

#include "tools/common.h"

// TODO(gr3yknigh1): Add tests for deep refed structs

#define testing_IS_OK(expr, ...)                                               \
    do {                                                                       \
        cs_Status status = expr;                                               \
        cr_assert(status == cs_OK, "CS call != cs_OK; status == %d\n",         \
                  status __VA_OPT__(, ) __VA_ARGS__);                          \
    } while (0)

cs_List *generateList(size_t length, int min, int max) {
    cs_List *list = cs_List_New(CS_TYPE_I32);
    for (size_t i = 0; i < length; i++) {
        int randNum = randInt(min, max);
        cs_List_PushBack(list, &randNum);
    }
    return list;
}

struct {
    cs_List *intList;
} sdata;

void setup(void) {
    srand(time(NULL));
    sdata.intList = generateList(10, 0, 20);
}

void teardown(void) { cs_List_Free(sdata.intList); }

TestSuite(test_list, .init = setup, .fini = teardown);

Test(test_list, List_Creation_Full) {
    cs_List *list = cs_List_New(CS_TYPE_I32);

    cr_assert(list != NULL);
    cr_assert(list->head == NULL);
    cr_assert(list->tail == NULL);
    cr_assert(list->length == 0);
    cr_assert(sizeof(*list) == 32);

    cs_List_Free(list);
}

Test(test_list, List_Creation_Default) {
    cs_List *list = cs_List_New(CS_TYPE_I32);

    cr_assert(list != NULL);
    cr_assert(list->head == NULL);
    cr_assert(list->tail == NULL);
    cr_assert(list->length == 0);
    cr_assert(sizeof(*list) == 32);

    cs_List_Free(list);
}

Test(test_list, List_Operations_PushBack) {
    cs_List *list = cs_List_New(CS_TYPE_I32);

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

    cs_List_Free(list);
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

    cs_List_Free(list);
}

Test(test_list, List_DataAccess) {
    cs_List *list = sdata.intList;

    for (u64 i = 0; i < list->length; i++) {
        int *x = NULL;
        testing_IS_OK(cs_List_Get(list, i, (void **)(&x)));
        cr_assert(x != NULL);
    }

    int *x;
    cs_Status status;
    int indexes[3] = {-1, list->length, list->length + 1};

    for (int i = 0; i < 3; i++) {
        x = NULL;
        status = CS_LIST_GET(list, indexes[i], x);
        cr_assert(status == cs_INDEX_ERROR, "Tryed access '%d' index\n",
                  indexes[i]);
        cr_assert(x == NULL, "Tryed access '%d' index\n", indexes[i]);
    }
}

void testing_CheckListInsertingAtIndex(cs_List *list, unsigned long index) {

    int randNum = randInt(0, 10);

    cs_Status status;
    CS_LIST_INSERT(list, index, randNum, status);

    cr_assert(status == cs_OK);

    int *storedNum = NULL;
    testing_IS_OK(CS_LIST_GET(list, index, storedNum));

    cr_assert(*storedNum == randNum, "%lu %d %d", index, *storedNum, randNum);
}

Test(test_list, List_Inserting) {
    cs_List *list = sdata.intList;

    int indexes[] = {0, list->length / 2, list->length - 1};

    for (int i = 0; i < 3; i++) {
        testing_CheckListInsertingAtIndex(list, indexes[i]);
    }
}

void testing_CheckListNodeRefs(cs_List *list) {
    CS_LIST_FOREACHN(list, i, n, {
        if (i != 0)
            cr_assert(n->prev != NULL);
        if (i != list->length - 1)
            cr_assert(n->next != NULL);
    });
}

void testing_CheckListPopAtIndex(cs_List *list, unsigned long index) {
    unsigned long lengthBefore = list->length;

    int *valueFromGet = NULL;
    CS_LIST_GET(list, index, valueFromGet);

    int *valueFromPop = NULL;
    cr_assert(cs_List_Pop(list, index, (void **)(&valueFromPop)) == cs_OK);

    cr_assert(list->length == lengthBefore - 1);
    cr_assert(valueFromGet == valueFromPop);
    cr_assert(*valueFromGet == *valueFromPop);
}

Test(test_list, List_Deletion_Pop_First) {
    cs_List *list = sdata.intList;

    testing_CheckListPopAtIndex(list, 0);
    testing_CheckListNodeRefs(list);
}

Test(test_list, List_Deletion_Pop_Middle) {
    cs_List *list = sdata.intList;
    testing_CheckListPopAtIndex(list, list->length / 2);
    testing_CheckListNodeRefs(list);
}

Test(test_list, List_Deletion_Pop_Last) {
    cs_List *list = sdata.intList;
    testing_CheckListPopAtIndex(list, list->length - 1);
    testing_CheckListNodeRefs(list);
}

void testing_CheckListRemoveAtIndex(cs_List *list, unsigned long index) {

    unsigned long lengthBefore = list->length;
    int *itemBefore = NULL;
    int *itemNext = NULL;

    testing_IS_OK(CS_LIST_GET(list, index, itemBefore));

    testing_IS_OK(CS_LIST_GET(
        list, index == list->length - 1 ? list->length - 2 : index + 1,
        itemNext));
    testing_IS_OK(cs_List_Remove(list, index));

    int *itemAfter = NULL;
    testing_IS_OK(CS_LIST_GET(
        list, index == list->length ? list->length - 1 : index, itemAfter));

    cr_assert(list->length == lengthBefore - 1);
    cr_assert(*itemAfter != *itemBefore);
    cr_assert(itemAfter != itemBefore);

    cr_assert(*itemAfter == *itemNext);
    cr_assert(itemAfter == itemNext);
}

Test(test_list, List_Deletion_Remove_First) {
    cs_List *list = sdata.intList;
    testing_CheckListRemoveAtIndex(list, 0);
    testing_CheckListNodeRefs(list);
}

Test(test_list, List_Deletion_Remove_Middle) {
    cs_List *list = sdata.intList;
    testing_CheckListRemoveAtIndex(list, list->length / 2);
    testing_CheckListNodeRefs(list);
}

Test(test_list, List_Deletion_Remove_Last) {
    cs_List *list = sdata.intList;
    testing_CheckListRemoveAtIndex(list, list->length - 1);
    testing_CheckListNodeRefs(list);
}

Test(test_list, List_Deletion_Clear) {
    cs_List *list = sdata.intList;
    cs_List_Clear(list);

    cr_assert(list->length == 0);
    cr_assert(list->head == NULL);
    cr_assert(list->tail == NULL);

    testing_CheckListNodeRefs(list);
}

Test(test_list, List_Free) {
    cs_List *list = cs_List_NewD(sizeof(int));
    cs_List_Free(list);
}

Test(test_list, List_FreeFull) {
    cs_List *list = generateList(10, 0, 20);
    cs_List_Free(list);
}
