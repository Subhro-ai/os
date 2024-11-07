#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_BLOCKS 100 // Define the maximum number of blocks
#define MAX_FILES 20   // Define the maximum number of files

// Structure to represent a memory block
struct Block {
    int block_no;
    int flag; // 0 = free, 1 = allocated
};

// Function to generate a random free block
int getRandomFreeBlock(struct Block blocks[], int total_blocks) {
    int index;
    while (1) {
        index = rand() % total_blocks;
        if (blocks[index].flag == 0) {
            return index;
        }
    }
}

int main() {
    struct Block blocks[MAX_BLOCKS];
    int num_files, file_length[MAX_FILES];
    int allocated[MAX_FILES][MAX_BLOCKS]; // Stores allocated blocks for each file

    // Initialize memory blocks
    for (int i = 0; i < MAX_BLOCKS; i++) {
        blocks[i].block_no = i;
        blocks[i].flag = 0; // All blocks are initially free
    }

    // Seed the random number generator
    srand(time(0));

    printf("Enter the number of files: ");
    scanf("%d", &num_files);

    // Get the memory requirement for each file
    for (int i = 0; i < num_files; i++) {
        printf("Enter the memory requirement (number of blocks) for file %d: ", i + 1);
        scanf("%d", &file_length[i]);
    }

    // Allocate blocks using the chained method
    for (int i = 0; i < num_files; i++) {
        printf("\nAllocating blocks for file %d:\n", i + 1);

        for (int j = 0; j < file_length[i]; j++) {
            int block_index = getRandomFreeBlock(blocks, MAX_BLOCKS);

            // Mark block as allocated
            blocks[block_index].flag = 1;
            allocated[i][j] = block_index; // Store allocated block for file

            printf("Block %d allocated.\n", block_index);
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
