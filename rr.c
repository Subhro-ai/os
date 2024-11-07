#include <stdio.h>

int main() {
    int n, timeQuantum, i, total = 0, x, counter = 0;
    float totalWaitTime = 0, totalTurnaroundTime = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    int burstTime[n], remainingBurstTime[n], waitTime[n], turnaroundTime[n];

    printf("Enter the time quantum: ");
    scanf("%d", &timeQuantum);

    // Input burst time for each process
    for (i = 0; i < n; i++) {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &burstTime[i]);
        remainingBurstTime[i] = burstTime[i];
        waitTime[i] = 0;
    }

    x = n; // Number of processes left to execute

    // Round Robin scheduling
    while (x != 0) {
        for (i = 0; i < n; i++) {
            if (remainingBurstTime[i] > 0) {
                if (remainingBurstTime[i] <= timeQuantum) {
                    total += remainingBurstTime[i];
                    remainingBurstTime[i] = 0;
                    waitTime[i] = total - burstTime[i];
                    turnaroundTime[i] = waitTime[i] + burstTime[i];
                    x--; // Process is finished
                } else {
                    total += timeQuantum;
                    remainingBurstTime[i] -= timeQuantum;
                }
            }
        }
    }

    // Calculate total wait time and turnaround time
    for (i = 0; i < n; i++) {
        totalWaitTime += waitTime[i];
        totalTurnaroundTime += turnaroundTime[i];
    }

    // Display results
    printf("\nProcess\tBurst Time\tWait Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", i + 1, burstTime[i], waitTime[i], turnaroundTime[i]);
    }

    printf("\nAverage Waiting Time: %.2f", totalWaitTime / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTurnaroundTime / n);

    return 0;
}
