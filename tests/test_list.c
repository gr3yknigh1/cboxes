#include <criterion/criterion.h>

#include "cboxes/list.h"

void init() {}
void fini() {}

TestSuite(List, .init = init, .fini = fini);
