#include <stdlib.h>
#include <stdint.h>

#include <cboxes/list.h>
#include <cboxes/type.h>

typedef struct PlainStruct {
    int decimal;
    float floatingPoint;
} PlainStruct;

DEFINE_CS_TYPE(PLAINSTRUCT_TYPE);
INIT_PRIMITIVE_CS_TYPE(PLAINSTRUCT_TYPE, PlainStruct);

typedef struct DeepStruct {
    long number;
    PlainStruct *plainStruct;
    double array[10];
} DeepStruct;

int32_t randI32(int32_t min, int32_t max) { return min + rand() % (max + 1 - min); }

int32_t *randI32Array(size_t length, int32_t min, int32_t max) {
    int32_t *array = malloc(sizeof(int32_t) * length);
    for (size_t i = 0; i < length; i++) {
        array[i] = randI32(min, max);
    }
    return array;
}

char randChar(void) {
    return randI32(33, 126);
}

const char *randStr(uint64_t min, uint64_t max) {
    size_t size = randI32(min, max);
    char *string = malloc(size);
    for (size_t i = 0; i < size; i++) {
        string[i] = randChar();
    }
    return string;
}

cs_List *randI32List(size_t length, int min, int max) {
    cs_List *list = cs_List_New(CS_TYPE_I32);
    for (size_t i = 0; i < length; i++) {
        int randNum = randI32(min, max);
        cs_List_PushBack(list, &randNum);
    }
    return list;
}

