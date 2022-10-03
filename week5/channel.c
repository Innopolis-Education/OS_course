// Copyright 2022 Zener
// Created by Zener on 30.09.22.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include "publisher.c"
#include "subscriber.c"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Please fill the arguments correctly!");
        exit(EXIT_FAILURE);
    }

    char *str = argv[1], *end_str;
    long n = strtol(str, &end_str, 0);

    if (end_str == str) {
        fprintf(stderr, "No such digits in the arguments!");
        exit(EXIT_FAILURE);
    }

    mkfifo(TEMP_FILE, 0666);

    while (1) {
        publish_msg();
        for (int i = 0; i < n; i++) {
            if (fork() == 0) {
                subscribe_msg();
                wait(NULL);
            }
        }
    }
}
