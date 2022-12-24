#include <criterion/criterion.h>
#include <criterion/internal/assert.h>

#include "darray.h"

Test(test_darray, DArray_Construct) {
    DArray* arr = DArray_Construct();

    cr_expect(arr != NULL);
    cr_expect(arr->items == NULL);
    cr_expect(arr->itemSize == 0);
    cr_expect(arr->length == 0);
}

Test(test_darray, DArray_ConstructC) {
}

