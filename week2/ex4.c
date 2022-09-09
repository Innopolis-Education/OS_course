// Copyright Zener 2022
// Created by zener on 08.09.22.
//

#include <ctype.h>
#include <string.h>
#include <stdio.h>

#define MAX_STR_LEN 256

/// Changes all chars to become lowercase mode in the string
/// @param str string line, which must be changed
/// @param len length of the string
void lowercase(char *str, const unsigned int len) {
    for (int i = 0; i < len; i++)
        str[i] = (char) tolower(str[i]);
}

/// Prints number of meetings some character in the string
/// @param str original string
/// @param c character, which will be counted in the string
/// @param len length of the number
void count_char(const char *str, const char c, const unsigned int len) {
    int count = 0;

    for (int i = 0; i < len; i++)
        if (str[i] == c) count++;

    printf("%c:%d", c, count);
}

/// prepare string and define length of the string before counting char
/// @param str original string
/// @param c character, which will be counted in the string
void count(char *str, const char c) {
    unsigned int len = strlen(str) - 1;
    lowercase(str, len);
    count_char(str, c, len);
    printf("\n");
}

/// Counts and prints all characters from the string
/// @param str original string
void countAll(char *str) {
    unsigned int len = strlen(str) - 1;
    lowercase(str, len);

    count_char(str, str[0], len);

    for (int i = 1; i < len; i++) {
        printf(", ");
        count_char(str, str[i], len);
    }

    printf("\n");
}

int main() {
    char str[MAX_STR_LEN], c;

    fgets(str, MAX_STR_LEN, stdin);

    countAll(str);
}