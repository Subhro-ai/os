#include <stdio.h>

int main() {
    int n, i;
    float totalWaitTime = 0, totalTurnaroundTime = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int burstTime[n], waitTime[n], turnaroundTime[n];

    // Input burst times
    printf("Enter the burst time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &burstTime[i]);
    }

    // FCFS scheduling: wait time of the first process is 0
    waitTime[0] = 0;
    for (i = 1; i < n; i++) {
        waitTime[i] = waitTime[i - 1] + burstTime[i - 1];
    }

    // Calculate turnaround time for each process
    for (i = 0; i < n; i++) {
        turnaroundTime[i] = waitTime[i] + burstTime[i];
    }

    // Calculate total wait time and total turnaround time
    for (i = 0; i < n; i++) {
        totalWaitTime += waitTime[i];
        totalTurnaroundTime += turnaroundTime[i];
    }

    // Display results
    printf("\nProcess\tBurst Time\tWait Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", i + 1, burstTime[i], waitTime[i], turnaroundTime[i]);
    }

    printf("\nAverage Wait Time: %.2f", totalWaitTime / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTurnaroundTime / n);

    return 0;
}
