#include "cboxes/string.h"
#include <string.h>

u64 cs_cstr_Length(cstr string) {
    u64 length = 0;
    while (string[length] != '\0') {
        length++;
    }
    return length;
}

cs_String cs_String_New(cstr source) {
    cs_String string = {.data = NULL, .length = 0};
    cs_String_Set(string, source);
    return string;
}

cs_String cs_String_NewC(cs_String source) {
    cs_String string = {.data = NULL, .length = 0};
    cs_String_SetC(string, source);
    return string;
}

void cs_String_Set(cs_String str, cstr new) {
    u64 newLength = strlen(new);
    if (newLength != str.length) {
        if (str.length != 0)
            free(str.data);
        str.data = malloc(newLength + 1);
    }
    memcpy(str.data, new, newLength);
    str.data[newLength + 1] = '\0';
    str.length = newLength;
}

void cs_String_SetC(cs_String str, cs_String new) {
    if (new.length != str.length) {
        if (str.length != 0)
            free(str.data);
        str.data = malloc(new.length + 1);
    }
    memcpy(str.data, new.data, new.length);
    str.data[new.length + 1] = '\0';
    str.length = new.length;
}
