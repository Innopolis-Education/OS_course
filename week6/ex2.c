// Copyright 2022 Zener
// Created by Zener on 09.10.22.
//

#include <stdio.h>
#include <limits.h>

/**
 * Creates copies of arrays of arrival times and burst times of the processes
 * @param n number of processes
 * @param arrival_time array with arrival times of the processes
 * @param burst_time array with arrival times of the processes
 * @param at copy of array with arrival times of the processes
 * @param bt copy of array with arrival times of the processes
 */
void copy_times(int n, const int arrival_time[], const int burst_time[], int at[], int bt[]) {
    for (int i = 0; i < n; i++) {
        at[i] = arrival_time[i];
        bt[i] = burst_time[i];
    }
}

/**
 * Finds index of the next process, which must be started
 * @param n number of processes
 * @param tick actual tick (counts passed from the start)
 * @param at arrival times of the processes
 * @param bt burst times of the processes
 * @return index of the next process
 */
int find_min(const int n, const int tick, int at[], int bt[]) {
    int mini = INT_MAX;
    int min_i = -1;
    for (int i = 0; i < n; i++) {
        if (mini > bt[i] && tick >= at[i]) {
            mini = bt[i];
            min_i = i;
        }
    }
    at[min_i] = INT_MAX;
    bt[min_i] = INT_MAX;

    return min_i;
}

/**
 * Finds waiting times, turnaround times and completion times of the processes by <shortest job first> algorithm
 * @param n number of processes
 * @param arrival_time arrival times of the processes
 * @param burst_time burst times of the processes
 * @param waiting_time waiting times of the processes
 * @param turnaround_time turnaround times of the processes
 * @param completion_time completion times of the processes
 */
void find_time(int n,
              const int arrival_time[],
              const int burst_time[],
              int waiting_time[],
              int turnaround_time[],
              int completion_time[]) {
    int at[n], bt[n];
    copy_times(n, arrival_time, burst_time, at, bt);

    int waiting, min_index, prev, tick = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (tick > at[i]) {
            tick = at[i];
            min_index = i;
        } if (tick == at[i] && bt[i] < bt[min_index]) {
            min_index = i;
        }
    }

    waiting_time[min_index] = 0;
    turnaround_time[min_index] = burst_time[min_index];
    completion_time[min_index] = tick = at[min_index] + bt[min_index];
    at[min_index] = INT_MAX;
    bt[min_index] = INT_MAX;

    for (int i = 1; i < n; i++) {
        prev = min_index;
        min_index = find_min(n, tick, at, bt);
        waiting = completion_time[prev] - arrival_time[min_index];
        waiting_time[min_index] = (waiting > 0) ? waiting : 0;
        turnaround_time[min_index] = burst_time[min_index] + waiting_time[min_index];
        completion_time[min_index] = tick = arrival_time[min_index] + turnaround_time[min_index];
    }
}

/**
 * <Shortest job first> algorithm for some processes
 * @param n number of processes
 * @param arrival_time arrival times of the processes
 * @param burst_time burst times of the processes
 */
void sjf(int n, int arrival_time[], int burst_time[]) {
    int waiting_time[n], turnaround_time[n], completion_time[n], total_waiting_time = 0, total_turnaround_time = 0;

    find_time(n, arrival_time, burst_time, waiting_time, turnaround_time, completion_time);

    printf(" Completion time Turnaround time Waiting time\n");

    for (int i = 0; i < n; i++) {
        total_turnaround_time = total_turnaround_time + turnaround_time[i];
        total_waiting_time = total_waiting_time + waiting_time[i];
        printf("\t%d", completion_time[i]);
        printf("\t\t%d", turnaround_time[i]);
        printf("\t\t%d\n", waiting_time[i]);
    }
    float t = (float) total_turnaround_time / (float) n;
    float s = (float) total_waiting_time / (float) n;
    printf("Average turn around time = %f\n", t);
    printf("Average waiting time = %f\n", s);
}

int main() {
    int n;

    printf("Print number of processes: ");
    scanf("%d", &n);

    int arrival_time[n];
    int burst_time[n];

    for (int i = 0; i < n; i++) {
        printf("Arrival time of process №%d: ", i + 1);
        scanf("%d", &arrival_time[i]);

        printf("Burst time of process №%d: ", i + 1);
        scanf("%d", &burst_time[i]);
    }

    sjf(n, arrival_time, burst_time);

    return 0;
}
