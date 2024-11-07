#include <stdio.h>

int main() {
    int n, m, i, j, k;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    printf("Enter the number of resource types: ");
    scanf("%d", &m);

    int allocation[n][m], max[n][m], need[n][m], available[m];
    int finished[n], safeSequence[n];
    
    // Input allocation matrix
    printf("Enter allocation matrix:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        for (j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input maximum demand matrix
    printf("Enter maximum demand matrix:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        for (j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input available resources
    printf("Enter available resources:\n");
    for (j = 0; j < m; j++) {
        scanf("%d", &available[j]);
    }

    // Calculate the need matrix (Need = Max - Allocation)
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Initialize finished array to 0 (indicating all processes are not finished)
    for (i = 0; i < n; i++) {
        finished[i] = 0;
    }

    int processCount = 0;
    while (processCount < n) {
        int found = 0;
        for (i = 0; i < n; i++) {
            if (!finished[i]) { // Check if process is unfinished
                int canExecute = 1;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > available[j]) {
                        canExecute = 0; // Not enough resources
                        break;
                    }
                }
                if (canExecute) {
                    // Process can execute
                    for (k = 0; k < m; k++) {
                        available[k] += allocation[i][k]; // Release resources
                    }
                    safeSequence[processCount++] = i;
                    finished[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) {
            printf("System is not in a safe state.\n");
            return 0;
        }
    }

    // Print the safe sequence
    printf("System is in a safe state.\nSafe sequence: ");
    for (i = 0; i < n; i++) {
        printf("P%d ", safeSequence[i] + 1);
    }
    printf("\n");

    return 0;
}
