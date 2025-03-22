#include <stdio.h>

// Structure to store process details
struct Process {
    int id, bt, rt, at, wt, tat;
};

// Function to get the index of the process with the longest remaining time
int getLongestRemaining(int time, struct Process p[], int n) {
    int maxRt = -1, index = -1;
    for (int i = 0; i < n; i++) {
        if (p[i].at <= time && p[i].rt > 0 && p[i].rt > maxRt) {
            maxRt = p[i].rt;
            index = i;
        }
    }
    return index;
}

// Function to implement LRTF scheduling
void LRTF(struct Process p[], int n) {
    int completed = 0, time = 0;
    int totalWT = 0, totalTAT = 0;

    // Process execution loop
    while (completed < n) {
        int idx = getLongestRemaining(time, p, n);

        if (idx == -1) { // No process available, CPU idle
            time++;
            continue;
        }

        p[idx].rt--; // Execute the process for 1 time unit

        if (p[idx].rt == 0) { // Process completion check
            completed++;
            int endTime = time + 1;
            p[idx].tat = endTime - p[idx].at;  // Turnaround Time = Completion Time - Arrival Time
            p[idx].wt = p[idx].tat - p[idx].bt; // Waiting Time = Turnaround Time - Burst Time
            totalWT += p[idx].wt;
            totalTAT += p[idx].tat;
        }

        time++; // Move to next time unit
    }

    // Display results
    printf("\nProcess\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].wt, p[i].tat);
    }

    // Display average times
    printf("\nAverage Waiting Time: %.2f", (float)totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)totalTAT / n);
}

int main() {
    int n;

    // Taking input
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter arrival time and burst time for process P%d: ", p[i].id);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt; // Remaining time initialized as burst time
    }

    // Execute LRTF scheduling
    LRTF(p, n);

    return 0;
}

