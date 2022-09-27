// Copyright 2022 Zener
// Created by Zener on 25.09.22.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define NUMBER_OF_PROCESSES 2

/// Prints ids of the process and it's parent
void get_all_id() {
    printf("id of process: %d;\tid of parent process: %d;\t", getpid(), getppid());
}


int main(void) {
    for (int i = 0; i < NUMBER_OF_PROCESSES; i++) {
        if (fork() == 0) {
            clock_t t = clock();
            get_all_id();
            t = clock() - t;
            printf("time taken: %f\n", (float) t / CLOCKS_PER_SEC);
            exit(0);
        }
    }

    clock_t t = clock();
    get_all_id();
    t = clock() - t;
    printf("time taken: %f\n", (float) t / CLOCKS_PER_SEC);

    return EXIT_SUCCESS;
}
