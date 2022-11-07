// Copyright 2022 Zener
// Created by Zener on 02.11.22.
//

#include <stdlib.h>
#include <stdio.h>

#define PROCESSES 1000
#define FILE_NAME "input.txt"

typedef struct Page {
    int number;
    unsigned int r;
} Page;

int* aging_algorithm(const int page_frames, const int references[]) {
    return 0;
}

int main(int argc, char *argv[]){
    if (argc != 2) return EXIT_FAILURE;

    int page_frames = atoi(argv[1]);

    FILE *input = fopen(FILE_NAME, "r");

    int references[PROCESSES];
    for (int i = 0; i < PROCESSES; i++) {
        fscanf(input, "%d", &references[i]);
    }
    int *hit_miss = aging_algorithm(page_frames, references);

    printf("Hit: %d times\n", hit_miss[0]);
    printf("Miss: %d times\n", hit_miss[1]);

    fclose(input);
    return 0;
}
