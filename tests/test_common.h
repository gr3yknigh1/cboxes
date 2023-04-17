#include <stdint.h>
#include <stdlib.h>

#include <cboxes/list.h>
#include <cboxes/type.h>

typedef struct PlainStruct {
    int decimal;
    float floatingPoint;
} PlainStruct;

DEFINE_CS_TYPE(PLAINSTRUCT_TYPE);
INIT_PRIMITIVE_CS_TYPE(PLAINSTRUCT_TYPE, PlainStruct);

#define DEEP_STRUCT_ARRAY_SIZE 10

typedef struct DeepStruct {
    long number;
    PlainStruct *plainStruct;
    double array[DEEP_STRUCT_ARRAY_SIZE];
} DeepStruct;

int32_t randI32(int32_t min, int32_t max) {
    return min + rand() % (max + 1 - min);
}

int32_t *randI32Array(const size_t length, int32_t min, int32_t max) {
    int32_t *array = malloc(sizeof(int32_t) * length);
    for (size_t i = 0; i < length; i++) {
        array[i] = randI32(min, max);
    }
    return array;
}

uint64_t randU64(uint64_t min, uint64_t max) {
    return min + (uint64_t)rand() % (max + 1 - min);
}

#define ASCII_CHAR_START 33
#define ASCII_CHAR_END 126

char randChar(void) { return (char)randI32(ASCII_CHAR_START, ASCII_CHAR_END); }

const char *randStr(uint64_t min, uint64_t max) {
    size_t size = randU64(min, max);
    char *string = malloc(size);
    for (size_t i = 0; i < size; i++) {
        string[i] = randChar();
    }
    return string;
}

cs_List *randI32List(const size_t length, int32_t min, int32_t max) {
    cs_List *list = cs_List_New(CS_TYPE_I32);
    for (size_t i = 0; i < length; i++) {
        int randNum = randI32(min, max);
        cs_List_PushBack(list, &randNum);
    }
    return list;
}
