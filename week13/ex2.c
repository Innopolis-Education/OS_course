// Copyright 2022 Zener
// Created by Zener on 29.11.22.
//

#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    struct input_event event;
    ssize_t n;
    int input = open("/dev/input/by-path/platform-i8042-serio-0-event-kbd", O_RDONLY);
    FILE *output = fopen("ex2.txt", "w");

    while (1) {
        read(input, &event, sizeof(event));
        if (event.type == EV_KEY) {
            if (event.value == 0)
                fprintf(output, "RELEASED ");
            else if (event.value == 1)
                fprintf(output, "PRESSED ");
            fprintf(output, "0x%04x (%d)\n", event.code, event.code);
        }
    }
    return 0;
}
