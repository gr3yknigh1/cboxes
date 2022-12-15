#include <criterion/criterion.h>
#include <criterion/internal/assert.h>

#include "list.h"

Test(test_list, List_Construct) {
    List* list = List_Construct();

    cr_expect(list != NULL, "List_Construct must return valid pointer to List");
    cr_expect(list->length == 0, "List_Construct must initialize empty List");
    cr_expect(list->head == NULL, "Head must be null");
    cr_expect(list->tail == NULL, "Tail must be null");
}

