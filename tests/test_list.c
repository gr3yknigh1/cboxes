#include <criterion/criterion.h>
#include <criterion/internal/assert.h>

#include "list.h"

void setup   (void) {}
void teardown(void) {}

TestSuite(test_list, .init=setup, .fini=teardown);

Test(test_list, List_Construct) {
    List* list = List_Construct();
    cr_expect(list != NULL, "List_Construct must return valid pointer to List");
    cr_expect(list->length == 0, "List_Construct must initialize empty List");
    cr_expect(list->head == NULL, "Head must be null");
    cr_expect(list->tail == NULL, "Tail must be null");
}

Test(test_list, List_PushBack) {
    List* list = List_Construct();

    const int expectedSize = 10;
    for (int i = 0; i < expectedSize; i++) {
        List_PushBack(list, &i, sizeof(int));
    }

    cr_expect(*(int*)list->head->value == 0, "Failed to push first element");
    cr_expect(*(int*)list->head->next->next->next->value == 3, "Failed to push 4th element");
    cr_expect(*(int*)list->tail->value == 9, "Failed to push last element");

    LNode* node = list->head;
    for (int i = 0; i < expectedSize; i++) {
        int pushedValue = *(int*)node->value;
        cr_expect(pushedValue == i, "kailed to push some item correctly");
        node = node->next;
    }
}

Test(test_list, List_Clear) {
    List* list = List_Construct();

    const int expected_size = 10;
    for (int i = 0; i < expected_size; i++) {
        List_PushBack(list, &i, sizeof(int));
    }

    List_Clear(list);

    cr_expect(list->length == 0, "Length must equal to 0 in empty List");
    cr_expect(list->head == NULL, "Head in empty list must be null");
    cr_expect(list->tail == NULL, "Tail in empty list must be null");
}

