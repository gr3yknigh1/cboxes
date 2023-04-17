#include "cboxes/string.h"
#include "cboxes/assert.h"
#include "cboxes/memory.h"
#include <string.h>

u64 cs_cstr_Length(cstr string) {
    u64 length = 0;
    while (string[length] != '\0') {
        length++;
    }
    return length;
}

cs_String *cs_String_New(cstr source) {
    cs_String *string = malloc(sizeof(cs_String));
    *string = (cs_String){.data = NULL, .length = 0};
    cs_String_Set(string, source);
    return string;
}

cs_String *cs_String_NewC(cs_String *source) {
    cs_String *string = malloc(sizeof(cs_String));
    *string = (cs_String){.data = NULL, .length = 0};
    cs_String_SetC(string, source);
    return string;
}

void cs_String_Set(cs_String *str, cstr new) {
    u64 newLength = strlen(new);

    if (newLength != str->length) {
        if (str->length != 0) {
            free(str->data);
        }
        str->data = malloc(newLength + 1);
    }
    str->length = newLength;

    CS_ASSERT(str->data != NULL, "");
    cs_CopyMemory(str->data, new, newLength + 1, newLength);

    str->data[newLength] = '\0';
}

void cs_String_SetC(cs_String *str, cs_String *otherStr) {
    if (otherStr->length != str->length) {
        if (str->length != 0) {
            free(str->data);
        }
        str->data = malloc(otherStr->length + 1);
    }
    str->length = otherStr->length;

    CS_ASSERT(str->data != NULL, "");
    cs_CopyMemory(str->data, otherStr->data, str->length, otherStr->length);
    str->data[otherStr->length] = '\0';
}

void cs_String_Free(void *ptr) {
    cs_String *string = (cs_String *)ptr;
    free(string->data);
    free(ptr);
}
