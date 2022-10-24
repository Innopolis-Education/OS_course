// Copyright 2022 Zener
// Created by Zener on 19.10.22.
//

#include <stdio.h>
#include <malloc.h>

int main() {
    int n;
    printf("Print the value of the N: ");
    scanf("%d", &n);

    int* numbers = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        numbers[i] = i;
    }

    printf("Numbers from the array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    free(numbers);
}
