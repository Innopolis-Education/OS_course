// Copyright 2022 Zener
// Created by zener085 on 26.09.22.
//

#include <stdio.h>
#include <stdlib.h>

#define COMMAND_LENGTH 128

void command_line() {
    char command[COMMAND_LENGTH];
    while (1) {
        fgets(command, COMMAND_LENGTH, stdin);
        system(command);
    }
}


int main(void) {
    command_line();
    return EXIT_SUCCESS;
}
