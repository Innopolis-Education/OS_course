// Copyright 2022 Zener
// Created by Zener on 09.11.22.
//

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

#define DIRECTORY_NAME "./tmp"
#define OUTPUT_FILE_NAME "./ex4.txt"
#define MAX_FILE_NAME_LEN 256
#define DIRECTORY_NOT_FOUND(name) printf("Error: directory %s not found", name)

/**
 * Dynamic array for storing files, which have more than 1 links
 */
typedef struct {
    char **files;
    ino_t *inodes;
    size_t used;
    size_t size;
} ArrayLinks;

/**
 * Initialization of dynamic array of files
 * @param files pointer to dynamic array
 */
void initArrayLinks(ArrayLinks *files) {
    files->files = malloc(sizeof(char[MAX_FILE_NAME_LEN]));
    files->inodes = malloc(sizeof(int));
    files->used = 0;
    files->size = 1;
}

/**
 * Adds file and it's inode number to the dynamic array
 * @param links dynamic array
 * @param file_name name of file, which has at least 2 links
 * @param inode inode number of the file
 */
void add_link(ArrayLinks *links, char *file_name, const ino_t inode) {
    if (links->used == links->size) {
        links->size *= 2;
        links->files = realloc(links->files, links->size * sizeof(char[MAX_FILE_NAME_LEN]));
        links->inodes = realloc(links->inodes, links->size * sizeof(int));
    }

    links->files[links->used] = file_name;
    links->inodes[links->used++] = inode;
}

/**
 * Scans files to find some having 2 links at least
 * @param directory_name name of the directory, where the scanning would be
 * @return dynamic array, which contains files and its inode numbers
 */
ArrayLinks scan_links(const char* directory_name) {
    DIR *directory = opendir(directory_name);
    if (directory == NULL) {
        DIRECTORY_NOT_FOUND(directory_name);
        exit(EXIT_FAILURE);
    }

    struct dirent *file;
    struct stat* stat_file;

    ArrayLinks links;
    initArrayLinks(&links);

    int i = 0;

    while ((file = readdir(directory)) != NULL) {
        stat_file = (struct stat*)malloc(sizeof(struct stat));
        lstat(file->d_name, stat_file);

        if (stat_file->st_nlink >= 2)
            add_link(&links, file->d_name, file->d_ino);
    }
    free(stat_file);

    return links;
}

/**
 * print all links of each file
 * @param output output file
 * @param inode inode number of the main file
 * @param directory_name name of the directory, where the scan was
 */
void print_links(FILE *output, ino_t inode, const char *directory_name) {
    DIR *directory = opendir(directory_name);
    if (directory == NULL) {
        DIRECTORY_NOT_FOUND(directory_name);
        exit(EXIT_FAILURE);
    }

    struct dirent *file;
    struct dirent *prev = NULL;
    int i = 0;

    while ((file = readdir(directory)) != NULL) {
        if (file->d_ino == inode) {
            if (prev != NULL)
                fprintf(output, "%s, ", prev->d_name);
            prev = file;
        }
    }

    if (prev != NULL)
        fprintf(output, "%s", prev->d_name);
}

/**
 * creates output file and print all information about files and its links
 * @param links dynamic array of files and its inode numbers
 * @param directory_name name of the directory, where the scan was
 */
void print_output(const ArrayLinks links, const char *directory_name) {
    FILE *output = fopen(OUTPUT_FILE_NAME, "w");
    fprintf(output, "File --- Hard Links\n");

    for (int i = 0; i < links.used; i++) {
        fprintf(output, "%s --- ", links.files[i]);
        print_links(output, links.inodes[i], directory_name);
        fprintf(output, "\n");
    }

    fclose(output);
}

int main() {
    ArrayLinks links = scan_links(DIRECTORY_NAME);

    print_output(links, DIRECTORY_NAME);

    free(links.files);
    free(links.inodes);

    return EXIT_SUCCESS;
}
