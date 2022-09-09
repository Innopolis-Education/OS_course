// Copyright Zener 2022
// Created by zener on 08.09.22.
//

#include <stdio.h>

/// Convert number from one number system to 10th
/// @param number number, which must be converted
/// @param system original numeral system of the number
long long to_int(long long number, int system) {
    long long answer = 0;
    int power = 1;
    int digit;

    while (number > 0) {
        digit = (int) number % 10;
        if (digit >= system)
            return 0;
        answer += digit * power;
        power *= system;
        number /= 10;
    }

    return answer;
}

/// Convert number from 10th to another numeral system
/// @param number number, which must be converted
/// @param system numeral system to which the number must be converted
long long from_int(long long number, int system) {
    long long answer = 0;
    int digit;
    int power = 1;

    while (number > 0) {
        digit = (int) number % system;
        answer = answer + digit * power;
        power *= 10;
        number /= system;
    }

    return answer;
}

/// Convert number from one numeral system to another
/// @param number number, which must be converted
/// @param from numeral system, from which number will be converted
/// @param to numeral system, to which number will be converted
void convert(long long number, int from, int to) {
    long long tenth = to_int(number, from);

    if (tenth == 0 && number != 0) {
        printf("cannot convert!");
        return;
    }

    printf("%lld\n", from_int(tenth, to));
}

int main() {
    long long number;
    int from, to;

    printf("Print your number: ");
    scanf("%lld", &number);

    printf("Print the first numeral system: ");
    scanf("%d", &from);

    printf("Print the second numeral system: ");
    scanf("%d", &to);

    convert(number, from, to);
    return 0;
}
