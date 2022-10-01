// Copyright 2022 Zener
// Created by Zener on 30.09.22.
//

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define MSG_LEN_MAX 1024
#define TEMP_FILE "tmp\\ex1.txt"

/// Reads message from FIFO file and prints it to the stdout
void subscribe_msg() {
    char msg[MSG_LEN_MAX];
    int fd = open(TEMP_FILE, O_RDONLY);

    read(fd, msg, MSG_LEN_MAX);

    fprintf(stdin, "%s", msg);
    close(fd);
}
