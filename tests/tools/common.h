#include <stdlib.h>

int randInt(int min, int max) { return min + rand() % (max + 1 - min); }

int *generateArray(size_t length, int min, int max) {
    int *array = malloc(sizeof(int) * length);
    for (size_t i = 0; i < length; i++) {
        array[i] = randInt(min, max);
    }
    return array;
}

