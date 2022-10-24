// Copyright 2022 Zener
// Created by Zener on 19.10.22.
//

#include <stdio.h>

int main() {
    char **s;
    char foo[] = "Hello World";

    *s = foo;
    printf("s is %p\n", s);

    s[0] = foo;
    printf("s[0] is %s\n", s[0]);

    return 0;
}
