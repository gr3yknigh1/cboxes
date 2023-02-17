#include <criterion/criterion.h>

void setup(void) {}
void teardown(void) {}

TestSuite(test_list, .init = setup, .fini = teardown);
