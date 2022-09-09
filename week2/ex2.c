// Copyright Zener 2022
// Created by Zener on 07.09.22.
//

#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 256

int main() {
    char string[MAX_LENGTH];
    fgets(string, MAX_LENGTH, stdin);

    short len = (short) strlen(string);
    short size_before_dot = 0;

    short index = 0;
    char reverse[len];

    while (string[index] != '\n' && string[index] != '.') {
        reverse[len - index - 1] = string[index];
        index++; size_before_dot++;
    }

    index = (short) (len - size_before_dot);

    printf("\"");
    for (int i = index; i < len; i++)
        printf("%c", reverse[i]);
    printf("\"\n");

    return 0;
}
