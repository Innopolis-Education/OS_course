//
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_NAME_LENGTH 63
#define MAX_FILE_DATA_LENGTH 1024
#define MAX_ALL_FILES 256

#define MAX_DIR_NAME_LENGTH 63 // Ask
#define MAX_PATH_LENGTH 2048
#define MAX_SUBDIRECTORIES 8
#define MAX_FILES 8 // Ask

struct Directory;
struct File;

struct File {
    unsigned char id;
    char name[MAX_FILE_NAME_LENGTH];
    unsigned short size;
    char data[MAX_FILE_DATA_LENGTH];

    struct Directory *directory; // The parent directory
};

struct Directory {
    char name[MAX_DIR_NAME_LENGTH];

    struct File *files[MAX_FILES];
    struct Directory *directories[MAX_SUBDIRECTORIES];

    int nf;
    int nd;

    char path[MAX_PATH_LENGTH];
};

typedef struct Directory Directory;
typedef struct File File;


// Operations on files
void add_to_file(File *file, const char *content);

void append_to_file(File *file, const char *content);

void pwd_file(File *file);


// Operations on directories
void add_file(File *file, Directory *dir);

void add_dir(Directory *dir1, Directory *dir2); // given to you

// Helper functions
void show_dir(Directory *dir);

void show_file(File *file);

void show_file_detailed(File *file);

int main() {

    char content1[] = "int printf(const char * format, ...);";
    char content2[] = "int main(){printf('Hello World');}";
    char content3[] = "//This is a comment in C language";
    char content4[] = "Bourne Again Shell!";


    Directory home, bin, root;

    root.nd = 0; root.nf = 0;
    home.nd = 0; home.nf = 0;
    bin.nd = 0; bin.nf = 0;

    strcpy(root.name, "/"); strcpy(root.path, "/");
    strcpy(home.name, "home");
    strcpy(bin.name, "bin");

    // Add subdirectories
    add_dir(&home, &root);
    add_dir(&bin, &root);

    File bash, ex31, ex32;

    strcpy(bash.name, "bash");
    bash.id = 0; ex31.id = 1; ex32.id = 2;

    strcpy(ex31.name, "ex3_1.c");
    strcpy(ex32.name, "ex3_2.c");


    add_file(&bash, &bin);
    add_file(&ex31, &home);
    add_file(&ex32, &home);

    add_to_file(&ex31, content1);
    add_to_file(&ex32, content3);
    add_to_file(&bash, content4);


    append_to_file(&ex31, content2);

    show_dir(&root);
    show_file_detailed(&bash);
    show_file_detailed(&ex31);
    show_file_detailed(&ex32);

    pwd_file(&bash);
    pwd_file(&ex31);
    pwd_file(&ex32);

    return EXIT_SUCCESS;
}

// Helper functions

// Displays the content of the Directory dir
void show_dir(Directory *dir) {
    printf("\nDIRECTORY\n");
    printf(" path: %s\n", dir->path);
    printf(" files:\n");
    printf("    [ ");
    for (int i = 0; i < dir->nf; i++) {
        show_file(dir->files[i]);
    }
    printf("]\n");
    printf(" directories:\n");
    printf("    { ");

    for (int i = 0; i < dir->nd; i++) {
        show_dir(dir->directories[i]);
    }
    printf("}\n");
}

// Prints the name of the File file
void show_file(File *file) {
    printf("%s ", file->name);
}

// Shows details of the File file
void show_file_detailed(File *file) {
    printf("\nFILE\n");
    printf(" id: %d\n", file->id);
    printf(" name: %s\n", file->name);
    printf(" size: %hu\n", file->size);
    printf(" data:\n");
    printf("    [ %s ]\n", file->data);
}



// Implementation: Operations on files

// Adds the content to the File file
void add_to_file(File *file, const char *content) {
    strcpy(file->data, content);
    file->size = strlen(content);
}

// Appends the content to the File file
void append_to_file(File *file, const char *content) {
    size_t len = strlen(content);
    strncat(file->data, content, len);
    file->size += len;
}

// Prints the path of the File file
void pwd_file(File *file) {
    char path[MAX_PATH_LENGTH];
    char *path_dir = file->directory->path;

    int i = 0;

    for (i = 0; i < strlen(path_dir); i++)
        path[i] = path_dir[i];

    path[i] = '/';

    for (int j = 0; j < strlen(file->name); j++)
        path[i+j] = path_dir[i];

    printf("%s\n", path);
}


// Implementation: Operations on directories

// Adds the File file to the Directory dir
void add_file(File *file, Directory *dir) {
    dir->files[dir->nf++] = file;
    file->directory = dir;
}

// Given to you
// Adds the subdirectory dir1 to the directory dir2
void add_dir(Directory *dir1, Directory *dir2) {
    if (dir1 && dir2) {
        dir2->directories[dir2->nd] = dir1;
        dir2->nd++;
        strcpy(dir1->path, dir2->path);
        strncat(dir1->path, dir1->name, strlen(dir1->name));
    }
}

