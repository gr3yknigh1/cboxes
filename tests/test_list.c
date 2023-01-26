#include <criterion/criterion.h>
#include <criterion/internal/assert.h>

#include "cboxes/list.h"

void setup(void) {}
void teardown(void) {}

TestSuite(test_list, .init = setup, .fini = teardown);

Test(test_list, List_Construct) {
}

