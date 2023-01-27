#include <criterion/criterion.h>
#include <criterion/internal/assert.h>

#include "cboxes/list.h"

void setup(void) {}
void teardown(void) {}

TestSuite(test_list, .init = setup, .fini = teardown);

// TODO: Check head and tail values
Test(test_list, List_Basic) {
    cs_List *list = cs_List_NewD(sizeof(int));

    for (int i = 0; i < 9; i++) {
        cs_List_PushBack(list, &i);
    }

    cs_LNode *cur = list->head;
    u32 idx = 0;
    while (cur != NULL) {
        cr_assert(*(int *)cur->value == idx);

        cur = cur->next;
        idx++;
    }

    cs_List_PushBack(list, NULL);

    int *x = NULL;
    cr_assert(CS_LIST_GET(list, 1, &x) == cs_OK);
    cr_assert(*x == 1);
}
