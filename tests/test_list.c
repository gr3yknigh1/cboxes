#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include <cboxes/list.h>
#include <cboxes/shallow.h>
#include <cboxes/type.h>

#include "cboxes/lnode.h"
#include "test_common.h"

// TODO(gr3yknigh1): Add tests for deep refed structs

const usize TEST_EXPECTED_LIST_SIZE = 32;

#define TEST_SHOULD_BE_OK(X)                                                   \
    do {                                                                       \
        cr_expect_eq((X), cs_OK);                                              \
    } while (0);

void testListShouldBeValid(cs_List *list) {
    cr_expect(list != NULL);
    cr_expect_eq(sizeof(*list), TEST_EXPECTED_LIST_SIZE);
}

void testListShouldBeEmpty(const cs_List *list) {
    cr_expect(list->head == NULL);
    cr_expect(list->tail == NULL);
    cr_expect(list->length == 0);
}

void testNodeShouldBeOrphan(const cs_LNode *node) {
    cr_expect_eq(node->next, NULL);
    cr_expect_eq(node->prev, NULL);
}

void init(void) {}
void fini(void) {}

TestSuite(test_list, .init = init, .fini = fini);

Test(test_list, List_New_ShouldCreateValidEmptyList) {
    cs_List *list = cs_List_New(CS_TYPE_I32);

    // NOTE: Should be valid
    cr_expect(list != NULL);
    cr_expect_eq(sizeof(*list), TEST_EXPECTED_LIST_SIZE);

    cr_expect_eq(list->type, CS_TYPE_I32);

    // NOTE: Should be empty
    cr_expect(list->head == NULL);
    cr_expect(list->tail == NULL);
    cr_expect(list->length == 0);

    cs_List_Free(list);
}

Test(test_list, List_PushBack_ShouldAdd_SingleShallowItem) {
    cs_List *numberList = cs_List_New(CS_TYPE_I32);

    int32_t numberToStore = randI32(0, 100);
    uint64_t expectedLength = 1;

    cs_List_PushBack(numberList, &numberToStore);

    cr_expect_eq(numberList->length, expectedLength);
    cr_expect_eq(numberList->head, numberList->tail);
    cr_expect_eq(CS_LNODE_GET(numberList->tail, int), numberToStore);

    // NOTE: Item should be copied
    cr_expect_neq(numberList->tail->value, &numberToStore);

    testNodeShouldBeOrphan(numberList->head);
    testNodeShouldBeOrphan(numberList->tail);

    cs_List_Free(numberList);
}

Test(test_list, List_PushBack_ShouldAdd_100ShallowItem) {
    cs_List *numbers = cs_List_New(CS_TYPE_I32);

    uint64_t expectedLength = 100;

    for (uint64_t i = 0; i < expectedLength; ++i) {
        int32_t number = randI32(0, 1000);
        cs_List_PushBack(numbers, &number);

        cs_LNode *node = numbers->tail;
        cr_expect_eq(CS_LNODE_GET(node, int32_t), number);
        cr_expect_neq(node->value, &number);
    }

    cr_expect_eq(numbers->length, expectedLength);
    cr_expect_neq(numbers->head, numbers->tail);


    cs_List_Free(numbers);
}

Test(test_list, List_PushFront_ShouldAddSingleShallowItem) {
    cs_List *list = cs_List_New(CS_TYPE_I32);

    int32_t storedNumber = 321;
    uint64_t expectedLength = 1;

    cs_List_PushFront(list, &storedNumber);

    cr_expect_eq(list->length, expectedLength);
    cr_expect_eq(list->head, list->tail);
    cr_expect_eq(CS_LNODE_GET(list->head, int), storedNumber);
    testDataShouldBeCopied(list->head->value, &storedNumber);

    testNodeShouldBeOrphan(list->head);
    testNodeShouldBeOrphan(list->tail);

    cs_List_Free(list);
}

Test(test_list, List_PushFront_ShouldAdd_100ShallowItem) {
    cs_List *numbers = cs_List_New(CS_TYPE_I32);

    uint64_t expectedLength = 100;

    for (uint64_t i = 0; i < expectedLength; ++i) {
        int32_t number = randI32(INT32_MIN, INT32_MAX);
        cs_List_PushFront(numbers, &number);

        cs_LNode *node = numbers->head;
        cr_expect_eq(CS_LNODE_GET(node, int32_t), number);
        testDataShouldBeCopied(node->value, &number);
    }

    cr_expect_eq(numbers->length, expectedLength);
    cr_expect_neq(numbers->head, numbers->tail);


    cs_List_Free(numbers);
}

// Test(test_list, List_Operations_PushFront) {
//     cs_List *list = cs_List_New(CS_TYPE_I32);
//
//     size_t sourceArrayLength = 10;
//     int *sourceArray = generateArray(sourceArrayLength, 0, 20);
//
//     for (size_t i = 0; i < sourceArrayLength; i++) {
//         cs_List_PushFront(list, sourceArray + i);
//     }
//
//     cr_assert(list->length == sourceArrayLength);
//
//     CS_LIST_FOREACH(list, int, i, storedValue, {
//         int *sourceValue = sourceArray - i + sourceArrayLength - 1;
//         cr_assert(sourceValue != storedValue);
//         cr_assert(*sourceValue == *storedValue);
//     });
//
//     cr_assert(list->head->prev == NULL);
//     cr_assert(list->tail->next == NULL);
//
//     cs_List_Free(list);
// }
//
// Test(test_list, List_DataAccess) {
//     cs_List *list = data.listI32;
//
//     for (u64 i = 0; i < list->length; i++) {
//         int *x = NULL;
//         testing_IS_OK(cs_List_Get(list, i, (void **)(&x)));
//         cr_assert(x != NULL);
//     }
//
//     int *x;
//     cs_Status status;
//     int indexes[3] = {-1, list->length, list->length + 1};
//
//     for (int i = 0; i < 3; i++) {
//         x = NULL;
//         status = CS_LIST_GET(list, indexes[i], x);
//         cr_assert(status == cs_INDEX_ERROR, "Tryed access '%d' index\n",
//                   indexes[i]);
//         cr_assert(x == NULL, "Tryed access '%d' index\n", indexes[i]);
//     }
// }
//
// Test(test_list, List_CopyEmptyPrimitiveList) {
//     cs_List *orig = cs_List_New(CS_TYPE_I32);
//     cs_List *copy = malloc(sizeof(cs_List));
//
//     cs_List_Copy(copy, orig, sizeof(cs_List));
//
//     cs_List_Free(orig);
// }
//
// void testing_CheckListInsertingAtIndex(cs_List *list, unsigned long index) {
//
//     int randNum = randInt(0, 10);
//
//     cs_Status status;
//     CS_LIST_INSERT(list, index, randNum, status);
//
//     cr_assert(status == cs_OK);
//
//     int *storedNum = NULL;
//     testing_IS_OK(CS_LIST_GET(list, index, storedNum));
//
//     cr_assert(*storedNum == randNum, "%lu %d %d", index, *storedNum, randNum);
// }
//
// Test(test_list, List_Inserting) {
//     cs_List *list = data.listI32;
//
//     int indexes[] = {0, list->length / 2, list->length - 1};
//
//     for (int i = 0; i < 3; i++) {
//         testing_CheckListInsertingAtIndex(list, indexes[i]);
//     }
// }
//
// void testing_CheckListNodeRefs(cs_List *list) {
//     CS_LIST_FOREACHN(list, i, n, {
//         if (i != 0)
//             cr_assert(n->prev != NULL);
//         if (i != list->length - 1)
//             cr_assert(n->next != NULL);
//     });
// }
//
// void testing_CheckListPopAtIndex(cs_List *list, unsigned long index) {
//     unsigned long lengthBefore = list->length;
//
//     int *valueFromGet = NULL;
//     CS_LIST_GET(list, index, valueFromGet);
//
//     int *valueFromPop = NULL;
//     cr_assert(cs_List_Pop(list, index, (void **)(&valueFromPop)) == cs_OK);
//
//     cr_assert(list->length == lengthBefore - 1);
//     cr_assert(valueFromGet == valueFromPop);
//     cr_assert(*valueFromGet == *valueFromPop);
// }
//
// Test(test_list, List_Deletion_Pop_First) {
//     cs_List *list = data.listI32;
//
//     testing_CheckListPopAtIndex(list, 0);
//     testing_CheckListNodeRefs(list);
// }
//
// Test(test_list, List_Deletion_Pop_Middle) {
//     cs_List *list = data.listI32;
//     testing_CheckListPopAtIndex(list, list->length / 2);
//     testing_CheckListNodeRefs(list);
// }
//
// Test(test_list, List_Deletion_Pop_Last) {
//     cs_List *list = data.listI32;
//     testing_CheckListPopAtIndex(list, list->length - 1);
//     testing_CheckListNodeRefs(list);
// }
//
// void testing_CheckListRemoveAtIndex(cs_List *list, unsigned long index) {
//
//     unsigned long lengthBefore = list->length;
//     int *itemBefore = NULL;
//     int *itemNext = NULL;
//
//     testing_IS_OK(CS_LIST_GET(list, index, itemBefore));
//
//     testing_IS_OK(CS_LIST_GET(
//         list, index == list->length - 1 ? list->length - 2 : index + 1,
//         itemNext));
//     testing_IS_OK(cs_List_Remove(list, index));
//
//     int *itemAfter = NULL;
//     testing_IS_OK(CS_LIST_GET(
//         list, index == list->length ? list->length - 1 : index, itemAfter));
//
//     cr_assert(list->length == lengthBefore - 1);
//     cr_assert(*itemAfter != *itemBefore);
//     cr_assert(itemAfter != itemBefore);
//
//     cr_assert(*itemAfter == *itemNext);
//     cr_assert(itemAfter == itemNext);
// }
//
// Test(test_list, List_Deletion_Remove_First) {
//     cs_List *list = data.listI32;
//     testing_CheckListRemoveAtIndex(list, 0);
//     testing_CheckListNodeRefs(list);
// }
//
// Test(test_list, List_Deletion_Remove_Middle) {
//     cs_List *list = data.listI32;
//     testing_CheckListRemoveAtIndex(list, list->length / 2);
//     testing_CheckListNodeRefs(list);
// }
//
// Test(test_list, List_Deletion_Remove_Last) {
//     cs_List *list = data.listI32;
//     testing_CheckListRemoveAtIndex(list, list->length - 1);
//     testing_CheckListNodeRefs(list);
// }
//
// Test(test_list, List_Deletion_Clear) {
//     cs_List *list = data.listI32;
//     cs_List_Clear(list);
//
//     cr_assert(list->length == 0);
//     cr_assert(list->head == NULL);
//     cr_assert(list->tail == NULL);
//
//     testing_CheckListNodeRefs(list);
// }
//
// Test(test_list, List_Free) {
//     cs_List *list = cs_List_New(CS_TYPE_I32);
//     cs_List_Free(list);
// }
//
// Test(test_list, List_FreeFull) {
//     cs_List *list = randI32List(10, 0, 20);
//     cs_List_Free(list);
// }
