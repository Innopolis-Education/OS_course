// Copyright 2022 Zener
// Created by Zener on 12/2/2022.
//

#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>

#define FILE_PATH "/home/zener085/CLionProjects/OS_course/week14/input_ok.txt"

/**
 * Vector of available or existent resources
 */
typedef struct {
    size_t size;
    int *resources;
} Vector;

/**
 * Add number of existent or available resources to the vector
 * @param vector vector itself
 * @param elem number of the recourse
 */
void add_num(Vector *vector, int elem) {
    if (!vector->size) {
        vector->resources = malloc(sizeof(int));
    } else {
        vector->resources = realloc(vector->resources, (vector->size + 1) * sizeof(int));
    }
    vector->resources[vector->size++] = elem;
}

/**
 * free all memory taken for vector
 * @param vector vector itself
 */
void free_vector(Vector *vector) {
    if (vector->size) {
        free(vector->resources);
        vector->size = 0;
    }
}

/**
 * Matrix of current or requested resources for all processes
 */
typedef struct {
    size_t size;
    size_t length;
    int **resources;
} Matrix;

/**
 * add description for 1 process to the matrix
 * @param line all resources for 1 process
 * @param matrix matrix itself
 */
void add_row(char *line, Matrix *matrix) {
    if (!matrix->size) {
        matrix->resources = malloc(sizeof(int) * matrix->length);
        int row[matrix->length];
        matrix->resources[0] = row;
    } else {
        matrix->resources = realloc(matrix->resources, sizeof(int) * matrix->length * (matrix->size + 1));
        int row[matrix->length];
        matrix->resources[matrix->size] = row;
    }
    char *str_num = strtok(line, " ");
    for (int i = 0; i < matrix->length; ++i) {
        matrix->resources[matrix->size][i] = atoi(str_num);
        str_num = strtok(NULL, " ");
    }

    matrix->size++;
}

/**
 * free all memory taken for matrix
 * @param matrix matrix itself
 */
void free_matrix(Matrix *matrix) {
    if (matrix->size) {
        free(matrix->resources);
        matrix->size = 0;
    }
}

/**
 * add resources for the vector
 * @param input input file
 * @param vector vector itself
 */
void add_vector(FILE *input, Vector *vector) {
    char *nums;
    size_t len;

    getline(&nums, &len, input);

    char *str_num = strtok(nums, " ");

    while (str_num != NULL) {
        add_num(vector, atoi(str_num));
        str_num = strtok(NULL, " ");
    }
}

/**
 * add all resources for 1 matrix
 * @param input input file
 * @param matrix matrix itself
 */
void get_matrix(FILE *input, Matrix *matrix) {
    char *nums;
    size_t len;

    getline(&nums, &len, input);

    while (strcmp(nums, "0")) {
        if (strcmp(nums, "\n") == 0) {
            break;
        }
        add_row(nums, matrix);
        getline(&nums, &len, input);
    }
}

/**
 * skip empty line in the input file
 * @param input input file
 */
void skip_line(FILE *input) {
    char *null_line;
    size_t len_null_line;

    getline(&null_line, &len_null_line, input);
}

/**
 * detect deadlock
 * @param E existent resources' vector
 * @param A available resources' vector
 * @param C current matrix
 * @param R request matrix
 */
void detect(Vector *E, Vector *A, Matrix *C, Matrix *R) {
    int c, temp, n = C->size, r = C->length, i, j, flag = 1, k, c1 = 0;
    int finish[n], dead[n], safe[n];

    for (i = 0; i < n; i++) {
        finish[i] = 0;
    }

    while (flag) {
        flag = 0;
        for (i = 0; i < n; i++) {
            c = 0;
            for (j = 0; j < r; j++) {
                if ((finish[i] == 0) && (R->resources[i][j] <= A->resources[j])) {
                    c++;
                    if (c == r) {
                        for (k = 0; k < r; k++) {
                            A->resources[k] += C->resources[i][j];
                            finish[i] = 1;
                            flag = 1;
                        }
                        if (finish[i] == 1) {
                            i = n;
                        }
                    }
                }
            }
        }
    }
    j = 0;
    flag = 0;
    for (i = 0; i < n; i++) {
        if (finish[i] == 0) {
            dead[j] = i;
            j++;
            flag = 1;
        }
    }
    if (flag == 1) {
        printf("Deadlocked processes:\n");
        for (i = 0; i < n; i++) {
            printf("%d; ", dead[i]);
        }
    } else {
        printf("No Deadlock Occur\n");
    }
}


int main() {
    Vector E, A;
    E.size = A.size = 0;

    Matrix C, R;
    C.size = R.size = 0;

    FILE *input = fopen(FILE_PATH, "r");

    add_vector(input, &E);
    skip_line(input);

    add_vector(input, &A);
    skip_line(input);

    C.length = R.length = E.size;

    get_matrix(input, &C);
    get_matrix(input, &R);

    for (int i = 0; i < C.size; ++i) {
        for (int j = 0; j < C.length; ++j) {
            printf("%d; ", C.resources[i][j]);
        }
        printf("\n");
    }

    fclose(input);

    detect(&E, &A, &C, &R);

    free_vector(&E);
    free_vector(&A);
    free_matrix(&C);
    free_matrix(&R);

    return 0;
}
