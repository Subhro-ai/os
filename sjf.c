#include <stdio.h>

int main() {
    int n, i, j;
    float totalWaitTime = 0, totalTurnaroundTime = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int process[n], burstTime[n], waitTime[n], turnaroundTime[n];

    // Input process IDs and burst times
    for (i = 0; i < n; i++) {
        process[i] = i + 1;
        printf("Enter burst time for process %d: ", process[i]);
        scanf("%d", &burstTime[i]);
    }

    // Sort processes based on burst time (SJF)
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (burstTime[i] > burstTime[j]) {
                // Swap burst times
                int temp = burstTime[i];
                burstTime[i] = burstTime[j];
                burstTime[j] = temp;

                // Swap process IDs to match burst time sorting
                temp = process[i];
                process[i] = process[j];
                process[j] = temp;
            }
        }
    }

    // Set waiting time for first process to 0
    waitTime[0] = 0;

    // Calculate waiting time and turnaround time for each process
    for (i = 1; i < n; i++) {
        waitTime[i] = waitTime[i - 1] + burstTime[i - 1];
    }
    for (i = 0; i < n; i++) {
        turnaroundTime[i] = waitTime[i] + burstTime[i];
    }

    // Calculate total waiting time and total turnaround time
    for (i = 0; i < n; i++) {
        totalWaitTime += waitTime[i];
        totalTurnaroundTime += turnaroundTime[i];
    }

    // Display results
    printf("\nProcess\tBurst Time\tWait Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", process[i], burstTime[i], waitTime[i], turnaroundTime[i]);
    }

    printf("\nAverage Waiting Time: %.2f", totalWaitTime / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTurnaroundTime / n);

    return 0;
}
