// Copyright Zener 2022
// Created by zener on 07.09.22.
//

#include <string.h>
#include <stdio.h>

/// Returns the tribonacci value with number n
/// @param n number of the tribonacci value
/// @return tribonacci value with exact number
int tribonacci(unsigned short n) {
    if (n == 0) return 0;
    if (n <= 2) return 1;

    int a = 0, b = 1, c = 1, temp1, temp2;

    for (int i = 0; i < n - 2; i++) {
        temp1 = a;
        temp2 = b;
        a = b;
        b = c;
        c += temp1 + temp2;
    }

    return c;
}

/// convert char argument to number to find tribonacci value
/// @param number number itself, in '*char' type
/// @return number in 'int' type
int convert(const char *number) {
    if (strlen(number) == 1) return number[0] - '0';
    return (number[0] - '0') * 10 + (number[1] - '0');
}

int main(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        int n = convert(argv[i]);
        printf("%d\n", tribonacci(n));
    }
    return 0;
}
