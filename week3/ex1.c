// Copyright 2022 Zener
// Created by Zener on 15.09.22.
//

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define VALUE_X 10
#define LENGTH_ARRAY 5

/// Calculates the current year
/// @return current year
int current_year() {
    time_t seconds = time(NULL);
    return localtime(&seconds)->tm_year + 1900;
}

/// Finds the birth year of student by given age
/// @param age age of the student
/// @return birth year of the student
int foo(int age) {
    int result;
    int year = current_year();
    result = year - age;
    return result;
}

int main() {
    const int x = VALUE_X;
    const int *q = &x;

    const int arr[LENGTH_ARRAY] = {*q, *q, *q, *q, *q};
    int *const p = arr;

    for (int i = 0; i < LENGTH_ARRAY; i++)
        fprintf(stdout, "%p\n", &p[i]);

    for (int i = 0; i < LENGTH_ARRAY; i++)
        fscanf(stdin, "%d", &p[i]);

    for (int i = 0; i < LENGTH_ARRAY; i++)
        p[i] = foo(p[i]);

    return EXIT_SUCCESS;
}
