#include <stdio.h>

// Structure to represent a process
struct Process {
    int pid;        // Process ID
    int burstTime;  // Burst Time
    int priority;   // Priority
};

// Function to sort processes based on priority
void sortProcessesByPriority(struct Process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].priority > proc[j + 1].priority) {
                // Swap the processes
                struct Process temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }
}

// Function to calculate waiting time for each process
void calculateWaitingTime(struct Process proc[], int n, int waitTime[]) {
    waitTime[0] = 0; // First process has no waiting time

    for (int i = 1; i < n; i++) {
        waitTime[i] = proc[i - 1].burstTime + waitTime[i - 1];
    }
}

// Function to calculate turnaround time for each process
void calculateTurnaroundTime(struct Process proc[], int n, int waitTime[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = proc[i].burstTime + waitTime[i];
    }
}

// Function to display the scheduling results
void displayResults(struct Process proc[], int n, int waitTime[], int tat[]) {
    int totalWaitTime = 0, totalTat = 0;

    printf("\nProcess\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        totalWaitTime += waitTime[i];
        totalTat += tat[i];
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].burstTime, proc[i].priority, waitTime[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f", (float)totalWaitTime / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)totalTat / n);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];
    int waitTime[n], tat[n];

    // Input processes data
    for (int i = 0; i < n; i++) {
        printf("Enter burst time and priority for process P%d: ", i + 1);
        scanf("%d %d", &proc[i].burstTime, &proc[i].priority);
        proc[i].pid = i + 1;  // Process ID
    }

    // Sort processes by priority
    sortProcessesByPriority(proc, n);

    // Calculate waiting time
    calculateWaitingTime(proc, n, waitTime);

    // Calculate turnaround time
    calculateTurnaroundTime(proc, n, waitTime, tat);

    // Display results
    displayResults(proc, n, waitTime, tat);

    return 0;
}
