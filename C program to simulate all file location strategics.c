#include <stdio.h>
#include <stdlib.h>

// Sequential Allocation
void sequentialAllocation(int fileSize, int startBlock, int totalBlocks) {
    if (startBlock + fileSize > totalBlocks) {
        printf("Sequential allocation failed: Not enough contiguous blocks.\n");
        return;
    }
    printf("Sequential allocation successful: Blocks allocated: ");
    for (int i = startBlock; i < startBlock + fileSize; i++) {
        printf("%d ", i);
    }
    printf("\n");
}

// Indexed Allocation
void indexedAllocation(int fileSize, int indexBlock, int totalBlocks, int dataBlocks[]) {
    if (indexBlock >= totalBlocks) {
        printf("Indexed allocation failed: Invalid index block.\n");
        return;
    }
    if (fileSize > totalBlocks - 1) {
        printf("Indexed allocation failed: Not enough data blocks.\n");
        return;
    }
    printf("Indexed allocation successful: Index block: %d, Data blocks: ", indexBlock);
    for (int i = 0; i < fileSize; i++) {
        printf("%d ", dataBlocks[i]);
    }
    printf("\n");
}

// Linked Allocation
void linkedAllocation(int fileSize, int startBlock, int totalBlocks, int nextBlocks[]) {
    if (startBlock >= totalBlocks) {
        printf("Linked allocation failed: Invalid start block.\n");
        return;
    }
    if (fileSize > totalBlocks) {
        printf("Linked allocation failed: Not enough blocks.\n");
        return;
    }
    printf("Linked allocation successful: Blocks allocated: ");
    int currentBlock = startBlock;
    printf("%d ", currentBlock);
    for (int i = 0; i < fileSize - 1; i++) {
        if (nextBlocks[currentBlock] == -1) {
            printf("\nLinked allocation failed: Not enough blocks in the chain.\n");
            return;
        }
        currentBlock = nextBlocks[currentBlock];
        printf("%d ", currentBlock);
    }
    printf("\n");
}

int main() {
    int totalBlocks = 100;
    int fileSize, startBlock, indexBlock;

    printf("Enter file size: ");
    scanf("%d", &fileSize);

    printf("\n--- Sequential Allocation ---\n");
    printf("Enter starting block for sequential allocation: ");
    scanf("%d", &startBlock);
    sequentialAllocation(fileSize, startBlock, totalBlocks);

    printf("\n--- Indexed Allocation ---\n");
    int dataBlocks[fileSize];
    printf("Enter index block: ");
    scanf("%d", &indexBlock);
    printf("Enter %d data blocks: ", fileSize);
    for (int i = 0; i < fileSize; i++) {
        scanf("%d", &dataBlocks[i]);
    }
    indexedAllocation(fileSize, indexBlock, totalBlocks, dataBlocks);

    printf("\n--- Linked Allocation ---\n");
    int nextBlocks[totalBlocks];
    for (int i = 0; i < totalBlocks; i++) {
        nextBlocks[i] = -1;
    }
    printf("Enter start block for linked allocation: ");
    scanf("%d", &startBlock);
    printf("Enter %d block links (next block for each, use -1 for end):\n", fileSize - 1);
    int prev = startBlock;
    for (int i = 0; i < fileSize - 1; i++) {
        int next;
        scanf("%d", &next);
        if (next == -1 || next >= totalBlocks) {
            printf("Invalid block input. Allocation failed.\n");
            return 0;
        }
        nextBlocks[prev] = next;
        prev = next;
    }
    linkedAllocation(fileSize, startBlock, totalBlocks, nextBlocks);

    return 0;
}


/*Enter file size: 4

--- Sequential Allocation ---
Enter starting block for sequential allocation: 10
Sequential allocation successful: Blocks allocated: 10 11 12 13

--- Indexed Allocation ---
Enter index block: 5
Enter 4 data blocks: 20 30 40 50
Indexed allocation successful: Index block: 5, Data blocks: 20 30 40 50

--- Linked Allocation ---
Enter start block for linked allocation: 15
Enter 3 block links (next block for each, use -1 for end):
25 35 45
Linked allocation successful: Blocks allocated: 15 25 35 45

