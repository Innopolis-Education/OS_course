// Copyright 2022 Zener
// Created by Zener on 26.09.22.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    if (argc != 2) return EXIT_FAILURE;

    int n = atoi(argv[1]);

    for (int i = 0; i < n; i++) {
        fork();
        sleep(5);
    }

    return EXIT_SUCCESS;

}
