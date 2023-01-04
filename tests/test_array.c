#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "cboxes/darray.h"


Test(test_darray, DArray_Construct) {
    DArray* arr = DArray_Construct();

    cr_expect(arr != NULL);
    cr_expect(arr->items == NULL);
    cr_expect(arr->itemSize == 0);
    cr_expect(arr->length == 0);
}

Test(test_darray, DArray_ConstructC) {
    int nums[10] = {0};

    DArray* array = DArray_ConstructC(nums, sizeof(int), 10);

    cr_expect(nums != NULL);
    cr_expect(array != NULL);
    cr_expect(array->items != NULL);
    cr_expect(array->itemSize == sizeof(int));
    cr_expect(array->length == 10);

    for (unsigned long i = 0; i < 10; i++) {
        if (nums[i] != ((int*)array->items)[i]) {
            cr_fail(
                "Numbers in source doesn't match dest: %d & %d",
                nums[i],
                ((int*)array->items)[i]
            );
            break;
        }
    }
}

Test(test_darray, DArray_ConstructF) {
    int numbers[10] = {0};
    DArray* array = DArray_ConstructC(numbers, sizeof(int), 10);
    array = DArray_ConstructF(array);

    cr_expect(numbers != NULL);
    cr_expect(array != NULL);
    cr_expect(array->items != NULL);
    cr_expect(array->itemSize == sizeof(int));
    cr_expect(array->length == 10);

    for (unsigned long i = 0; i < 10; i++) {
        if (numbers[i] != ((int*)array->items)[i]) {
            cr_fail(
                "Numbers in source doesn't match dest: %d & %d",
                numbers[i],
                ((int*)array->items)[i]
            );
            break;
        }
    }
}
