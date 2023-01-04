#ifndef ERROR_H
#define ERROR_H

#include "cboxes/types.h"

enum cboxes_ErrorCode {
    cboxes_Ok,
    cboxes_IndexError,
};

const char* cboxes_Error_GetErrorString(enum cboxes_ErrorCode code);

#endif // ERROR_H
