#include <stdio.h>
#include <stdlib.h>

void fcfs(int requests[], int n, int head) {
    int seek_count = 0;
    int distance, cur_track;

    printf("\nFCFS Disk Scheduling:\n");
    printf("Seek Sequence: ");
    for (int i = 0; i < n; i++) {
        cur_track = requests[i];
        distance = abs(cur_track - head);
        seek_count += distance;
        head = cur_track;
        printf("%d ", cur_track);
    }
    printf("\nTotal Seek Operations (FCFS): %d\n", seek_count);
}

void scan(int requests[], int n, int head, int disk_size, int direction) {
    int seek_count = 0;
    int distance, cur_track;
    int left[100], right[100], left_size = 0, right_size = 0;

    // Separate requests to left and right of head
    for (int i = 0; i < n; i++) {
        if (requests[i] < head)
            left[left_size++] = requests[i];
        else
            right[right_size++] = requests[i];
    }

    // Sort left and right arrays
    for (int i = 0; i < left_size - 1; i++) {
        for (int j = 0; j < left_size - i - 1; j++) {
            if (left[j] > left[j + 1]) {
                int temp = left[j];
                left[j] = left[j + 1];
                left[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < right_size - 1; i++) {
        for (int j = 0; j < right_size - i - 1; j++) {
            if (right[j] > right[j + 1]) {
                int temp = right[j];
                right[j] = right[j + 1];
                right[j + 1] = temp;
            }
        }
    }

    printf("\nSCAN Disk Scheduling:\n");
    printf("Seek Sequence: ");

    // Move toward the direction and then reverse
    if (direction == 1) { // Right
        for (int i = 0; i < right_size; i++) {
            cur_track = right[i];
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
            printf("%d ", cur_track);
        }
        // Reach end and reverse
        seek_count += abs(disk_size - 1 - head);
        head = disk_size - 1;

        for (int i = left_size - 1; i >= 0; i--) {
            cur_track = left[i];
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
            printf("%d ", cur_track);
        }
    } else { // Left
        for (int i = left_size - 1; i >= 0; i--) {
            cur_track = left[i];
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
            printf("%d ", cur_track);
        }
        // Reach start and reverse
        seek_count += abs(head - 0);
        head = 0;

        for (int i = 0; i < right_size; i++) {
            cur_track = right[i];
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
            printf("%d ", cur_track);
        }
    }

    printf("\nTotal Seek Operations (SCAN): %d\n", seek_count);
}

void cscan(int requests[], int n, int head, int disk_size) {
    int seek_count = 0;
    int distance, cur_track;
    int left[100], right[100], left_size = 0, right_size = 0;

    // Separate requests to left and right of head
    for (int i = 0; i < n; i++) {
        if (requests[i] < head)
            left[left_size++] = requests[i];
        else
            right[right_size++] = requests[i];
    }

    // Sort left and right arrays
    for (int i = 0; i < left_size - 1; i++) {
        for (int j = 0; j < left_size - i - 1; j++) {
            if (left[j] > left[j + 1]) {
                int temp = left[j];
                left[j] = left[j + 1];
                left[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < right_size - 1; i++) {
        for (int j = 0; j < right_size - i - 1; j++) {
            if (right[j] > right[j + 1]) {
                int temp = right[j];
                right[j] = right[j + 1];
                right[j + 1] = temp;
            }
        }
    }

    printf("\nC-SCAN Disk Scheduling:\n");
    printf("Seek Sequence: ");

    // Move to right, reach end, jump to beginning, then move right again
    for (int i = 0; i < right_size; i++) {
        cur_track = right[i];
        distance = abs(cur_track - head);
        seek_count += distance;
        head = cur_track;
        printf("%d ", cur_track);
    }

    // Go to end of disk
    seek_count += abs(disk_size - 1 - head);
    head = 0;

    for (int i = 0; i < left_size; i++) {
        cur_track = left[i];
        distance = abs(cur_track - head);
        seek_count += distance;
        head = cur_track;
        printf("%d ", cur_track);
    }

    printf("\nTotal Seek Operations (C-SCAN): %d\n", seek_count);
}

int main() {
    int n, head, disk_size, direction;

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &disk_size);

    printf("Enter direction for SCAN (1 for high, 0 for low): ");
    scanf("%d", &direction);

    fcfs(requests, n, head);
    scan(requests, n, head, disk_size, direction);
    cscan(requests, n, head, disk_size);

    return 0;
}
