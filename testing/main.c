#include "cboxes/status.h"
#include <stdio.h>

#include <cboxes/dynamic_array.h>
#include <cboxes/type.h>


int
main(void) {
    cs_dynamic_array_t array = {0};
    cs_dynamic_array_init(&array, CS_TYPE_I32);


    for (uint64_t i = 0; i < 10; ++i) {
        cs_dynamic_array_push_back(&array, &i);
    }

    for (uint64_t i = 0; i < array.item_count; ++i) {
        printf("%i\n", *((int *)array.data + i));
        // int *out_ptr = NULL;
        // cs_status_t status = cs_dynamic_array_get_item_ptr(&array, i, (const void **)(&out_ptr));
        // if (status != cs_OK) {
        //     fprintf(stderr, "Error during item retriving from dynamic array. Status: %i\n", status);
        //     return 1;
        // }
        // printf("%i\n", *out_ptr);
    }

    cs_dynamic_array_free(&array);

    return 0;
}
