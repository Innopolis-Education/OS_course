// Copyright 2022 Zener
// Created by Zener on 02.11.22.
//

#include <stdlib.h>
#include <stdio.h>

#define PROCESSES 1000
#define FILE_NAME "input.txt"
#define PAGE_BITS 8

typedef struct Page {
    int number;
    unsigned int r;
} Page;

int page_in_frame(const Page page, const Page frame[], const int page_frames) {
    for (int i = 0; i < page_frames; i++) {
        if (frame[i].number == page.number) return i;
    }
    return -1;
}

int find_min_page(const Page frame[], const int page_frames) {
    int min_index = 0;
    unsigned int min_r = 1000;
    for (int i = 0; i < page_frames; i++) {
        if (frame[i].r < min_r) {
            min_index = i;
            min_r = frame[i].r;
        }
    }
    return min_index;
}

void decrease_r_reg(const int index, Page frame[], int page_frames) {
    for (int i = 0; i < page_frames; i++) {
        if (i != index) {
            frame[i].r = frame[i].r >> 1;
        }
    }
}

void add_page(Page page, Page frame[], const int page_frames) {
    int index = find_min_page(frame, page_frames);
    frame[index] = page;
    page.r = 0x1 << (PAGE_BITS - 1);
    decrease_r_reg(index, frame, page_frames);
}

int aging_algorithm(const int page_frames, const Page references[]) {
    int hit = 0;
    Page frame[page_frames];
    for (int i = 0; i < page_frames - PAGE_BITS; i++) {
        frame[i] = references[i];
    }
    for (int i = page_frames - PAGE_BITS; i < page_frames; i++) {
        frame[i] = references[i];
        frame[i].r = 0x1 << (i - page_frames + PAGE_BITS);
    }
    int index;
    for (int i = page_frames; i < PROCESSES; i++) {
        index = page_in_frame(references[i], frame, page_frames);
        if (index == -1) {
            add_page(references[i], frame, page_frames);
        } else {
            hit++;
            decrease_r_reg(-1, frame, page_frames);
            frame[i].r += 0x1 << (PAGE_BITS - 1);
        }
    }
    return hit;
}

int main(int argc, char *argv[]){
    if (argc != 2) return EXIT_FAILURE;

    int page_frames = atoi(argv[1]);

    FILE *input = fopen(FILE_NAME, "r");

    Page references[PROCESSES];
    for (int i = 0; i < PROCESSES; i++) {
        fscanf(input, "%d", &references[i].number);
        references[i].r = 0;
    }
    int hit = aging_algorithm(page_frames, references);

    printf("Hit: %d times\n", hit);
    printf("Miss: %d times\n", PROCESSES - hit);

    fclose(input);
    return 0;
}
