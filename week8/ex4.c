// Copyright 2022 Zener
// Created by Zener on 24.10.22.
//

#include <stdlib.h>
#include <string.h>

size_t get_size(void *ptr) {
    size_t *in = ptr;
    if (in) {
        --in;
        return *in;
    }
    return -1;
}

void *my_realloc(void *ptr, size_t size) {
    void *new_ptr;

    if (ptr == NULL) {
        return malloc(size);
    }

    if (size == 0) {
        free(ptr);
        return new_ptr;
    }

    new_ptr = malloc(size);
    size_t old_size = get_size(ptr);

    if (size < old_size) {
        (char *) memcpy(new_ptr, ptr, size);
    } else {
        (char *) memcpy(new_ptr, ptr, old_size);
    }

    free(ptr);

    return new_ptr;
}
