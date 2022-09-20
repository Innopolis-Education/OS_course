// Copyright 2022 Zener
// Created by Zener on 9/18/2022.
//

#include <stdio.h>
#include <stdlib.h>


void *aggregate(void *base, size_t size, int n, void *initial_value, void *(*opr)(const void *, const void *));

void *addInt(const void *a, const void *b) {
    int result = *(int *) a + *(int *) b;
    return &result;
}

void *addDouble(const void *a, const void *b) {
    double result = *(double *) a + *(double *) b;
    return &result;
}

void *mulInt(const void *a, const void *b) {
    int result = *(int *) a * *(int *) b;
    return &result;
}

void *mulDouble(const void *a, const void *b) {
    double result = *(double *) a * *(double *) b;
    return &result;
}

void *meanInt(const void *a, const void *b) {
    int result = (*(int *) a + *(int *) b) / 2;
    return &result;
}

void *meanDouble(const void *a, const void *b) {
    double result = (*(double *) a + *(double *) b) / 2;
    return &result;
}

void *aggregate(void *base, size_t size, int n, void *initial_value, void *(*opr)(const void *, const void *)) {
    if (n < 2) return NULL;

    void *output;

    if (size == sizeof(int)) { // base is a pointer to an integer

        output = (int *) opr(&base[0], &base[1]);

    } else { // base is a pointer to a double

        output = (double *) opr(&base[0], &base[1]);

    }

    return output;
}


int main() {

    int *ints = malloc(sizeof(int) * 5);
    double *doubles = malloc(sizeof(double) * 5);

    for (int i = 1; i <= 5; i++)
        ints[i - 1] = i;
    for (int i = 1; i <= 5; i++)
        doubles[i - 1] = i;


    // Addition

    int *result1a;

    result1a = aggregate(ints, sizeof(ints[0]), 5, 0, addInt);

    printf("%d\n", *result1a);

    double *result2a;

    result2a = aggregate(doubles, sizeof(doubles[0]), 5, 1, addDouble);

    printf("%f\n", *result2a);


    // Multiplication

    int *result1m;

    result1m = aggregate(ints, sizeof(ints[0]), 5, 0, mulInt);

    printf("%d\n", *result1m);

    double *result2m;

    result2m = aggregate(doubles, sizeof(doubles[0]), 5, 1, mulDouble);

    printf("%f\n", *result2m);



    // Mean

    int *result1mean;

    result1mean = aggregate(ints, sizeof(ints[0]), 5, 0, meanInt);

    printf("%d\n", *result1mean);

    double *result2mean;

    result2mean = aggregate(doubles, sizeof(doubles[0]), 5, 1, meanDouble);

    printf("%f\n", *result2mean);


    // free the pointers
    free(ints);
    free(doubles);
    free(result1a);
    free(result1m);
    free(result1mean);
    free(result2a);
    free(result2m);
    free(result2mean);

    return EXIT_SUCCESS;
}
