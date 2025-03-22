#include <stdio.h>
#include <stdlib.h>

struct Process
{
    int id, bt, wt, tat;
};

// Function to sort processes by Burst Time (SJF - Non-Preemptive)
void sortProcesses(struct Process p[], int n)
{
    struct Process temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[i].bt > p[j].bt) // Fixed: Sorting in ascending order
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

// Function to calculate Waiting Time and Turnaround Time
void calculateTimes(struct Process p[], int n)
{
    p[0].wt = 0; // First process has no waiting time

    for (int i = 1; i < n; i++)
    {
        p[i].wt = p[i - 1].wt + p[i - 1].bt;
    }

    for (int i = 0; i < n; i++)
    {
        p[i].tat = p[i].wt + p[i].bt;
    }
}

// Function to display the process table
void displayTable(struct Process p[], int n)
{
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t\t%d\t\t%d\n", p[i].id, p[i].bt, p[i].wt, p[i].tat);
    }
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process *p = (struct Process *)malloc(n * sizeof(struct Process)); // Fixed: Dynamic Memory Allocation

    for (int i = 0; i < n; i++)
    {
        p[i].id = i + 1;
        printf("Enter burst time for process P%d: ", p[i].id);
        scanf("%d", &p[i].bt);
    }

    sortProcesses(p, n);   // Sort processes by burst time (SJF)
    calculateTimes(p, n);  // Calculate waiting and turnaround times
    displayTable(p, n);    // Display result table

    free(p); // Free dynamically allocated memory
    return 0;
}
