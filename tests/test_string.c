#include "cboxes/string.h"
#include <criterion/criterion.h>
#include <stdlib.h>
#include <string.h>

TestSuite(test_string);

Test(test_string, cstr_Length_Normal) {
    const char *string = "Hi hi there!";
    const size_t expected_length = strlen(string);
    cr_assert(expected_length == cs_cstr_Length(string));
}

Test(test_string, cstr_Length_EmptyString) {
    const char *string = "";
    const size_t expected_length = 0;
    cr_assert(expected_length == cs_cstr_Length(string));
}

Test(test_string, String_New) {
    const char *source = "Hi hi there!";
    const size_t source_length = strlen(source);

    cs_String *string = cs_String_New(source);

    cr_assert(string->length == source_length, "String[%ld] != cstr[%ld]",
              string->length, source_length);
    for (size_t i = 0; i < source_length; i++) {
        cr_assert(source[i] == string->data[i]);
    }
}

Test(test_string, String_NewC) {
    const char *source = "Hi hi there!";
    cs_String *string = cs_String_New(source);
    cs_String *string1 = cs_String_NewC(string);

    cr_assert(string->length == string1->length, "String[%ld] != String1[%ld]",
              string->length, string1->length);
    for (size_t i = 0; i < string1->length; i++) {
        cr_assert(string->data[i] == string->data[i]);
    }
}
