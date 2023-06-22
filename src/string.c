#include "cboxes/string.h"
#include "cboxes/assert.h"
#include "cboxes/memory.h"
#include <string.h>

cs_string_t *
cs_string_init(const char *src) {
    cs_string_t *string = malloc(sizeof(cs_string_t));
    *string = (cs_string_t){.data = NULL, .length = 0};
    cs_string_set(string, src);
    return string;
}

cs_string_t *
cs_string_init_0(const cs_string_t *src) {
    cs_string_t *string = malloc(sizeof(cs_string_t));
    *string = (cs_string_t){.data = NULL, .length = 0};
    cs_string_set_0(string, src);
    return string;
}

void
cs_string_set(cs_string_t *str, const char *other) {
    uint64_t new_len = strlen(other);

    if (new_len != str->length) {
        if (str->length != 0) {
            free(str->data);
        }
        str->data = malloc(new_len + 1);
    }
    str->length = new_len;

    CS_ASSERT(str->data != NULL, "");
    cs_copy_memory(str->data, other, new_len + 1, new_len);

    str->data[new_len] = '\0';
}

void
cs_string_set_0(cs_string_t *str, const cs_string_t *other) {
    if (other->length != str->length) {
        if (str->length != 0) {
            free(str->data);
        }
        str->data = malloc(other->length + 1);
    }
    str->length = other->length;

    CS_ASSERT(str->data != NULL, "");
    cs_copy_memory(str->data, other->data, str->length, other->length);
    str->data[other->length] = '\0';
}

void
cs_string_free(void *ptr) {
    cs_string_t *string = (cs_string_t *)ptr;
    free(string->data);
    free(ptr);
}
