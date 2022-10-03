// Copyright 2022 Zener
// Created by Zener on 01.10.22.
//

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

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

/// Counts number of primes in some interval
/// @param start start of the interval, included value
/// @param finish end of the interval, excluded value
/// @return number of prime numbers in the interval
int primes_count_in_interval(int start, int finish) {
    int ret = 0;
    for (int i = start; i < finish; i++)
        if (is_prime(i) != 0)
            ret++;
    return ret;
}

// The structure that will be passed to the threads, corresponding to an interval to count the number of primes in.
typedef struct prime_counter_request {
    int start, finish;
} prime_counter_request;

/// Calculates number of prime numbers in some interval using threads
/// @param arg prime_counter_request, which contains start and finish of the interval
/// @return address to number of prime numbers
void *prime_counter(void *arg) {
    prime_counter_request *request = malloc(sizeof(prime_counter_request));
    *request = *(prime_counter_request *) arg;

    int *ret = malloc(sizeof(int));

    *ret = primes_count_in_interval(request->start, request->finish);

    return ret;
}

int main(int argc, char *argv[]) {
    double time_spent = 0.0;

    clock_t begin = clock();

    int n = atoi(argv[1]), n_threads = atoi(argv[2]);
    int segment_size = n / n_threads + (n % n_threads == 0 ? 0 : 1);

    pthread_t *threads = malloc(n_threads * sizeof(pthread_t));

    prime_counter_request *requests = malloc(n_threads * sizeof(prime_counter_request));

    void **results = malloc(n_threads * sizeof(void *));

    int start = 1, finish = segment_size;

    for (int i = 0; i < n_threads; i++) {
        requests[i].start = start;
        start += segment_size;

        requests[i].finish = finish;
        finish += segment_size;

        pthread_create(&threads[i], NULL, prime_counter, &requests[i]);
    }

    for (int i = 0; i < n_threads; i++) {
        pthread_join(threads[i], &results[i]);
    }

    int total_result = 0;
    for (int i = 0; i < n_threads; i++)
        total_result += *(int *) results[i];

    free(threads);
    free(requests);
    free(results);

    printf("%d\n", total_result);

    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("The elapsed time is %f seconds\n", time_spent);

    exit(EXIT_SUCCESS);
}
