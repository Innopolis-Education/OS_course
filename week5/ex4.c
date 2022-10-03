// Copyright 2022 Zener
// Created by Zener on 01.10.22.
//

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

/// Checks is the number is prime or not
/// @param n the number
/// @return 1 if the number is prime, otherwise 0
int is_prime(int n) {
    if (n <= 1)
        return 0;
    for (int d = 2; d * d <= n; d++)
        if (n % d == 0)
            return 0;
    return 1;
}

int n = 0;

// You will be locking and unlocking this
pthread_mutex_t global_lock = PTHREAD_MUTEX_INITIALIZER;

// Don't modify these variables directly, use the functions below.
int next_number_to_check = 0;
int primes_found_so_far = 0;

/// Returns the next number for checking if this number is prime
/// @return the next number to check if it is prime or not
int get_number_to_check() {
    int ret = next_number_to_check;
    if (next_number_to_check != n)
        next_number_to_check++;
    return ret;
}

/// Increases number of prime numbers found
void increment_primes() {
    primes_found_so_far++;
}

///
void *check_primes(void *arg) {
    int x;

    while (1) {
        pthread_mutex_lock(&global_lock);
        x = get_number_to_check();

        if (is_prime(x)) {
            increment_primes();
        }
        pthread_mutex_unlock(&global_lock);

        if (x == n) return NULL;
    }
}

int main(int argc, char *argv[]) {
    double time_spent = 0.0;

    clock_t begin = clock();

    int n_threads = atoi(argv[2]);
    n = atoi(argv[1]);

    pthread_t *threads = malloc(n_threads * sizeof(pthread_t));

    if (pthread_mutex_init(&global_lock, NULL) != 0) {
        printf("\n mutex init has failed\n");
        return 1;
    }

    int *p_n = malloc(sizeof(int));
    *p_n = n;

    for (int i = 0; i < n_threads; i++) {
        int error = pthread_create(&(threads[i]), NULL, &check_primes, p_n);
        if (error != 0) {
            printf("\nThread can't be created :[%s]", strerror(error));
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < n_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    free(threads);
    pthread_mutex_destroy(&global_lock);

    printf("%d\n", primes_found_so_far);

    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("The elapsed time is %f seconds\n", time_spent);

    exit(EXIT_SUCCESS);
}
