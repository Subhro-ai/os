#include <stdio.h>
#include <limits.h>

void fifo(int pages[], int n, int capacity) {
    int frames[capacity];
    int faults = 0, next = 0;

    for (int i = 0; i < capacity; i++) frames[i] = -1;

    printf("\nFIFO Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            frames[next] = pages[i];
            next = (next + 1) % capacity;
            faults++;
        }

        printf("Page %d -> ", pages[i]);
        for (int j = 0; j < capacity; j++) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }
    printf("Total Page Faults (FIFO): %d\n", faults);
}

void lru(int pages[], int n, int capacity) {
    int frames[capacity];
    int faults = 0;
    int recent[capacity];

    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;
        recent[i] = 0;
    }

    printf("\nLRU Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        int found = 0, replaceIdx = -1, leastUsed = INT_MAX;

        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                recent[j] = i;  // Update recent use
                break;
            }
        }

        if (!found) {
            for (int j = 0; j < capacity; j++) {
                if (frames[j] == -1) {
                    replaceIdx = j;
                    break;
                } else if (recent[j] < leastUsed) {
                    leastUsed = recent[j];
                    replaceIdx = j;
                }
            }
            frames[replaceIdx] = pages[i];
            recent[replaceIdx] = i;
            faults++;
        }

        printf("Page %d -> ", pages[i]);
        for (int j = 0; j < capacity; j++) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }
    printf("Total Page Faults (LRU): %d\n", faults);
}

void lfu(int pages[], int n, int capacity) {
    int frames[capacity], count[capacity];
    int faults = 0;

    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;
        count[i] = 0;
    }

    printf("\nLFU Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        int found = 0, replaceIdx = -1, minCount = INT_MAX;

        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                count[j]++;
                break;
            }
        }

        if (!found) {
            for (int j = 0; j < capacity; j++) {
                if (frames[j] == -1) {
                    replaceIdx = j;
                    break;
                } else if (count[j] < minCount) {
                    minCount = count[j];
                    replaceIdx = j;
                }
            }

            frames[replaceIdx] = pages[i];
            count[replaceIdx] = 1;
            faults++;
        }

        printf("Page %d -> ", pages[i]);
        for (int j = 0; j < capacity; j++) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }
    printf("Total Page Faults (LFU): %d\n", faults);
}

int main() {
    int n, capacity;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the pages:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the capacity of the frames: ");
    scanf("%d", &capacity);

    fifo(pages, n, capacity);
    lru(pages, n, capacity);
    lfu(pages, n, capacity);

    return 0;
}
