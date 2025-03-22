#include <stdio.h>

int main()
{
    int n, m;

    // Taking input for blocks and processes
    printf("Enter number of Blocks & Processes: ");
    scanf("%d %d", &n, &m);

    int bs[n], ps[m], orig_bs[n];

    // Input Block Sizes
    printf("Enter Block Sizes: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &bs[i]);
        orig_bs[i] = bs[i]; // Store original block sizes
    }

    // Input Process Sizes
    printf("Enter Process Sizes: ");
    for (int i = 0; i < m; i++)
        scanf("%d", &ps[i]);

    // Loop through 3 allocation algorithms: Worst Fit, Best Fit, First Fit
    for (int algo = 0; algo < 3; algo++)
    {
        int alloc[m];

        // Initialize allocation array (-1 means "Not Allocated")
        for (int i = 0; i < m; i++)
            alloc[i] = -1;

        // Memory allocation based on the algorithm type
        for (int i = 0; i < m; i++)
        {
            int best_block = -1;
            int best_size = (algo == 0) ? 99999 : -1; // Worst Fit should have large initial value

            for (int j = 0; j < n; j++)
            {
                if (bs[j] >= ps[i])
                {
                    if (algo == 0 && bs[j] > best_size) // Worst Fit (Largest Block)
                    {
                        best_size = bs[j];
                        best_block = j;
                    }
                    else if (algo == 1 && bs[j] < best_size) // Best Fit (Smallest Possible Block)
                    {
                        best_size = bs[j];
                        best_block = j;
                    }
                    else if (algo == 2 && best_block == -1) // First Fit (First Suitable Block)
                    {
                        best_block = j;
                        break;
                    }
                }
            }

            // Allocate process if a suitable block was found
            if (best_block != -1)
            {
                alloc[i] = best_block;
                bs[best_block] -= ps[i]; // Reduce block size
            }
        }

        // Display Results
        printf("\n%s Fit Allocation:\n", (algo == 0) ? "Worst" : (algo == 1) ? "Best" : "First");
        for (int i = 0; i < m; i++)
        {
            printf("P%d -> ", i + 1);
            if (alloc[i] != -1)
                printf("B%d\n", alloc[i] + 1);
            else
                printf("Not Allocated\n");
        }

        // Restore original block sizes for next algorithm run
        for (int i = 0; i < n; i++)
            bs[i] = orig_bs[i];
    }

    return 0;
}



//Enter number of Blocks & Processes: 5 4
//Enter Block Sizes: 100 500 200 300 600
//Enter Process Sizes: 212 417 112 426





