#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_BLOCKS 100 // Define maximum blocks for simulation

// Structure to represent a block
struct Block {
    int block_no;
    int flag; // Flag to indicate if block is free (0) or allocated (1)
};

int main() {
    struct Block blocks[MAX_BLOCKS]; // Array to represent memory blocks
    int num_files, file_length[20], start_block, count, success;
    int allocated[20][20]; // Stores allocated blocks for each file

    // Initialize memory blocks
    for (int i = 0; i < MAX_BLOCKS; i++) {
        blocks[i].block_no = i;
        blocks[i].flag = 0; // All blocks are initially free
    }

    // Seed for random number generator
    srand(time(0));

    printf("Enter the number of files: ");
    scanf("%d", &num_files);

    // Get the memory requirement for each file
    for (int i = 0; i < num_files; i++) {
        printf("Enter the memory requirement (number of blocks) for file %d: ", i + 1);
        scanf("%d", &file_length[i]);
    }

    // Allocate memory for each file
    for (int i = 0; i < num_files; i++) {
        success = 0; // To check if allocation was successful
        while (!success) {
            start_block = rand() % (MAX_BLOCKS - file_length[i]); // Random start block
            count = 0;

            // Check if required blocks are free
            for (int j = start_block; j < start_block + file_length[i]; j++) {
                if (blocks[j].flag == 0) {
                    count++;
                }
            }

            // If all blocks are free, allocate them
            if (count == file_length[i]) {
                for (int j = start_block; j < start_block + file_length[i]; j++) {
                    blocks[j].flag = 1; // Mark block as allocated
                    allocated[i][j - start_block] = j; // Store allocated block for the file
                }
                success = 1;
            }
        }
    }

    // Display allocation details
    printf("\nFile No\tFile Length\tBlocks Allocated\n");
    for (int i = 0; i < num_files; i++) {
        printf("%d\t%d\t\t", i + 1, file_length[i]);
        for (int j = 0; j < file_length[i]; j++) {
            printf("%d ", allocated[i][j]);
        }
        printf("\n");
    }

    return 0;
}
