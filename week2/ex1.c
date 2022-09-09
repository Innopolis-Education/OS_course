// Copyright Zener 2022
// Created by Zener on 07.09.22.
//

#include <limits.h>
#include <float.h>
#include <stdio.h>

int main() {
    int first = INT_MAX;
    unsigned short second = USHRT_MAX;
    long third = LONG_MAX;
    float fourth = FLT_MAX;
    double fifth = DBL_MAX;

    printf("Maximum of integer: %d, size: %lu\n", first, sizeof(first));
    printf("Maximum of unsigned short integer: %d, size: %lu\n", second, sizeof(second));
    printf("Maximum of long integer: %ld, size: %lu\n", third, sizeof(third));
    printf("Maximum of float: %.1f, size: %lu\n", fourth, sizeof(fourth));
    printf("Maximum of double: %.1f, size: %lu\n", fifth, sizeof(fifth));

    return 0;
}
