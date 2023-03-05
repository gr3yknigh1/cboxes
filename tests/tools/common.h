#include <stdlib.h>
#include <stdint.h>

int randInt(int min, int max) { return min + rand() % (max + 1 - min); }

int *generateArray(size_t length, int min, int max) {
    int *array = malloc(sizeof(int) * length);
    for (size_t i = 0; i < length; i++) {
        array[i] = randInt(min, max);
    }
    return array;
}

char randChar() {
    return randInt(33, 126);
}

const char *randStr(uint64_t min, uint64_t max) {
    size_t size = randInt(min, max);
    char *string = malloc(size);
    for (size_t i = 0; i < size; i++) {
        string[i] = randChar();
    }
    return string;
}


