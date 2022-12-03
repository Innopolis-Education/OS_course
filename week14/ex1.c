// Copyright 2022 Zener
// Created by Zener on 12/2/2022.
//

#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    int size;
    int *resources;
} Vector;

typedef struct {
    int size;
    int length;
    int **resources;
} Matrix;


void get_vector(const FILE *input, Vector vector) {
    char *nums;
}


int main() {
    Vector E, A;
    Matrix C, R;

    FILE *input = fopen("input_dl.txt", O_RDONLY);

    return 0;
}
