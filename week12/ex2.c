// Copyright 2022 Zener
// Created by Zener on 21.11.22.
//

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("\\"))!= NULL) {
        while ((ent = readdir (dir)) != NULL)
            printf ("%s\n", ent->d_name);
        closedir (dir);
    }
    else return EXIT_FAILURE;

    return 0;
}
