#ifndef CBOXES_STRING_H_
#define CBOXES_STRING_H_

#include "cboxes/numtypes.h"
#include <memory.h>
#include <stdlib.h>

typedef const char *cstr;
typedef unsigned char byte;
typedef unsigned char *bytes;

typedef struct cs_String {
    char *data;
    u64 length;
} cs_String;

u64 cs_cstr_Length(cstr string);
cs_String *cs_String_New(cstr source);
cs_String *cs_String_NewC(cs_String *source);
void cs_String_Set(cs_String *str, cstr new);
void cs_String_SetC(cs_String *str, cs_String *otherStr);

void cs_String_Free(void *ptr);

#endif // CBOXES_STRING_H_
