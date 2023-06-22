#ifndef CBOXES_STRING_H_
#define CBOXES_STRING_H_

#include <stdint.h>
#include <stdlib.h>

typedef struct cs_string {
    char *data;
    uint64_t length;
} cs_string_t;

cs_string_t *cs_string_init(const char *str);
cs_string_t *cs_string_init_0(const cs_string_t *str);

void cs_string_set(cs_string_t *str, const char *new_str);
void cs_string_set_0(cs_string_t *str, const cs_string_t *other);

void cs_string_free(void *ptr);

#endif // CBOXES_STRING_H_
