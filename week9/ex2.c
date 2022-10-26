// Copyright 2022 Zener
// Created by Zener on 26.10.22.
//

#include <malloc.h>
#include <string.h>
#include <unistd.h>

#define TIMES 10
#define MEMORY (10*1024*1024)
#define SET_VALUE 0
#define WAIT_TIME 1

int main() {
    for (int i = 0; i < TIMES; i++) {
        int* ptr = malloc(sizeof(int) * MEMORY);
        memset(ptr, SET_VALUE, MEMORY);
        sleep(WAIT_TIME);
        // The memory decreases every second for 10 mb usually
        // si and so fields are not changed somehow, there are 2 zeros always
    }

    return 0;  // Then the memory increases immediately for 10 mb
}

/* Exercise 3
 *
 * There is 1 more process in the top when the program is executed.
 * Nothing special, it's not even in the top 3 usually.
 * */
