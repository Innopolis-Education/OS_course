// Copyright 2022 Zener
// Created by Zener on 07.10.22.
//

#include<stdio.h>

void findTime(int n,
              const int arrival_time[],
              const int burst_time[],
              int waiting_time[],
              int turnaround_time[],
              int completion_time[]) {
    int waiting;
    waiting_time[0] = 0;
    turnaround_time[0] = burst_time[0];
    completion_time[0] = arrival_time[0] + burst_time[0];

    for (int i = 1; i < n; i++) {
        waiting = completion_time[i - 1] - arrival_time[i];
        waiting_time[i] = (waiting > 0) ? waiting : 0;
        turnaround_time[i] = burst_time[i] + waiting_time[i];
        completion_time[i] = arrival_time[i] + turnaround_time[i];
    }
}

void fcfs(const int arrival_time[], const int burst_time[], int n) {
    int waiting_time[n], turnaround_time[n], completion_time[n], total_waiting_time = 0, total_turnaround_time = 0;

    findTime(n, arrival_time, burst_time, waiting_time, turnaround_time, completion_time);

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

    fcfs(arrival_time, burst_time, n);
    return 0;
}
