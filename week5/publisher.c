// Copyright 2022 Zener
// Created by Zener on 30.09.22.
//

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MSG_LEN_MAX 1024
#define TEMP_FILE "tmp\\ex1.txt"

/// Reads message from stdin and prints it to the FIFO file
void publish_msg() {
    char msg[MSG_LEN_MAX];
    int fd = open(TEMP_FILE, O_WRONLY);

    fgets(msg, MSG_LEN_MAX, stdin);

    write(fd, msg, strlen(msg));
    close(fd);
}
