// Copyright 2022 Zener
// Created by Zener on 26.10.22.
//

#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include <sys/resource.h>

#define TIMES 10
#define MEMORY (10*1024*1024)
#define SET_VALUE 0
#define WAIT_TIME 1

int main() {
    struct rusage usage;

    for (int i = 0; i < TIMES; i++) {
        int* ptr = malloc(sizeof(int) * MEMORY);
        memset(ptr, SET_VALUE, MEMORY);
        sleep(WAIT_TIME);
        getrusage(0, &usage);
        printf("%d:\n\t", i + 1);
        printf("maximum resident set size: %ld;\n\t", usage.ru_maxrss);
        printf("integral shared memory size: %ld\n\t", usage.ru_ixrss);
        printf("integral unshared data size: %ld\n\t", usage.ru_idrss);
        printf("integral unshared stack size: %ld\n\t", usage.ru_isrss);
        printf("page reclaims (soft page faults): %ld\n\t", usage.ru_minflt);
        printf("page faults (hard page faults): %ld\n\t", usage.ru_majflt);
        printf("swaps: %ld\n\t", usage.ru_nswap);
        printf("block input operations: %ld\n\t", usage.ru_inblock);
        printf("block output operations: %ld\n\t", usage.ru_oublock);
        printf("IPC messages sent: %ld\n\t", usage.ru_msgsnd);
        printf("IPC messages received: %ld\n\t", usage.ru_msgrcv);
        printf("signals received: %ld\n\t", usage.ru_nsignals);
        printf("voluntary context switches: %ld\n\t", usage.ru_nvcsw);
        printf("involuntary context switches: %ld\n\n\n", usage.ru_nivcsw);
    }
    return 0;
}
