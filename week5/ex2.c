// Copyright 2022 Zener
// Created by Zener on 01.10.22.
//

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <string.h>

#define MAX_MSG_LEN 256
#define MSG "Hello from thread "

typedef struct {
    pthread_t id;
    unsigned int i;
    char message[MAX_MSG_LEN];
} Thread;

void *thread_act(void *arg) {
    Thread *ret = malloc(sizeof(Thread));
    ret = (Thread *) arg;
    fprintf(stdin, "Id: %lu\nMessage: %s", ret->id, ret->message);
}


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

    Thread threads[n];

    for (unsigned int i = 0; i < n; i++) {
        threads[i].i = i;
        strcpy(threads[i].message, MSG);
        threads[i].message[strlen(MSG)] = (char) i - '0';
        pthread_create(&threads[i].id, NULL, thread_act, &threads[i]);
        fprintf(stdin, "Thread %d is created", threads[i].i);
    }

    return EXIT_SUCCESS;
}